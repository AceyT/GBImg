#ifndef COLOR_PALETTE_HPP_
# define COLOR_PALETTE_HPP_

# include "Colors.hpp"
# include <array>
# include <string>
# include <map>

namespace GB
{
	enum class ColorPalette : uint32_t
	{
		White		= 0xFFFFFFFF,
		Gray		= 0xA89987FF,
		Darkgray	= 0x544D43FF,
		Black		= 0x000000FF,
		Purple		= 0x960040FF,
		Magenta		= 0xCF4485FF,
		Red			= 0xDB1D23FF,
		Orange		= 0xFFA811FF,
		Brown		= 0xCF8E44FF,
		Beige		= 0xFFD690FF,
		Yellow		= 0xF5E700FF,
		Lightgreen	= 0x85CF44FF,
		Green		= 0x008B50FF,
		Darkblue	= 0x004385FF,
		Blue		= 0x4485CFFF,
		Lightblue	= 0x7DBBFFFF
	};

	static const std::array<Color, 16> defaultColorMap = {
		(uint32_t)ColorPalette::Black,
		(uint32_t)ColorPalette::Darkblue,
		(uint32_t)ColorPalette::Purple,
		(uint32_t)ColorPalette::Green,
		(uint32_t)ColorPalette::Brown,
		(uint32_t)ColorPalette::Darkgray,
		(uint32_t)ColorPalette::Gray,
		(uint32_t)ColorPalette::White,
		(uint32_t)ColorPalette::Red,
		(uint32_t)ColorPalette::Orange,
		(uint32_t)ColorPalette::Yellow,
		(uint32_t)ColorPalette::Lightgreen,
		(uint32_t)ColorPalette::Lightblue,
		(uint32_t)ColorPalette::Blue,
		(uint32_t)ColorPalette::Magenta,
		(uint32_t)ColorPalette::Beige
	};

	static const std::array<Color, 16> edgeColorMap = {
		0xE4A672FF,
		0xB86F50FF,
		0x743F39FF,
		0x3F2832FF,
		0x9E2835FF,
		0xE53B44FF,
		0xFB922BFF,
		0xFFE762FF,
		0x63C64DFF,
		0x327345FF,
		0x193D3FFF,
		0x4F6781FF,
		0xAFBFD2FF,
		0xFFFFFFFF,
		0x2CE8F4FF,
		0x0484D1FF
	};

	static const std::array<Color, 16> customColorMap = {
		0x000000FF,
		0xB86F50FF,
		0x743F39FF,
		0x3F2832FF,
		0x9E2835FF,
		0xE53B44FF,
		0xFB922BFF,
		0xFFE762FF,
		0x63C64DFF,
		0x327345FF,
		0x193D3FFF,
		0x4F6781FF,
		0xAFBFD2FF,
		0xFFFFFFFF,
		0x2CE8F4FF,
		0x0484D1FF
	};

	static const std::map<const std::string, const std::array<Color, 16> > s_mColorPalette =
	{
		{ "default", defaultColorMap },
		{ "edge16", edgeColorMap },
		{ "custom", customColorMap }
	};
}


/*
 * GAMEBUINO META DEFAULT
 * ORDER OF COLOR
 *
 * black,
 * darkblue,
 * purple,
 * green,
 * brown,
 * darkgray,
 * gray,
 * white,
 * red,
 * orange,
 * yellow,
 * lightgreen,
 * lightblue,
 * blue,
 * pink, // Magenta
 * beige
 *
 */

#endif //COLOR_PALETTE_HPP_
