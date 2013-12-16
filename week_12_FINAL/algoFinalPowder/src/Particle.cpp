//
//  Particle.cpp
//  Forces
//
//  Created by Bernardo Schorr.
//
//  Based in code by Charlie Whitney.//
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
    
    vel*= 0.9;
    
    accel.set(0);
}

void Particle::draw( ofPixels &vidPlayerPixels, float &vidMult ) {
    
    ofVec2f myPos = pos / vidMult;
    
    if (pos.x < 1) pos.x = 1;
    
    ofColor myColor = vidPlayerPixels.getColor ( floor(myPos.x), floor(myPos.y) );
    ofSetColor( myColor );
    
    ofCircle( pos, 1 );
}