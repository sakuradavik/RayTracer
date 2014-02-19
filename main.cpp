//
//  main.cpp
//  CompGraphicsProj1
//
//  Created by Lianet Cuella on 1/28/14.
//  Copyright (c) 2014 Alex. All rights reserved.
//
#ifdef WIN32
#include <windows.h>
#endif

#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#endif

#include <iostream>
#include "Vectors.h"
#include "math.h"

using namespace std;

#define WIDTH 256
#define HEIGHT 256

struct rgbf{float r; float g; float b;};
void display();
void raytracer();

/*
 GLOBAL VARIABLES
 */

Vectors c1 (-60,-10,1); // Center of circle 1
Vectors c2 (75,-10,1); //Center of circle 2
Vectors LightDir (-2,1,4); //Light Vector
Vectors LookAt (0,0,-1); //Look at vector
float r1 = 50; //radius of circle 1
float r2 = 35; //radius of circle 2
rgbf pixels[WIDTH*HEIGHT];

int main(int argc, char *argv[])
{
    glutInit(&argc, argv); //starts GLUT
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE); //set display mode
    glutInitWindowSize(WIDTH,HEIGHT); // set size of window
    glutCreateWindow("CompGraphics Project 1"); //create the window with title as argument
    
    for(int i = 0; i < WIDTH*HEIGHT;i++){
        pixels[i].r = 0;
        pixels[i].g = 0;
        pixels[i].b = 0;
    }
    
    raytracer(); //does the raytracing
    glutDisplayFunc(display);//makes sure that glut uses my display method to display
    
    //NEED TO CALL WHEN USING GLUT
    glutMainLoop();
    
    return 0;
}

void display(){
    //clears our buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    //Clears my buffer by making everything black initially
    //try drawing using glDrawPixels
    glDrawPixels(WIDTH, HEIGHT, GL_RGB, GL_FLOAT, pixels);
    
    
    //switches the buffer into our window
    glutSwapBuffers();
    
}

Vectors shading(float discriminant, Vectors e, Vectors c, float r, Vectors kd){
    float t = (LookAt.mul(-1).dotProduct(e.sub(c)) + sqrtf(discriminant))/(LookAt.dotProduct(LookAt));
    if(t < 0)
        t = (LookAt.mul(-1).dotProduct(e.sub(c)) - sqrtf(discriminant))/(LookAt.dotProduct(LookAt));
    Vectors normal = e.sub(LookAt.mul(t)).sub(c).mul(1/r);
    Vectors temp = LookAt.add(LightDir);
    Vectors h = LookAt.add(LightDir).mul(1/temp.magnitude());
    
    float max1 = normal.dotProduct(LightDir);
    float max2 = normal.dotProduct(h);
    if(max1 < 0)
        max1 = 0;
    if(max2 < 0)
        max2 = 0;
    
    
    Vectors ka (.8,.4,.4);
    Vectors ks (1,1,1);
    Vectors La;
    Vectors Ld;
    Vectors Ls;
    La = ka.mul(.3);
    Ld = kd.mul(.5).mul(max1);
    Ls = ks.mul(.4).mul(powf(max2, 10));
    
    return La.add(Ld).add(Ls);
    
}

void raytracer(){
    
    for(int x = 0; x < WIDTH; x++){
        for(int y = 0; y < HEIGHT;y++){
            
            float u = (-128) + (256)*(x+0.5)/(WIDTH);
            float v = (-128) + (256)*(y+0.5)/(HEIGHT);
            
            //Hard code for now the values
            Vectors vecU (0,1,0);
            
            //defing vecU's values
            if(LookAt.getX() == 0 && LookAt.getY() == 0){
                vecU.setZ(0);
                vecU.setX(0);
                vecU.setY(1);
            }
            else{
                vecU.setX(LookAt.getY()*(-1));
                vecU.setY(LookAt.getX()*(-1));
                vecU.setZ(LookAt.getZ()*(-1));
            }
            
            float x1 = (LookAt.getY()*vecU.getZ())-(LookAt.getZ()*vecU.getY());
            float y1 = ((LookAt.getX()*vecU.getZ())-(LookAt.getZ()*vecU.getX()))*(-1);
            float z1 = (LookAt.getX()*vecU.getY())-(LookAt.getY()*vecU.getX());
            
            if(y1 == -0 )
                y1 = 0;
            
            
            Vectors vecV (x1,y1,z1);
            //Vectors vecV (1,0,0);
            Vectors e (0,0,-1);
            vecU = vecU.mul(u);
            vecV = vecV.mul(v);
            e = e.add(vecU);
            e = e.add(vecV);
            
            //if hits first circle
            float A = powf(LookAt.dotProduct(e.sub(c1)),2);
            float B = (LookAt.dotProduct(LookAt))*(e.sub(c1).dotProduct(e.sub(c1))-powf(r1,2));
            float discriminant1 = A-B;
            // cout<<discriminant1<<endl;
            
            //if hits second circle
            float A2 = powf(LookAt.dotProduct(e.sub(c2)),2);
            float B2 = (LookAt.dotProduct(LookAt))*(e.sub(c2).dotProduct(e.sub(c2))-powf(r2,2));
            float discriminant2 = A2-B2;
            
            if(discriminant1 >= 0){
                Vectors kd (0.5f,0.25f,0.6f);
                Vectors shade = shading(discriminant1,e,c1,r1,kd);
                pixels[(WIDTH*x)+y].r = shade.getX();
                pixels[(WIDTH*x)+y].g = shade.getY();
                pixels[(WIDTH*x)+y].b = shade.getZ();
            }
            if(discriminant2 >= 0){
                Vectors kd (0,0.4f,.8f);
                Vectors shade = shading(discriminant2,e,c2,r2,kd);
                pixels[(WIDTH*x)+y].r = shade.getX();
                pixels[(WIDTH*x)+y].g = shade.getY();
                pixels[(WIDTH*x)+y].b = shade.getZ();
            }
            
            
        }
    }
    
}




