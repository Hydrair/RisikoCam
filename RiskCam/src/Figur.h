#pragma once

#include <ofColor.h>

class Figur
{
private:
	ofColor color;
	int xPos, yPos;

public:
	Figur(ofColor inColor, int inXPos, int inYPos);
	~Figur();
	ofColor getColor();
};

