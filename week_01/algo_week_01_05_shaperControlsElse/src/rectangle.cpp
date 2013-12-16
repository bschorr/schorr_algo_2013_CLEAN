//
//  rectangle.cpp
//  algo_week_01
//
//  Created by Bernardo Santos Schorr on 8/27/13.
//
//

#include "rectangle.h"

Rectangle::Rectangle() {
    
    ofSetRectMode(OF_RECTMODE_CENTER);
    
}

void Rectangle::update() {
    
  //  pos.x = pos.x + ofRandom(-10, 10);
    
}

void Rectangle::draw() {
    
    //(255, 255, 255);
    ofRect(pos.x, pos.y, size, size);
    
}


void Rectangle::xenoToPoint(float catchX, float catchY){
    
    float catchUpSpeed = 0.03f;
    
    pos.x = catchUpSpeed * catchX + (1-catchUpSpeed) * pos.x;
    pos.y = catchUpSpeed * catchY + (1-catchUpSpeed) * pos.y;
    
    size = ofDist(pos.x, pos.y, catchX, catchY) / 3;
    
    ofColor color;    
    color.setHsb(size, 255, 255);
    ofSetColor(color);
        
    
}
