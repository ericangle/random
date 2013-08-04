/*  Problem statement:
 1. From a text file, read in the dimension of the space, and a series of points, each with a corresponding volume.
 2. For each point:
    A. Construct a hypercube "box" around the point with the specifed volume, such that each vertex of the unit hypercube is moved the same fractional distance to the point.
    B. Generate:
       I.  3 random points inside the box.
       II. 1 random point inside the unit hypercube, and outside the box.
 3. Output the coordinates of all generated points to a text file.
 
 Some assumptions made:
 1. The input text file will be in tab delimited form.
 2. Random numbers should be generated from a uniform distribution.
 3. We have hard coded 2BI and 2BII to generate 3 and 1 points, respectively. If there is time, we could make this more generic.
 */

#include <iostream>
#include <vector>
#include <math.h>
#include <fstream>
#include <sstream>
#include <string>
#include "Box.h"
using namespace std;

int main() {
    int dim;            // number of spatial dimensions
    double invDim;      // 1/dim
    
    vector <Box> boxes; // Box object for each box in text file

    int numBoxes = -1;  // number of boxes, initialized to -1 because
                        // the first line is dimension and not a point

    /*** 1. Read in input data ***/
    
    // Note: would be nice to allow user to specify path and file name
    ifstream inputFile("/Users/angle/Desktop/GS/random/random/input.txt");
    string tempLine;
    
    int coordCount;
    
    while (getline(inputFile, tempLine, '\n')) {
        // Read in dimension
        if (numBoxes == -1) {
            dim = atof(tempLine.c_str());
            invDim = 1.0/( (double) dim );
        }
        // Read in box data
        else {
            Box* tempBox = new Box;
            
            double tempVolume;
            vector <double> tempPoint;
            double tempCoord;
    
            coordCount = -1; // initialized to -1 because first column is volume
            
            stringstream ss(tempLine);
            string temp;
            
            // Will just ignore extra point coords
            while (getline(ss, temp, '\t') && (coordCount < dim)) {
                // Read in volume
                if (coordCount == -1) {
                    tempVolume = atof(temp.c_str());
                    // Note: think about inclusive versus exclusive
                    if ((tempVolume > 0.0) && (tempVolume < 1.0)) {
                        tempBox->volume = atof(temp.c_str());
                        cout << "volume " << tempBox->volume << endl;
                        tempBox->fracDist = 1.0 - pow(tempBox->volume,invDim);
                        cout << "fracDist = " << tempBox->fracDist << endl;
                    }
                    // Error if volume is not in allowable range
                    else {
                        cout << "ERROR: Point " << numBoxes << " has a volume that is not ";
                        cout << "greater than 0.0 and less than 1.0." << endl << endl;
                        return 1;
                    }
                }
                // Read in point
                else {
                    tempCoord = atof(temp.c_str());
                    // Note: think about inclusive versus exclusive
                    if ((tempCoord >= 0.0) && (tempCoord <= 1.0)) {
                        tempPoint.push_back(tempCoord);
                        cout << "point " << tempPoint[coordCount] << endl;
                    }
                    // Error if coordinate is not in allowable range
                    else {
                        cout << "ERROR: The " << coordCount << " coordinate of point ";
                        cout << numBoxes << " is not greater than or equal to 0.0 ";
                        cout << " and less than 1.0." << endl << endl;
                        return 1;
                    }
                }
                coordCount++;
            }
            
            // Error if not enough coordinates for point
            if (coordCount < dim) {
                cout << "ERROR: Point " << numBoxes << " has " << coordCount << " coordinates ";
                cout << "instead of " << dim << ".";
                return 1;
            }
            
            tempBox->point = tempPoint;
            boxes.push_back(*tempBox);
            delete tempBox;
            
            /*** 2a. Construct boxes ***/
            boxes[numBoxes].setLowerUpper(dim);
        }
        numBoxes++;
    }
    
    // Note: would be nice to provide better error message
    if (numBoxes == -1) {
        cout << "Text file is empty or not readable." << endl;
    }
    
    /*** 2b. Generate random numbers ***/
    for (int i = 0; i < numBoxes; i++) {
        boxes[i].generateRandomNumbers(dim);
    }
    
    /*** 3. Output data ***/
    ofstream output;
    output.open("/Users/angle/Desktop/GS/random/random/output.txt");
    for (int i = 0; i < numBoxes; i++) {
        boxes[i].outputData(output, dim);
    }
    output.close();
    
    return 0;
}