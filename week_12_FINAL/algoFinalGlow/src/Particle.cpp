//
//  Particle.cpp
//  Forces
//
//  Created by Bernardo Schorr.
//
//  Based in code by Charlie Whitney.
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
    //pos += vel;
    
    if (pos.x >= ofGetWindowWidth()) pos.x = 1;
    if (pos.x <= 0) pos.x = ofGetWindowWidth()-1;
    
    if (pos.y >= ofGetWindowHeight()) pos.y = 1;
    if (pos.y <= 0) pos.x = ofGetWindowHeight()-1;
    
    vel*= 0.9;
    
    accel.set(0);
}

void Particle::draw( ofPixels &vidPlayerPixels, float &vidMult, ofImage &sprite ) {
    
    ofVec2f myPos = pos / vidMult;
    
    if (pos.x < 1) pos.x = 1;

    float size = vel.length();
    
    if (size > 2) {
        ofSetColor(ofRandom(255), ofRandom(255), ofRandom(255));
        sprite.draw(pos - (size*0.5), size*2, size*2);
    }
}