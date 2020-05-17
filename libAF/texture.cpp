
#include "af2-texture.h"

#include <cmath>
#include <exception>
#include <stdexcept>
#include <cstring>

using namespace libAF2;

const int16_t format_pixel_size[] = {
	4,
	4,
	4,
	4,
	3,
	3,
	2,
	2,
	2,

	1	// Last
};


Texture::Texture() :
	m_width(0),
	m_height(0)
{
}

Texture::Texture( const Texture& other ) :
	m_width	(other.m_width),
	m_height(other.m_height)
{
	m_pixels.insert(m_pixels.end(), other.m_pixels.begin(), other.m_pixels.end());
}

Texture::~Texture()
{
	m_pixels.clear();
}

Texture& Texture::operator=(const Texture& rhs)
{
	if (this == &rhs) return (*this);

	m_width = rhs.m_width;
	m_height = rhs.m_height;

	m_pixels.clear();
	m_pixels.insert(m_pixels.end(), rhs.m_pixels.begin(), rhs.m_pixels.end());

	return (*this);
}


std::vector<uint32_t>& Texture::getPixelsInternal( )
{
	return m_pixels;
}

std::vector<uint32_t> Texture::getPixels( )
{
	return m_pixels;
}

uint32_t Texture::getWidth() const
{
	return m_width;
}

uint32_t Texture::getHeight() const
{
	return m_height;
}


void Texture::setPixels( const uint32_t& width, const uint32_t& height, std::vector<uint32_t>& pixels )
{
	if (!width || width >= 16384)
		throw std::invalid_argument("Invalid argument: `width`");
	if (!height || height >= 16384)
		throw std::invalid_argument("Invalid argument: `height`");
	if (pixels.empty() || pixels.size() < width*height)
		throw std::invalid_argument("Invalid argument: `pixels`");

	m_width = width;
	m_height = height;

	m_pixels.clear();
	m_pixels.insert(m_pixels.end(), pixels.begin(), pixels.begin() + (width*height));
}

void Texture::setPixels( const uint32_t& width, const uint32_t& height, std::vector<uint16_t>& pixels )
{
	if (!width || width >= 16384)
		throw std::invalid_argument("Invalid argument: `width`");
	if (!height || height >= 16384)
		throw std::invalid_argument("Invalid argument: `height`");
	if (pixels.empty() || pixels.size() < width*height)
		throw std::invalid_argument("Invalid argument: `pixels`");

	m_pixels.clear();

	for (auto pix: pixels)
	{
		uint32_t c = 0;
		uint8_t* pc = (uint8_t*)&c;
		*(pc + 0) = ( (pix>>0 ) & 31 ) * 8; //0-248
		*(pc + 1) = ( (pix>>5 ) & 31 ) * 8;
		*(pc + 2) = ( (pix>>10) & 31 ) * 8;
		*(pc + 3) = ( (pix & 0x7FFF) == 0 ) ? 0 : 255;
		m_pixels.push_back(c);
	}

	m_width = width;
	m_height = height;
}
