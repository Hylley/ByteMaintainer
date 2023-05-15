#ifndef FILES_H
#define FILES_H

#include "main.h"

void shot(std::string origin_path, std::string destination_path);
bool directory_exists(std::string folderPath);
bool CreateFile(std::string path, std::string default_content);
std::unordered_map<std::string, std::string> load_config();

#endif