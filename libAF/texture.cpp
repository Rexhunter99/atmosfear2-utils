
#include "af2-texture.h"

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


Texture::Pixel::Pixel( )
{
	r = 0.0f;
	g = 0.0f;
	b = 0.0f;
	a = 0.0f;
}

Texture::Pixel::Pixel( float red, float green, float blue, float alpha )
{
	r = red;
	g = green;
	b = blue;
	a = alpha;
}

Texture::Pixel::Pixel(const Texture::Pixel& pixel)
{
	r = pixel.r;
	g = pixel.g;
	b = pixel.b;
	a = pixel.a;
}

Texture::Pixel& Texture::Pixel::operator= (const Texture::Pixel& pixel)
{
	r = pixel.r;
	g = pixel.g;
	b = pixel.b;
	a = pixel.a;
	return (*this);
}


Texture::Texture()
{
	this->m_width = 0;
	this->m_height = 0;
	this->m_pixels = nullptr;
}

Texture::Texture( const Texture& texture )
{
	this->m_width = texture.m_width;
	this->m_height = texture.m_height;

	this->m_pixels = new Pixel [ this->m_width * this->m_height ];

	std::memcpy(this->m_pixels, texture.m_pixels, ( this->m_width * sizeof(Pixel) ) * this->m_height );
}

Texture::~Texture()
{
	if ( this->m_pixels != nullptr )
	{
		delete [] this->m_pixels;
	}
}

Texture& Texture::operator=(const Texture& texture)
{
	this->m_width = texture.m_width;
	this->m_height = texture.m_height;

	this->m_pixels = new Pixel [ this->m_width* this->m_height ];

	std::memcpy(this->m_pixels, texture.m_pixels, ( this->m_width * sizeof(Pixel) ) * this->m_height );

	return (*this);
}


const float* Texture::getPixelsInternal( ) const
{
	return reinterpret_cast<float*>(this->m_pixels);
}

const float* Texture::getPixels( )
{
	Pixel* pixels = new Pixel [ this->m_width * this->m_height ];
	std::memcpy(this->m_pixels, pixels, ( this->m_width * sizeof(Pixel) ) * this->m_height );

	return reinterpret_cast<float*>(pixels);
}

uint32_t Texture::getWidth() const
{
	return this->m_width;
}

uint32_t Texture::getHeight() const
{
	return this->m_height;
}


void Texture::setPixels( const uint32_t& width, const uint32_t& height, const float* pixels )
{
	if ( width == 0 || height == 0 || pixels == nullptr )
	{
		//TODO: Throw an exception
		return;
	}

	if ( this->m_pixels != nullptr )
	{
		delete [] this->m_pixels;
		this->m_pixels = nullptr;
	}
	// TODO: Check that the dimensions don't exceed "16384"
	this->m_width = width;
	this->m_height = height;
	this->m_pixels = new Pixel [ width * height ];

	std::memcpy(this->m_pixels, pixels, ( this->m_width * sizeof(Pixel) ) * this->m_height );
}

