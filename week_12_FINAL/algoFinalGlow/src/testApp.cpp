#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    vidPlayer.loadMovie("arthurCadreDanceSmall.mp4");
    vidPlayer.setSpeed(0.1);
    vidPlayer.play();
    vidPlayer.setVolume(0.0);
    flowSolver.setup(vidPlayer.getWidth(), vidPlayer.getHeight());
    
    //ofEnableAlphaBlending();
    ofSetBackgroundAuto(true);
    ofBackground(255);
    
    vidMult = ofGetWindowWidth() / vidPlayer.getWidth();
    
    myField.setup( ofGetWindowWidth(), ofGetWindowHeight(), 1 );
    
    particleList.clear();
    
    for( int i=0; i<10000; i++ ){
        addParticle();
    }
    
    vidPlayerPixels.allocate(vidPlayer.getWidth(), vidPlayer.getHeight(), OF_IMAGE_COLOR);
    
    frameNum = 0;
    
    sprite.loadImage("texture2.png");
    
    ofEnableBlendMode(OF_BLENDMODE_SUBTRACT);
    
}

//--------------------------------------------------------------
void testApp::addParticle() {
    Particle part;
    part.pos = ofVec2f( ofRandomWidth(), ofRandomHeight() );
    part.initPos = part.pos;
    
    particleList.push_back( part );
}

//--------------------------------------------------------------
void testApp::update(){
    
    frameNum ++;

    if (frameNum > 3600) {
        std::exit(1);
    }
    
    vidPlayer.setFrame(frameNum);

    bIsFrameNew = vidPlayer.isFrameNew();
    
    myField.setOptical( flowSolver, vidMult );
    //myField.update();
    
    for( int i=0; i<particleList.size(); i++ ){
        particleList[i].applyForce( myField.getForceAtPosition(particleList[i].pos ) * 1.0 );
        particleList[i].update();
    }
    
    if(bIsFrameNew){
        flowSolver.update(vidPlayer);
        vidPlayerPixels.clear();
        vidPlayerPixels.setFromPixels(vidPlayer.getPixels(), vidPlayer.getWidth(), vidPlayer.getHeight(), OF_IMAGE_COLOR);
    }
    
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
}

//--------------------------------------------------------------
void testApp::draw(){
    
        ofSetColor(255);
        ofFill();
    
        ofSetRectMode(OF_RECTMODE_CORNER);
        ofRectangle(0,0,ofGetWidth(),ofGetHeight());
        ofSetColor(255, 255, 255);
        
        //draw layers
        if (bDrawOrigVideo) {
            vidPlayer.draw(0, 0,vidPlayer.getWidth()*vidMult, vidPlayer.getHeight()*vidMult);
        }
        
        //myField.draw();
        ofSetColor(255);
    
        for( int i=0; i<particleList.size(); i++ ){
            particleList[i].draw( vidPlayerPixels, vidMult, sprite );
        }
    
        if (bDrawColorFlow) {
        flowSolver.drawColored(vidPlayer.getWidth()*vidMult, vidPlayer.getHeight()*vidMult, 10, 3);
        }
        
        cout << vidPlayer.getCurrentFrame() << endl;
        ofSaveFrame();

    
    
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