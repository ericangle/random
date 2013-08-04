//  Box.h

#ifndef __random__Box__
#define __random__Box__

#include <iostream>
#include <random>
#include <vector>
using namespace std;

class Box {
public:
    double volume;
    double fracDist; // fractional distance that the unit cube's vertices
    // will be moved toward point
    vector <double> point;
    vector <double> lower;
    vector <double> upper;
    vector <double> randomInside[3];
    vector <double> randomOutside;
    
    // Set Upper and lower indices
    void setLowerUpper(int dim);
    
    // Generate random numbers
    void generateRandomNumbers(int dim);
    
    // maybe some methods, such as:
    // void input
    // void output ???
};

#endif /* defined(__random__Box__) */
