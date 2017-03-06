

#include "af2-files.h"

#include <string>
#include <cstdint>
#include <iostream>


int main( int argc, char* argv[] )
{
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

	return 0; // Success
}
