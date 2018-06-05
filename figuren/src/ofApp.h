#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "ofxGui.h"
#include "ofxOpenCv.h"

class ofApp : public ofBaseApp {
public:
	void setup();
	void update();
	void draw();
	void keyPressed(int key);

	ofVideoGrabber cam;
	ofxCv::RunningBackground background;
	ofImage thresholded,olddiff;
	ofImage mapBG,compare;



	ofxPanel gui;
	ofParameter<float> minArea, maxArea, threshold;
	ofParameter<bool> holes;
	ofParameter<bool> resetBackground;
	ofParameter<float> learningTime, thresholdValue;
	ofxCv::ContourFinder contour;
	vector<ofPolyline> lines;
	ofVec3f points;
	cv::Mat dst;
	
};