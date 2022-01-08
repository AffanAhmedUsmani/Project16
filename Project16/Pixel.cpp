#include "Pixel.h"
/*----------------------------------------------------------------*/
/* Pixel class implementation.                                    */
/* File name: Pixel.cpp                                           */

/* Addition (+) operator.                                         */
Pixel Pixel::operator+(const Pixel& p) const
{
	Pixel temp;
	temp.red = red + p.red;
	temp.green = green + p.green;
	temp.blue = blue + p.blue;
	temp.validate();
	return temp;
}



Pixel Pixel::operator*(const Pixel& p) const
{
	Pixel temp;
	temp.red = red * p.red;
	temp.green = green * p.green;
	temp.blue = blue * p.blue;
	temp.validate();
	return temp;
}
/*----------------------------------------------------------------*/
/* Multiplication (*) operator.                                   */
Pixel Pixel::operator*(double v) const
{
	Pixel temp;
	temp.red = static_cast<unsigned int>(red * v);
	temp.green = static_cast<unsigned int>(green * v);
	temp.blue = static_cast<unsigned int>(blue * v);
	temp.validate();
	return temp;
}
/*----------------------------------------------------------------*/

/* Division (/) operator.                                         */
Pixel Pixel::operator/(unsigned int v) const
{
	Pixel temp;
	temp.red = red / v;
	temp.green = green / v;
	temp.blue = blue / v;
	temp.validate();
	return temp;
}
/*----------------------------------------------------------------*/
/* Output << operator.                                            */
ostream& operator<<(ostream& out, const Pixel& p)
{
	out << p.red << ' ';
	out << p.green << ' ';
	out << p.blue;
	return out;
}
/*----------------------------------------------------------------*/
/* Input (>>) operator.                                           */
istream& operator>>(istream& in, Pixel& p)
{
	in >> p.red >> p.green >> p.blue;
	p.validate();
	return in;
}
/*----------------------------------------------------------------*/
/* default constructor, sets the rgb to 0.                        */
Pixel::Pixel()
{
	//Black
	red = green = blue = 0;
	return;
}
/*----------------------------------------------------------------*/
/* alternate constructor 1, sets the rgb to value.                */
Pixel::Pixel(unsigned int value)
{
	//Grey scale
	red = green = blue = value;
	validate();
	return;
}
/*----------------------------------------------------------------*/
/* alternate constructor 2, sets the rgb value to r,g,b.          */
Pixel::Pixel(unsigned int r, unsigned int g, unsigned int b)
{
	//Full color range
	red = r;
	green = g;
	blue = b;
	validate();
	return;
}
/*----------------------------------------------------------------*/
/*  overloaded assignment operator                                */
Pixel& Pixel::operator=(const Pixel& rhs)
{
	if (this != &rhs)
	{
		red = rhs.red;
		green = rhs.green;
		blue = rhs.blue;
		overflowFlag = rhs.overflowFlag;
		validate();
		return *this;
	}
	else return *this;
}


/*----------------------------------------------------------------*/
/* set the rgb value of a pixel                                   */
Pixel& Pixel::setPixel(unsigned r, unsigned g, unsigned b)
{
	red = r;
	green = g;
	blue = b;
	return *this;
}

Pixel& Pixel::setRoot(unsigned r, unsigned g, unsigned b)
{
	red = sqrt(r);
	green = sqrt(g);
	blue = sqrt(b);
	return *this;
}

/*----------------------------------------------------------------*/
/* set the red value of a pixel                                   */
Pixel& Pixel::setRed(unsigned r)
{
	red = r;
	return *this;
}


/*----------------------------------------------------------------*/
/* set the green value of a pixel                                   */
Pixel& Pixel::setGreen(unsigned g)
{
	green = g;
	return *this;
}


/*----------------------------------------------------------------*/
/* set the blue value of a pixel                                   */
Pixel& Pixel::setBlue(unsigned b)
{
	blue = b;
	return *this;
}


/*----------------------------------------------------------------*/
/* check for overflow                                             */
bool Pixel::overflow()
{
	return(overflowFlag & CHECK);
}

/*----------------------------------------------------------------*/
/* reset the rgb values to 255 (white)                            */
void Pixel::reset()
{
	if (red > MAXVAL) red = MAXVAL;
	if (green > MAXVAL) green = MAXVAL;
	if (blue > MAXVAL) blue = MAXVAL;
	overflowFlag = 0;
}

/*----------------------------------------------------------------*/
/* set the overflow flag                                          */
void Pixel::validate()
{
	if (red > MAXVAL) overflowFlag = overflowFlag | RMASK;
	if (green > MAXVAL) overflowFlag = overflowFlag | GMASK;
	if (blue > MAXVAL) overflowFlag = overflowFlag | BMASK;
}


