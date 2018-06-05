#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "ofxOpenCv.h"
#include "kontinent.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		ofVideoGrabber cam;

		ofImage camOut;
		ofImage map1;
		cv::Mat map3;
		ofxCv::ContourFinder contour;
		vector<ofPolyline> lines;

		kontinent NA,SA,EU,AF,AS,AU;

};

