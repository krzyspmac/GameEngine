#include <iostream>
#include "renderer_entry.h"


int main(int argc, char* argv[])
{
	std::cout << "Hello world" << std::endl;

	engine::RendererEntry entry;
	entry.doMain(argc, argv);

	return 0;
}