//
// Created by Sydney Lam on 11/16/22.
//

#include "Image.h"
#include <cmath>

//Reads in the tga file's image data (color data) itself
void Image::readColorData(std::ifstream &inStream) {
    for (int i = 0; i < width*height; i++) {
        pixel p;
        p.readColorPixel(inStream);
        pixelVector.push_back(p);
    }
}

//Writes the tga file's image data (color data) itself
void Image::writeColorData(std::ofstream &outStream) {
    for(int i = 0; i < pixelVector.size(); i++) {
        pixelVector[i].writeColorPixel(outStream);
    }
}

//Function which performs the multiply blending action on two layers
Image Image::multiply(const Image &front, const Image &back) {
    Image img;
    float blue = 0;
    float green = 0;
    float red = 0;
    pixel p;
    //Multiplies each channel of the pixel and ensures it does not overflow the 255 max value
    for (int i = 0; i < front.pixelVector.size(); i++) {
        blue = front.pixelVector[i].blue*back.pixelVector[i].blue;
        p.blue = Image::clampImagePixel(round(blue/255.0));
        green = front.pixelVector[i].green*back.pixelVector[i].green;
        p.green = Image::clampImagePixel(round(green/255.0));
        red = front.pixelVector[i].red*back.pixelVector[i].red;
        p.red = Image::clampImagePixel(round(red/255.0));
        img.pixelVector.push_back(p);
    }
    return img;
}

//Function which performs the subtract blending action on two layers
Image Image::subtract(const Image &first, const Image &second) {
    Image img;
    int blue = 0;
    int green = 0;
    int red = 0;
    pixel p;

    for (int i = 0; i < first.pixelVector.size(); i++) {
        blue = second.pixelVector[i].blue - first.pixelVector[i].blue;
        p.blue = clampImagePixelMin(blue);

        green = second.pixelVector[i].green - first.pixelVector[i].green;
        p.green = clampImagePixelMin(green);

        red = second.pixelVector[i].red - first.pixelVector[i].red;
        p.red = clampImagePixelMin(red);
        img.pixelVector.push_back(p);
    }
    return img;
}

//Function which performs the screen blending action on two layers
Image Image::screen(const Image &front, const Image &back) {
    Image img;
    float blue1,blue2;
    float green1,green2;
    float red1,red2;

    float blue,green,red;
    pixel p;

    for (int i = 0; i < front.pixelVector.size(); i++) {
        red1 = float(front.pixelVector[i].red)/255;
        red2 = float(back.pixelVector[i].red)/255;

        green1 = float(front.pixelVector[i].green)/255;
        green2 = float(back.pixelVector[i].green)/255;

        blue1 = float(front.pixelVector[i].blue)/255;
        blue2 = float(back.pixelVector[i].blue)/255;

        blue = 1 - (1-blue1)*(1-blue2);
        p.blue = Image::clampImagePixel(round(blue*255));
        green = 1 - (1-green1)*(1-green2);
        p.green = Image::clampImagePixel(round(green*255));
        red = 1 - (1-red1)*(1-red2);
        p.red = Image::clampImagePixel(round(red*255));


        img.pixelVector.push_back(p);
    }

    return img;

}

//Function which performs the overlay blending action on two layers
Image Image::overlay(const Image &front, const Image &back) {

    Image img;
    float blue1,blue2;
    float green1,green2;
    float red1,red2;

    float blue,green,red;
    pixel p;

    for (int i = 0; i < front.pixelVector.size(); i++) {
        red1 = float(front.pixelVector[i].red)/255;
        red2 = float(back.pixelVector[i].red)/255;

        green1 = float(front.pixelVector[i].green)/255;
        green2 = float(back.pixelVector[i].green)/255;

        blue1 = float(front.pixelVector[i].blue)/255;
        blue2 = float(back.pixelVector[i].blue)/255;

        //manipulating blue pixels
        if (blue2 > 0.5) {
            blue = 1 - 2*(1-blue1)*(1-blue2);
            p.blue = Image::clampImagePixel(round(blue*255));
        } else {
            blue = 2*blue1*blue2;
            p.blue = Image::clampImagePixel(round(blue*255));
        }

        //manipulating green pixels
        if (green2 > 0.5) {
            green = 1 - 2*(1-green1)*(1-green2);
            p.green = Image::clampImagePixel(round(green*255));
        } else {
            green = 2*green1*green2;
            p.green = Image::clampImagePixel(round(green*255));
        }

        //manipulating red pixels
        if (red2 > 0.5) {
            red= 1 - 2*(1-red1)*(1-red2);
            p.red = Image::clampImagePixel(round(red*255));
        } else {
            red = 2*red1*red2;
            p.red = Image::clampImagePixel(round(red*255));
        }

        img.pixelVector.push_back(p);

    }
        return img;
}

//Function which adds 200 to the green channel
Image Image::greenChannel(const Image &manipulateImg) {
    Image img;
    int blue = 0;
    int green = 0;
    int red = 0;
    pixel p;

    for (int i = 0; i < manipulateImg.pixelVector.size(); i++) {
        blue = manipulateImg.pixelVector[i].blue;
        p.blue = clampImagePixelMax(blue);
        green = manipulateImg.pixelVector[i].green;
        p.green = clampImagePixelMax(green+200);
        red = manipulateImg.pixelVector[i].red;
        p.red = clampImagePixelMax(red);

        img.pixelVector.push_back(p);
    }

    return img;
}

//Function which multiplies the red channel by 4, and multiplies the blue channel by 0
Image Image::redChannel(const Image &manipulateImg) {
    Image img;
    int blue = 0;
    int green = 0;
    int red = 0;
    pixel p;

    for (int i = 0; i < manipulateImg.pixelVector.size(); i++) {
        p.blue = blue;
        green = manipulateImg.pixelVector[i].green;
        p.green = clampImagePixelMax(green);
        red = manipulateImg.pixelVector[i].red;
        p.red = clampImagePixelMax(red*4);

        img.pixelVector.push_back(p);
    }

    return img;
}

//Takes a tga file and only writes out its red channel
Image Image::OnlyRedChannel(const Image &manipulateImg) {
    Image img;
    int blue = 0;
    int green = 0;
    int red = 0;
    pixel p;

    for (int i = 0; i < manipulateImg.pixelVector.size(); i++) {
        p.blue = manipulateImg.pixelVector[i].red;
        p.green = manipulateImg.pixelVector[i].red;
        p.red = manipulateImg.pixelVector[i].red;

        img.pixelVector.push_back(p);
    }
    return img;
}

//Takes a tga file and only writes out its green channel
Image Image::OnlyGreenChannel(const Image &manipulateImg) {
    Image img;
    int blue = 0;
    int green = 0;
    int red = 0;
    pixel p;

    for (int i = 0; i < manipulateImg.pixelVector.size(); i++) {
        p.blue = manipulateImg.pixelVector[i].green;
        p.green = manipulateImg.pixelVector[i].green;
        p.red = manipulateImg.pixelVector[i].green;

        img.pixelVector.push_back(p);
    }
    return img;
}

//Takes a tga file and only writes out its blue channel
Image Image::OnlyBlueChannel(const Image &manipulateImg) {
    Image img;
    int blue = 0;
    int green = 0;
    int red = 0;
    pixel p;

    for (int i = 0; i < manipulateImg.pixelVector.size(); i++) {
        p.blue = manipulateImg.pixelVector[i].blue;
        p.green = manipulateImg.pixelVector[i].blue;
        p.red = manipulateImg.pixelVector[i].blue;

        img.pixelVector.push_back(p);
    }
    return img;
}

//Combines three separate channel files and combines them into one file
Image Image::CombineFiles(const Image &file1, const Image &file2, const Image &file3) {
    Image img;
    int blue = 0;
    int green = 0;
    int red = 0;
    pixel p;

    for (int i = 0; i < file1.pixelVector.size(); i++) {
        blue = file1.pixelVector[i].blue;
        p.blue = clampImagePixelMax(blue);
        green = file2.pixelVector[i].green;
        p.green = clampImagePixelMax(green);
        red = file3.pixelVector[i].red;
        p.red = clampImagePixelMax(red);

        img.pixelVector.push_back(p);
    }

    return img;
}

//Rotates a tga file by 180 degrees
Image Image::RotateFile(const Image &manipulateImg) {
    int var = manipulateImg.pixelVector.size()-1;
    Image img;
    img.pixelVector.resize(var+1);
    for (int i = var; i >= 0; i--) {
        img.pixelVector[var-i] = manipulateImg.pixelVector[i];
    }
    return img;
}

//Clamping maximum and clamping minimum in order to prevent underflow and overflow

//Just maximum
int Image::clampImagePixelMax(int val) {
    if (val > 255) {
        return 255;
    }
    return val;
}

//Just minimum
int Image::clampImagePixelMin(int val) {
    if (val < 0 ) {
        return 0;
    }
    return val;
}

//Both max and min clamping
int Image::clampImagePixel(int val) {
    if (val < 0 ) {
        return 0;
    }
    if (val > 255) {
        return 255;
    }
    return val;
}