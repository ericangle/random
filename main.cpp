#include <math.h>
#include "Box.h"
using namespace std;

int readInput(string inFilePath, vector <Box>& boxes, int& numBoxes, int& dim,
              double& invDim);

int main ( int argc, char *argv[] ) {

    string inFilePath = argv[1];
    string outFilePath = argv[2];

    if (argc != 2 + 1) {
       cout << "ERROR: Wrong number of command line arguments." << endl;
       cout << "You provided " << argc << " expecting 2." << endl;
       return 1;
    }
    else {
       inFilePath = argv[1];
       outFilePath = argv[2];
    }
    
    int dim;            // number of spatial dimensions
    double invDim;      // 1/dim
    
    vector <Box> boxes; // Box object for each box in text file

    int numBoxes = -1;  // number of boxes, initialized to -1 because
                        // the first line is dimension and not a point

    /*** 1. Read in input data ***/
    int error = 0;
    error = readInput(inFilePath, boxes, numBoxes, dim, invDim);
    if (error == 1) {
        return 1;
    }
    
    ofstream output;
    char delimit = '\t';
    output.open(outFilePath);

    for (int i = 0; i < numBoxes; i++) {
        /*** 2a. Construct boxes ***/
        boxes[i].setLowerUpper(dim);
        
        /*** 2b. Generate random numbers ***/
        boxes[i].generateRandomNumbers(dim);
        
        /*** 3. Output data ***/
        boxes[i].outputData(output, dim, delimit);
    }

    output.close();
    
    return 0;
}

int readInput(string inFilePath, vector <Box>& boxes, int& numBoxes, int& dim,
              double& invDim) {
    
    ifstream inputFile(inFilePath);
    string tempLine;
    
    int coordCount;
    
    while (getline(inputFile, tempLine, '\n')) {
        // Read in dimension
        if (numBoxes == -1) {
            double tempDim = atof(tempLine.c_str());
            if (tempDim > 0) {
                dim = tempDim;
                invDim = 1.0/( (double) dim );
            }
            // Error if invalid dimension
            else {
                cout << "ERROR: Dimension must be greater than 0." << endl;
                return 1;
            }
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
                    if ((tempVolume > 0.0) && (tempVolume < 1.0)) {
                        tempBox->volume = atof(temp.c_str());
                        tempBox->fracDist = 1.0 - pow(tempBox->volume,invDim);
                    }
                    // Error if volume is not in allowable range
                    else {
                        cout << "ERROR: Point " << numBoxes << " has a volume ";
                        cout << "that is not greater than 0.0 and less than 1.0.";
                        cout << endl;
                        return 1;
                    }
                }
                // Read in point
                else {
                    tempCoord = atof(temp.c_str());
                    if ((tempCoord >= 0.0) && (tempCoord <= 1.0)) {
                        tempPoint.push_back(tempCoord);
                    }
                    // Error if coordinate is not in allowable range
                    else {
                        cout << "ERROR: The " << coordCount << " coordinate of ";
                        cout << "point " << numBoxes << " is not greater than or ";
                        cout << "equal to 0.0 and less than or equal to 1.0.";
                        cout << endl;
                        return 1;
                    }
                }
                coordCount++;
            }
            
            // Error if not enough coordinates for point
            if (coordCount < dim) {
                cout << "ERROR: Point " << numBoxes << " has " << coordCount
                     << " coordinates instead of " << dim << "."
                     << endl;
                return 1;
            }
            
            tempBox->point = tempPoint;
            boxes.push_back(*tempBox);
            delete tempBox;
            
        }
        numBoxes++;
    }
    
    // Error if no points provided
    if (numBoxes == 0) {
        cout << "ERROR: No points were specified." << endl;
        return 1;
    }
    
    // Error if no data read in
    if (numBoxes == -1) {
        cout << "ERROR: Text file is empty or not readable." << endl;
        return 1;
    }
    return 0;
}
