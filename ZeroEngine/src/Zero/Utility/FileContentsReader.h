#pragma once
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
//#include <Zero.h>

std::string GetFileContents(const std::string filePath)
{
	std::stringstream stream;
	std::ifstream source(filePath,std::ifstream::in);
	std::string tempString;
	
	std::cout << std::endl;
	if (source.is_open())
	{
		
		while (std::getline(source, tempString))
		{
			stream << tempString << "\n";
		}

		return stream.str();
	}
	ZERO_CORE_ASSERT(false, "Cant open file!");

	return "";
}