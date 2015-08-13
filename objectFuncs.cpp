// Functions that can be done on the object structure

#include "object.h"


//Elastic Collision

void collide(Object& a, Object& b){
    double temp1 = (a.velocity*(a.mass-b.mass)+2*b.mass*b.velocity)/(a.mass+b.mass);
    double temp2 = (b.velocity*(b.mass-a.mass)+2*a.mass*a.velocity)/(a.mass+b.mass);
    a.velocity = temp1;
    b.velocity = temp2;
}

// Hit the Wall
void hit_wall(Object& b){
    b.velocity = -1 * b.velocity;
}

//Movement
void movement(Object &b){
    double temp = b.position;
    b.position = temp + b.velocity;
}


bool approx_equal_pos(Object& a, Object& b){
    double delta_p = abs(a.position - b.position);
    double delta_v = abs(a.velocity - b.velocity);
    if(delta_v > delta_p)
        return true;
    else
        return false;
