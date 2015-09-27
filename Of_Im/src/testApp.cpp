#include "testApp.h"

using namespace ofxCv;
using namespace cv;

float minEye,
      maxEye;

void testApp::setup() {
	ofSetVerticalSync(true);
	cam.initGrabber(640, 480);
	
	tracker.setup();
	tracker.setRescale(.5);
    
    verdana14.loadFont("verdana.ttf", 7, true, true);
    verdana14.setLineHeight(18.0f);
    verdana14.setLetterSpacing(1.037);
    
    minEye = 100.0;
    maxEye = 0.0;
    
    normScale = 6;
    
}

void testApp::update() {
	cam.update();
	if(cam.isFrameNew()) {
		if(tracker.update(toCv(cam))) {
			classifier.classify(tracker);
		}
	}
}

void testApp::draw() {
	ofSetColor(255);
	cam.draw(0, 0);
	tracker.draw();
    
    vector<ofVec2f> imagePoints  = tracker.getImagePoints();
    
//    Global Scale Var
    scaleVar = tracker.getScale();
//    cout << scaleVar << "   ";
    
    float currentScale = scaleVar / normScale;
//        cout << currentScale << "   ";
    
//    Calculate the feature areas
    
    if(tracker.getFound()) {
        
//      Track + Quanitify Mouth
        ofVec2f
        mouthUpper  = tracker.getImagePoint(51),
        mouthBottom = tracker.getImagePoint(57),
        mouthLeft   = tracker.getImagePoint(48),
        mouthRight  = tracker.getImagePoint(54);
        
        ofPolyline outerMouth = tracker.getImageFeature(ofxFaceTracker::OUTER_MOUTH);
        
        ofVec2f outerMouthCenter = outerMouth.getBoundingBox().getCenter();
        
        float mouthHorzRadius = (outerMouthCenter.distance(mouthLeft) + outerMouthCenter.distance(mouthRight)) / 2;
        float mouthVertRadius = ((outerMouthCenter.distance(mouthBottom) + outerMouthCenter.distance(mouthUpper)) / 2) * currentScale;
        float mouthVertNorm = ofMap(mouthVertRadius, 10, 30, 0, 1);
        
//        string printMin = ofToString(mouthVertRadius);
////        cout << printMin << "  ";
        
//      Track + Quanitify Eyes
        ofVec2f
        leftOuter = tracker.getImagePoint(36),
        leftInner = tracker.getImagePoint(39),
        rightInner = tracker.getImagePoint(42),
        rightOuter = tracker.getImagePoint(45);

        ofPolyline leftEye = tracker.getImageFeature(ofxFaceTracker::LEFT_EYE);
        ofPolyline rightEye = tracker.getImageFeature(ofxFaceTracker::RIGHT_EYE);
        
        ofVec2f leftCenter = leftEye.getBoundingBox().getCenter();
        ofVec2f rightCenter = rightEye.getBoundingBox().getCenter();
        
        float leftRadius = (leftCenter.distance(leftInner) + leftCenter.distance(leftOuter)) / 2;
        float rightRadius = (rightCenter.distance(rightInner) + rightCenter.distance(rightOuter)) / 2;
        float eyeAvg = ((leftRadius + rightRadius) / 2) * currentScale;
//        float eyeAvgNorm = ofMap(eyeAvg, , 30, 0, 1);
        
        string printMin = ofToString(eyeAvg);
                cout << printMin << "  ";
    
        
        ofVec2f
        leftOuterObj = tracker.getObjectPoint(36),
        leftInnerObj = tracker.getObjectPoint(39),
        rightInnerObj = tracker.getObjectPoint(42),
        rightOuterObj = tracker.getObjectPoint(45);
        
        ofVec3f upperBorder(0, -3.5, 0), lowerBorder(0, 2.5, 0);
        ofVec3f leftDirection(-1, 0, 0), rightDirection(+1, 0, 0);
        float innerBorder = 1.5, outerBorder = 2.5;
        
        ofMesh leftRect, rightRect;
        leftRect.setMode(OF_PRIMITIVE_LINE_LOOP);
        leftRect.addVertex(leftOuterObj + upperBorder + leftDirection * outerBorder);
        leftRect.addVertex(leftInnerObj + upperBorder + rightDirection * innerBorder);
        leftRect.addVertex(leftInnerObj + lowerBorder + rightDirection * innerBorder);
        leftRect.addVertex(leftOuterObj + lowerBorder + leftDirection * outerBorder);
        rightRect.setMode(OF_PRIMITIVE_LINE_LOOP);
        rightRect.addVertex(rightInnerObj+ upperBorder + leftDirection * innerBorder);
        rightRect.addVertex(rightOuterObj + upperBorder + rightDirection * outerBorder);
        rightRect.addVertex(rightOuterObj + lowerBorder + rightDirection * outerBorder);
        rightRect.addVertex(rightInnerObj + lowerBorder + leftDirection * innerBorder);
        
        for( int i = 0; i < imagePoints.size(); i++){
            //        ofCircle(imagePoints[i].x,imagePoints[i].y,1);
            verdana14.drawString(ofToString(i), imagePoints[i].x,imagePoints[i].y);
        }
        
        
        int w = 100, h = 12;
        ofPushStyle();
        ofPushMatrix();
        ofTranslate(5, 10);
        int n = classifier.size();
        int primary = classifier.getPrimaryExpression();
        for(int i = 0; i < n; i++){
            ofSetColor(i == primary ? ofColor::red : ofColor::black);
            ofRect(0, 0, w * classifier.getProbability(i) + .5, h);
            ofSetColor(255);
            ofDrawBitmapString(classifier.getDescription(i), 5, 9);
            ofTranslate(0, h + 5);
        }
        ofPopMatrix();
        ofPopStyle();

        
    }
    
	
	ofDrawBitmapString(ofToString((int) ofGetFrameRate()), ofGetWidth() - 20, ofGetHeight() - 10);
	drawHighlightString(
		string() +
		"r - reset\n" +
		"e - add expression\n" +
		"a - add sample\n" +
		"s - save expressions\n"
		"l - load expressions",
		14, ofGetHeight() - 7 * 12);
    
}



void testApp::joy() {
    //This function returns a normalized float determiniting the faces happiness profile
}

void testApp::surprise() {
    //This function returns a normalized float determiniting the faces happiness profile
}

void testApp::sadness() {
    //This function returns a normalized float determiniting the faces happiness profile
}

void testApp::contempt() {
    //This function returns a normalized float determiniting the faces happiness profile
}

void testApp::disgust() {
    //This function returns a normalized float determiniting the faces happiness profile
}

void testApp::fear() {
    //This function returns a normalized float determiniting the faces happiness profile
}

void testApp::anger() {
    //This function returns a normalized float determiniting the faces happiness profile
}


void testApp::keyPressed(int key) {
	if(key == 'r') {
		tracker.reset();
		classifier.reset();
	}
	if(key == 'e') {
		classifier.addExpression();
	}
	if(key == 'a') {
		classifier.addSample(tracker);
	}
	if(key == 's') {
		classifier.save("expressions");
	}
	if(key == 'l') {
		classifier.load("expressions");
	}
}