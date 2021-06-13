#pragma once
#include "Colors.h"
#include <fstream>
#include <string>
#include <assert.h>
#include "ChiliWin.h"
class Surface {
public:
	Surface(int width, int height) :
		width(width),
		height(height),
		pPixel(new Color[width * height])
	{
	}
	Surface(const Surface& surface);
	Surface& operator=(const Surface& surface);
	~Surface();
	Surface(std::string& file_name);
	Color getPixel(int x, int y) const;
	void putPixel(int x, int y, Color& color);
	int getWidth() const;
	int getHeight() const;
private:
	int width;
	int height;
	Color* pPixel = nullptr;
};
