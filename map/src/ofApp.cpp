#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	cam.setup(1600, 1200);
	map1.load("images/mapworldsmall3.jpg");
	map3 = ofxCv::toCv(map1);
	NA.set(5, 0, 0, map3.cols*0.38, map3.rows*0.5);
	SA.set(2, 0, map3.rows*0.5, map3.cols*0.38, map3.rows*0.5);
	EU.set(5, map3.cols*0.38, 0, map3.cols*0.17, map3.rows*0.48);
	AF.set(3, map3.cols*0.38, map3.rows*0.55, map3.cols*0.22, map3.rows*0.5);
	AS.set(7, map3.cols*0.55, 0, map3.cols*0.5,map3.rows*0.6);
	AU.set(2, map3.cols*0.65, map3.rows*0.6, map3.cols*0.5, map3.rows*0.5);
}

//--------------------------------------------------------------
void ofApp::update(){
	cam.update();
	if (cam.isFrameNew())
	{
		camOut = cam.getPixels();
		//camOut.resize(1043, 676);
	}
	contour.setMinAreaRadius(10);
	contour.setMaxAreaRadius(400);
	contour.setThreshold(5);
	contour.findContours(map3);
	contour.setFindHoles(1);
	lines = contour.getPolylines();	
}

//--------------------------------------------------------------
void ofApp::draw(){
	//cam.draw(0, 0);
	camOut.draw(0, 0);
	//ofSetColor(ofColor::green);
	//ofxCv::drawMat(map3, 0, 0,1500,800);
	
	//ofSetColor(ofColor::blue);
	//contour.draw();

	

	ofSetColor(ofColor::red);
	for (auto e: lines)
	{
		if (NA.range.inside(e.getCentroid2D()))
		{
			ofSetColor(ofColor::yellow);
			e.draw();
		}
		else if(EU.range.inside(e.getCentroid2D()))
		{
			ofSetColor(ofColor::blue);
			e.draw();
		}
		else if(AF.range.inside(e.getCentroid2D()))
		{
			ofSetColor(ofColor::red);
			e.draw();
		}
		else if(AS.range.inside(e.getCentroid2D()))
		{
			ofSetColor(ofColor::green);
			e.draw();
		}
		else if(AU.range.inside(e.getCentroid2D()))
		{
			ofSetColor(ofColor::purple);
			e.draw();
		}
		else if(SA.range.inside(e.getCentroid2D()))
		{
			ofSetColor(ofColor::orange);
			e.draw();
		}
		else
		{
			ofSetColor(ofColor::grey);
			e.draw();
		}
		ofDrawCircle(e.getCentroid2D(), 5);
		
	}
	

	

	//ofDrawCircle(200, 200, 5);
	int count=0;
	for (auto e : lines)
	{
		if (e.inside(200, 200))
		{
			count++;
		}
	}

	ofSetColor(ofColor::white);
	string buf;
	//42 l‰nder, 6 kontinente
	//NA 9, SA 4, EU 7, AF 6, AU 4, AS 12
	//zeigt 43 wegen Bildrahmen, wenn MaxRadius zu groﬂ
	buf = "Lines: " + ofToString(lines.size()) + "\nOK:" + ofToString(count);
	ofDrawBitmapString(buf, 10, 20);
}


