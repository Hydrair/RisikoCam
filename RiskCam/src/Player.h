#pragma once

//#include <ofColor.h>
#include "ofxCv.h"
#include "ofxGui.h"
#include "Figur.h"
#include <list>

class Player
{
private:
	int hMin, hMax, sMin, sMax, vMin, vMax;
	ofColor minColor, maxColor;
	std::list<Figur> list;
	int count = 0;

public:
	Player();
	Player(int minH, int minS, int minV, int maxH, int maxS, int maxV);
	Player(ofColor inMinColor, ofColor inMaxColor);
	~Player();

	bool isPlayer(int inH, int inS, int inV);
	bool isPlayer(ofColor inColor);
	bool addFigur(Figur inFigur);
	int getCount();

};

