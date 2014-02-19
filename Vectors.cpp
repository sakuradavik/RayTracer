//
//  Vectors.cpp
//  CompGraphicsProj1
//
//  Created by Alex on 1/28/14.
//  Copyright (c) 2014 Alex. All rights reserved.
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
Vectors::Vectors(){
    x=0;y=0;z=0;
}
Vectors Vectors::add(Vectors v){
    return Vectors((this->x+v.getX()),(this->y+v.getY()),(this->z+v.getZ()));
    
}
float Vectors::getX(){
    return this->x;
}
float Vectors::getY(){
    return this->y;
}
float Vectors::getZ(){
    return this->z;
}
float Vectors::dotProduct(Vectors v){
    return (((this->x)*v.getX())+((this->y)*v.getY())+((this->z)*v.getZ()));
}
Vectors Vectors::sub(Vectors v){
    return Vectors((this->x-v.getX()),(this->y-v.getY()),(this->z-v.getZ()));
}
Vectors Vectors::mul(float b){
    return Vectors((this->x*b),(this->y*b),(this->z*b));
}
float Vectors::magnitude(){
    return sqrtf(powf(this->x, 2)+powf(this->y, 2)+powf(this->z, 2));
}
Vectors Vectors::pow(float b){
    return Vectors(powf(this->x, b),powf(this->y, b),powf(this->z, 2));
}
void Vectors::setX(float x){this->x = x;}
void Vectors::setY(float y){this->y = y;}
void Vectors::setZ(float z){this->z = z;}

