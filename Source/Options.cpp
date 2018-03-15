#include "Options.hpp"
#include <cxxopts.hpp>


Options	parseOptions(int ac, const char **av)
{
	cxxopts::Options	argparser(av[0], "Convert images to Gamebuino flash Image");
	argparser.add_options()
		("o, output-path", "File name of the export", cxxopts::value<std::string>()->default_value("code.hpp"))
		("i, image-input", "Image path to convert", cxxopts::value<std::string>())
		("c, code-name", "identifier in the exported code", cxxopts::value<std::string>()->default_value("image"))
		("transparency", "Choosen color index used for transparency. "
		"Value greater than 15 (0x0F) will make the program not handle transparency", cxxopts::value<uint32_t>()->default_value("255")->implicit_value("0"), "N")
		("palette", "Choosen color palette used for finding correct indexes", cxxopts::value<std::string>()->default_value("default"), "default / edge16")
		("palette-file", "File from which the color palette will be used (override palette option)", cxxopts::value<std::string>())
		("h, help", "Print the help", cxxopts::value<bool>())
		;

	argparser.add_options("Spritesheet")
		("s, spritesheet", "Activate the spritesheets mode", cxxopts::value<bool>()->default_value("false"))
		("tile-x", "Number of tiles on X coord | Sub width will be deduced with image-width / tile-x", cxxopts::value<uint32_t>()->default_value("0"), "N")
		("tile-y", "Number of tiles on Y coord | Sub height will be deduced with image-height / tile-y", cxxopts::value<uint32_t>()->default_value("0"), "N")
		("framerate", "Framerate of the animation | number of frame per animation", cxxopts::value<uint32_t>()->default_value("0"), "N")
		;

	auto result = argparser.parse(ac, av);

	if (result.count("help"))
	{
		std::cout << argparser.help({"", "Spritesheet"}) << std::endl;
		exit(0);
	}
	else if (result.count("image-input"))
	{
		Options	opt;
		opt.sImagePath = result["image-input"].as<std::string>();
		opt.sOutputPath = result["output-path"].as<std::string>();
		opt.sCodeName = result["code-name"].as<std::string>();
		opt.iTransparency = result["transparency"].as<uint32_t>();
		opt.bTransparency = (opt.iTransparency <= 0x0F);
		if (result.count("palette-file"))
			opt.fColorPalette = result["palette-file"].as<std::string>();
		else
			opt.sColorPalette = result["palette"].as<std::string>();

		opt.bSpritesheet = result["spritesheet"].as<bool>();
		if (opt.bSpritesheet)
		{
			opt.uTilesX = result["tile-x"].as<uint32_t>();
			opt.uTilesY = result["tile-y"].as<uint32_t>();
			opt.uFramerate = result["framerate"].as<uint32_t>();
			if (opt.uTilesY == 0 || opt.uTilesX == 0)
				throw cxxopts::OptionException("tile-x and tile-y must be specified if spritesheet activated and different from 0");
		}

		return opt;
	}
	std::cerr << "Invalid Options" << std::endl;
	std::cerr << argparser.help({"", "Spritesheet"}) << std::endl;
	exit(1);
}
