/******************************************************************
    @name	AtmosFEAR 2 Library - Loader
    @author Rexhunter99
    @date	7th March 2017
*/

#pragma once

#ifndef LIBAF2_LOADER_H
#define LIBAF2_LOADER_H

#include <af2-mesh.h>
#include <af2-texture.h>
#include <af2-animation.h>
#include <af2-sound.h>


namespace libAF2 {

class Character
{
public:
	const uint32_t			version = 2;

	Mesh					mesh;
	Texture					texture;
	std::vector<Animation>	animations;
	std::vector<Sound>		sounds;
    std::vector<uint32_t>	anim_sound_table;
};

class Object
{
public:
	const uint32_t			version = 2;

	Mesh					mesh;
	Texture					texture;
};


class FileLoader
{
public:

	FileLoader();
	virtual ~FileLoader();

    static bool loadCharacterFile( const std::string& file_name, Character& character );
    static bool loadObjectFile( const std::string& file_name, Object& object );

    static bool enableExceptions;
};


}; //namespace libAF2

#endif //LIBAF2_LOADER_H
