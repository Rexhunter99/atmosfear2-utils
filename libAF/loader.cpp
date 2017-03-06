
#include "af2-loader.h"

#include <fstream>
#include <exception>
#include <stdexcept>

using namespace libAF2;


bool FileLoader::enableExceptions = false;


bool FileLoader::loadCharacterFile( const std::string& file_name, Character& character )
{
	std::fstream file;

	file.open(file_name, std::ios::in | std::ios::binary);

	if ( !file.is_open() )
	{
		if ( FileLoader::enableExceptions )
		{
			// throw an exception
		}

		return false;
	}

	file.close();

	return true;
}

bool FileLoader::loadObjectFile( const std::string& file_name, Object& object )
{
	std::fstream file;

	file.open(file_name, std::ios::in | std::ios::binary);

	if ( !file.is_open() )
	{
		if ( FileLoader::enableExceptions )
		{
			// throw an exception
		}

		return false;
	}

	// Local scope structure for object header.
	struct file_object_s {
		uint32_t	num_vertices;
		uint32_t	num_triangles;
		uint32_t	num_bones;
		uint32_t	texture_length;
		int16_t*	texture_data;
	} obj;

	// Header block
	file.read( (char*)&obj.num_vertices, sizeof(uint32_t) );
	file.read( (char*)&obj.num_triangles, sizeof(uint32_t) );
	file.read( (char*)&obj.num_bones, sizeof(uint32_t) );
	file.read( (char*)&obj.texture_length, sizeof(uint32_t) );

	// Triangle/Face block
	for ( unsigned i = 0; i < obj.num_triangles; i++ )
	{
		uint32_t		t_uv[2][3];
		Mesh::Triangle	tri;

		file.read( (char*)tri.i, sizeof(uint32_t) * 3 );
		file.read( (char*)t_uv, sizeof(uint32_t) * 6 );
		file.read( (char*)&tri.flags, sizeof(uint16_t) );
		file.read( (char*)&tri.dmask, sizeof(uint16_t) );
		file.read( (char*)&tri.prev, sizeof(uint32_t) );
		file.read( (char*)&tri.next, sizeof(uint32_t) );
		file.read( (char*)&tri.group, sizeof(uint32_t) );
		file.read( (char*)tri.reserved, sizeof(uint32_t) * 4 );

		// Convert Texture co-ordinates from unsigned int to float
		for ( unsigned n=0; n < 3; n++ )
		{
			tri.uv[0][n] = (float)t_uv[0][n] / 256.0f;
			tri.uv[1][n] = (float)t_uv[1][n] / 256.0f;
		}

		object.mesh.addTriangle(tri);
	}

	// Vertex/Point block
	for ( unsigned i = 0; i < obj.num_vertices; i++ )
	{
		Mesh::Vertex	vert;

		file.read( (char*)&vert.x, sizeof(float) );
		file.read( (char*)&vert.y, sizeof(float) );
		file.read( (char*)&vert.z, sizeof(float) );
		file.read( (char*)&vert.bone, sizeof(uint16_t) );
		file.read( (char*)&vert.visible, sizeof(uint16_t) );

		object.mesh.addVertex(vert);
	}

	// Bone block
	for ( unsigned i = 0; i < obj.num_bones; i++ )
	{
		Mesh::Bone	bone;
		char		name[32];

		file.read( name, 32 );
		file.read( (char*)&bone.x, sizeof(float) );
		file.read( (char*)&bone.y, sizeof(float) );
		file.read( (char*)&bone.z, sizeof(float) );
		file.read( (char*)&bone.parent, sizeof(uint16_t) );
		file.read( (char*)&bone.visible, sizeof(uint16_t) );

		bone.name = name;

		object.mesh.addBone(bone);
	}

	// Texture block (please forgive me!)
	obj.texture_data = new int16_t [ obj.texture_length / 2 ];
	file.read( (char*)obj.texture_data, obj.texture_length );
	float* texture_data = new float [ ( 256 * 4 ) * 256 ];

	for ( unsigned i = 0; i < 256 * 256; i++ )
	{
		uint16_t c = obj.texture_data[i];
		texture_data[ (i * 4) + 0 ] = ( (c>>0 ) & 31 ) / 31.0f;
		texture_data[ (i * 4) + 1 ] = ( (c>>5 ) & 31 ) / 31.0f;
		texture_data[ (i * 4) + 2 ] = ( (c>>10) & 31 ) / 31.0f;
		texture_data[ (i * 4) + 3 ] = ( !c ) ? 0.0f : 1.0f;
	}

	object.texture.setPixels( 256, 256, texture_data );

	delete [] texture_data;
	texture_data = nullptr;
	delete [] obj.texture_data;
	obj.texture_data = nullptr;

	file.close();

	return true;
}
