#ifndef META_IMG_HPP_
# define META_IMG_HPP_

# include <cstdint>
# include "Colors.hpp"

enum class	ColorMode : uint8_t
{
	RGB_565 = 0,
	INDEXED = 1
};

struct	IndexedImage
{
	uint8_t		width{0};
	uint8_t		height{0};
	uint8_t		framesLowerBits{0};
	uint8_t		framesUpperBits{0};
	uint8_t		frameLoop{0};
	uint8_t		transparentColor{0xFF};
	uint8_t		colorMode{(uint8_t)ColorMode::INDEXED};

	uint8_t		*imgData{nullptr};
	uint32_t	size{0};

	IndexedImage() {}
	~IndexedImage();
	IndexedImage(uint32_t, uint32_t);

	IndexedImage(const IndexedImage&);
	IndexedImage& operator=(const IndexedImage&);

	void		allocateBuffer();
	void		freeBuffer();

	uint8_t		getIdxByte(uint8_t x, uint8_t y) const;
	void		setIdxByte(uint8_t x, uint8_t y, uint8_t idx);

	explicit operator bool()const
	{ return (imgData != nullptr); }

};

struct	MetaImage
{
	uint16_t		width{0};
	uint16_t		height{0};
	uint16_t		frames{0};
	uint16_t		frameLoop{0};
	uint16_t		transparentColor{0xFFFF};
	uint16_t		colorMode{(uint16_t)ColorMode::RGB_565};

	uint16_t		*imgData{nullptr};
	uint32_t		size{0};

	MetaImage() {}
	~MetaImage();

	MetaImage(uint32_t, uint32_t);
	MetaImage(const MetaImage&);
	MetaImage& operator=(const MetaImage&);

	void	allocateBuffer();
	void	freeBuffer();

	RGB565	getColor(uint16_t x, uint16_t y) const;
	void	setColor(uint16_t x, uint16_t y, RGB565 color);

	explicit operator bool() const
	{ return (imgData != nullptr); }

};



#endif //META_IMG_HPP_
