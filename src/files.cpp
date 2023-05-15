#include "files.h"


bool directory_exists(std::string folderPath)
{
	DWORD attributes = GetFileAttributesA(folderPath.c_str());
	return attributes != INVALID_FILE_ATTRIBUTES && (attributes	& FILE_ATTRIBUTE_DIRECTORY);
}

bool CreateFile(std::string path, std::string default_content)
{
	std::ofstream file(path);
	if (!file.is_open())
		return false;
	file << default_content;
	file.close();

	return true;
}

std::regex config_regex("^(.+)=(.+)$");
std::unordered_map<std::string,	std::string> load_config()
{
	std::ifstream config_file(".byter\\.config");
	if(!config_file.good())
		throw_error("Unable	to open	.config	file");

	std::unordered_map<std::string,	std::string> result;
	std::smatch	matches;
	std::string	line;
	while(getline(config_file, line)){
		if(!std::regex_match(line, matches,	config_regex))
			throw_error("Bad .config file");
		
		result.insert({	 trim(matches[1]), trim(matches[2]) });
	}

	return result;
}