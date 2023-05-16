#pragma once

#include "main.h"

bool directory_exists(std::string folderPath);
bool CreateFile(std::string path, std::string default_content);
std::vector<std::regex> load_lock_rules();
std::unordered_map<std::string, std::string> load_config();
bool set_config(std::unordered_map<std::string,	std::string> config);