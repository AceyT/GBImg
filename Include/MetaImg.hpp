#ifndef META_IMG_HPP_
# define META_IMG_HPP_

# include <cstdint>

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

struct	Meta16Image
{
	uint16_t		width{0};
	uint16_t		height{0};
	uint16_t		frames{0};
	uint16_t		frameLoop{0};
	uint16_t		transparentColor{0xFFFF};
	uint16_t		colorMode{(uint16_t)ColorMode::RGB_565};

	uint16_t		*imgData{nullptr};
};



#endif //META_IMG_HPP_
