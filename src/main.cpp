#include "main.h"


int main(int argc, char *argv[])
{
	if(argc	< 2)
		throw_error("Command not specified");

	std::string	instruction	= argv[1];

	// do
	// {
	//	scanf("%s",	&instruction);
	// } while (instruction	== "");
	
	// if(instruction == "quit")
	//	exit(0)

	if(instruction == "init")
	{
		if(directory_exists(".byter"))
			throw_error("There is already a repo in this folder");

		if(!CreateDirectory(".byter", NULL))
			throw_error("Failed to create main repo folder");
		if(!CreateDirectory(".byter\\versions",	NULL))
			throw_error("Failed to create versions folder");

		std::ofstream lock_file(".byter\\.lock");
		if (!lock_file.is_open())
			throw_error("Failed to create .lock file");
		lock_file << "*.[oad]";
		lock_file.close();

		std::ofstream config_file(".byter\\.config");
		if (!config_file.is_open())
			throw_error("Failed to create .config file");
		config_file	<< "last_shot =	0";
		config_file.close();

		return 0;
	}

	if(instruction == "shot")
	{
		if(!directory_exists(".byter"))
			throw_error("Repository does not exists");
		
		std::unordered_map<std::string,	std::string> config = load_config();
		
		unsigned int last_version = stoi(config["last_shot"]);
		std::string path_to_copy = ".byter\\versions\\" + std::to_string(last_version + 1) + "\\";
		if(!CreateDirectory(path_to_copy.c_str(), NULL))
			throw_error("Failed to create shot directory");
		
		shot("./", path_to_copy);
		return 0;
	}
}

std::string trim(const std::string& str)
{
	const auto begin = str.find_first_not_of(" \t\n\r");

	if (begin == std::string::npos)
		return "";

	const auto end = str.find_last_not_of("	\t\n\r");
	return str.substr(begin, end - begin + 1);
}