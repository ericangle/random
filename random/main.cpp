/*  Problem statement:
 1. From a text file, read in the dimension of the space, and a series of points, each with a corresponding volume.
 2. For each point:
 a. Construct a hypercube "box" around the point with the specifed volume, such that each vertex of the unit hypercube is moved the same fractional distance to the point.
 b. Generate 3 random points inside the box, and 1 inside the unit hypercube, and outside the box.
 3. Output the coordinates of all generated points to a text file.
 */

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

int main() {
    
    // Class for boxes
    class Box {
    public:
        double volume;
        double alpha; // re-name this.
        vector <double> point;
        vector <double> lower;
        vector <double> upper;
        vector <double> randomInside[3];
        vector <double> randomOutside;
        
        // maybe some methods, such as:
        // void setLowerUpper()
        
    } boxes;
    
    int dim;           // number of spatial dimensions
    int numBoxes = -1; // number of boxes, initialized to -1 because
                       // the first line is dimension and not a point
    double invDim;     // 1/dim
    
    // 1. READ IN DATA
    
    // Note: would be nice to allow user to specify path and file name
    ifstream inputFile("/Users/angle/Desktop/GS/random/random/input.txt");
    string tempLine;
    
    while (getline(inputFile, tempLine, '\n')) {
        if (numBoxes == -1) {
            dim = atof(tempLine.c_str());
            invDim = 1.0/( (double) dim );
            cout << "dimension = " << dim << endl;
        }
        else {
            cout << "point " << numBoxes << endl;
        }
        numBoxes++;
    }
    
    // Note: would be nice to provide better error message
    if (numBoxes == -1) {
        cout << "Text file is empty or not readable." << endl;
    }
    cout << "numBoxes = " << numBoxes;
    
    // 2a. CONSTRUCT BOXES
    
    // 2B. GENERATE RANDOM NUMBERS
    
    // 3. OUTPUT DATA TO TEXT FILE
    
    return 0;
}

