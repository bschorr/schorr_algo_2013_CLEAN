//
//  FlowField.cpp
//  VectorField
//
//  Created by Bernardo Schorr.
//
//  Based in code by Charlie Whitney.
//
//

#include "FlowField.h"

FlowField::FlowField() {
    
}

void FlowField::setup( int width, int height, int res ) {
    fieldWidth = width;
    fieldHeight = height;
    resolution = res;
    
    int cols = fieldWidth / resolution;
    int rows = fieldHeight / resolution;
    
    for( int y=0; y<rows; y++){
        VectorList myList;
        flowList.push_back( myList );
        
        for( int x=0; x<cols; x++){
            ofVec2f dir(0,0);
            flowList[y].push_back( dir );
        }
    }
}

void FlowField::setOptical( ofxOpticalFlowFarneback &flowSolver, float &vidMult ) {
    for( int y=0; y<flowList.size(); y++){
        for( int x=0; x<flowList[y].size(); x++){
            
            float fx = (x * resolution) / vidMult;
            float fy = (y * resolution) / vidMult;
            
            flowSolver.getVelAtPixel(fx, fy);
            
            ofVec2f velAtPoint = flowSolver.getVelAtPixel(fx, fy);            flowList[y][x].set( velAtPoint );
        }
    }
}

void FlowField::update() {
    for( int y=0; y<flowList.size(); y++){
        for( int x=0; x<flowList[y].size(); x++){
//            flowList[y][x] *= 0.99;
            
            // don't let the force get too small
            
            float vecSize =flowList[y][x].length();
            
            if( vecSize < 1.0){
                flowList[y][x].normalize();
            }else if( vecSize > 20.0 ){
                flowList[y][x].normalize() * 20.0;
            }
            
            // lets also limit the max
        }
    }
}

ofVec2f FlowField::getForceAtPosition( ofVec2f pos ){
    float pctX = pos.x / fieldWidth;
    float pctY = pos.y / fieldHeight;
    
    int cols = fieldWidth / resolution;
    int rows = fieldHeight / resolution;
    
    int xVal = ofClamp( pctX * cols, 0, cols-1 );
    int yVal = ofClamp( pctY * rows, 0, rows-1 );
    
    ofVec2f newPos;
    newPos.set( flowList[yVal][xVal] );
    
    return newPos;
}

void FlowField::draw() {
    for( int y=0; y<flowList.size(); y++){
        for( int x=0; x<flowList[y].size(); x++){
            ofVec2f np( x*resolution, y*resolution );
            drawVectorAt( flowList[y][x], np, flowList[y][x].length() );
        }
    }
}

void FlowField::drawVectorAt( const ofVec2f &vec, const ofVec2f &pos, const float &strength ) {
    ofVec2f np = pos;
    drawVector( np, np + vec.normalized() * strength, 5, 3 );
}

void FlowField::drawVector( const ofVec3f &start, const ofVec3f &end, float headLength, float headRadius ) {
	const int NUM_SEGMENTS = 32;
	float lineVerts[3*2];
	ofVec3f coneVerts[NUM_SEGMENTS+2];
	glEnableClientState( GL_VERTEX_ARRAY );
	glVertexPointer( 3, GL_FLOAT, 0, lineVerts );
	lineVerts[0] = start.x; lineVerts[1] = start.y; lineVerts[2] = start.z;
	lineVerts[3] = end.x; lineVerts[4] = end.y; lineVerts[5] = end.z;
	glDrawArrays( GL_LINES, 0, 2 );
	
	// Draw the cone
	ofVec3f axis = ( end - start ).normalized();
    ofVec3f temp = ( axis.dot( ofVec3f(0,1,0) ) > 0.999f ) ? axis.crossed( ofVec3f(1,0,0) ) : axis.crossed( ofVec3f(0,1,0) );
	ofVec3f left = ofVec3f(axis.crossed( temp )).normalized();
	ofVec3f up = axis.crossed( left ).normalized();
    
	glVertexPointer( 3, GL_FLOAT, 0, &coneVerts[0].x );
	coneVerts[0] = ofVec3f( end + axis * headLength );
	for( int s = 0; s <= NUM_SEGMENTS; ++s ) {
		float t = (float)s / (float)NUM_SEGMENTS;
		coneVerts[s+1] = ofVec3f( end + left * headRadius * cos( t * 2.0f * 3.14159f )
                                 + up * headRadius * sin( t * 2.0f * 3.14159f ) );
	}
	glDrawArrays( GL_TRIANGLE_FAN, 0, NUM_SEGMENTS+2 );
    
	// draw the cap
	glVertexPointer( 3, GL_FLOAT, 0, &coneVerts[0].x );
	coneVerts[0] = end;
	for( int s = 0; s <= NUM_SEGMENTS; ++s ) {
		float t = s / (float)NUM_SEGMENTS;
		coneVerts[s+1] = ofVec3f( end - left * headRadius * (float)cos( t * 2 * 3.14159f )
                                 + up * headRadius * (float)sin( t * 2 * 3.14159f ) );
	}
	glDrawArrays( GL_TRIANGLE_FAN, 0, NUM_SEGMENTS+2 );
    
	glDisableClientState( GL_VERTEX_ARRAY );
}