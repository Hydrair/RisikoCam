#include "Figur.h"


Figur::Figur(ofColor inColor, int inXPos, int inYPos)
{
	color = inColor;
	xPos = inXPos;
	yPos = inYPos;
}

Figur::~Figur()
{
}

ofColor Figur::getColor()
{
	return color;
}