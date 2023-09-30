//
// Created by Sydney Lam on 11/15/22.
//

#pragma once

#include <vector>
#include <iostream>
#include <fstream>

//A structure for the image to contain all of its elements (channels)
struct pixel
{
    unsigned char red;
    unsigned char green;
    unsigned char blue;


    void readColorPixel(std::ifstream &inStream);
    void writeColorPixel(std::ofstream &outStream);


    pixel();
    pixel(int b, int g, int r);


};

