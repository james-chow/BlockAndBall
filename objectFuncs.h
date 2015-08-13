// contains function prototypes for utility.cpp

#include "object.h"

//void collide(Object a, Object b);
void collide(Object& a, Object& b);
void movement(Object &b);
void hit_wall(Object& b);
bool approx_equal_pos(Object& a, Object& b);
