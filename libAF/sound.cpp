
#include "af2-sound.h"

#include <cmath>
#include <exception>
#include <stdexcept>
#include <cstring>

using namespace libAF2;


Sound::Sound()
{
	this->m_bitdepth	= 0;
	this->m_channels	= 0;
	this->m_length		= 0;
	this->m_frequency	= 0;
	this->m_data = nullptr;
}

Sound::Sound( const Sound& sound )
{
	this->m_bitdepth	= sound.m_bitdepth;
	this->m_channels	= sound.m_channels;
	this->m_length		= sound.m_length;
	this->m_frequency	= sound.m_frequency;

	this->m_data = new int8_t [ this->m_length ];

	std::memcpy(this->m_data, sound.m_data, this->m_length );
}

Sound::~Sound()
{
	if ( this->m_data != nullptr )
	{
		delete [] this->m_data;
	}
}

Sound& Sound::operator=(const Sound& sound)
{
	this->m_bitdepth	= sound.m_bitdepth;
	this->m_channels	= sound.m_channels;
	this->m_length		= sound.m_length;
	this->m_frequency	= sound.m_frequency;

	this->m_data = new int8_t [ this->m_length ];

	std::memcpy(this->m_data, sound.m_data, this->m_length );

	return (*this);
}


const int8_t* Sound::getWaveDataCopy( )
{
	return reinterpret_cast<int8_t*>(this->m_data);
}

const int8_t* Sound::getWaveData( ) const
{
	int8_t* data = new int8_t [ this->m_length ];
	std::memcpy(this->m_data, data, this->m_length );

	return reinterpret_cast<int8_t*>(data);
}

uint16_t Sound::getBitDepth() const
{
	return this->m_bitdepth;
}

uint16_t Sound::getChannels() const
{
	return this->m_channels;
}

uint32_t Sound::getLength() const
{
	return this->m_length;
}

uint32_t Sound::getFrequency() const
{
	return this->m_frequency;
}


void Sound::setWaveData( uint16_t bitdepth, uint16_t channels, uint32_t length, uint32_t frequency, const int8_t* bits  )
{
	if ( bitdepth == 0 || channels == 0 || length == 0 || frequency == 0 || bits == nullptr )
	{
		//TODO: Throw an exception
		return;
	}

	if ( this->m_data != nullptr )
	{
		delete [] this->m_data;
		this->m_data = nullptr;
	}

	// TODO: Check that the dimensions don't exceed "16384"
	this->m_bitdepth	= bitdepth;
	this->m_channels	= channels;
	this->m_length		= length;
	this->m_frequency	= frequency;
	this->m_data = new int8_t [ length ];

	std::memcpy( this->m_data, bits, length );
}

