#include <iostream>
#include "ImageProgram.hpp"


#include "MetaImg.hpp"
#include "Colors.hpp"
#include "Image.hpp"
#include "ColorManip.hpp"
#include "ColorPalette.hpp"
#include "CodeExporter.hpp"


void	runProgram(const Options& opt)
{
	if (!opt.fColorPalette.empty())
		std::cerr << "Loading color palette from file will be done later" << std::endl;
	const std::array<Color, 16>& palette = selectColorPalette(opt.sColorPalette);
	Image	img(opt.sImagePath);
	if (!img)
		throw std::runtime_error(std::string("Couldn't open image " + opt.sImagePath));
	if (opt.bSpritesheet) //spritesheet image export
		spritesheetImageExport(opt, img, palette);
	else // single image export
		singleImageExport(opt, img, palette);
}

void	spritesheetImageExport(const Options& opt, const Image& img, const std::array<Color, 16>& palette)
{
	uint32_t		width = static_cast<uint32_t>(img.getWidth());
	uint32_t		height = static_cast<uint32_t>(img.getHeight());
	uint32_t		sub_width = width / opt.uTilesX;
	uint32_t		sub_height = height / opt.uTilesY;
	IndexedImage	spritesheet(width, height);
	if (!spritesheet)
		throw std::runtime_error(std::string("Couldn't allocate memory for the spritesheet"));
	spritesheet.transparentColor = static_cast<uint8_t>(opt.iTransparency);
	for (uint32_t idx = 0 ; idx < (width * height) ; ++idx)
	{
		uint32_t	real_x = idx % width;
		uint32_t	real_y = idx / width;

		/*
		** It's simple to transform a single coordinate to a 2D array
		** However to also get the right tiles at the same time, the process is a bit more complicated
		** First we calculate the height in the tiles.
		** Since the Y tile can overflow, we offset the X tiles by the proportional amount of way past the Y tiles.
		** Then we have to correct the Y in the tiles (he has overflowed) with a simple modulo to the tile height.
		** But now, the X will overflow from the image width.
		** So we have to offset the Y by the tiles height proportional to the number of time the X has overflown from the width.
		** Now our sub height is correct and cycles through the tiles by the right amount.
		** We can correct our sub width by the modulo of the image width.
		*/
		uint32_t	sub_y = (idx / sub_width);
		uint32_t	sub_x = (idx % sub_width) + (sub_width * (sub_y / sub_height));
		sub_y = (sub_y % sub_height) + ( sub_height * (sub_x / width));
		sub_x = sub_x % width;

		Color	color = img.getPixelColor(sub_x, sub_y);
		if (color.a < 0xFF && opt.bTransparency)
			spritesheet.setIdxByte(real_x, real_y, static_cast<uint8_t>(opt.iTransparency));
		else
		{
			uint8_t		indexColorMap = static_cast<uint8_t>(findNearestColor(palette, color));
			spritesheet.setIdxByte(real_x, real_y, indexColorMap);
		}
	}
	spritesheet.width = sub_width;
	spritesheet.height = sub_height;
	uint16_t frames = opt.uTilesY * opt.uTilesX;
	spritesheet.framesLowerBits = frames & 0xFF;
	spritesheet.framesUpperBits = (frames >> 8) & 0xFF;
	spritesheet.frameLoop = static_cast<uint8_t>(opt.uFramerate);
	spritesheetTo(spritesheet, opt.sOutputPath, opt.sCodeName, width, height);
}

void	singleImageExport(const Options& opt, const Image& img, const std::array<Color, 16>& colorMap)
{
	int32_t	width, height;
	width = img.getWidth();
	height = img.getHeight();
	IndexedImage	result(width, height);
	if (result)
	{
		result.transparentColor = static_cast<uint8_t>(opt.iTransparency);
		for (int32_t y = 0 ; y < height ; ++y)
			for (int32_t x = 0 ; x < width ; ++x)
			{
				Color 		color(img.getPixelColor(x, y));
				if (color.a < 0xFF && opt.bTransparency)
					result.setIdxByte(x, y, static_cast<uint8_t>(opt.iTransparency));
				else
				{
					uint8_t		indexColorMap = static_cast<uint8_t>(findNearestColor(colorMap, color));
					result.setIdxByte(x, y, indexColorMap);
				}
			}
		exportTo(result, opt.sOutputPath, opt.sCodeName);
	}
	else
		throw std::runtime_error("Couldn't allocate memory for Image Export");
}




const std::array<Color, 16>&	selectColorPalette(const std::string& sPalette)
{
	auto colorMapIt = GB::s_mColorPalette.find(sPalette);
	if (colorMapIt != GB::s_mColorPalette.cend())
		return colorMapIt->second;
	return GB::defaultColorMap;
}
