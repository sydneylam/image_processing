//
// Created by Sydney Lam on 11/13/22.
//
#pragma once

//A structure for the header to contain all of its elements
struct Header
{
    char  idLength;
    char  colorMapType;
    char  dataTypeCode;
    short colorMapOrigin;
    short colorMapLength;
    char  colorMapDepth;
    short xOrigin;
    short yOrigin;
    short width;
    short height;
    char  bitsPerPixel;
    char  imageDescriptor;

    void readHeader(std::ifstream &inStream);
    void writeHeader(std::ofstream &outStream);


};


