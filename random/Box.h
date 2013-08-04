//  Box.h

#ifndef __random__Box__
#define __random__Box__

#include <iostream>
#include <random>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
using namespace std;

class Box {
public:
    double volume;
    
    // Fractional distance that the unit cube's vertices will be moved toward point
    double fracDist;
    
    vector <double> point;
    vector <double> lower;
    vector <double> upper;
    vector <double> randomInside[3];
    vector <double> randomOutside;
    
    // Set Upper and lower indices
    void setLowerUpper(int dim);
    
    // Generate random numbers
    void generateRandomNumbers(int dim);
    
    // Output data
    void outputData(ofstream & output, int dim);
    
    // Make line
    string makeLine(vector <double> data, int dim);

    // void input ???
};

#endif /* defined(__random__Box__) */
