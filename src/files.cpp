#include "files.h"

void shot(std::string origin_path, std::string destination_path)
{
	WIN32_FIND_DATA	fileData;
	HANDLE hFind;

	std::string searchPath = origin_path + "\\*.*";
	hFind =	FindFirstFile(searchPath.c_str(), &fileData);

	if (hFind != INVALID_HANDLE_VALUE)
	{
		do
		{
			if ((fileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0)
			{
				std::string origin_full_path = origin_path + "\\" + fileData.cFileName;
				std::string destination_full_path = destination_path + "\\" + fileData.cFileName;

				CopyFile(origin_full_path.c_str(), destination_full_path.c_str(), FALSE);
			}
		} while (FindNextFile(hFind, &fileData) != 0);

		FindClose(hFind);
	}
}


bool directory_exists(std::string folderPath)
{
	DWORD attributes = GetFileAttributesA(folderPath.c_str());
	return attributes != INVALID_FILE_ATTRIBUTES && (attributes	& FILE_ATTRIBUTE_DIRECTORY);
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