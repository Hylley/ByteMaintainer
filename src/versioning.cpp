#include "versioning.h"

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
			// If this is a folder
			if(fileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				std::string folderName = fileData.cFileName;
				if(folderName == "." || folderName == ".." || folderName == ".byter")
					continue;

				std::string subfolder_origin = origin_path + folderName + "\\";
				std::string subfolder_destination = destination_path + folderName + "\\";

				// std::cout << "Folder: " << folderName << std::endl;
				// std::cout << "Origin: " << subfolder_origin << std::endl;
				// std::cout << "Destin: " << subfolder_destination << std::endl;

				if(!CreateDirectory(subfolder_destination.c_str(), NULL))
					throw_error("Failed creating destination subfolder \"" + subfolder_destination + "\"");

				shot(subfolder_origin, subfolder_destination);
			}
			// If not a folder, it's a file
			else
			{
				std::string origin_full_path = origin_path + "\\" + fileData.cFileName;
				std::string destination_full_path = destination_path + "\\" + fileData.cFileName;

				CopyFile(origin_full_path.c_str(), destination_full_path.c_str(), FALSE);
			}
		} while (FindNextFile(hFind, &fileData) != 0);

		FindClose(hFind);
	}
}