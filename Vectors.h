//
//  Vectors.h
//  CompGraphicsProj1
//
//  Created by Alex on 1/28/14.
//  Copyright (c) 2014 Lianet Cuella. All rights reserved.
//

/*
	I was having some issure determining which of the vector
	classes I would be able to import. For some reason I was
	not able to find one that met all my needs so I decided
	it would be easier to create a vector class that did all
	the things I needed it to and kept track of my vector
	points.

*/
#ifndef CompGraphicsProj1_Vectors_h
#define CompGraphicsProj1_Vectors_h

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <math.h>

class Vectors{
    private:
	float x;
	float y;
	float z;	
public:
	Vectors(float,float,float);
	Vectors();
	Vectors add(Vectors);
	float getX();
	float getY();
	float getZ();
	float dotProduct(Vectors);
	Vectors sub(Vectors);
	Vectors mul(float);
	float magnitude();
	Vectors pow(float);
	void setX(float);
	void setY(float);
	void setZ(float);

};

#endif
