/******************************************************************
    @name		AtmosFEAR 2 Library
    @author 	Rexhunter99
    @date		12th June 2019
    @version	2
*/
#ifndef LIBAF2_TEXTURE_H
#define LIBAF2_TEXTURE_H

#include <cstdint>
#include <string>
#include <vector>


namespace libAF2 {

/***************************************************************************
	@var enableExceptions
	@namespace libAF2
	Setting this to true will allow FileLoader static methods to throw C++
	exceptions
	@todo: Implement exceptions
*/
extern bool enableExceptions;

class Texture
{
public:

	Texture();
	Texture( const Texture& texture );
	~Texture();

	Texture& operator= (const Texture& texture);


	const uint32_t getVersion() const { return this->m_version; }

	/***************************************************************************
		@fn getPixels()
		@return vector<uint32_t> A vector of uint32_t elements in 32-bit color mode.
		Returns a copy of the internal pixel data.
	*/
	std::vector<uint32_t> getPixels( );

	/***************************************************************************
		@fn getPixelsInternal()
		@return vector<uint32_t>& A reference to a vector of uint32_t elements in 32-bit color mode.
		This is an 'unsafe' method as it returns the pointer that is used internally
		inside the class, any changes made to the pointer's memory are reflected in the
		class.
	*/
	std::vector<uint32_t>& getPixelsInternal( );

	/***************************************************************************
		@fn getWidth()
		@return uint32_t The width of the texture in pixels
	*/
	uint32_t getWidth() const;

	/***************************************************************************
		@fn getHeight()
		@return uint32_t The height of the texture in pixels
	*/
	uint32_t getHeight() const;

	/***************************************************************************
		@fn setPixels( width, height, pixels, format )
		@param width The width in pixels of the texture
		@param height The height of the texture in pixels
		@param pixels A vector of 'pixel' structures.
		Copies the values data in <pixels> with the structure of <format> to the internal
		floating point structure of the class.
	*/
	void setPixels( const uint32_t& width, const uint32_t& height, std::vector<uint32_t>& pixels  );
	void setPixels( const uint32_t& width, const uint32_t& height, std::vector<uint16_t>& pixels  );


private:

	const uint32_t			m_version = 2;
	uint32_t				m_width,
							m_height;
	std::vector<uint32_t>	m_pixels;
};


}; //namespace libAF2


#endif // LIBAF2_TEXTURE_H
