#include "ofApp.h"

using namespace ofxCv;
using namespace cv;

void ofApp::setup() {
	cam.setup(640, 480);
	thresholded.allocate(640, 480, OF_IMAGE_GRAYSCALE);
	gui.setup();
	gui.add(resetBackground.set("Reset Background", false));
	gui.add(learningTime.set("Learning Time", 0, 0, 100));
	gui.add(thresholdValue.set("Threshold Value", 30, 0, 255));
	gui.add(minArea.set("Min area", 5, 1, 100));
	gui.add(maxArea.set("Max area", 15, 1, 500));
	gui.add(threshold.set("Threshold", 128, 0, 255));
	gui.add(holes.set("Holes", false));
	cam.update();
	mapBG.allocate(640, 480, OF_IMAGE_COLOR);
	compare.allocate(640, 480, OF_IMAGE_COLOR);
}

void ofApp::update() {
	cam.update();
	
	
	
	/*if (cam.isFrameNew()) {
		background.setLearningTime(learningTime);
		background.setThresholdValue(thresholdValue);
		background.update(cam, thresholded);
		thresholded.update();
	}*/
	olddiff = cam.getPixels();

	//contour.setMinAreaRadius(minArea); //5
	//contour.setMaxAreaRadius(maxArea); //15
	//contour.setThreshold(threshold);
	//contour.findContours(thresholded);
	//contour.setFindHoles(holes);
	//lines = contour.getPolylines();
	
}

void ofApp::draw() {
	mapBG.draw(0, 480);
	compare.draw(0, 0);

	if (thresholded.isAllocated()) {
		thresholded.draw(640, 0);
	}

	/*for (auto e : lines)
	{
		ofSetColor(olddiff.getColor(e.getCentroid2D().x, e.getCentroid2D().y));
		ofDrawCircle(e.getCentroid2D()+ ofPoint(640,480) , 10);
	}*/

	ofSetColor(ofColor::white);
	gui.draw();

}

void ofApp::keyPressed(int key)
{
	printf("KEY\n");
	if (key == 'a')
	{
		ofPixelsRef pixels = cam.getPixelsRef();
		compare.setFromPixels(pixels);

	}

	if (key == 'b')
	{
		ofPixelsRef pixels = cam.getPixelsRef();
		mapBG.setFromPixels(pixels);
	}
	if (key == 'c')
	{
		if (resetBackground) {
			background.reset();
			resetBackground = false;
		}

		background.setLearningTime(learningTime);
		background.setThresholdValue(thresholdValue);
		background.update(mapBG, thresholded);
		thresholded.update();

		contour.setMinAreaRadius(minArea); //5
		contour.setMaxAreaRadius(maxArea); //15
		contour.setThreshold(threshold);
		contour.findContours(thresholded);
		contour.setFindHoles(holes);
		lines = contour.getPolylines();
		
	}
	/*if (key = 'r')
	{
		background.reset();
		resetBackground = false;
	}*/

}


