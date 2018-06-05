#pragma once


class kontinent {

public:
	void set(int _value, float xpos, float ypos, float width, float height)
	{
		value = _value;
		range = ofRectangle(xpos, ypos, width, height);
	}
	void add(ofPolyline country)
	{
		countries.push_back(country);
	}
	void check()
	{
	}

	bool full = false;
	int value;
	vector<ofPolyline> countries;
	ofRectangle range;

};