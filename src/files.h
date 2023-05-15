#pragma once

#include "main.h"

bool directory_exists(std::string folderPath);
bool CreateFile(std::string path, std::string default_content);
std::unordered_map<std::string, std::string> load_config();