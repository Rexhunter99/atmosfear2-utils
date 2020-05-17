
#include "af2-loader.h"

#include <fstream>
#include <exception>
#include <stdexcept>

using namespace libAF2;


bool libAF2::enableExceptions = false;


bool FileLoader::loadCharacterFile( const std::string& file_name, Character& character )
{
	std::fstream file;

	file.open(file_name, std::ios::in | std::ios::binary);

	if ( !file.is_open() )
	{
		if ( enableExceptions )
		{
			// throw an exception
		}

		return false;
	}

	// Local scope structure for object header.
	struct file_character_s {
		char		name[32];
		uint32_t	num_anims;
		uint32_t	num_sounds;
		uint32_t	num_vertices;
		uint32_t	num_triangles;
		uint32_t	texture_length;
		std::vector<uint16_t>	texture_data;
		uint32_t	anim_sfx[16];
	} obj;

	// Header block
	file.read( obj.name, 32 );
	character.mesh.setName(obj.name);
	file.read( (char*)&obj.num_anims, sizeof(uint32_t) );
	file.read( (char*)&obj.num_sounds, sizeof(uint32_t) );
	file.read( (char*)&obj.num_vertices, sizeof(uint32_t) );
	file.read( (char*)&obj.num_triangles, sizeof(uint32_t) );
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
		file.read( (char*)tri.reserved, sizeof(uint32_t) * 3 );

		// Convert Texture co-ordinates from unsigned int to float
		for ( unsigned n=0; n < 3; n++ )
		{
			tri.uv[0][n] = (float)t_uv[0][n] / 256.0f;
			tri.uv[1][n] = (float)t_uv[1][n] / 256.0f;
		}

		character.mesh.addTriangle(tri);
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

		character.mesh.addVertex(vert);
	}

	// Bone block
	// TODO: Approximate based on vertices
/*	for ( unsigned i = 0; i < obj.num_bones; i++ )
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
*/

	// Texture block (please forgive me!)
	int t_height = (obj.texture_length / 2) / 256;
	obj.texture_data.reserve(256 * t_height);
	file.read( (char*)obj.texture_data.data(), obj.texture_length );
	character.texture.setPixels( 256, t_height, obj.texture_data );

	// Animation block
	for ( unsigned i = 0; i < obj.num_anims; i++ )
	{
		Animation	anim;
		char		name[32];
		uint32_t	kps = 0;
		uint32_t	num_frames = 0;

		//uint32_t	pos = file.tellg();

		file.read( name, 32 );
		file.read( (char*)&kps, sizeof(uint32_t) );
		file.read( (char*)&num_frames, sizeof(uint32_t) );

		for ( unsigned n = 0; n < num_frames; n++ )
		{
			Animation::Frame frame;

			for ( unsigned v = 0; v < obj.num_vertices; v++ )
			{
				std::array<float, 3>	pos;
				int16_t					pos16[3];

				file.read( (char*)pos16, sizeof(int16_t)*3 );

				pos[0] = (float)pos16[0];
				pos[1] = (float)pos16[1];
				pos[2] = (float)pos16[2];

				frame.vertex_table.push_back(pos);
			}

			anim.addFrame(frame);
		}

		anim.setName(name);
		anim.setKPS(kps);

		character.animations.push_back(anim);
	}

	// Sound block
	for ( unsigned i = 0; i < obj.num_sounds; i++ )
	{
		Sound	snd;
		char		name[32];
		uint32_t	length = 0;
		std::vector<int16_t>	snd_data;

		file.read( name, 32 );
		file.read( (char*)&length, sizeof(uint32_t) );

		snd_data.reserve(length/sizeof(int16_t));
		file.read( (char*)snd_data.data(), length );

		snd.setName(name);
		snd.setWaveData( 16, 1, length, 22050, snd_data );

		character.sounds.push_back(snd);
	}

	// Animation-SoundEffect Table
	file.read( (char*)&obj.anim_sfx, sizeof(uint32_t) * 16 );
	for ( unsigned i = 0; i < 16; i++ )
	{
		character.anim_sound_table.push_back( obj.anim_sfx[i] );
	}

	file.close();
	return true;
}

bool FileLoader::loadObjectFile( const std::string& file_name, Object& object )
{
	std::ifstream file;

	file.open(file_name, std::ios::binary);

	if ( !file.is_open() )
	{
		if ( enableExceptions )
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
		std::vector<uint16_t>	texture_data;
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
		file.read( (char*)tri.reserved, sizeof(uint32_t) * 3 );

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
	int t_height = (obj.texture_length / 2) / 256;
	obj.texture_data.reserve(256 * t_height);
	file.read( (char*)obj.texture_data.data(), obj.texture_length );
	object.texture.setPixels( 256, t_height, obj.texture_data );

	file.close();

	return true;
}
