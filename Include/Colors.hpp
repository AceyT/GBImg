#ifndef COLORS_HPP_
# define COLORS_HPP_

# include <cstdint>

struct Color;

using RGB888 = Color;
using RGB565 = uint16_t;


struct Color
{
	enum class Type
	{
		RGB = 0,
		HSV = 1
	};

	Color();
	~Color();
	Color(uint8_t, uint8_t, uint8_t, uint8_t = 0xFF, Type = Type::RGB);
	Color(uint32_t);
	Color(RGB565);
	Color(const Color& other);
	Color& operator=(const Color& other);


	union{ uint8_t r ; uint8_t h ; uint8_t x ; };
	union{ uint8_t g ; uint8_t s ; uint8_t y ; };
	union{ uint8_t b ; uint8_t v ; uint8_t z ; };
	union{ uint8_t a ; uint8_t w ; };

	uint32_t		toSingle() const;
	void			toRGB();
	void			toHSV();
	bool			isRGB() const;
	bool			isHSV() const;
	RGB565			toRGB565() const;
	void			fromRGB565(RGB565 color);

	private:

	void			HsvToRgb();
	void			RgbToHsv();

	private:

	Type	type;
};


#endif //COLORS_HPP_
