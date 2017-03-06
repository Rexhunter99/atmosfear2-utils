
/******************************************************************
    @name		AtmosFEAR 2 Library - Animation
    @author 	Rexhunter99
    @date		6th March 2017
    @version	2
*/
#pragma once

#ifndef LIBAF2_TEXTURE_H
#define LIBAF2_TEXTURE_H

#include <cstdint>
#include <string>
#include <vector>


// Allow this header to be included separately from "af-files.h"
#ifndef LIBAF2_NAMESPACE
namespace libAF2 {
#endif // LIBAF2_NAMESPACE


class Animation
{
public:

	class Frame
	{
	public:
		std::vector<std::array<float, 3>>	vertex_table;
	};


	Animation();
	Animation( const Animation& animation );
	~Animation();

	Animation& operator= (const Animation& animation);

	cosnt uint32_t	getVersion() const {return this->version;}

	std::string		getName() const;
	void			setName( const std::string& name );

	/****************************************************************
		@fn getTime()
		@return double The length of the animation in seconds
	*/
	double			getTime() const;

	/****************************************************************
		@fn getKPS()
		@return uint32_t The KeysPerSecond of the animation
	*/
	uint32_t		getKPS() const;
	void			setKPS(const uint32_t& kps);

	/****************************************************************
		Deal with the key frames
	*/
	std::vector<Frame>	getFrames() const;
	size_t				getFrameCount() const;
	Frame				getFrame(size_t frame);
	void				addFrame(const Frame& frame);

private:

	const uint32_t		version = 2;
	std::string			m_name;
	std::vector<Frame>	m_frames;
	uint32_t			m_kps; // need a better name for this
};

#ifndef LIBAF2_NAMESPACE
};
#endif // LIBAF2_NAMESPACE

#endif // LIBAF2_ANIMATION_H
