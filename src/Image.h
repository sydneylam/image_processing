//
// Created by Sydney Lam on 11/16/22.
//

#pragma once
#include <vector>
#include "pixel.h"

//A structure for the image to contain all of its elements
struct Image {
    int height;
    int width;
    std::vector<pixel> pixelVector;

    void readColorData(std::ifstream &inStream);
    void writeColorData(std::ofstream &outStream);
    static Image multiply(const Image &front, const Image &back);
    static Image subtract(const Image &first, const Image &second);
    static int clampImagePixelMax(int val);
    static int clampImagePixelMin(int val);
    static Image screen(const Image &front, const Image &back);
    static Image overlay(const Image &front, const Image &back);
    static Image greenChannel(const Image &img);
    static Image redChannel(const Image &manipulateImg);
    static Image OnlyRedChannel(const Image &manipulateImg);
    static Image OnlyGreenChannel(const Image &manipulateImg);
    static Image OnlyBlueChannel(const Image &manipulateImg);


    static Image CombineFiles(const Image &file1, const Image &file2, const Image &file3);
    static Image RotateFile(const Image &manipulateImg);


    static int clampImagePixel(int val);
};
