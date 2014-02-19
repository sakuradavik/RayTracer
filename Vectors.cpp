//
//  Vectors.cpp
//  CompGraphicsProj1
//
//  Created by Alex on 1/28/14.
//  Copyright (c) 2014 Lianet Cuella. All rights reserved.
//

#include "Vectors.h"
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <math.h>

Vectors::Vectors(float x,float y,float z){
    this->x = x;
    this->y = y;
    this->z = z;
}
//If not values given make the point 0
Vectors::Vectors(){
    x=0;y=0;z=0;
}
//returns the sum of two vectors
Vectors Vectors::add(Vectors v){
    return Vectors((this->x+v.getX()),(this->y+v.getY()),(this->z+v.getZ()));
    
}
//returns x
float Vectors::getX(){
    return this->x;
}

//returns y
float Vectors::getY(){
    return this->y;
}

//returns z
float Vectors::getZ(){
    return this->z;
}

//reeturns the dot product of two vectors
float Vectors::dotProduct(Vectors v){
    return (((this->x)*v.getX())+((this->y)*v.getY())+((this->z)*v.getZ()));
}

//returns the subtraction of two vectors
Vectors Vectors::sub(Vectors v){
    return Vectors((this->x-v.getX()),(this->y-v.getY()),(this->z-v.getZ()));
}

//returns the multiplication of a vector by a magnitude
Vectors Vectors::mul(float b){
    return Vectors((this->x*b),(this->y*b),(this->z*b));
}
//returns the magnitude of this vector
float Vectors::magnitude(){
    return sqrtf(powf(this->x, 2)+powf(this->y, 2)+powf(this->z, 2));
}

//returns this vector raised to a power
Vectors Vectors::pow(float b){
    return Vectors(powf(this->x, b),powf(this->y, b),powf(this->z, 2));
}

//Setter methods for my three properties
void Vectors::setX(float x){this->x = x;}
void Vectors::setY(float y){this->y = y;}
void Vectors::setZ(float z){this->z = z;}

