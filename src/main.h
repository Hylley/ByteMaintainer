#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <string>
#include <windows.h>
#include <fstream>
#include <unordered_map>
#include <regex>

#include "debug.h"
#include "files.h"

bool folder_exists(std::string folderPath);
std::string trim(const std::string& str);

#endif