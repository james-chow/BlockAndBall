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

int num_collisions;
double length;


int main(){
    
    Object * block = new Object;
    Object * ball = new Object;
    Object * wall = new Object;
    
    wall->position = 0;
    wall->velocity = 0;
    
    
    // testing movement and collisions
    cout << "This will simulate 100 seconds of motion\nEnter starting distance from wall in m" << endl;
    cin >> length;
    ball->position = -1*length; //meters
    block->position = -1*length;
    cout << "Enter mass of Block and Ball in kg (separated by space)" << endl;
    cin >> block->mass >> ball->mass;
    cout << "Enter initial velocity in m/s"  << endl;
    cin >> block->velocity;
    
    ball->velocity = 0;
    block->velocity = 0.001 * block->velocity; // meters per millisecond
    
    collide(*block,*ball);
    num_collisions = 1;
    
    cout << "Block and Ball positions every 0.1 seconds" << endl;

    for(int time = 1; time <= 100000; time++){ //100 seconds turned into millisecond step
        
        movement(*ball);
        movement(*block);
        
 
        if(approx_equal_pos(*ball,*wall) && (ball->velocity)) {
            hit_wall(*ball);
            cout << "     BOUNCE" << endl;
        }
       
        if(approx_equal_pos(*block,*ball) && (ball->velocity < 0)){
            collide(*block,*ball);
            cout << "   COLLISION" << endl;
            num_collisions++;

        }
        
        
        if(time%100 == 0)
            cout << static_cast<double>(time)/1000 << ": " << block->position << " " << ball->position << endl;
        
        if(block->velocity < 0) {
            cout << "END POSITION: " << block->position << endl;
            cout << "COLLISION COUNT: " << num_collisions << endl;
            cout << "Stopped in " << static_cast<double>(time)/1000 << " seconds" << endl;
            cout << "Theoretical Position: " << -1 * length * sqrt(ball->mass/block->mass) << endl;
            cout << "Theoretical Collision #: " << 0.5*M_PI/atan(2*(sqrt(block->mass*ball->mass))/(block->mass - ball->mass)) << endl;
            delete block;
            delete ball;
            return 0;
        }
    }


    
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