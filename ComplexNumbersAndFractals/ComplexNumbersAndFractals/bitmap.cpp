#include <vector>
#include <cassert>
#include <fstream>
#include <algorithm>
#include <iostream>
#include "complexnumbers.h"

struct Color
{
public:
    Color ();
    Color (float, float, float);

    float GetR() const { return r; }
    float GetG() const { return g; }
    float GetB() const { return b; }

    Color& operator += (Color);
    Color& operator -= (Color);
    Color& operator *= (float);
    Color& operator *= (Color);

private:
	float r, g, b;
};

Color::Color () :
	r (1), g (1), b (1)
{
}

Color::Color (float R, float G, float B) :
	r (R), g (G), b (B)
{
}

Color& Color::operator += (Color c)
{
	r += c.r; g += c.g; b += c.b; return *this;
}

Color& Color::operator -= (Color c)
{
	r -= c.r; g -= c.g; b -= c.b; return *this;
}

Color& Color::operator *= (float s)
{
	r *= s; g *= s; b *= s; return *this;
}

Color& Color::operator *= (Color s)
{
	r *= s.r; g *= s.g; b *= s.b; return *this;
}


Color operator + (Color a, Color b)
{
	return a += b;
}

Color operator - (Color a, Color b)
{
	return a -= b;
}

Color operator * (Color a, Color b)
{
	return a *= b;
}


Color operator * (Color a, float b)
{
	return a *= b;
}

const Color Red (1, 0, 0);
const Color Green (0, 1, 0);
const Color Blue (0, 0, 1);
const Color Black (0, 0, 0);
const Color White (1, 1, 1);

class Bitmap
{
public:
	Bitmap (unsigned, unsigned);

	Color& operator () (unsigned, unsigned);
	Color operator () (unsigned, unsigned) const;

	unsigned GetWidth () const;
	unsigned GetHeight () const;

	void Fill (Color);
	void Save (const char*) const;

private:
	unsigned width, height;
	std::vector<Color> pixels;

	static void Write (std::ostream&, float);
	static void Write (std::ostream&, unsigned, int);
};

Bitmap::Bitmap (unsigned w, unsigned h) :
	width (w), height (h), pixels (width * height)
{
	//assert (width < 32767);		//original: 32767
	//assert (height < 32767);	//original: 32767
}

Color& Bitmap::operator () (unsigned x, unsigned y)
{
	assert (x < width);
	assert (y < height);
	return pixels[y * width + x];
}

Color Bitmap::operator () (unsigned x, unsigned y) const
{
	assert (x < width);
	assert (y < height);
	return pixels[y * width + x];
}

inline unsigned Bitmap::GetWidth () const
{
	return width;
}

inline unsigned Bitmap::GetHeight () const
{
	return height;
}

void Bitmap::Fill (Color color)
{
	std::fill (pixels.begin (), pixels.end (), color);
}

void Bitmap::Save (const char* filename) const
{
	assert (filename);
	std::ofstream file (filename, std::ios::binary);

	enum {WORD = 2, DWORD = 4, LONG = 4};
	const unsigned padding = (4 - width * 3 % 4) % 4;

	// BITMAPFILEHEADER
	Write (file, WORD, 0x4d42);	// bfType
	Write (file, DWORD, 14 + 40 + (width * 3 + padding) * height);	// bfSize
	Write (file, WORD, 0);		// bfReserved1
	Write (file, WORD, 0);		// bfReserved2
	Write (file, DWORD, 14 + 40);	// bfOffBits

	// BITMAPINFOHEADER
	Write (file, DWORD, 40);	// biSize
	Write (file, LONG, width);	// biWidth
	Write (file, LONG, - ((int) height));	// biHeight
	Write (file, WORD, 1);		// biPlanes
	Write (file, WORD, 24);		// biBitCount
	Write (file, DWORD, 0);		// biCompression
	Write (file, DWORD, 0);		// biSizeImage
	Write (file, LONG, 0);		// biXPelsPerMeter
	Write (file, LONG, 0);		// biYPelsPerMeter
	Write (file, DWORD, 0);		// biClrUsed
	Write (file, DWORD, 0);		// biClrImportant

	for (unsigned y = 0; y != height; ++y)
	{
		for (unsigned x = 0; x != width; ++x)
		{
			const Color& color (pixels[y * width + x]);
			Write (file, color.GetB());
			Write (file, color.GetG());
			Write (file, color.GetR());
		}

		for (unsigned x = 0; x != padding; ++x)
			Write (file, 0);
	}
}

void Bitmap::Write (std::ostream& os, float value)
{
    int intValue = 256 * (value < 0 ? 0 : value > 1 ? 1 : value);
	os.put (intValue < 256 ? intValue : 255);
}

void Bitmap::Write (std::ostream& os, unsigned length, int value)
{
	while (length--) os.put (value & 0xff), value >>= 8;
}

/*
int main ()
{
	Bitmap bitmap (1024, 1024);

	Color top = Red;
	Color bottom = Green;

	for (unsigned y = 0; y != bitmap.GetHeight (); ++y)
	{
		Color color = top + (bottom - top) * (float (y) / bitmap.GetHeight ());

		for (unsigned x = 0; x != bitmap.GetWidth (); ++x)
			bitmap (x, y) = color;
	}

	bitmap.Save ("test.bmp");
}*/

//################-----END BITMAP.CPP-----#####################

void drawMandelbrotFractal(unsigned int, unsigned int);

using namespace std;

int main()
{
	unsigned int xres;
	unsigned int yres;
	cout << "Resolution:";
	cin >> xres;
	cin >> yres;

	drawMandelbrotFractal(xres, yres);

	return 0;
}

void drawMandelbrotFractal(unsigned int xres, unsigned int yres)
{
	Bitmap bitmap(xres, yres);

	const float zoom = 100;
	const float xoffset = 0.4;	// [-] right	, [+] left
	const float yoffset = 0.2;	// [-] down		, [+] up

	float fxres = xres;
	float fyres = yres;

	for (float y = 0; y < bitmap.GetHeight(); ++y)
	{
		for (float x = 0; x < bitmap.GetWidth(); ++x)
		{
			float iterations = 0;
			complex z1;
			complex c((1/zoom)*x/fxres + xoffset, (1/zoom)*y/fyres + yoffset);

			while (z1.cabs() <= 4 && iterations <= 64)
			{
				z1 = z1*z1 + c;
				++iterations;
			}

			if (iterations > 64)
				bitmap(x, y) = Black;
			else
				bitmap(x, y) = Red * (25/iterations);

		}
	}

	bitmap.Save("madelbrot.bmp");
}