#ifndef COLOR_MANIP_HPP_
# define COLOR_MANIP_HPP_

# include "Colors.hpp"
# include <cstdint>
# include <array>
# include <limits>

uint32_t	getColorDistance(const Color& src, const Color& dest);

template<std::size_t SIZE>
uint32_t	findNearestColor(const std::array<Color, SIZE>& map, const Color& current)
{
	uint32_t	shortestDistance = std::numeric_limits<uint32_t>::max();
	uint32_t	index = 0;

	for( uint32_t idx = 0 ; idx < map.size() ; ++idx )
	{
		uint32_t	distance = getColorDistance(current, map[idx]);
		if (distance < shortestDistance)
		{
			shortestDistance = distance;
			index = idx;
		}
		if (shortestDistance == 0)
			break;
	}
	return index;
}



#endif //COLOR_MANIP_HPP_
