#pragma once

#include <fstream>
#include <iostream>
#include <vector>
#include <color/color.hpp>

using namespace std;

class Imagen {
    public:
    unsigned int width, height;
    double maxNumber;

    Imagen(unsigned int w, unsigned int h) : width(w), height(h), maxNumber(1), imageData(h, vector<RGB>(w)) {}

    Imagen(unsigned int w, unsigned int h, vector<vector<RGB>> data, double max) : width(w), height(h), maxNumber(max), imageData(data) {}
    void writeToPPM(const string& path, unsigned int res = 255) const;
    static Imagen readPPM(const string& path);

    void writeToBMP(const string& path) const;

    static Imagen readBMP(const string& path);
    
    friend ostream& operator<<(ostream& os, const Imagen& image);

    vector<vector<RGB>> imageData;

    double getMaxNumber();
};

/**
 * @brief Print general image infomation to an output stream
 * 
 * @param os The output stream
 * @param image The image object
 * @return ostream& The same output stream
 */
ostream& operator<<(ostream& os, const Imagen& image);