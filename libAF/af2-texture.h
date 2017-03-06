/******************************************************************
    @name	AtmosFEAR 2 Library
    @author Rexhunter99
    @date	6th March 2017
*/
#pragma once

#ifndef LIBAF2_TEXTURE_H
#define LIBAF2_TEXTURE_H

#include <cmath>
#include <cstdint>
#include <string>
#include <vector>


// Allow this header to be included separately from "af-files.h"
#ifndef LIBAF2_NAMESPACE
namespace libAF2 {
#endif // LIBAF2_NAMESPACE


class Texture
{
public:

	Texture();
	Texture( const Texture& texture );
	~Texture();

	Texture& operator= (const Texture& texture);


	const uint32_t	getVersion() const { return this->version; }

	/***************************************************************************
		@fn getPixels()
		@param format Specifies what format the array will have the pixels formatted as.
		@return float* Pointer to an array of bytes in the requested pixel format
		Returns a copy of the internal pixel data that the user must safely free.
		You can use std::unique_ptr to ensure no memory leaks occur.
	*/
	const float*	getPixels( );

	/***************************************************************************
		@fn getPixelsInternal()
		@param format Specifies what format the array will have the pixels formatted as.
		@return float* Pointer to an array of bytes in the requested pixel format
		This is an 'unsafe' method as it returns the pointer that is used internally
		inside the class, any changes made to the pointer's memory are reflected in the
		class.
	*/
	const float*	getPixelsInternal( ) const;

	/***************************************************************************
		@fn getWidth()
		@return uint32_t The width of the texture in pixels
	*/
	uint32_t		getWidth() const;

	/***************************************************************************
		@fn getHeight()
		@return uint32_t The height of the texture in pixels
	*/
	uint32_t		getHeight() const;

	/***************************************************************************
		@fn setPixels( pixels, format )
		@param width The width in pixels of the texture
		@param height The height of the texture in pixels
		@param pixels A pointer to an array of pixels in <format>.
		@param format Specifies what format the array will have the pixels formatted as.
		Copies the values data in <pixels> with the structure of <format> to the internal
		floating point structure of the class.
	*/
	void	setPixels( const uint32_t& width, const uint32_t& height, const float* pixels  );


private:

	class Pixel
	{
	public:
		float	r, g, b, a;

		Pixel();
		Pixel( float red, float green, float blue, float alpha );
		Pixel(const Pixel& pixel);

		Pixel& operator= (const Pixel& pixel);
	};

	const uint32_t	version = 2;
	Pixel*			m_pixels;
	uint32_t		m_width,
					m_height;
};

#ifndef LIBAF2_NAMESPACE
};
#endif // LIBAF2_NAMESPACE


#endif // LIBAF2_TEXTURE_H
