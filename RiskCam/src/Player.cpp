#include "Player.h"

/*
blue:	h: 137-160
		s: 120-255
		v: 30-255
green:	h: 95-120
		s: 31-255
		h: 30-255
orange:	h: 0-20
		s: 200-255
		h: 30-255
yellow: h: 20-40
		s: 200-255
		v: 30-255
black:	h: 0-255
		s: 0-255
		v: 0-30
*/



Player::Player()
{
}

Player::Player(int minH, int minS, int minV, int maxH, int maxS, int maxV)
{
	hMin = minH;
	sMin = minS;
	vMin = minV;
	hMax = maxH;
	sMax = maxS;
	vMax = maxV;
}

Player::Player(ofColor inMinColor, ofColor inMaxColor)
{

}

bool Player::isPlayer(int inH, int inS, int inV)
{
	return false;
}

bool Player::isPlayer(ofColor inColor)
{
	return (inColor.getHue() <= hMax) && (inColor.getHue() >= hMin) && (inColor.getSaturation() <= sMax) && (inColor.getSaturation() >= sMin) && (inColor.getLightness() <= vMax) && (inColor.getLightness() >= vMin);
}

bool Player::addFigur(Figur inFigur)
{
	if (isPlayer(inFigur.getColor()))
	{
		list.push_back(inFigur);
		count++;
		return true;
	}
	return false;
}

int Player::getCount()
{
	return count;
}

Player::~Player()
{
}
