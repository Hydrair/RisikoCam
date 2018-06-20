#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "ofxOpenCv.h"
#include "ofxGui.h"
#include "kontinent.h"
#include "Player.h"

#define winWidth 1600
#define winHeigth 1200


class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);

/*==================MapFuncs======================*/
		void kontInit();
		void findCountries();
		void drawCountries();

		void guiInit();
		void drawFigures();
/*==================Images======================*/
		ofVideoGrabber cam;
		ofImage map1;
		cv::Mat map2;

		ofImage figureBG, olddiff;
		ofImage mapBG, compare;

/*==================Helpers======================*/
		ofxCv::ContourFinder mapContour;
		vector<ofPolyline> mapLines;

		ofxPanel gui;
		ofParameter<float> minArea, maxArea, threshold;
		ofParameter<bool> holes;
		ofParameter<bool> resetBackground;
		ofParameter<float> learningTime, thresholdValue;
		ofxCv::RunningBackground background;
		ofxCv::ContourFinder figureContour;
		vector<ofPolyline> figureLines;
/*==================Other======================*/
		kontinent NA, SA, EU, AF, AS, AU;
		Player player[5];
		vector<Figur> figuren;
		int score();
		bool toggleCam=0;

};
