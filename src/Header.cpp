//
// Created by Sydney Lam on 11/13/22.
//
#include <fstream>
#include "Header.h"

//Reading in the tga's header
void Header::readHeader(std::ifstream &inStream) {
    inStream.read((char *)&idLength,sizeof(idLength));
    inStream.read((char *)&colorMapType,sizeof(colorMapType));
    inStream.read((char *)&dataTypeCode,sizeof(dataTypeCode));
    inStream.read((char *)&colorMapOrigin,sizeof(colorMapOrigin));
    inStream.read((char *)&colorMapLength,sizeof(colorMapLength));
    inStream.read((char *)&colorMapDepth,sizeof(colorMapDepth));
    inStream.read((char *)&xOrigin,sizeof(xOrigin));
    inStream.read((char *)&yOrigin,sizeof(yOrigin));
    inStream.read((char *)&width,sizeof(width));
    inStream.read((char *)&height,sizeof(height));
    inStream.read((char *)&bitsPerPixel,sizeof(bitsPerPixel));
    inStream.read((char *)&imageDescriptor,sizeof(imageDescriptor));
}

//Writing out a tga header
void Header::writeHeader(std::ofstream &outStream) {
    outStream.write((char *)&idLength,sizeof(idLength));
    outStream.write((char *)&colorMapType,sizeof(colorMapType));
    outStream.write((char *)&dataTypeCode,sizeof(dataTypeCode));
    outStream.write((char *)&colorMapOrigin,sizeof(colorMapOrigin));
    outStream.write((char *)&colorMapLength,sizeof(colorMapLength));
    outStream.write((char *)&colorMapDepth,sizeof(colorMapDepth));
    outStream.write((char *)&xOrigin,sizeof(xOrigin));
    outStream.write((char *)&yOrigin,sizeof(yOrigin));
    outStream.write((char *)&width,sizeof(width));
    outStream.write((char *)&height,sizeof(height));
    outStream.write((char *)&bitsPerPixel,sizeof(bitsPerPixel));
    outStream.write((char *)&imageDescriptor,sizeof(imageDescriptor));
}


