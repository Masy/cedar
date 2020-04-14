//
// Created by masy on 14.04.20.
//

#include "cedar/Image.hpp"
#include "cedar/Renderer2D.hpp"

using namespace cedar;

Image::Image(const float originX, const float originY, const unsigned char zIndex, const float width, const float height,
			 const std::shared_ptr<Texture> &texture, const cedar::Vector4f &uvSection, const unsigned int alignment)
		: Element(originX, originY, zIndex, width, height, alignment)
{
	if (!dynamic_cast<Texture2D *>(texture.get()))
		throw ElementCreationException("Could not create image element. The provided texture is not a two dimensional texture!");

	this->m_texture = texture;
	this->m_uvSection = uvSection;
}

void Image::render(const unsigned long currentTime)
{
	Renderer2D::drawTexturedRect(this->m_posX, this->m_posY, this->m_zIndex, this->m_width, this->m_height,
								 this->m_uvSection.x, this->m_uvSection.y, this->m_uvSection.z, this->m_uvSection.w,
								 dynamic_cast<Texture2D *>(this->m_texture.get()));
}
