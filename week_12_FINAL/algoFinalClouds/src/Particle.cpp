//
//  Particle.cpp
//  Forces
//
//  Created by bernardo Schorr.
//
//  Based in code by Charlie Whitney on 9/30/13.
//
//

#include "Particle.h"
#include "testApp.h"

Particle::Particle() {
    mass = 1.0;
    size = ofRandom(5, 40);
    
    float choice = ofRandomf();
    
    if (choice > 0) {
        color = ofColor (255, 0, 0);
    } else {
        color = ofColor (255, 255, 0);
    }
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
    
    vel*= 0.6;
    
    accel.set(0);
}

void Particle::draw( ofPixels &vidPlayerPixels, float &vidMult, ofImage &sprite ) {
    
    ofVec2f myPos = pos / vidMult;
    
    if (pos.x < 1) pos.x = 1;

    float curVel = vel.length();
    
    color.a = ofMap(curVel, 0, 30, 0, 255);
    ofSetColor( color );
    
    if (curVel > 0) {
        sprite.draw(pos - (size*0.5), size, size);
    }
}