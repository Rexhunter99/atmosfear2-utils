

#include "af2-files.h"

#include <string>
#include <cstdint>
#include <iostream>


int main( int argc, char* argv[] )
{
	try {
		std::cout << "libAF Testing application.\n" << std::endl;

		libAF2::Object object;

		std::cout << "Loading object file \'" << "tree.3df" << "\'" << std::endl;

		if ( !libAF2::FileLoader::loadObjectFile("tree.3df", object) )
		{
			std::cout << "\tError!\t Failed to load the object file \'" << "tree.3df" << "\'" << std::endl;
		}
		else
		{
			std::cout << "tree.3df {\n";
			std::cout << "\tversion:\t\'" << object.mesh.getVersion() << "\'\n";
			std::cout << "\tname:\t\t\'" << object.mesh.getName() << "\'\n";
			std::cout << "\tv_num:\t\t\'" << object.mesh.getVertexCount() << "\'\n";
			std::cout << "\tt_num:\t\t\'" << object.mesh.getTriangleCount() << "\'\n";
			std::cout << "\tb_num:\t\t\'" << object.mesh.getBoneCount() << "\'\n";
			std::cout << "}" << std::endl;
		}

		////////////////////////////////
		libAF2::Character character;

		std::cout << "Loading character file \'" << "revolver.car" << "\'" << std::endl;

		if ( !libAF2::FileLoader::loadCharacterFile("revolver.car", character) )
		{
			std::cout << "\tError!\t Failed to load the object file \'" << "tree.3df" << "\'" << std::endl;
		}
		else
		{
			std::cout << "revolver.car {\n";
			std::cout << "\tversion:\t\'" << character.mesh.getVersion() << "\'\n";
			std::cout << "\tname:\t\t\'" << character.mesh.getName() << "\'\n";
			std::cout << "\tv_num:\t\t\'" << character.mesh.getVertexCount() << "\'\n";
			std::cout << "\tt_num:\t\t\'" << character.mesh.getTriangleCount() << "\'\n";
			std::cout << "\ta_num:\t\t\'" << character.animations.size() << "\'\n";
			std::cout << "\ts_num:\t\t\'" << character.sounds.size() << "\'\n";

			std::cout << "\t{\n";
			std::cout << "\t\tAnim : Sound\n";
			for ( unsigned i = 0; i < character.anim_sound_table.size(); i++ )
			{
				std::cout << "\t\t" << i << " : " << character.anim_sound_table.at(i) << "\n";
			}
			std::cout << "\t}\n";

			std::cout << "}" << std::endl;
		}
	}
	catch (...)
	{

	}

	return 0; // Success
}
