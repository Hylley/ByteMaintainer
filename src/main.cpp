#include "main.h"


int main(int argc, char *argv[])
{
	if(argc	< 2)
		throw_error("Command not specified");

	SetConsoleOutputCP(65001);

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
		
		if(!CreateFile(".byter\\.lock", "# You're not welcome here.\n.git"))
			throw_error("Failed to create .lock file");
		if(!CreateFile(".byter\\.config", "[last_shot, 0]"))
			throw_error("Failed to create .config file");

		return 0;
	}

	if(instruction == "shot")
	{
		if(!directory_exists(".byter"))
			throw_error("Repository does not exists");
		
		if(argc	< 3)
			throw_error("Shot needs a summary");
		
		std::string sumary = "";
		for(unsigned int i = 2; i < argc; i++)
		{
			sumary += argv[i];
			sumary += " ";
		}

		std::unordered_map<std::string,	std::string> config = load_config();
		std::vector<std::regex> lock = load_lock_rules();
		
		std::string current_version = std::to_string(stoi(config["last_shot"]) + 1);
		std::string path_to_copy = ".byter\\versions\\" + current_version + "\\";
		
		if(!CreateDirectory(path_to_copy.c_str(), NULL))
			throw_error("Failed to create shot directory");
		
		shot("./", path_to_copy, lock);

		if(!CreateFile(path_to_copy + "sumary.txt", sumary))
			throw_error("Failed to create sumary file");

		config["last_shot"] = current_version;
		set_config(config);

		return 0;
	}

	if(instruction == "undo")
	{

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