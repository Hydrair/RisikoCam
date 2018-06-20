#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	cam.setup(winWidth, winHeigth);
	map1.load("images/mapworldsmall4.jpg");
	map2 = ofxCv::toCv(map1);

	figureBG.allocate(winWidth, winHeigth, OF_IMAGE_GRAYSCALE);
	mapBG.allocate(winWidth, winHeigth, OF_IMAGE_COLOR);
	compare.allocate(winWidth, winHeigth, OF_IMAGE_COLOR);

	kontInit();
	guiInit();

	cam.update();

	player[0] = Player(137, 120, 30, 160, 255, 250);
	player[1] = Player(95, 31, 30, 120, 255, 250);
	player[2] = Player(0, 200, 30, 20, 255, 250);
	player[3] = Player(20, 200, 30, 40, 255, 250);
	player[4] = Player(0, 200, 0, 255, 255, 30);
}

//--------------------------------------------------------------
void ofApp::update(){
	cam.update();
	olddiff = cam.getPixels();

	findCountries();


	
}

//--------------------------------------------------------------
void ofApp::draw(){
	if (toggleCam)
	{
		ofSetColor(255, 255, 255, 128);
		cam.draw(0, 0);
		ofSetColor(255, 255, 255, 255);
	}
	drawCountries();
	drawFigures();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	printf("KEY\n");
	if (key == '0')
	{
		ofPixelsRef pixels = cam.getPixelsRef();
		compare.setFromPixels(pixels);

	}

	if (key == 'q')
	{
		ofPixelsRef pixels = cam.getPixelsRef();
		mapBG.setFromPixels(pixels);
	}
	if (key == 'w')
	{
		if (resetBackground) {
			background.reset();
			resetBackground = false;
		}
		//figureBG.allocate(640, 480, OF_IMAGE_GRAYSCALE);
		background.setIgnoreForeground(true);
		background.setLearningTime(learningTime);
		background.setThresholdValue(thresholdValue);
		background.update(mapBG, figureBG);
		figureBG.update();

		figureContour.setMinAreaRadius(minArea); //5
		figureContour.setMaxAreaRadius(maxArea); //15
		figureContour.setThreshold(threshold);
		figureContour.findContours(figureBG);
		figureContour.setFindHoles(holes);
		figureLines = figureContour.getPolylines();

		/////////////////////////////////////////////////////
		player[0] = Player(137, 120, 30, 160, 255, 250);
		player[1] = Player(95, 31, 30, 120, 255, 250);
		player[2] = Player(0, 200, 30, 20, 255, 250);
		player[3] = Player(20, 200, 30, 40, 255, 250);
		player[4] = Player(0, 200, 0, 255, 255, 30);
		for (auto e : figureLines)
		{
			ofColor farbe = olddiff.getColor(e.getCentroid2D().x, e.getCentroid2D().y);

			Figur figTemp(farbe, e.getCentroid2D().x, e.getCentroid2D().y);

			for (int i = 0; i < 5; i++)
			{
				if (player[i].addFigur(figTemp))
				{
					ofSetColor(olddiff.getColor(e.getCentroid2D().x, e.getCentroid2D().y));
					ofDrawCircle(e.getCentroid2D(), 10);
				}
				printf("Player %d : %d\n", i, player[i].getCount());

			}

		}
		////////////////////////////////////////////////////////
	}
	if (key == 'r')
	{
		background.reset();

	}
	if (key == 't')
	{
		toggleCam = !toggleCam;
	}
}


void ofApp::kontInit()
{
	NA.set(5, 0, 0, map2.cols*0.38, map2.rows*0.5);
	SA.set(2, 0, map2.rows*0.5, map2.cols*0.38, map2.rows*0.5);
	EU.set(5, map2.cols*0.38, 0, map2.cols*0.17, map2.rows*0.48);
	AF.set(3, map2.cols*0.38, map2.rows*0.55, map2.cols*0.22, map2.rows*0.5);
	AS.set(7, map2.cols*0.55, 0, map2.cols*0.5, map2.rows*0.6);
	AU.set(2, map2.cols*0.65, map2.rows*0.6, map2.cols*0.5, map2.rows*0.5);
}

void ofApp::findCountries()
{

	mapContour.setMinAreaRadius(10);
	mapContour.setMaxAreaRadius(400);
	mapContour.setThreshold(5);
	mapContour.findContours(map2);
	mapContour.setFindHoles(1);
	mapLines = mapContour.getPolylines();
}

void ofApp::drawCountries()
{
	ofSetColor(ofColor::red);
	for (auto e : mapLines)
	{
		if (NA.range.inside(e.getCentroid2D()))
		{
			ofSetColor(ofColor::yellow);
			e.draw();
		}
		else if (EU.range.inside(e.getCentroid2D()))
		{
			ofSetColor(ofColor::blue);
			e.draw();
		}
		else if (AF.range.inside(e.getCentroid2D()))
		{
			ofSetColor(ofColor::red);
			e.draw();
		}
		else if (AS.range.inside(e.getCentroid2D()))
		{
			ofSetColor(ofColor::green);
			e.draw();
		}
		else if (AU.range.inside(e.getCentroid2D()))
		{
			ofSetColor(ofColor::purple);
			e.draw();
		}
		else if (SA.range.inside(e.getCentroid2D()))
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

	int count = 0;
	for (auto e : mapLines)
	{
		if (e.inside(200, 200))
		{
			count++;
		}
	}

	ofSetColor(ofColor::white);
	string buf;
	//42 l�nder, 6 kontinente
	//NA 9, SA 4, EU 7, AF 6, AU 4, AS 12
	//zeigt 43 wegen Bildrahmen, wenn MaxRadius zu groß
	buf = "mapLines: " + ofToString(mapLines.size()) + "\nOK:" + ofToString(count);
	ofDrawBitmapString(buf, 10, 20);
}

void ofApp::guiInit()
{
	gui.setup();
	gui.add(resetBackground.set("Reset Background", false));
	gui.add(learningTime.set("Learning Time", 0, 0, 100));
	gui.add(thresholdValue.set("Threshold ValueBG", 30, 0, 255));
	gui.add(minArea.set("Min area", 10, 1, 100));
	gui.add(maxArea.set("Max area", 40, 1, 500));
	gui.add(threshold.set("Threshold", 128, 0, 255));
	gui.add(holes.set("Holes", false));
}

void ofApp::drawFigures()
{
	/*mapBG.draw(0, 480, 640, 480);
	compare.draw(0, 0);
	*/
	ofSetColor(255, 255, 255, 70);
	mapBG.draw(0, 0, 1600, 1200);
	if (figureBG.isAllocated()) {
		
		figureBG.draw(0,0,1600,1200);
		
	}
	//player[0] = Player(137, 120, 30, 160, 255, 250);
	//player[1] = Player(95, 31, 30, 120, 255, 250);
	//player[2] = Player(0, 200, 30, 20, 255, 250);
	//player[3] = Player(20, 200, 30, 40, 255, 250);
	//player[4] = Player(0, 200, 0, 255, 255, 30);
	//for (auto e : figureLines)
	//{
	//	ofColor farbe = olddiff.getColor(e.getCentroid2D().x, e.getCentroid2D().y);
	//		
	//	Figur figTemp(farbe, e.getCentroid2D().x, e.getCentroid2D().y);

	//	for (int i = 0; i < 5; i++)
	//	{
	//		if (player[i].addFigur(figTemp))
	//		{
	//			ofSetColor(olddiff.getColor(e.getCentroid2D().x, e.getCentroid2D().y));

	//			ofDrawCircle(e.getCentroid2D()/* + ofPoint(640, 480)*/, 10);
	//		}
	//		printf("Player %d : %d\n", i,player[i].getCount());

	//	}
	//	
	//}

	ofSetColor(ofColor::white);
	gui.draw();
}

int score()
{
	return 0;
}