# include "Surface.h"

Surface::Surface(const Surface& surface) :
	Surface(surface.width, surface.height)
{
	for (int i = 0; i < width * height; i++) {
		pPixel[i] = surface.pPixel[i];
	}
}

Surface& Surface::operator=(const Surface& surface) {
	width = surface.width;
	height = surface.height;
	delete[] pPixel;
	pPixel = new Color[width * height];
	const int nPixels = width * height;
	for (int i = 0; i < nPixels; i++) {
		pPixel[i] = surface.pPixel[i];
	}
	return *this;
}

Surface::~Surface()
{
	delete[] pPixel;
	pPixel = nullptr;
}

Surface::Surface(std::string& file_name)
{
	std::ifstream bmfile(file_name, std::ios::binary);
	assert(bmfile);

	BITMAPFILEHEADER bitmap_file_header;
	bmfile.read(reinterpret_cast<char*>(&bitmap_file_header), sizeof(bitmap_file_header));

	BITMAPINFOHEADER bitmap_info_header;
	bmfile.read(reinterpret_cast<char*>(&bitmap_info_header), sizeof(bitmap_info_header));

	assert(bitmap_info_header.biBitCount == 24);
	assert(bitmap_info_header.biCompression == BI_RGB);
	bool xd = bitmap_info_header.biBitCount == 24;

	width = bitmap_info_header.biWidth;
	height = bitmap_info_header.biHeight;

	pPixel = new Color[width * height];
	const int padding = (4 - ((width * 3) % 4)) % 4;

	bmfile.seekg(bitmap_file_header.bfOffBits);
	for (int j = height - 1; j > -1; j--) {
		for (int i = 0; i < width; i++) {
			const unsigned char b = bmfile.get();
			const unsigned char g = bmfile.get();
			const unsigned char r = bmfile.get();
			putPixel(i, j, Color(r, g, b));
		}
		bmfile.seekg(padding, std::ios::cur);
	}
}

void Surface::putPixel(int x, int y, Color& color) {
	pPixel[(width * y) + x] = color;
}

Color Surface::getPixel(int x, int y) const {
	return pPixel[(width * y) + x];
}

int Surface::getHeight() const
{
	return height;
}

int Surface::getWidth() const
{
	return width;
}
