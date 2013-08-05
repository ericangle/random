//  Box.h
//  Class to represent boxes

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
    
    // Set upper and lower vertices
    void setLowerUpper(int dim);
    
    // Generate random numbers
    void generateRandomNumbers(int dim);
    
    // Output data
    void outputData(ofstream & output, int dim, char delimit);
    
    // Make line with elements of data
    string makeLine(vector <double> data, int dim, char delimit);
};

#endif /* defined(__random__Box__) */
