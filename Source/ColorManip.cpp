#include "ColorManip.hpp"


/*
 *	If you see each color as a vec3
 *	Then it is just a matter of calculating the Euclidean distance between them
 *	Note that this implementation does it squared but it work nonetheless
 */

uint32_t getColorDistance(const Color& src, const Color& dest)
{
	int32_t redDifference;
	int32_t greenDifference;
	int32_t blueDifference;

	if ( src.isRGB() && dest.isRGB() )
	{
		redDifference = src.r - dest.r;
		greenDifference = src.g - dest.g;
		blueDifference = src.b - dest.b;
	}
	else
	{
		Color	srcCpy(src);
		Color	destCpy(dest);
		srcCpy.toRGB();
		destCpy.toRGB();

		redDifference = srcCpy.r - destCpy.r;
		greenDifference = srcCpy.g - destCpy.g;
		blueDifference = srcCpy.b - destCpy.b;
	}

	return (redDifference * redDifference + 
			greenDifference * greenDifference + 
			blueDifference * blueDifference);
}




