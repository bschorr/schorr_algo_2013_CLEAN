//
//  Particle.h
//  VectorField
//
//  Created by Charlie Whitney on 10/7/13.
//
//

#pragma once

#include "ofMain.h"

class Particle {
  public:
    Particle();
    
    ofVec2f pos;
    ofVec2f initPos;
    ofVec2f vel;
    ofVec2f accel;
    float mass;
    
    void applyForce( ofVec2f force );
    void applyReturnForce();
    void update();
    void draw( ofPixels &vidPlayerPixels, float &vidMult, ofImage &sprite );
    float size;
    ofColor color;
};