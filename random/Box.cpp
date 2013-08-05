//  Box.cpp
//  Class to represent boxes

#include "Box.h"

void Box::setLowerUpper(int dim) {
    for (int i = 0; i < dim; i++) {
        lower.push_back(fracDist * point[i]);
        upper.push_back(1.0 - fracDist * (1.0 - point[i]));
    }
}

void Box::generateRandomNumbers(int dim) {
    default_random_engine generator((int) time(0));
    double lowerBound = 0.0, upperBound = 0.0, randomNumber = 0.0;
    
    for (int i = 0; i < dim; i++) {
        /*** 2BI. Generate 3 random points inside the box ***/
        lowerBound = lower[i];
        upperBound = upper[i];
        for (int k = 0; k < 3; k++) {
            uniform_real_distribution<double> distribution(lowerBound, upperBound);
            randomNumber = distribution(generator);
            randomInside[k].push_back(randomNumber);
        }
        
        /*** 2BII. Generate 1 random point inside the unit hypercube, and outside the box ***/
        uniform_real_distribution<double> distribution(0.0, 1.0 - (upperBound - lowerBound));
        randomNumber = distribution(generator);
        // If number is inside box, shift it
        if (randomNumber > lowerBound) {
            randomNumber += upperBound - lowerBound;
        }
        randomOutside.push_back(randomNumber);
    }
}

void Box::outputData(ofstream & output, int dim, char delimit){
    // Output 3 points inside box
    for (int j = 0; j < 3; j++) {
        output << makeLine(randomInside[j], dim, delimit) << '\n';
    }
    // Output 1 point inside unit hypercube, and outside box
    output << makeLine(randomOutside, dim, delimit) << '\n';
}

string Box::makeLine(vector <double> data, int dim, char delimit) {
    string line = "";
    ostringstream strs;
    string str;
    for (int j = 0; j < dim; j++) {
        strs.str("");
        strs << data[j];
        str = strs.str();
        line += str + delimit;
    }
    return line;
}