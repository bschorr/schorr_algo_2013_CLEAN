#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    vidPlayer.loadMovie("arthurCadreDanceSmall.mp4");
    vidPlayer.setSpeed(0.1);
    vidPlayer.play();
    vidPlayer.setVolume(0.0);
    flowSolver.setup(vidPlayer.getWidth(), vidPlayer.getHeight());
    
    ofEnableAlphaBlending();
    ofSetBackgroundAuto(true);
    ofBackground(0);
    
    vidMult = ofGetWindowWidth() / vidPlayer.getWidth();
    
    myField.setup( ofGetWindowWidth(), ofGetWindowHeight(), 10 );
    
    vidPlayerPixels.allocate(vidPlayer.getWidth(), vidPlayer.getHeight(), OF_IMAGE_COLOR);
    
    frameNum = 0;
    
    bDrawColorFlow = true;
    
    //fluid simulations
    
    width = ofGetWindowWidth();
    height = ofGetWindowHeight();
    
    // Initial Allocation
    //
    fluid.allocate(width, height, 0.5);
    
    // Seting the gravity set up & injecting the background image
    //
    fluid.dissipation = 0.8;
    fluid.velocityDissipation = 0.99;
    
    fluid.setGravity(ofVec2f(0.0,0.0));
    //    fluid.setGravity(ofVec2f(0.0,0.0098));

}

//--------------------------------------------------------------
void testApp::update(){
    
    frameNum ++;
    
    if (frameNum > 3600) {
        std::exit(1);
    }
    
    vidPlayer.setFrame(frameNum);

    //vidPlayer.update();
    
    bIsFrameNew = vidPlayer.isFrameNew();
    
    myField.setOptical( flowSolver, vidMult );
    

    
    if(bIsFrameNew){
        flowSolver.update(vidPlayer);
        vidPlayerPixels.clear();
        vidPlayerPixels.setFromPixels(vidPlayer.getPixels(), vidPlayer.getWidth(), vidPlayer.getHeight(), OF_IMAGE_COLOR);
        
        for( int y=0; y<height; y+=10){
            for( int x=0; x<width; x+=10){
                ofVec2f force = myField.getForceAtPosition( ofVec2f(x, y) );
                
                if (force.lengthSquared() > 1){
                fluid.addTemporalForce(ofPoint(x, y), force*5.0, ofFloatColor(0.8, 0.5, 0.1), force.length()*0.5);
                }
            }
        }
        
        fluid.update();
        
    }
    
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
}

//--------------------------------------------------------------
void testApp::draw(){
    
    ofBackground(0);
    
    //flowSolver.drawColored(width, height);
    
    //ofSetColor(255);
    fluid.draw();

    //vidPlayer.draw(0, 0,vidPlayer.getWidth()*vidMult, vidPlayer.getHeight()*vidMult);
    
    //cout << vidPlayer.getCurrentFrame() << endl;
    
    //String
    //ofSaveImage( );
    ofSaveScreen(ofToString(vidPlayer.getCurrentFrame()) + ".png");

    
    
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
    switch (key)
    {
        case 'o':
            bDrawOrigVideo = !bDrawOrigVideo;
            break;
        case 'f':
            bDrawColorFlow = !bDrawColorFlow;
            break;
    }
    
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}