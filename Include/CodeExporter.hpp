#ifndef CODE_EXPORTER_HPP_
# define CODE_EXPORTER_HPP_

# include "MetaImg.hpp"
# include <string>
# include <cstdint>

void	debug(const IndexedImage& img);
void	exportTo(const IndexedImage& img, const std::string& path, const std::string& name = "image");
void	spritesheetTo(const IndexedImage& img, const std::string& path, const std::string& name, uint32_t rx, uint32_t ry);

#endif //CODE_EXPORTER_HPP_
