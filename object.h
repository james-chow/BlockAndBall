#ifndef object_h
#define object_h


struct Object {
    double position; //negative numbers representing how far to the left from the wall
    double velocity; //positive moves towards the wall
    double mass;
};

#endif // object_h
