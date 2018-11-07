#include <iostream>
using namespace std;

class complex
{
private:
	double re;
	double im;

public:
	complex() : re(0), im(0)
	{}
	complex(double a, double b) : re(a), im(b)
	{}

	double real();

	double imag();

	double cabs();

	void setimag(double);

	void setreal(double);

	complex operator * (const complex);

	complex operator + (const complex);

	complex operator - (const complex);

	complex operator / (const complex);

	complex operator += (const complex);

	complex operator -= (const complex);

	complex operator *= (const complex);

	complex operator /= (const complex);

	bool operator == (const complex);

	bool operator != (const complex);
};

ostream& operator << (ostream&, complex);

istream& operator >> (istream&, complex&);