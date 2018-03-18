#include <iostream>
#include <string>
#include <stdexcept>
#include <cxxopts.hpp>
#include "Options.hpp"
#include "ImageProgram.hpp"

//TODO	Loading Palette from files
//TODO	Rework MetaImg data
//TODO	RGB_565 Conversion Colors
//TODO	RGB_565 Image
//TODO	handle multiples images in a single conversion
//TODO	Other Export methods (multiple images in one header | cout | raw array)
//TODO	GUI


int	main(int ac, const char **av)
{
	try
	{
		Options	opt = parseOptions(ac, av);
		runProgram(opt);
	}
	catch(const cxxopts::OptionException& e)
	{
		std::cerr << "Error in the options : " << e.what() << std::endl;
		return (1);
	}
	catch(const std::exception& e)
	{
		std::cerr << "Error : " << e.what() << std::endl;
		return (1);
	}
	catch(...)
	{
		std::cerr << "UNKNOWN ERROR" << std::endl;
		return (1);
	}

	return 0;
}
