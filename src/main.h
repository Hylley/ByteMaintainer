#pragma once

#include <stdio.h>
#include <string>
#include <windows.h>
#include <fstream>
#include <unordered_map>
#include <regex>

#include "debug.h"
#include "files.h"
#include "versioning.h"

bool folder_exists(std::string folderPath);
std::string trim(const std::string& str);