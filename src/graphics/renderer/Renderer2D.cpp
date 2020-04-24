//
// Created by masy on 23.02.20.
//

#include "cedar/Renderer2D.hpp"
#include "cedar/Cedar.hpp"
#include "glad/glad.h"
#include <cmath>
#include <regex>

using namespace cedar;

ShaderProgram *Renderer2D::shader = nullptr;
int *Renderer2D::uniformLocations = nullptr;
Matrix4f *Renderer2D::projectionMatrix = nullptr;
Texture2D *Renderer2D::defaultTexture = nullptr;

Quad *Renderer2D::batch = nullptr;
Quad *Renderer2D::nextQuad = nullptr;
unsigned int Renderer2D::quadCount = 0;
unsigned int Renderer2D::batchSize = 0;
unsigned int Renderer2D::textureUnitCount = 0;
int *Renderer2D::textureUnits = nullptr;
unsigned int *Renderer2D::textures = nullptr;
unsigned int Renderer2D::textureCount = 0;

unsigned int Renderer2D::vaoId = 0;
unsigned int Renderer2D::quadVboId = 0;
unsigned int Renderer2D::instanceVboId = 0;


Renderer2D::Renderer2D()
= default;

void Renderer2D::cleanup()
{
	delete[] batch;
	delete[] textures;
	delete[] textureUnits;
	delete defaultTexture;
	delete shader;
	delete[] uniformLocations;
	// don't delete projection matrix as it is handled by the master renderer
	glDeleteBuffers(2, &quadVboId);
	glDeleteVertexArrays(1, &vaoId);
}

void Renderer2D::initShader(const int maxTextureUnits)
{

	std::string guiVertexShader = R"glsl(
#version 450

layout (location = 0) in vec2 v_unitQuad;
layout (location = 1) in vec4 v_positionOffset;
layout (location = 2) in float v_zIndex;
layout (location = 3) in int v_textureUnit;
layout (location = 4) in vec4 v_uvOffset;
layout (location = 5) in vec4 v_tint;

flat out int f_textureUnit;
out vec2 f_uvs;
out vec4 f_tint;

uniform mat4 u_projectionMatrix;

void main()
{
	vec2 movedPosition = mix(v_positionOffset.xy, v_positionOffset.zw, v_unitQuad);
	gl_Position = u_projectionMatrix * vec4(movedPosition, v_zIndex, 1.0);
	f_textureUnit = v_textureUnit;
	f_uvs = mix(v_uvOffset.xy, v_uvOffset.zw, v_unitQuad);
	f_tint = v_tint;
}

)glsl";

	std::string guiFragmentShaderTemplate = R"glsl(
#version 450

layout (location = 0) out vec4 diffuseColor;

flat in int f_textureUnit;
in vec2 f_uvs;
in vec4 f_tint;

uniform sampler2D[${MAX_TEXTURE_UNITS}] u_samplers;

void main()
{
	diffuseColor = texture(u_samplers[f_textureUnit], f_uvs) * f_tint;
}

)glsl";

	// Replace the sampler array size with the actual maximum number of texture units the graphics card supports
	std::regex pattern(R"(\$\{MAX_TEXTURE_UNITS\})");
	std::string guiFragmentShader = std::regex_replace(guiFragmentShaderTemplate, pattern, std::to_string(maxTextureUnits));

	shader = new cedar::ShaderProgram();
	shader->createVertexShader(guiVertexShader);
	shader->createFragmentShader(guiFragmentShader);
	shader->link();

	const char *guiUniformNames[] = {"u_projectionMatrix", "u_samplers"};
	uniformLocations = new int[2];
	shader->createUniforms(2, guiUniformNames, uniformLocations);
}

void Renderer2D::init(const unsigned int _batchSize, Matrix4f *_projectionMatrix)
{
	projectionMatrix = _projectionMatrix;
	int maxTextures;
	glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &maxTextures);
	initShader(maxTextures);

	batch = new Quad[_batchSize];
	nextQuad = batch;
	batchSize = _batchSize;

	textureUnitCount = static_cast<unsigned int>(maxTextures);
	textures = new unsigned int[textureUnitCount];
	textureUnits = new int[textureUnitCount];
	for (unsigned int n = 0; n < textureUnitCount; n++)
		textureUnits[n] = static_cast<int>(n);

	defaultTexture = new Texture2D(1, 1);
	unsigned char pixel[] = {255, 255, 255, 255};
	defaultTexture->init(CEDAR_RGBA, CEDAR_UNSIGNED_BYTE, pixel);
	textures[0] = defaultTexture->getId();

	glGenVertexArrays(1, &vaoId);
	glBindVertexArray(vaoId);

	glGenBuffers(2, &quadVboId);

	glBindBuffer(GL_ARRAY_BUFFER, quadVboId);
	float data[8] = {0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f};
	glVertexAttribPointer(0, 2, GL_FLOAT, false, sizeof(float) * 2, nullptr);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 8, data, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, instanceVboId);

	glVertexAttribPointer(1, 4, GL_FLOAT, false, sizeof(Quad), (void *) (offsetof(Quad, m_corners)));
	glVertexAttribDivisor(1, 1);
	glVertexAttribPointer(2, 1, GL_FLOAT, false, sizeof(Quad), (void *) (offsetof(Quad, m_zIndex)));
	glVertexAttribDivisor(2, 1);
	glVertexAttribIPointer(3, 1, GL_INT, sizeof(Quad), (const void *) (offsetof(Quad, m_textureUnit)));
	glVertexAttribDivisor(3, 1);
	glVertexAttribPointer(4, 4, GL_FLOAT, false, sizeof(Quad), (void *) (offsetof(Quad, m_uvs)));
	glVertexAttribDivisor(4, 1);
	glVertexAttribPointer(5, 4, GL_FLOAT, false, sizeof(Quad), (void *) (offsetof(Quad, m_tint)));
	glVertexAttribDivisor(5, 1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Quad) * _batchSize, nullptr, GL_DYNAMIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Renderer2D::beginBatch()
{
	nextQuad = batch;
	quadCount = 0;
	textureCount = 1;
	for (unsigned int n = 1; n < textureUnitCount; n++)
		textures[n] = 0;
}

void Renderer2D::endBatch()
{
	glBindBuffer(GL_ARRAY_BUFFER, instanceVboId);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Quad) * quadCount, batch);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Renderer2D::flush()
{
	for (unsigned int n = 0; n < textureCount; n++)
		glBindTextureUnit(n, textures[n]);

	shader->bind();
	shader->setUniform4x4f(uniformLocations[0], *projectionMatrix);
	shader->setUniform1iv(uniformLocations[1], textureCount, textureUnits);

	glBindVertexArray(vaoId);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);
	glEnableVertexAttribArray(4);
	glEnableVertexAttribArray(5);
	glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, quadCount);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(3);
	glDisableVertexAttribArray(4);
	glDisableVertexAttribArray(5);
	glBindVertexArray(0);

	shader->unbind();
}

void Renderer2D::drawRect(const float posX, const float posY, const float posZ, const float width, const float height, const Vector4f *color)
{
	if (quadCount == batchSize)
	{
		endBatch();
		flush();
		beginBatch();
	}

	nextQuad->set(posX, posY, posX + width, posY + height, -posZ, 0,
				  0.0f, 0.0f, 1.0f, 1.0f, color->x, color->y, color->z, color->w);

	nextQuad++;
	quadCount++;
}

void Renderer2D::drawTexturedRect(float posX, float posY, float posZ, float width, float height, const Vector4f &uvs,
								  const std::shared_ptr<Texture> &texture, const Vector4f &color)
{
	drawTexturedRect(posX, posY, posZ, width, height, uvs.x, uvs.y, uvs.z, uvs.w, texture, color);
}

void Renderer2D::drawTexturedRect(float posX, float posY, float posZ, float width, float height, float uvX1, float uvY1, float uvX2, float uvY2,
								  const std::shared_ptr<Texture> &texture, const Vector4f &color)
{
	if (quadCount == batchSize)
	{
		endBatch();
		flush();
		beginBatch();
	}

	int textureUnit = 0;
	for (unsigned int n = 0; n < textureUnitCount; n++)
	{
		if (textures[n] == texture->getId())
		{
			textureUnit = static_cast<int>(n);
			break;
		}
		else if (textures[n] == 0)
		{
			textures[n] = texture->getId();
			textureUnit = static_cast<int>(n);
			textureCount++;
			break;
		}
	}

	if (textureUnit == 0)
	{
		endBatch();
		flush();
		beginBatch();
		textureUnit = 1.0f;
		textures[1] = texture->getId();
	}

	nextQuad->set(posX, posY, posX + width, posY + height, -posZ, textureUnit,
				  uvX1, uvY1, uvX2, uvY2, color.x, color.y, color.z, color.w);

	nextQuad++;
	quadCount++;
}

void Renderer2D::drawText(const float posX, const float posY, const float posZ, const std::string &text, const std::shared_ptr<Font> &font,
						  const Vector4f &color,
						  const unsigned int alignment, Vector2f *size)
{
	if (quadCount + text.length() > batchSize)
	{
		endBatch();
		flush();
		beginBatch();
	}

	int textureUnit = 0;
	for (unsigned int n = 0; n < textureUnitCount; n++)
	{
		if (textures[n] == font->getGlyphAtlas()->getId())
		{
			textureUnit = static_cast<int>(n);
			break;
		}
		else if (textures[n] == 0)
		{
			textures[n] = font->getGlyphAtlas()->getId();
			textureUnit = static_cast<int>(n);
			textureCount++;
			break;
		}
	}

	if (textureUnit == 0)
	{
		endBatch();
		flush();
		beginBatch();
		textureUnit = 1.0f;
		textures[1] = font->getGlyphAtlas()->getId();
	}

	float width = 0.0f;
	float height = 0.0f;
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

				nextQuad->set(Vector4f(currentPosX, nextPosY, currentPosX + static_cast<float>(glyph->m_size.x), nextPosY + static_cast<float>(glyph->m_size.y)),
							  -posZ, textureUnit, glyph->m_uvs, color);

				nextQuad++;
				quadCount++;

				nextPosX += static_cast<float>(glyph->m_advance);
				width += static_cast<float>(glyph->m_advance);
				height = std::max(height, static_cast<float>(glyph->m_size.y));
			}
		}
	}
	else
	{
		Glyph glyphs[text.length()];
		unsigned int characters = 0;
		for (const uint8_t *s = (uint8_t *) text.c_str(); *s; ++s)
		{
			if (!Font::decode(&state, &codepoint, *s))
			{
				glyphs[characters] = *font->getGlyph(codepoint);
				width += static_cast<float>(glyphs[characters].m_advance);
				height = std::max(height, static_cast<float>(glyphs[characters].m_size.y));
				characters++;
			}
		}

		if (horizontalAlignment == CEDAR_ALIGNMENT_CENTER)
			nextPosX = posX - std::floor(width * 0.5f);
		else
			nextPosX = posX - width;

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

			nextQuad->set(Vector4f(currentPosX, nextPosY, currentPosX + static_cast<float>(glyphs[n].m_size.x), nextPosY + static_cast<float>(glyphs[n].m_size.y)),
						  -posZ, textureUnit, glyphs[n].m_uvs, color);

			nextQuad++;
			quadCount++;

			nextPosX += static_cast<float>(glyphs[n].m_advance);
		}
	}

	if (size)
		*size = Vector2f(width, height);
}

TextBuffer *Renderer2D::generateTextBuffer(const std::string &text, const std::shared_ptr<Font> &font, const unsigned int alignment)
{
	Quad *quads = new Quad[text.length()];

	float width = 0.0f;
	float height = 0.0f;
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
						0.0f, 0, glyph->m_uvs, Vector4f(1.0f, 1.0f, 1.0f, 1.0f));

				nextPosX += static_cast<float>(glyph->m_advance);
				width += static_cast<float>(glyph->m_advance);
				height = std::max(height, static_cast<float>(glyph->m_size.y));
			}
		}
	}
	else
	{
		Glyph glyphs[text.length()];
		unsigned int characters = 0;
		for (const uint8_t *s = (uint8_t *) text.c_str(); *s; ++s)
		{
			if (!Font::decode(&state, &codepoint, *s))
			{
				glyphs[characters] = *font->getGlyph(codepoint);
				width += static_cast<float>(glyphs[characters].m_advance);
				height = std::max(height, static_cast<float>(glyphs[characters].m_size.y));
				characters++;
			}
		}

		if (horizontalAlignment == CEDAR_ALIGNMENT_CENTER)
			nextPosX = -std::floor(width * 0.5f);
		else
			nextPosX = -width;

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
					0.0f, 0, glyphs[n].m_uvs, Vector4f(1.0f, 1.0f, 1.0f, 1.0f)
								   );

			nextPosX += static_cast<float>(glyphs[n].m_advance);
		}
	}

	return new TextBuffer(font->getGlyphAtlas()->getId(), glyphCount, quads, Vector2f(width, height));
}

void Renderer2D::drawText(const float offsetX, const float offsetY, const float offsetZ, const TextBuffer *textBuffer, const Vector4f &color)
{
	if (quadCount + textBuffer->getGlyphCount() > batchSize)
	{
		endBatch();
		flush();
		beginBatch();
	}

	int textureUnit = 0;
	for (unsigned int n = 0; n < textureUnitCount; n++)
	{
		if (textures[n] == textBuffer->getGlyphAtlas())
		{
			textureUnit = static_cast<int>(n);
			break;
		}
		else if (textures[n] == 0)
		{
			textures[n] = textBuffer->getGlyphAtlas();
			textureUnit = static_cast<int>(n);
			textureCount++;
			break;
		}
	}

	if (textureUnit == 0)
	{
		endBatch();
		flush();
		beginBatch();
		textureUnit = 1.0f;
		textures[1] = textBuffer->getGlyphAtlas();
	}

	for (int n = 0; n < textBuffer->getGlyphCount(); n++)
	{
		nextQuad->set(textBuffer->getQuads()[n].m_corners + Vector4f(offsetX, offsetY, offsetX, offsetY),
					  -offsetZ, textureUnit, textBuffer->getQuads()[n].m_uvs, color);

		nextQuad++;
		quadCount++;
	}
}
