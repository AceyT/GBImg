#include "Colors.hpp"

Color::Color() :
	r(0), g(0), b(0), a(0), type(Type::RGB)
{

}

Color::Color(uint8_t _x, uint8_t _y, uint8_t _z, uint8_t _a, Type _type) :
	x(_x), y(_y), z(_z), a(_a), type(_type)
{

}

Color::Color(uint32_t _color) :
	r((_color >> 24) & 0xFF),
	g((_color >> 16) & 0xFF),
	b((_color >> 8) & 0xFF),
	a((_color) & 0xFF),
	type(Type::RGB)
{

}

Color::~Color()
{

}

Color::Color(const Color& other) :
	x(other.x), y(other.y), z(other.z), w(other.w), type(other.type)
{

}


Color&	Color::operator=(const Color& other)
{
	if (&other != this)
	{
		x = other.x;
		y = other.y;
		z = other.z;
		w = other.w;
		type = other.type;
	}
	return (*this);
}

uint32_t	Color::toSingle() const
{
	return ((r << 24) + (g << 16) + (b << 8) + (a));
}

bool	Color::isRGB() const
{
	return (type == Type::RGB );
}

bool	Color::isHSV() const
{
	return (!isRGB());
}

void	Color::toHSV()
{
	if (type == Type::HSV)
		return;
	RgbToHsv();
}

void	Color::toRGB()
{
	if (type == Type::RGB)
		return;
	HsvToRgb();
}

void	Color::HsvToRgb()
{
    Color rgb;
    unsigned char region, remainder, p, q, t;

    if (s == 0)
    {
        rgb.r = v;
        rgb.g = v;
        rgb.b = v;
    }
	else
	{
		region = h / 43;
		remainder = (h - (region * 43)) * 6;

		p = (v * (255 - s)) >> 8;
		q = (v * (255 - ((s * remainder) >> 8))) >> 8;
		t = (v * (255 - ((s * (255 - remainder)) >> 8))) >> 8;

	switch (region)
	{
		case 0:
	    	rgb.r = v; rgb.g = t; rgb.b = p;
			break;
		case 1:
	    	rgb.r = q; rgb.g = v; rgb.b = p;
	    	break;
		case 2:
	    	rgb.r = p; rgb.g = v; rgb.b = t;
	    	break;
		case 3:
	    	rgb.r = p; rgb.g = q; rgb.b = v;
	    	break;
		case 4:
	    	rgb.r = t; rgb.g = p; rgb.b = v;
	    	break;
		default:
			rgb.r = v; rgb.g = p; rgb.b = q;
			break;
	  }
	}
	type = Type::RGB;
	r = rgb.r;
	g = rgb.g;
	b = rgb.b;
}

void	Color::RgbToHsv()
{
    Color hsv;
    unsigned char rgbMin, rgbMax;

    rgbMin = r < g ? (r < b ? r : b) : (g < b ? g : b);
    rgbMax = r > g ? (r > b ? r : b) : (g > b ? g : b);

    hsv.v = rgbMax;
    if (hsv.v == 0)
    {
        hsv.h = 0;
        hsv.s = 0;

				type = Type::HSV;
				h = hsv.h;
				s = hsv.s;
				v = hsv.v;
				return;
    }

    hsv.s = 255 * long(rgbMax - rgbMin) / hsv.v;
    if (hsv.s == 0)
    {
        hsv.h = 0;

				type = Type::HSV;
				h = hsv.h;
				s = hsv.s;
				v = hsv.v;
        return;
    }

    if (rgbMax == r)
        hsv.h = 0 + 43 * (g - b) / (rgbMax - rgbMin);
    else if (rgbMax == g)
        hsv.h = 85 + 43 * (b - r) / (rgbMax - rgbMin);
    else
        hsv.h = 171 + 43 * (r - g) / (rgbMax - rgbMin);

		type = Type::HSV;
		h = hsv.h;
		s = hsv.s;
		v = hsv.v;
}
