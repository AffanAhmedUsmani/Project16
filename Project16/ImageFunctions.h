#pragma once
#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include "Pixel.h"
using namespace std;

const int MAXWIDTH(5);
const int MAXLEN(1000);
const char newline('\n');
const char terminator('@');
const char nullChar('\0');



void openIOFiles(ifstream& fin, ofstream& fout, char inputFilename[], string &k);
void convertP6ToP3(ifstream& bin, ofstream& out, vector<vector<Pixel> >& image, int info[1]);
void smooth(vector<vector<Pixel> >& image);
void writeP3Image(ofstream& out, vector<vector<Pixel> >& image, string comment, int maxColor);
void readAndWriteImageData(ifstream& fin, ofstream& fout, vector<vector<Pixel> >& image, int w, int h);
void readHeader(ifstream& fin, ofstream& fout, int imageInfo[]);
void writeHeader(ofstream& fout, char magicNumber[], string comment, int w, int h, int maxPixelVal);
void sharpen(vector<vector<Pixel> >& image );
void edgeDetection(vector<vector<Pixel> >& image);




