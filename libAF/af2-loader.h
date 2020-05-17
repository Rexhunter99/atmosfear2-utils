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

/***************************************************************************
	@var enableExceptions
	@namespace libAF2
	Setting this to true will allow FileLoader static methods to throw C++
	exceptions
	@todo: Implement exceptions
*/
extern bool enableExceptions;

// TODO: move Character to it's own header
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

// TODO: Move Object to it's own header
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

	/***************************************************************************
		@fn loadCharacterFile( file_name, character )
		@param file_name A string containing the file name and path to load from
		@param character A reference of an instance of the Character class to load into
		@return bool <true> if the file successfully loaded without isse, <false> if otherwise
	*/
    static bool loadCharacterFile( const std::string& file_name, Character& character );

    /***************************************************************************
		@fn loadObjectFile( file_name, object )
		@param file_name A string containing the file name and path to load from
		@param object A reference of an instance of the Object class to load into
		@return bool <true> if the file successfully loaded without isse, <false> if otherwise
	*/
    static bool loadObjectFile( const std::string& file_name, Object& object );

    /***************************************************************************
		@fn saveCharacterFile( file_name, character )
		@param file_name A string containing the file name and path to save to
		@param character A reference of an instance of the Character class to save from
		@return bool <true> if the file successfully saved without isse, <false> if otherwise
		@todo: implement
	*/
    static bool saveCharacterFile( const std::string& file_name, const Character& character );

    /***************************************************************************
		@fn saveObjectFile( file_name, object )
		@param file_name A string containing the file name and path to save to
		@param object A reference of an instance of the Object class to save from
		@return bool <true> if the file successfully saved without isse, <false> if otherwise
		@todo: implement
	*/
    static bool saveObjectFile( const std::string& file_name, const Object& object );

	/***************************************************************************
		@fn loadObjectFile( file_name, object )
		@param file_name A string containing the file name and path to load from
		@param object A reference of an instance of the Object class to load into
		@return bool <true> if the file successfully loaded without isse, <false> if otherwise

		@todo: Better name...?
		@todo: implement
    */
    static bool saveVertexTransformedList( const std::string& file_name, const Animation& animation );
};


}; //namespace libAF2

#endif //LIBAF2_LOADER_H
