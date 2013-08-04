/*  Problem statement:
 1. From a text file, read in the dimension of the space, and a series of points, each with a corresponding volume.
 2. For each point:
 a. Construct a hypercube "box" around the point with the specifed volume, such that each vertex of the unit hypercube is moved the same fractional distance to the point.
 b. Generate 3 random points inside the box, and 1 inside the unit hypercube, and outside the box.
 3. Output the coordinates of all generated points to a text file.
 */

#include <iostream>
#include <vector>
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
    };
    
    
    
    
    return 0;
}

