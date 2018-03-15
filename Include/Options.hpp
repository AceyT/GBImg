#ifndef OPTIONS_HPP_
# define OPTIONS_HPP_

# include <string>
# include <cstdint>

struct	Options
{
	//Mandatory options
	std::string	sImagePath{};
	std::string	sOutputPath{"code.hpp"};
	std::string	sCodeName{"image"};
	//Other options
	bool		bTransparency{false};
	uint32_t	iTransparency{0};
	std::string	sColorPalette{"default"};
	std::string	fColorPalette{};
	//Spritesheet options
	bool		bSpritesheet{false};
	uint32_t	uTilesX{0};
	uint32_t	uTilesY{0};
	uint32_t	uFramerate{0};
};

Options	parseOptions(int ac, const char **av);


#endif //OPTIONS_HPP_
