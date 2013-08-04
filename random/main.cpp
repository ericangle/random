/*  Problem statement:
 1. From a text file, read in the dimension of the space, and a series of
    points, each with a corresponding volume.
 2. For each point:
    a. Construct a hypercube "box" around the point with the specifed
       volume, such that each vertex of the unit hypercube is moved
       the same fractional distance to the point.
    b. Generate:
       I.  3 random points inside the box.
       II. 1 random point inside the unit hypercube, and outside the box.
 3. Output the coordinates of all generated points to a text file.
 */

#include <iostream>
#include <vector>
#include <math.h>
#include <fstream>
#include <sstream>
#include <string>
#include "Box.h"
using namespace std;

string makeLine(vector <double> data, int dim);

int main() {
    
    int dim;            // number of spatial dimensions
    double invDim;      // 1/dim
    
    vector <Box> boxes; // Box object for each box in text file

    int numBoxes = -1;  // number of boxes, initialized to -1 because
                        // the first line is dimension and not a point

    // 1. READ IN DATA
    
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

            vector <double> tempPoint;
            double tempCoord;
    
            coordCount = -1; // initialized to -1 because first column is volume
            
            stringstream ss(tempLine);
            string temp;
            // will just ignore extra point coords
            while (getline(ss, temp, '\t') && (coordCount < dim)) {
                // Read in volume
                if (coordCount == -1) {
                    double tempVolume = atof(temp.c_str());
                    // Think about inclusive versus exclusive
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
                else {
                    tempCoord = atof(temp.c_str());
                    // Think about inclusive versus exclusive
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
            
            // 2a. CONSTRUCT BOXES     
            boxes[numBoxes].setLowerUpper(dim);
            
        }
        numBoxes++;
    }
    
    // Note: would be nice to provide better error message
    if (numBoxes == -1) {
        cout << "Text file is empty or not readable." << endl;
    }
    
    // TODO: Verify calculation of lower and upper vertices
    
    // 2B. GENERATE RANDOM NUMBERS
    boxes[numBoxes].generateRandomNumbers(dim);
    
    // TODO: Verify random numbers
    
    // 3. OUTPUT DATA TO TEXT FILE
    
    ofstream output;
    output.open("/Users/angle/Desktop/GS/random/random/output.txt");
    for (int i = 0; i < numBoxes; i++) {
        for (int j = 0; j < 3; j++) {
            output << makeLine(boxes[i].randomInside[j], dim) << '\n';
        }
        output << makeLine(boxes[i].randomOutside, dim) << '\n';
    }
    output.close();
    
    return 0;
}

string makeLine(vector <double> data, int dim) {
    string line = "";
    ostringstream strs;
    string str;
    for (int j = 0; j < dim; j++) {
        strs.str("");
        strs << data[j];
        str = strs.str();
        line += str + '\t';
    }
    return line;
}


