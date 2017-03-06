
#include "af2-animation.h"

#include <exception>
#include <stdexcept>

using namespace libAF2;


Animation::Animation()
{
	this->m_name	= "";
	this->m_kps		= 1;
}

Animation:::Animation( const Animation& animation )
{
	this->m_name	= animation.m_name;
	this->m_kps		= animation.m_kps;
	this->m_frames	= animation.m_frames;
}

Animation::~Animation()
{
	this->m_frames.clear();
}

Animation& Animation::operator= (const Animation& animation)
{
	this->m_name	= animation.m_name;
	this->m_kps		= animation.m_kps;
	this->m_frames	= animation.m_frames;
	return (*this);
}


std::string Animation::getName() const
{
	return this->m_name;
}

void Animation::setName( const std::string& name )
{
	this->m_name = name;
}

uint32_t Animation::getKPS() const
{
	return this->m_kps;
}

void Animation::setKPS(const uint32_t& kps)
{
	if ( kps == 0 )
	{
		throw std::invalid_argument("Animation::setKPS( kps ), the argument \'kps\' cannot be set to 0!");
	}

	this->m_kps = kps;
}

double Animation::getTime() const
{
	if ( this->m_kps == 0 )
	{
		throw std::invalid_argument("Animation::getTime(), the member \'kps\' is 0!");
	}

	if ( this->m_frames.size() == 0 )
	{
		return 0;
	}

	return (double)this->m_frames.size() / (double)this->m_kps;
}

std::vector<Frame> Animation::getFrames() const
{
	return this->m_frames;
}

size_t Animation::getFrameCount() const
{
	return this->m_frames.size();
}

Frame Animation::getFrame(size_t frame)
{
	if ( this->m_frames.size() == 0 )
	{
		throw std::out_of_range("Animation::m_frames in ::getFrame(), there are no frames!");
	}
	if ( this->m_frames.size() <= frame )
	{
		throw std::out_of_range("Animation::m_frames in ::getFrame(), the index refers to a frame beyond the max range!");
	}

	return this->m_frames[frame];
}

void Animation::addFrame(const Frame& frame)
{
	this->m_frames.push_back(frame);
}
