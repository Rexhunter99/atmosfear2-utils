
#include "af2-sound.h"

#include <cmath>
#include <exception>
#include <stdexcept>
#include <cstring>

using namespace libAF2;


Sound::Sound()
{
	m_bitdepth	= 0;
	m_channels	= 0;
	m_length	= 0;
	m_frequency	= 0;
}

Sound::Sound( const Sound& other )
{
	m_bitdepth	= other.m_bitdepth;
	m_channels	= other.m_channels;
	m_length	= other.m_length;
	m_frequency	= other.m_frequency;

	m_data = other.m_data;
}

Sound::~Sound()
{
	m_data.clear();
}

Sound& Sound::operator=(const Sound& rhs)
{
	if ((this) == &rhs) return (*this);

	m_bitdepth	= rhs.m_bitdepth;
	m_channels	= rhs.m_channels;
	m_length	= rhs.m_length;
	m_frequency	= rhs.m_frequency;

	m_data.clear();
	m_data = rhs.m_data;

	return (*this);
}


std::string Sound::getName() const
{
	return this->m_name;
}

void Sound::setName( const std::string& name )
{
	this->m_name = name;
}

std::vector<int16_t> Sound::getWaveData()
{
	return m_data;
}

std::vector<int16_t>& Sound::getWaveDataInternal()
{
	return m_data;
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


void Sound::setWaveData( uint16_t bitdepth, uint16_t channels, uint32_t length, uint32_t frequency, std::vector<int16_t>& bits  )
{
	size_t sample_bytes = bitdepth / 8;

	if (sample_bytes == 0 || sample_bytes > 4) {
		if (enableExceptions)
			throw std::invalid_argument("bitdepth is invalid.");
		return;
	}

	if (bitdepth == 0 ||
		channels == 0 ||
		length == 0 ||
		frequency == 0 ||
		bits.empty() ||
		bits.size() < (length/(bitdepth/8)) )
	{
		if (enableExceptions)
			throw std::invalid_argument("An invalid argument was supplied");
		return;
	}

	// TODO: Sound conversion to 16-bit 22050hz Mono
	//size_t sample_count = length / (bitdepth / 8);

	m_bitdepth	= bitdepth;
	m_channels	= channels;
	m_length	= length;
	m_frequency	= frequency;

	m_data.clear();
	m_data.insert(m_data.end(), bits.begin(), bits.end());
	//std::copy(bits.begin(), bits.begin() + sample_count, m_data);
}

