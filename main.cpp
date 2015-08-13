//The body of the function

//#include "objectFuncs.h"
#include "object.h"
#include <iostream>
#include <cmath>

using namespace std;

void collide(Object& a, Object& b);
void movement(Object &b);
void hit_wall(Object& b);
bool approx_equal_pos(Object& a, Object& b);
double length;

int main(){
    
    Object * block = new Object;
    Object * ball = new Object;
    Object * wall = new Object;
    
    wall->position = 0;
    wall-> velocity = 0;
    
    /*
    cout << "Enter initial velocity of block:" << endl;
    cin >> block->velocity;
    cout << "Enter mass of block and ball" << endl;
    cin >> block->mass >> ball->mass;
    cout << "Enter initial distance from wall" << endl;
    cin >> length;
    ball->position = -1*length;
    block->position = -1 * length;
    */
    
    // testing movement and collisions
    length = 50;
    ball->position = -50; //meters
    block->position = -50;
    ball->mass = 1; //kg
    block->mass = 50; //kg
    block->velocity = 1; //meters per second
    ball->velocity = 0;
    
    
    block->velocity = 0.001; // meters per millisecond
    collide(*block,*ball);
    
    cout << "velocity: " << block->velocity << " " << ball->velocity << endl; //meters per millisecond

    for(int time = 0; time <= 1000000; time ++){ //time is 100,000 milliseconds, or 1000 seconds
        movement(*ball);
        movement(*block);
        
 
       
        if(approx_equal_pos(*ball,*wall) && (ball->velocity)) {
            hit_wall(*ball);
            cout << "BOUNCE" << endl;
        }
       
        if(approx_equal_pos(*block,*ball) && (ball->velocity < 0)){
            collide(*block,*ball);
            cout << "COLLISION" << endl;

        }
        
        
        if(time%1000 == 0)
            cout << block->position << " " << ball->position << endl;
        
        if(block->velocity <0) {
            cout << "END VELOCITY: " << block->velocity << endl;
            cout << "END POSITION: " << block->position << endl;
            cout << "Theoretical pos: " << -1 * length * sqrt(ball->mass/block->mass) << endl;
            return 0;
        }
    }
    cout << "velocity: " << block->velocity << " " << ball->velocity << endl; //meters per millisecond


    
    delete block;
    delete ball;
    return 0;
}

// required functions

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
}