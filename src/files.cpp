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

std::vector<std::regex> load_lock_rules()
{
	std::ifstream lock_file(".byter\\.lock");
	if(!lock_file.good())
		throw_error("Unable	to open	.lock file");

	std::vector<std::regex> result;

	std::string	line;
	while(getline(lock_file, line)){
		if(line.rfind('#', 0) != std::string::npos)
			continue;
			
		try
		{
			result.emplace_back(line);
		}
		catch (const std::regex_error& e)
		{
			throw_warn("Invalid lock rule: " + line);
		}
	}

	return result;
}

std::regex config_regex("\\[[ ]*([^ ]*)[ ]*,[ ]*([^ ]*)[ ]*\\]");
std::unordered_map<std::string,	std::string> load_config()
{
	std::ifstream config_file(".byter\\.config");
	if(!config_file.good())
		throw_error("Unable	to open	.config file");

	std::unordered_map<std::string,	std::string> result;
	std::smatch	matches;
	std::string	line;
	while(getline(config_file, line)){
		if(!std::regex_match(line, matches,	config_regex))
			throw_error("Bad .config file");
		
		result.insert({	 matches[1], matches[2] });
	}

	return result;
}

bool set_config(std::unordered_map<std::string,	std::string> config)
{
	std::string result = "";

	for (const auto& pair : config)
	{
		result += '[' + pair.first + ", " + pair.second + "]\n";
	}

	return CreateFile(".byter\\.config", result);
}