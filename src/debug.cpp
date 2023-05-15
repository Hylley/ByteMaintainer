#include "debug.h"

void throw_error(std::string error_message)
{
	std::cout << "Error: " << error_message << std::endl;

	exit(1);
}