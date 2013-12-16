#pragma once

#include "ofMain.h"
#include "ofxOpticalFlowFarneback.h"
#include "ofxOpticalFlowLK.h"
#include "FlowField.h"
#include "Particle.h"


class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
        void addParticle();
		
    
    ofVideoPlayer vidPlayer;
    ofxOpticalFlowFarneback flowSolver;
    
    ofPixels vidPlayerPixels;
    
    bool bIsFrameNew;
    bool bDrawOrigVideo;
    bool bDrawColorFlow;
    
    float vidMult;
    
    int frameNum;
    
    FlowField           myField;
    vector<Particle>    particleList;
    
};
