//
//  Ball.h
//  algo_week_02_02
//
//  Created by Bernardo Santos Schorr on 9/3/13.
//
//

#pragma once
#include "ofMain.h"

class Ball {
public:
    
    Ball();
    void update();
    void draw();
    
    ofVec3f pos;
    float xVelocity;
    float yVelocity;
    float zVelocity;
    
    float boxSize = 800;
    
    
    
    
};