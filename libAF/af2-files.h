/******************************************************************
    @name		AtmosFEAR 2 Library
    @author 	Rexhunter99
    @date		7th March 2017
    @version	1
*/

#pragma once

#ifndef LIBAF2_FILES_H
#define LIBAF2_FILES_H

#include <string>
#include <cstdint>

/**************************************************************/

// AtmosFEAR 2 Character & Object
#include <af2-mesh.h>
#include <af2-texture.h>
#include <af2-animation.h>
#include <af2-sound.h>

/*
// AtmosFEAR 1 Area (Carnivores 1)
#include <af1-map.h>
#include <af1-resources.h>
// AtmosFEAR 2 Area (Carnivores 2)
#include <af2-map.h>
#include <af2-resources.h>
*/

/*
// AtmosFEAR 2 Text Formats
#include <af2-restxt.h>
*/

#include <af2-loader.h>

/**************************************************************/


namespace libAF2 {

/***************************************************************************
	@var enableExceptions
	@namespace libAF2
	Setting this to true will allow FileLoader static methods to throw C++
	exceptions
	@todo: Implement exceptions
*/
extern bool enableExceptions;

};


#endif // LIB3DF_H
