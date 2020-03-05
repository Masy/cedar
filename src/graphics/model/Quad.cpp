//
// Created by masy on 05.03.20.
//

#include "cedar/Quad.h"

using namespace cedar;

Quad::Quad() : Quad(Vector4f(0.0f), Vector2f(0.0f, 0.0f), Vector4f(0.0f), Vector4f(1.0f))
{}

Quad::Quad(const cedar::Vector4f &corners, const Vector2f &layerAndTexture, const cedar::Vector4f &uvs, const cedar::Vector4f &tint)
{
	this->m_corners = corners;
	this->m_layerAndTexture = layerAndTexture;
	this->m_uvs = uvs;
	this->m_tint = tint;
}

void Quad::set(const Vector4f &corners, const Vector2f &layerAndTexture, const Vector4f &uvs, const Vector4f &tint)
{
	this->m_corners = corners;
	this->m_layerAndTexture = layerAndTexture;
	this->m_uvs = uvs;
	this->m_tint = tint;
}

void Quad::set(const float cornerX1, const float cornerY1, const float cornerX2, const float cornerY2, const float layer, const float textureUnit,
			   const float uvX1, const float uvY1, const float uvX2, const float uvY2,
			   const float tintRed, const float tintGreen, const float tintBlue, const float tintAlpha)
{
	this->m_corners = Vector4f(cornerX1, cornerY1, cornerX2, cornerY2);
	this->m_layerAndTexture = Vector2f(layer, textureUnit);
	this->m_uvs = Vector4f(uvX1, uvY1, uvX2, uvY2);
	this->m_tint = Vector4f(tintRed, tintGreen, tintBlue, tintAlpha);
}
