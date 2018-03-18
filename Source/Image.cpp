#include "Image.hpp"

#define STB_IMAGE_IMPLEMENTATION
# define STBI_ONLY_PNG
# define STBI_ONLY_BMP
#include "stb_image.h"
#include <cstring>

Image::Image() :
	m_iWidth(0),
	m_iHeight(0),
	m_iBpp(0),
	m_pImg(nullptr)
{

}

Image::Image(const std::string& sImagePath) :
	m_iWidth(0),
	m_iHeight(0),
	m_iBpp(0),
	m_pImg(nullptr)
{
	loadImage(sImagePath);
}

Image::~Image()
{
	freeResource();
}

Image::Image(const Image& other) :
	m_iWidth(other.m_iWidth),
	m_iHeight(other.m_iHeight),
	m_iBpp(other.m_iBpp),
	m_pImg(nullptr)
{
	allocateResource(other.m_pImg);
}

Image&	Image::operator=(const Image& other)
{
	if (&other != this)
	{
		freeResource();
		m_iWidth = other.m_iWidth;
		m_iHeight = other.m_iHeight;
		m_iBpp = other.m_iBpp;
		allocateResource(other.m_pImg);
	}
	return (*this);
}

bool	Image::loadImage(const std::string& sImagePath)
{
	freeResource();
	uint8_t*	pImageTmp = stbi_load(sImagePath.c_str(), &m_iWidth, &m_iHeight, &m_iBpp, 0);
	if (pImageTmp != nullptr)
	{
		allocateResource(pImageTmp);
		stbi_image_free(pImageTmp);
		return (m_pImg != nullptr);
	}
	else
		return (false);
}

int32_t		Image::getWidth(void) const
{
	return (m_iWidth);
}

int32_t		Image::getHeight(void) const
{
	return (m_iHeight);
}

uint32_t	Image::getPixelColor(int32_t x, int32_t y) const
{
	if (m_pImg != nullptr && x < m_iWidth && y < m_iHeight)
	{
		uint32_t	offset = (y * m_iWidth * m_iBpp + x * m_iBpp);
		uint8_t		alpha = (m_iBpp == 4) ? m_pImg[offset+3] : 0xFF;
		return ( (m_pImg[offset] << 24) +
				 (m_pImg[offset+1] << 16) +
				 (m_pImg[offset+2] << 8) +
				 alpha );
	}
	else
		return (0);
}

void	Image::allocateResource(const uint8_t* pImageData)
{
	if (m_iWidth > 0 && m_iHeight > 0 && m_iBpp > 0)
	{
		m_pImg = new uint8_t[m_iWidth * m_iHeight * m_iBpp];
		std::memcpy(m_pImg, pImageData, m_iWidth * m_iHeight * m_iBpp);
	}
}

void	Image::freeResource()
{
	if (m_pImg != nullptr)
	{
		delete[] m_pImg;
		m_iWidth = 0;
		m_iHeight = 0;
		m_iBpp = 0;
		m_pImg = nullptr;
	}
}
