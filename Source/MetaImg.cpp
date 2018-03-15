#include "MetaImg.hpp"
#include <cstring>

IndexedImage::~IndexedImage()
{
	freeBuffer();
}

IndexedImage::IndexedImage(uint32_t _width, uint32_t _height) :
	width(_width),
	height(_height),
	framesLowerBits(0),
	framesUpperBits(0),
	frameLoop(0),
	transparentColor(0xFF),
	colorMode((uint8_t)ColorMode::INDEXED),
	imgData(nullptr),
	size(0)
{
	allocateBuffer();
}

IndexedImage::IndexedImage(const IndexedImage& other) :
	width(other.width),
	height(other.height),
	framesLowerBits(other.framesLowerBits),
	framesUpperBits(other.framesUpperBits),
	frameLoop(other.frameLoop),
	transparentColor(other.transparentColor),
	colorMode(other.colorMode),
	imgData(nullptr),
	size(0)
{
	allocateBuffer();
	std::memcpy(imgData, other.imgData, size);
}

IndexedImage&	IndexedImage::operator=(const IndexedImage& other)
{
	if (&other != this)
	{
		freeBuffer();
		width = other.width;
		height = other.height;
		framesLowerBits = other.framesLowerBits;
		framesUpperBits = other.framesUpperBits;
		frameLoop = other.frameLoop;
		transparentColor = other.transparentColor;
		colorMode = other.colorMode;
		allocateBuffer();
		if (other.imgData != nullptr)
			std::memcpy(imgData, other.imgData, size);
	}
	return (*this);
}


void	IndexedImage::allocateBuffer()
{
	if (width > 0 && height > 0)
	{
		size = height * ((width+1) / 2);
		imgData = new uint8_t[size];
		std::memset(imgData, 0, size);
	}
}

void	IndexedImage::freeBuffer()
{
	if (*this)
	{
		delete[] imgData;
		imgData = nullptr;
		size = 0;
	}
}

uint8_t		IndexedImage::getIdxByte(uint8_t x, uint8_t y) const
{
	if (*this)
	{
		uint16_t	offset = (y * ((width+1)/2) + x/2);
		uint8_t		value = imgData[offset];
		if (x%2 == 0)
			return (value >> 4 & 0x0F);
		else
			return (value & 0x0F);
	}
	return(0x00);
}

void		IndexedImage::setIdxByte(uint8_t x, uint8_t y, uint8_t val)
{
	if (*this)
	{
		uint16_t	offset = (y * ((width+1)/2) + x/2);
		uint8_t old = imgData[offset];
		if (x%2 == 0)
			imgData[offset] = ((val << 4) & 0xF0) + (old & 0x0F);
		else
			imgData[offset] = (old & 0xF0) + (val & 0x0F);
	}
}
