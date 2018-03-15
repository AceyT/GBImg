#include "CodeExporter.hpp"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstring>

void	debug(const IndexedImage& img)
{
		printf("width = [0x%02X]\nheight = [0x%02X]\n", img.width, img.height);
		printf("Frames = [0x%02X%02X]\nFrame Loop = [0x%02X]\n", img.framesUpperBits, img.framesLowerBits, img.frameLoop);
		printf("Transparent color = [0x%02X]\nColor mode = [", img.transparentColor);
		if (img.colorMode == (uint8_t)ColorMode::RGB_565)
			printf("RGB 565]\n");
		else
			printf("INDEXED]\n");
		printf("Image data pointer = [0x%08X]\n", img.imgData);
		if (img.imgData != nullptr)
		{
			for (uint8_t y = 0 ; y < img.height ; ++y)
			{
				std::cout << "0x" << std::flush;
				for (uint8_t x = 0 ; x < (img.width+1)/2 ; ++x)
				{
					uint16_t	offset = (y * ((img.width+1)/2)) + x;
					printf("[%02X]", img.imgData[offset]);
				}
				printf("\n");
			}
		}
}

void	exportTo(const IndexedImage& img, const std::string& path, const std::string& name)
{
	std::ofstream	oFile(path);


	oFile << "const uint8_t " << name << "Data[] = {" << std::endl;
	oFile << +img.width << ',' << +img.height << ',' << std::endl
		<< +img.framesLowerBits << ',' << +img.framesUpperBits << ',' << +img.frameLoop << ',' << std::endl
		<< "0x" << std::setfill('0') << std::setw(2) << std::uppercase << std::hex << +img.transparentColor << ','
		<< std::endl << std::nouppercase << std::dec << +img.colorMode << ',' <<  std::endl << std::endl;
	oFile << std::uppercase << std::hex;
	for (uint8_t y = 0 ; y < img.height ; ++y)
	{
		for (uint8_t x = 0 ; x < (img.width+1)/2 ; ++x)
		{
			uint16_t	offset = (y * ((img.width+1)/2)) + x;
			oFile << "0x" << std::setw(2) << std::setfill('0') << +img.imgData[offset] << std::flush;
			if (! (!(((y+1) < img.height)) && (!((x+1) < ((img.width+1)/2)))) )
				oFile << ',';
		}
		oFile << std::endl;
	}
	oFile << "};" << std::endl
		<< "Image " << name << " = Image(" << name << "Data);" << std::endl;
}

void	spritesheetTo(const IndexedImage& img, const std::string& path, const std::string& name, uint32_t rx, uint32_t ry)
{
	std::ofstream	oFile(path);


	oFile << "const uint8_t " << name << "Data[] = {" << std::endl;
	oFile << +img.width << ',' << +img.height << ',' << std::endl
		<< +img.framesLowerBits << ',' << +img.framesUpperBits << ',' << +img.frameLoop << ',' << std::endl
		<< "0x" << std::setfill('0') << std::setw(2) << std::uppercase << std::hex << +img.transparentColor << ','
		<< std::endl << std::nouppercase << std::dec << +img.colorMode << ',' <<  std::endl << std::endl;
	oFile << std::uppercase << std::hex;
	for (uint8_t y = 0 ; y < ry ; ++y)
	{
		for (uint8_t x = 0 ; x < (rx+1)/2 ; ++x)
		{
			uint16_t	offset = (y * ((rx+1)/2)) + x;
			oFile << "0x" << std::setw(2) << std::setfill('0') << +img.imgData[offset] << std::flush;
			if (! (!(((y+1) < ry)) && (!((x+1) < ((rx+1)/2)))) )
				oFile << ',';
		}
		oFile << std::endl;
	}
	oFile << "};" << std::endl
		<< "Image " << name << " = Image(" << name << "Data);" << std::endl;
}
