//
// Created by masy on 23.02.20.
//

#include "cedar/GuiRenderer.h"
#include "cedar/Cedar.h"
#include "glad/glad.h"
#include <cmath>

using namespace cedar;

GuiRenderer::GuiRenderer()
{
	this->m_shader = nullptr;
	this->m_uniformLocations = nullptr;
	this->m_projectionMatrix = nullptr;
	this->m_batch = nullptr;
	this->m_nextQuad = nullptr;
	this->m_quadCount = 0;
	this->m_batchSize = 0;
	this->m_textureUnitCount = 0;
	this->m_textures = nullptr;
	this->m_textureCount = 1;
	this->m_vaoId = 0;
	this->m_quadVboId = 0;
	this->m_instanceVboId = 0;
}

GuiRenderer::~GuiRenderer()
{
	delete[] this->m_batch;
	delete[] this->m_textures;
	delete[] this->m_textureUnits;
	delete this->m_defaultTexture;
	delete this->m_shader;
	delete[] this->m_uniformLocations;
	// don't delete projection matrix as it is handled by the master renderer
	glDeleteBuffers(2, &this->m_quadVboId);
	glDeleteVertexArrays(1, &this->m_vaoId);
}

void GuiRenderer::initShader()
{

	std::string guiVertexShader = R"glsl(
#version 450

layout (location = 0) in vec2 v_unitQuad;
layout (location = 1) in vec4 v_positionOffset;
layout (location = 2) in vec2 v_layerAndTexture;
layout (location = 3) in vec4 v_uvOffset;
layout (location = 4) in vec4 v_tint;

out vec3 f_uvs;
out vec4 f_tint;

uniform mat4 u_projectionMatrix;

void main()
{
	vec2 movedPosition = mix(v_positionOffset.xy, v_positionOffset.zw, v_unitQuad);
	gl_Position = u_projectionMatrix * vec4(movedPosition, v_layerAndTexture.x, 1.0);
	vec2 movedUvs = mix(v_uvOffset.xy, v_uvOffset.zw, v_unitQuad);
	f_uvs = vec3(movedUvs, v_layerAndTexture.y);
	f_tint = v_tint;
}

)glsl";

	std::string guiFragmentShader = R"glsl(
#version 450

layout (location = 0) out vec4 diffuseColor;

in vec3 f_uvs;
in vec4 f_tint;

uniform sampler2D[32] u_samplers;

void main()
{
	int samplerIndex = int(f_uvs.z);
	diffuseColor = texture(u_samplers[samplerIndex], f_uvs.xy) * f_tint;
}

)glsl";

	this->m_shader = new cedar::ShaderProgram();
	this->m_shader->createVertexShader(guiVertexShader);
	this->m_shader->createFragmentShader(guiFragmentShader);
	this->m_shader->link();

	const char *guiUniformNames[] = {"u_projectionMatrix", "u_samplers"};
	this->m_uniformLocations = new int[2];
	this->m_shader->createUniforms(2, guiUniformNames, this->m_uniformLocations);
}

void GuiRenderer::init(const unsigned int batchSize, Matrix4f *projectionMatrix)
{
	this->m_projectionMatrix = projectionMatrix;
	this->initShader();

	this->m_batch = new Quad[batchSize];
	this->m_nextQuad = this->m_batch;
	this->m_batchSize = batchSize;

	int maxTextures;
	glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &maxTextures);
	this->m_textureUnitCount = static_cast<unsigned int>(maxTextures);
	this->m_textures = new unsigned int[this->m_textureUnitCount];
	this->m_textureUnits = new int[this->m_textureUnitCount];
	for (unsigned int n = 0; n < this->m_textureUnitCount; n++)
		this->m_textureUnits[n] = static_cast<int>(n);

	this->m_defaultTexture = new Texture2D(1, 1);
	unsigned char pixel[] = {255, 255, 255, 255};
	this->m_defaultTexture->init(CEDAR_RGBA, CEDAR_UNSIGNED_BYTE, pixel);
	this->m_textures[0] = this->m_defaultTexture->getId();

	glGenVertexArrays(1, &this->m_vaoId);
	glBindVertexArray(this->m_vaoId);

	glGenBuffers(2, &this->m_quadVboId);

	glBindBuffer(GL_ARRAY_BUFFER, this->m_quadVboId);
	float data[8] = {0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f};
	glVertexAttribPointer(0, 2, GL_FLOAT, false, sizeof(float) * 2, nullptr);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 8, data, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, this->m_instanceVboId);

	glVertexAttribPointer(1, 4, GL_FLOAT, false, sizeof(Quad), (void *) (offsetof(Quad, m_corners)));
	glVertexAttribDivisor(1, 1);
	glVertexAttribPointer(2, 2, GL_FLOAT, false, sizeof(Quad), (void *) (offsetof(Quad, m_layerAndTexture)));
	glVertexAttribDivisor(2, 1);
	glVertexAttribPointer(3, 4, GL_FLOAT, false, sizeof(Quad), (void *) (offsetof(Quad, m_uvs)));
	glVertexAttribDivisor(3, 1);
	glVertexAttribPointer(4, 4, GL_FLOAT, false, sizeof(Quad), (void *) (offsetof(Quad, m_tint)));
	glVertexAttribDivisor(4, 1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Quad) * this->m_batchSize, nullptr, GL_DYNAMIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void GuiRenderer::beginBatch()
{
	this->m_nextQuad = this->m_batch;
	this->m_quadCount = 0;
	this->m_textureCount = 1;
	for (unsigned int n = 1; n < this->m_textureUnitCount; n++)
		this->m_textures[n] = 0;
}

void GuiRenderer::endBatch()
{
	glBindBuffer(GL_ARRAY_BUFFER, this->m_instanceVboId);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Quad) * this->m_quadCount, this->m_batch);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void GuiRenderer::flush()
{
	for (unsigned int n = 0; n < this->m_textureCount; n++)
		glBindTextureUnit(n, this->m_textures[n]);

	this->m_shader->bind();
	this->m_shader->setUniform4x4f(this->m_uniformLocations[0], *this->m_projectionMatrix);
	this->m_shader->setUniform1iv(this->m_uniformLocations[1], this->m_textureCount, this->m_textureUnits);

	glBindVertexArray(this->m_vaoId);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);
	glEnableVertexAttribArray(4);
	glEnableVertexAttribArray(5);
	glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, this->m_quadCount);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(3);
	glDisableVertexAttribArray(4);
	glDisableVertexAttribArray(5);
	glBindVertexArray(0);

	this->m_shader->unbind();
}

void GuiRenderer::drawRect(const float posX, const float posY, const float posZ, const float width, const float height, const Vector4f *color)
{
	if (this->m_quadCount == this->m_batchSize)
	{
		this->endBatch();
		this->flush();
		this->beginBatch();
	}

	this->m_nextQuad->set(posX, posY, posX + width, posY + height, -posZ, 0.0f,
					  0.0f, 0.0f, 1.0f, 1.0f, color->x, color->y, color->z, color->w);

	this->m_nextQuad++;
	this->m_quadCount++;
}

void GuiRenderer::drawTexturedRect(float posX, float posY, float posZ, float width, float height, float uvX1, float uvY1, float uvX2, float uvY2,
								   const Texture2D *texture)
{
	if (this->m_quadCount == this->m_batchSize)
	{
		this->endBatch();
		this->flush();
		this->beginBatch();
	}

	float textureUnit = 0.0f;
	for (unsigned int n = 0; n < this->m_textureUnitCount; n++)
	{
		if (this->m_textures[n] == texture->getId())
		{
			textureUnit = static_cast<float>(n);
			break;
		}
		else if (this->m_textures[n] == 0)
		{
			this->m_textures[n] = texture->getId();
			textureUnit = static_cast<float>(n);
			this->m_textureCount++;
			break;
		}
	}

	if (textureUnit == 0.0f)
	{
		this->endBatch();
		this->flush();
		this->beginBatch();
		textureUnit = 1.0f;
		this->m_textures[1] = texture->getId();
	}

	this->m_nextQuad->set(posX, posY, posX + width, posY + height, -posZ, textureUnit,
						 uvX1, uvY1, uvX2, uvY2, 1.0f, 1.0f, 1.0f, 1.0f);

	this->m_nextQuad++;
	this->m_quadCount++;
}

void GuiRenderer::drawText(const float posX, const float posY, const float posZ, const std::string &text, Font *font, const Vector4f *color,
						   const unsigned int alignment)
{
	if (this->m_quadCount + text.length() > this->m_batchSize)
	{
		this->endBatch();
		this->flush();
		this->beginBatch();
	}

	float textureUnit = 0.0f;
	for (unsigned int n = 0; n < this->m_textureUnitCount; n++)
	{
		if (this->m_textures[n] == font->getGlyphAtlas()->getId())
		{
			textureUnit = static_cast<float>(n);
			break;
		}
		else if (this->m_textures[n] == 0)
		{
			this->m_textures[n] = font->getGlyphAtlas()->getId();
			textureUnit = static_cast<float>(n);
			this->m_textureCount++;
			break;
		}
	}

	if (textureUnit == 0.0f)
	{
		this->endBatch();
		this->flush();
		this->beginBatch();
		textureUnit = 1.0f;
		this->m_textures[1] = font->getGlyphAtlas()->getId();
	}

	float nextPosX = posX;
	float currentPosX;
	float nextPosY;
	unsigned int codepoint;
	unsigned int state = UTF8_ACCEPT;

	unsigned int horizontalAlignment = alignment & 0x03u;
	unsigned int verticalAlignment = alignment & 0x0Cu;
	if (horizontalAlignment == CEDAR_ALIGNMENT_LEFT)
	{
		for (const uint8_t *s = (uint8_t *) text.c_str(); *s; ++s)
		{
			if (!Font::decode(&state, &codepoint, *s))
			{
				const Glyph *glyph = font->getGlyph(codepoint);

				currentPosX = nextPosX + static_cast<float>(glyph->m_bearing.x);

				switch (verticalAlignment)
				{
					case CEDAR_ALIGNMENT_TOP:
						nextPosY = posY - static_cast<float>(glyph->m_bearing.y) + static_cast<float>(font->getSize());
						break;

					case CEDAR_ALIGNMENT_MIDDLE:
						nextPosY = posY - static_cast<float>(glyph->m_bearing.y) + (static_cast<float>(font->getSize()) * 0.5f);
						break;

					default:
						nextPosY = posY - static_cast<float>(glyph->m_bearing.y);
						break;
				}

				this->m_nextQuad->set(
						Vector4f(currentPosX, nextPosY, currentPosX + static_cast<float>(glyph->m_size.x), nextPosY + static_cast<float>(glyph->m_size.y)),
						Vector2f(-posZ, textureUnit), glyph->m_uvs, *color
						);

				this->m_nextQuad++;
				this->m_quadCount++;

				nextPosX += static_cast<float>(glyph->m_advance);
			}
		}
	}
	else
	{
		Glyph glyphs[text.length()];
		unsigned int width = 0;
		unsigned int characters = 0;
		for (const uint8_t *s = (uint8_t *) text.c_str(); *s; ++s)
		{
			if (!Font::decode(&state, &codepoint, *s))
			{
				glyphs[characters] = *font->getGlyph(codepoint);
				width += glyphs[characters].m_advance;
				characters++;
			}
		}

		if (horizontalAlignment == CEDAR_ALIGNMENT_CENTER)
			nextPosX = posX - std::floor(static_cast<float>(width) * 0.5f);
		else
			nextPosX = posX - static_cast<float>(width);

		for (unsigned int n = 0; n < characters; n++)
		{
			currentPosX = nextPosX + static_cast<float>(glyphs[n].m_bearing.x);

			switch (verticalAlignment)
			{
				case CEDAR_ALIGNMENT_TOP:
					nextPosY = posY - static_cast<float>(glyphs[n].m_bearing.y) + static_cast<float>(font->getSize());
					break;

				case CEDAR_ALIGNMENT_MIDDLE:
					nextPosY = posY - static_cast<float>(glyphs[n].m_bearing.y) + (static_cast<float>(font->getSize()) * 0.5f);
					break;

				default:
					nextPosY = posY - static_cast<float>(glyphs[n].m_bearing.y);
					break;
			}

			this->m_nextQuad->set(
					Vector4f(currentPosX, nextPosY, currentPosX + static_cast<float>(glyphs[n].m_size.x), nextPosY + static_cast<float>(glyphs[n].m_size.y)),
					Vector2f(-posZ, textureUnit), glyphs[n].m_uvs, *color
					);

			this->m_nextQuad++;
			this->m_quadCount++;

			nextPosX += static_cast<float>(glyphs[n].m_advance);
		}
	}
}

TextBuffer *GuiRenderer::generateTextBuffer(const std::string &text, Font *font, const Vector4f *color, const unsigned int alignment)
{
	Quad *quads = new Quad[text.length()];

	unsigned int glyphCount = 0;
	float nextPosX = 0.0f;
	float currentPosX;
	float nextPosY;
	unsigned int codepoint;
	unsigned int state = UTF8_ACCEPT;

	unsigned int horizontalAlignment = alignment & 0x03u;
	unsigned int verticalAlignment = alignment & 0x0Cu;
	if (horizontalAlignment == CEDAR_ALIGNMENT_LEFT)
	{
		for (const uint8_t *s = (uint8_t *) text.c_str(); *s; ++s)
		{
			if (!Font::decode(&state, &codepoint, *s))
			{
				const Glyph *glyph = font->getGlyph(codepoint);

				currentPosX = nextPosX + static_cast<float>(glyph->m_bearing.x);

				switch (verticalAlignment)
				{
					case CEDAR_ALIGNMENT_TOP:
						nextPosY = -static_cast<float>(glyph->m_bearing.y) + static_cast<float>(font->getSize());
						break;

					case CEDAR_ALIGNMENT_MIDDLE:
						nextPosY = -static_cast<float>(glyph->m_bearing.y) + (static_cast<float>(font->getSize()) * 0.5f);
						break;

					default:
						nextPosY = -static_cast<float>(glyph->m_bearing.y);
						break;
				}

				quads[glyphCount++].set(
						Vector4f(currentPosX, nextPosY, currentPosX + static_cast<float>(glyph->m_size.x), nextPosY + static_cast<float>(glyph->m_size.y)),
						Vector2f(0.0f, 0.0f), glyph->m_uvs, *color
									   );

				nextPosX += static_cast<float>(glyph->m_advance);
			}
		}
	}
	else
	{
		Glyph glyphs[text.length()];
		unsigned int width = 0;
		unsigned int characters = 0;
		for (const uint8_t *s = (uint8_t *) text.c_str(); *s; ++s)
		{
			if (!Font::decode(&state, &codepoint, *s))
			{
				glyphs[characters] = *font->getGlyph(codepoint);
				width += glyphs[characters].m_advance;
				characters++;
			}
		}

		if (horizontalAlignment == CEDAR_ALIGNMENT_CENTER)
			nextPosX = -std::floor(static_cast<float>(width) * 0.5f);
		else
			nextPosX = -static_cast<float>(width);

		for (unsigned int n = 0; n < characters; n++)
		{
			currentPosX = nextPosX + static_cast<float>(glyphs[n].m_bearing.x);

			switch (verticalAlignment)
			{
				case CEDAR_ALIGNMENT_TOP:
					nextPosY = -static_cast<float>(glyphs[n].m_bearing.y) + static_cast<float>(font->getSize());
					break;

				case CEDAR_ALIGNMENT_MIDDLE:
					nextPosY = -static_cast<float>(glyphs[n].m_bearing.y) + (static_cast<float>(font->getSize()) * 0.5f);
					break;

				default:
					nextPosY = -static_cast<float>(glyphs[n].m_bearing.y);
					break;
			}

			quads[glyphCount++].set(
					Vector4f(currentPosX, nextPosY, currentPosX + static_cast<float>(glyphs[n].m_size.x), nextPosY + static_cast<float>(glyphs[n].m_size.y)),
					Vector2f(0.0f, 0.0f), glyphs[n].m_uvs, *color
			);

			nextPosX += static_cast<float>(glyphs[n].m_advance);
		}
	}

	return new TextBuffer(font->getGlyphAtlas()->getId(), glyphCount, quads);
}

void GuiRenderer::drawText(const float offsetX, const float offsetY, const float offsetZ, const TextBuffer *textBuffer)
{
	if (this->m_quadCount + textBuffer->getGlyphCount() > this->m_batchSize)
	{
		this->endBatch();
		this->flush();
		this->beginBatch();
	}

	float textureUnit = 0.0f;
	for (unsigned int n = 0; n < this->m_textureUnitCount; n++)
	{
		if (this->m_textures[n] == textBuffer->getGlyphAtlas())
		{
			textureUnit = static_cast<float>(n);
			break;
		}
		else if (this->m_textures[n] == 0)
		{
			this->m_textures[n] = textBuffer->getGlyphAtlas();
			textureUnit = static_cast<float>(n);
			this->m_textureCount++;
			break;
		}
	}

	if (textureUnit == 0.0f)
	{
		this->endBatch();
		this->flush();
		this->beginBatch();
		textureUnit = 1.0f;
		this->m_textures[1] = textBuffer->getGlyphAtlas();
	}

	for (int n = 0; n < textBuffer->getGlyphCount(); n++)
	{
		this->m_nextQuad->set(textBuffer->getQuads()[n].m_corners + Vector4f(offsetX, offsetY, offsetX, offsetY),
				Vector2f(-offsetZ, textureUnit), textBuffer->getQuads()[n].m_uvs, textBuffer->getQuads()[n].m_tint);

		this->m_nextQuad++;
		this->m_quadCount++;
	}
}
