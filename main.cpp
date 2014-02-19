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

//struct that I created for the purpose of storing my 
//rgb values
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

//Using the shading equations and using the vectors e(something I found), the center, the radius and a
//preset kd (diffuse lighting color)
Vectors shading(float discriminant, Vectors e, Vectors c, float r, Vectors kd){
    //find t
    float t = (LookAt.mul(-1).dotProduct(e.sub(c)) + sqrtf(discriminant))/(LookAt.dotProduct(LookAt));
    if(t < 0)
        t = (LookAt.mul(-1).dotProduct(e.sub(c)) - sqrtf(discriminant))/(LookAt.dotProduct(LookAt));

    //find the normal of the point we intersect
    Vectors normal = e.sub(LookAt.mul(t)).sub(c).mul(1/r);
    Vectors temp = LookAt.add(LightDir);
    Vectors h = LookAt.add(LightDir).mul(1/temp.magnitude());

    //Find the max value between the normal and lightDirection 
    float max1 = normal.dotProduct(LightDir);
    //Find the max between the normal and h
    float max2 = normal.dotProduct(h);

    //Since light in real life has not negative value, our
    //max vaues can only be positive
    if(max1 < 0)
        max1 = 0;
    if(max2 < 0)
        max2 = 0;
    
    //arbritraru values of ka (ambiance lighting), ks (specular lighting)
    Vectors ka (.8,.4,.4);
    Vectors ks (1,1,1);
    Vectors La;
    Vectors Ld;
    Vectors Ls;
    La = ka.mul(.3);
    Ld = kd.mul(.5).mul(max1);
    Ls = ks.mul(.4).mul(powf(max2, 10));
    
    //returns the color of the pixel with its ambiance, diffuse and specular shading
    return La.add(Ld).add(Ls);
    
}

//One hit ray tracer
void raytracer(){
    
    for(int x = 0; x < WIDTH; x++){
        for(int y = 0; y < HEIGHT;y++){
            
            //Change the coordinate system of my buffer so that it goes from -128 to positive 128
            float u = (-128) + (256)*(x+0.5)/(WIDTH);
            float v = (-128) + (256)*(y+0.5)/(HEIGHT);
            
            //arbitrary vector who's dotProduct with the LookAtVector is 0
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
            //finding abother vector who is perpendicular to U and the LookAt vector
            float x1 = (LookAt.getY()*vecU.getZ())-(LookAt.getZ()*vecU.getY());
            float y1 = ((LookAt.getX()*vecU.getZ())-(LookAt.getZ()*vecU.getX()))*(-1);
            float z1 = (LookAt.getX()*vecU.getY())-(LookAt.getY()*vecU.getX());
            
            if(y1 == -0 )
                y1 = 0;
            
            /*
                Now that we found a U,V an have the look at, we can create a local axis around
                an arbitrary point e.
            */
            Vectors vecV (x1,y1,z1);
            //pick an arbitrary e
            Vectors e (0,0,-1);
            vecU = vecU.mul(u);
            vecV = vecV.mul(v);
            e = e.add(vecU);
            e = e.add(vecV);
            
            //Determining the discriminant for both circles

            //if hits first circle
            float A = powf(LookAt.dotProduct(e.sub(c1)),2);
            float B = (LookAt.dotProduct(LookAt))*(e.sub(c1).dotProduct(e.sub(c1))-powf(r1,2));
            float discriminant1 = A-B;
            
            //if hits second circle
            float A2 = powf(LookAt.dotProduct(e.sub(c2)),2);
            float B2 = (LookAt.dotProduct(LookAt))*(e.sub(c2).dotProduct(e.sub(c2))-powf(r2,2));
            float discriminant2 = A2-B2;
            
            //if discriminant >= 0 then we have hit our circle at least once
            if(discriminant1 >= 0){
                //color of first circle
                Vectors kd (0.5f,0.25f,0.6f);
                //get the shading of circles
                Vectors shade = shading(discriminant1,e,c1,r1,kd);
                pixels[(WIDTH*x)+y].r = shade.getX();
                pixels[(WIDTH*x)+y].g = shade.getY();
                pixels[(WIDTH*x)+y].b = shade.getZ();
            }
            if(discriminant2 >= 0){
                //color of second circle
                Vectors kd (0,0.4f,.8f);
                //shading of the circle
                Vectors shade = shading(discriminant2,e,c2,r2,kd);
                pixels[(WIDTH*x)+y].r = shade.getX();
                pixels[(WIDTH*x)+y].g = shade.getY();
                pixels[(WIDTH*x)+y].b = shade.getZ();
            }
            
            
        }
    }
    
}




