#ifndef IMAGE_HPP_
# define IMAGE_HPP_

# include <cstdint>
# include <string>

class	Image
{
public:
	Image();
	~Image();
	Image(const std::string&);

	Image(const Image&);
	Image& operator=(const Image&);

	bool		loadImage(const std::string&);

	int32_t		getWidth(void) const;
	int32_t		getHeight(void) const;
	uint32_t	getPixelColor(int32_t x, int32_t y) const;

	explicit operator bool() const
	{ return m_pImg!=nullptr;}

private:
	void	freeResource();
	void	allocateResource(const uint8_t*);

private:
	int32_t		m_iWidth{0};
	int32_t		m_iHeight{0};
	int32_t		m_iBpp{0};
	uint8_t*	m_pImg{nullptr};
};

#endif //IMAGE_HPP_
