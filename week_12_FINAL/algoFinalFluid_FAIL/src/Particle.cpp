//
//  Particle.cpp
//  Forces
//
//  Created by Charlie Whitney on 9/30/13.
//
//

#include "Particle.h"
#include "testApp.h"

Particle::Particle() {
    mass = 1.0;
}

void Particle::applyForce(ofVec2f force){
    accel += (force / mass);
}

void Particle::applyReturnForce(){
    ofVec2f returnForce = (initPos - pos) * 0.01;
    accel += returnForce;
}

void Particle::update(){

    applyReturnForce();
    
    vel += accel;
    pos += vel;
    
//    if (pos.x >= ofGetWindowWidth()) pos.x = 1;
//    if (pos.x <= 0) pos.x = ofGetWindowWidth()-1;
//    
//    if (pos.y >= ofGetWindowHeight()) pos.y = 1;
//    if (pos.y <= 0) pos.x = ofGetWindowHeight()-1;
    
    vel*= 0.9;
    
    accel.set(0);
}

void Particle::draw( ofPixels &vidPlayerPixels, float &vidMult ) {
    
    ofVec2f myPos = pos / vidMult;
    
    if (pos.x < 1) pos.x = 1;
    
    ofColor myColor = vidPlayerPixels.getColor ( floor(myPos.x), floor(myPos.y) );
    ofSetColor( myColor );
    
//    if (vel.lengthSquared() > 100) {
//        ofSetColor(255);
//    } else {
//        ofSetColor (ofMap (vel.length(), 0, 10, 0, 255));
//    }
    
    ofCircle( pos, 1 );
}