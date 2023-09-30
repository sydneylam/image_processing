//
// Created by Sydney Lam on 11/15/22.
// Creating one pixel

#include <fstream>
#include "pixel.h"
#include "Header.h"

pixel::pixel() = default;

pixel::pixel (int b, int g, int r) {
    blue = b;
    green = g;
    red = r;
}

//Reads in the channels of individual pixels
void pixel::readColorPixel(std::ifstream &inStream) {
        inStream.read((char *)&blue, sizeof(blue));
        inStream.read((char *)&green, sizeof(green));
        inStream.read((char *)&red, sizeof(red));
}

//Writes out the channels of individual pixels
void pixel::writeColorPixel(std::ofstream &outStream) {
    outStream.write((char *)&blue, sizeof(blue));
    outStream.write((char *)&green, sizeof(green));
    outStream.write((char *)&red, sizeof(red));
}



