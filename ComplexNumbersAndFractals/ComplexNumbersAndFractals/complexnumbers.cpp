#include <iostream>
#include <cmath>
#include "complexnumbers.h"

using namespace std;

//ADD
complex complex::operator + (const complex b)
{
	complex result;
	result.re = re + b.re;
	result.im = im + b.im;
	return result;
}

//SUBTRACT
complex complex::operator - (const complex b)
{
	complex result;
	result.re = re - b.re;
	result.im = im - b.im;
	return result;
}

//MULTIPLY
complex complex::operator * (const complex b)
{
	complex result;
	result.re = re*b.re - im*b.im;
	result.im = re*b.im + im*b.re;
	return result;
}

//DIVIDE
complex complex::operator / (const complex b)
{
	complex result;
	result.re = ((re*b.re + im*b.im) / (b.re*b.re + b.im*b.im));
	result.im = ((im*b.re - re*b.im) / (b.re*b.re + b.im*b.im));
	return result;
}

//ADD=
complex complex::operator += (const complex b)
{
	re += b.re;
	im += b.im;
	return *this;
}

//SUBTRACT=
complex complex::operator -= (const complex b)
{
	re -= b.re;
	im -= b.im;
	return *this;
}

//MULTIPLY=
complex complex::operator *= (const complex b)
{
	re = re*b.re + im*b.im;
	im = re*b.im + im*b.re;
	return *this;
}

//DIVIDE=
complex complex::operator /= (const complex b)
{
	re = ((re*b.re + im*b.im) / (b.re*b.re + b.im*b.im));
	im = ((im*b.re - re*b.im) / (b.re*b.re + b.im*b.im));
	return *this;
}

//EUQAL
bool complex::operator == (const complex b)
{
	return (re == b.re && im == b.im);
}

//NOT EUQAL
bool complex::operator != (const complex b)
{
	return !(*this == b);
}

//ABSOLUTE VALUE
double complex::cabs()
{
	return sqrt(pow(re, 2) + pow(im, 2));
}

//READ REAL PART
double complex::real()
{
	return re;
}

//READ IMAGINARY PART
double complex::imag()
{
	return im;
}

//WRITE REAL PART
void complex::setreal(double real)
{
	re = real;
}

//WRITE IMAGINARY PART
void complex::setimag(double imag)
{
	im = imag;
}

//OUTPUT
ostream& operator << (ostream& o, complex a)
{
	if (a.real() == 0 && a.imag() == 0)
		return o << 0;
	else if (a.real() == 0)
		return o << a.imag() << "i";
	else if (a.imag() == 0)
		return o << a.real();

	char c;
	if (a.imag() > 0)
		c = '+';
	else
		c = '-';
	return o << a.real() << " " << c << " " << abs(a.imag()) << "i";
}

//INPUT
istream& operator >> (istream& i, complex& a)
{
	double real, imag;
	char c3;
	i >> real >> imag >> c3;

	a.setreal(real);
	a.setimag(imag);
	
	if (c3 != 'i')
	{
		complex a();
	}

	return i;
}