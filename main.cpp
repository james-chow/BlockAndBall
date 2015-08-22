//The body of the function

//#include "objectFuncs.h" - doesn't work due to 'linking error'
#include "object.h"
#include <iostream>
#include <iomanip>
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
    cout << "\nUp to 100s of motion will be calculated, or until the block stops. \nEnter initial distance from wall in m:" << endl;
    cin >> length;
    
    if(length<=0){
        cerr << "Invalid Input: Length is a positive quantity" << endl;
        exit(1);
    }
    
    ball->position = -1*length; //meters from the wall
    block->position = -1*length;
    cout << "Enter mass of Block, Ball in kg (separate by a space):" << endl;
    cin >> block->mass >> ball->mass;
    
    if(block->mass <=0 || ball->mass <=0){
        cerr << "Invalid Input: Mass should be positive" << endl;
        exit(1);
    }
    if(block->mass <= ball->mass){
        cerr << "Invalid Input: The Block is more massive!" << endl;
        exit(1);
    }
    
    cout << "Enter initial velocity in m/s:"  << endl;
    cin >> block->velocity;
    
    if(block->velocity <=0){
        cerr << "Invalid Input: Velocity should be positive" << endl;
        exit(1);
    }
    
    ball->velocity = 0;
    block->velocity = 0.000001 * block->velocity; // meters per microsecond
    
    collide(*block,*ball);
    num_collisions = 1;
    
    
    
    cout << "\nBlock and Ball positions every 0.1 seconds" << endl;
    for(int time = 1; time <= 100000000; time++){ //100 seconds turned into microsecond steps
        
        movement(*ball);
        movement(*block);
        
 
        if(approx_equal_pos(*ball,*wall) && (ball->velocity)) { //ball bounces off the wall
            hit_wall(*ball);
            cout << "       BOUNCE" << endl;
        }
       
        
        if(approx_equal_pos(*block,*ball) && (ball->velocity < 0)){ //block and ball collide
            collide(*block,*ball);
            cout << "     COLLISION" << endl;
            num_collisions++;

        }
        
        if(time%1000000 == 0)
            cout << setprecision(1) << fixed << static_cast<double>(time/1000000) << ": " << setprecision(2) << fixed << block->position << " " << ball->position << endl;
        
        else if(time%100000 == 0)
            cout << setprecision(1) << static_cast<double>(time)/1000000 << ": " << setprecision(2) << fixed << block->position << " " << ball->position << endl;
        
        if(block->velocity <= 0) { //ends simulation when block stops moving forward
            cout.precision(2);
            cout << "\nSIMULATION END\nApproximate Elapsed time: " << static_cast<double>(time)/1000000 << " seconds" << endl;
            cout << "Block stopped at: " << block->position << endl;
            cout << "Number of collisions: " << num_collisions << endl;
            cout << "Theoretical End Position: " << -1 * length * sqrt(ball->mass/block->mass) << endl;
            cout << "Theoretical Number of Collisions: " << 0.5*M_PI/atan(2*(sqrt(block->mass*ball->mass))/(block->mass - ball->mass)) << endl;
            
            delete block;
            delete ball;
            return 0;
        }
    }


    cout << "\nSIMULATION END" << endl;
    cout << "The Block did not stop or reverse direction." << endl;
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

//Relative Closeness of Objects
bool approx_equal_pos(Object& a, Object& b){
    double delta_p = abs(a.position - b.position);
    double delta_v = abs(a.velocity - b.velocity);
    if(delta_v > delta_p)
        return true;
    else
        return false;
}