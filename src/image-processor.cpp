#include <iostream>
#include <fstream>
#include "Header.h"
#include "pixel.h"
#include "Image.h"
#include <string>

struct tgaFile {
    tgaFile() = default;

    tgaFile(tgaFile const &i)
    {
        header = i.header;
        image = i.image;
    }

    Header header;
    Image image;
};

//Initializing functions
tgaFile readFile(std::string fileName);
void writeFile(std::string fileName, tgaFile file);


int main()
{

    //Task #1:
    tgaFile layerOneTga = readFile("layer1.tga");
    tgaFile patternOneTga = readFile("pattern1.tga");
    tgaFile partOneTga;

    partOneTga.header = layerOneTga.header;
    partOneTga.image = Image::multiply(layerOneTga.image, patternOneTga.image);

    writeFile("part1.tga", partOneTga);

    //Task #2:
    tgaFile layerTwoTga = readFile("layer2.tga");
    tgaFile carTga = readFile("car.tga");
    tgaFile partTwoTga;

    partTwoTga.header = layerTwoTga.header;
    partTwoTga.image = Image::subtract(layerTwoTga.image, carTga.image);

    writeFile("part2.tga", partTwoTga);

    //Task #3:
    tgaFile patternTwoTga = readFile("pattern2.tga");

    //Creating the temporary tga file to perform screen blending with
    tgaFile tempPartThreeTga;
    tempPartThreeTga.header = layerOneTga.header;
    tempPartThreeTga.image = Image::multiply(layerOneTga.image, patternTwoTga.image);

    tgaFile partThreeTga;
    tgaFile textTga = readFile("text.tga");

    partThreeTga.header = tempPartThreeTga.header;
    partThreeTga.image = Image::screen(tempPartThreeTga.image, textTga.image);

    writeFile("part3.tga", partThreeTga);

    //Task #4:
    tgaFile tempPartFourTga;
    tgaFile circlesTga = readFile("circles.tga");
    tempPartFourTga.header = layerTwoTga.header;
    tempPartFourTga.image = Image::multiply(layerTwoTga.image, circlesTga.image);

    tgaFile partFourTga;
    partFourTga.header = tempPartFourTga.header;
    partFourTga.image = Image::subtract(patternTwoTga.image, tempPartFourTga.image);

    writeFile("part4.tga", partFourTga);

    //Task #5:
    tgaFile partFiveTga;
    partFiveTga.header = layerOneTga.header;
    partFiveTga.image = Image::overlay(layerOneTga.image, patternOneTga.image);

    writeFile("part5.tga", partFiveTga);

    //Task #6:
    tgaFile partSixTga;
    partSixTga.header = carTga.header;
    partSixTga.image = Image::greenChannel(carTga.image);

    writeFile("part6.tga", partSixTga);

    //Task #7:
    tgaFile partSevenTga;
    partSevenTga.header = carTga.header;
    partSevenTga.image = Image::redChannel(carTga.image);

    writeFile("part7.tga", partSevenTga);

    //Task #8

    //red portion
    tgaFile partEightRedTga;
    partEightRedTga.header = carTga.header;
    partEightRedTga.image = Image::OnlyRedChannel(carTga.image);

    //green portion
    tgaFile partEightGreenTga;
    partEightGreenTga.header = carTga.header;
    partEightGreenTga.image = Image::OnlyGreenChannel(carTga.image);

    //blue portion
    tgaFile partEightBlueTga;
    partEightBlueTga.header = carTga.header;
    partEightBlueTga.image = Image::OnlyBlueChannel(carTga.image);

    //writing all red green and blue portions
    writeFile("part8_r.tga", partEightRedTga);
    writeFile("part8_g.tga", partEightGreenTga);
    writeFile("part8_b.tga", partEightBlueTga);


    //Task 9
    tgaFile partNineTga;

    tgaFile redLayer = readFile("layer_red.tga");
    tgaFile greenLayer = readFile("layer_green.tga");
    tgaFile blueLayer = readFile("layer_blue.tga");

    partNineTga.header = redLayer.header;
    partNineTga.image = Image::CombineFiles(blueLayer.image, greenLayer.image, redLayer.image);

    writeFile("part9.tga", partNineTga);

    //Task 10
    tgaFile partTenTga;
    tgaFile textTwoTga = readFile("text2.tga");

    partTenTga.header = textTwoTga.header;
    partTenTga.image = Image::RotateFile(textTwoTga.image);

    writeFile("part10.tga", partTenTga);

    return 0;
}

//Function created to read in tga files
tgaFile readFile(std::string fileName) {

    std::ifstream inStream("../input/" + fileName, std::ios::binary);

    Header header{};
    header.readHeader(inStream);

    tgaFile file{};
    file.header = header;

    Image image{};
    image.height = header.height;
    image.width = header.width;
    image.readColorData(inStream);
    file.image = image;

    return file;

}

//Function that will write a tga file when called
void writeFile(std::string fileName, tgaFile file) {
    std::ofstream outStream("../output/" + fileName, std::ios::binary);

    file.header.writeHeader(outStream);
    file.image.writeColorData(outStream);

}

