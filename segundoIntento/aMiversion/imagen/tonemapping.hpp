#pragma once

#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

// Clamps the values of the pixels between 0 and 1, transforming higher values
// into 1.
void clamping(double &r, double &g, double &b);

// Transforms a ppm file into another with the same content but with the values
// of the pixels between 0 and 1, following a clampling transformation.
void transform_clamping(string inFile, string outFile);

// Transforms a ppm file into another with the same content but with the values
// of the pixels between 0 and 1, dividing each value by the maximum one.
void equalization(double &r, double &g, double &b, double max);

// Transforms a ppm file into another with the same content but with the values
// of the pixels between 0 and 1, following a linear transformation.
void transform_equalization(string inFile, string outFile);

// Transforms a ppm file into another with the same content but with the values
// of the pixels between 0 and 1, dividing each value by the threshold, and
// reducing it to 1 if higher.
void clamping_equalization(double &r, double &g, double &b, double threshold);

// Transforms a ppm file into another with the same content but with the values
// of the pixels between 0 and 1, following a clamping transformation and then
// an equalization one.
void transform_clamp_equal(string inFile, string outFile, int threshold);

// Transforms a ppm file into another with the same content but with the values
// of the pixels between 0 and 1, rooting each value.
void gamma(double &r, double &g, double &b, double gamma_coef);

// Transforms a ppm file into another with the same content but with the values
// of the pixels between 0 and 1, following a gamma transformation.
void transform_gamma(string inFile, string outFile, double gamma_coef);

void transform_clamp_gamma(string inFile, string outFile, int threshold, double gamma_coef);
