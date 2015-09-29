#pragma once

#include "ofMain.h"
#include "ofxFaceTracker.h"

class testApp : public ofBaseApp {
public:
	void setup();
	void update();
	void draw();
    void joy();
    void surprise();
    void sadness();
    void contempt();
    void disgust();
    void fear();
    void anger();
	void keyPressed(int key);
    
    float minF(float num);
    float maxF(float num);
	
	ofVideoGrabber cam;
	ofxFaceTracker tracker;
	ExpressionClassifier classifier;
    ofTrueTypeFont	verdana14;
    
    float scaleVar;
    float normScale;
    
};
