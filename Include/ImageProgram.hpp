#ifndef IMAGE_PROGRAM_HPP_
# define IMAGE_PROGRAM_HPP_

# include <array>
# include "Colors.hpp"
# include "Options.hpp"
# include "Image.hpp"

void	runProgram(const Options& opt);

void	singleImageExport(const Options&, const Image&, const std::array<Color, 16>&);
void	spritesheetImageExport(const Options&, const Image&, const std::array<Color, 16>&);

const std::array<Color, 16>&	selectColorPalette(const std::string& sPalette);


#endif //IMAGE_PROGRAM_HPP_
