#include "ImageFunctions.h"

void openIOFiles(ifstream& fin, ofstream& fout, char inputFilename[],string &k)
{
	// define filestreams
	char outputFilename[MAXLEN];

	// prompt user for input file
	cout << "enter filename ";
	cin >> inputFilename;
	// open .ppm binary file for input
	fin.open(inputFilename, ios::binary);

	if (!fin) {
		cout << "could not open file: bye" << endl;
		exit(1);
	}

	// generate meaningful output filename
	strcpy_s(outputFilename, inputFilename);

	// terminate output fielname at .
	char* loc = strchr(outputFilename, '.');
	*loc = '\0';

	// add extension to name
	strcat_s(outputFilename, "P3.ppm");
	//strcat_s("C:\\Users\\user\\Desktop\\New folder (8)\\out\\",outputFilename);
	// open .ppm ascii file for output
	fout.open(outputFilename);
	k = outputFilename;
	
	if (!fout) {
		cout << "cannot open output file: bye" << endl;
	}

}
void sharpen(vector<vector<Pixel> >& image)
{

	int h = image.size();
	int w = image[0].size();

	Pixel SharpPixel;
	for (int i = 1; i < h-1; i++)
		for (int j = 1; j < w-1; j++)
		{
			SharpPixel = image[i - 1][j - 1] *0 + image[i - 1][j] *-0.5 + image[i - 1][j + 1] *0 + image[i][j - 1] *-0.5 + image[i][j] * 2 + image[i][j + 1] *-0.5 + image[i + 1][j - 1] *0 + image[i + 1][j] * -0.5 + image[i + 1][j + 1] *0;
			
			if ((SharpPixel.getBlue() > 255) == true)
			{
				SharpPixel = 255;
			}
			image[i][j] = SharpPixel;

		}

}


void edgeDetection(vector<vector<Pixel> >& image)
{
	int h = image.size();
	int w = image[0].size();
	
	Pixel horPixel;
	
	for (int i = 1; i < h - 1; i++)
		for (int j = 1; j < w - 1; j++)
		{
			horPixel = image[i - 1][j - 1] *-1 + image[i - 1][j] * 0 + image[i - 1][j + 1] *-1 + image[i][j - 1] * 0  + image[i][j + 1] * 0 + image[i][j] * 4 + image[i + 1][j - 1] * -1 + image[i + 1][j] * 0 + image[i + 1][j + 1] * -1;
			if ((horPixel.getBlue() > 255) == true)
			{
				horPixel = 255;
			}
			image[i][j] = horPixel;
		}

}

void convertP6ToP3(ifstream& bin, ofstream& out, vector<vector<Pixel> >& image, int info[1])
{
	readHeader(bin, out, info);
	int width = info[0], height = info[1];
	readAndWriteImageData(bin, out, image, width, height);
}


void smooth(vector<vector<Pixel> >& image)
{
	int h = image.size();
	int w = image[0].size();

	Pixel sum;
	for (int i = 1; i < h - 1; i++)
		for (int j = 1; j < w - 1; j++)
		{
			sum = image[i + 1][j] + image[i - 1][j] + image[i][j + 1] + image[i][j - 1];
			sum = sum / 4;
			
			image[i][j] = sum;
		}
}

void writeP3Image(ofstream& out, vector<vector<Pixel> >& image, string comment, int maxColor)
{
	int h, w, pCount(0);
	char magicNumber[3] = "P3";
	h = (int)image.size();
	w = (int)image[0].size();

	writeHeader(out, magicNumber, comment, w, h, maxColor);
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++)
		{
			out << image[i][j];
			++pCount;
			if (pCount == 10) {
				out << newline;
				pCount = 0;
			}
			else out << ' ';
		}
	}
	out.close();
}


void readAndWriteImageData(ifstream& fin, ofstream& fout, vector<vector<Pixel> >& image, int w, int h)
{
	// read and write image data
	// define input variables

	int charCount = 0;
	char colorByte;
	unsigned char aChar;
	unsigned int triple[3];   // red, green, blue

	// allocate memory
	image.resize(h); // allocate h rows

	for (int i = 0; i < h; i++)
	{
		image[i].resize(w);   // for each row allocate w columns
		for (int j = 0; j < w; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				// read one byte
				fin.read(&colorByte, 1);

				// convert to unsigned char
				aChar = (unsigned char)colorByte;

				// save as unsigned int
				triple[k] = (unsigned int)aChar;

				// write as int
				fout << triple[k] << ' ';
			}
			// CR printed over 32 pixels
			++charCount;
			if (charCount == 32) {
				fout << "\r\n";
				charCount = 0;
			}
			image[i][j].setPixel(triple[0], triple[1], triple[2]);
		}
	}
}

void readHeader(ifstream& fin, ofstream& fout, int imageInfo[])
{
	// define and initialise input variables
	char bData[MAXLEN] = { 0 }, magicNumber[MAXWIDTH], comment[MAXLEN] = { "#" };
	int bIndex = 0, charCount = 0, infoCount = 0;
	char ch, aNumber[MAXWIDTH];
	// input first line of text header(magic number)
	// if the magic number is not P6 exit the program
	fin.getline(magicNumber, 3);
	if (strcmp(magicNumber, "P6") != 0)
	{
		cout << "unexpected file format\n";
		exit(1);
	}
	// clear bData array and reset bIndex
	// input next line of text header
	strcpy_s(bData, " ");
	bIndex = 0;
	fin.getline(bData, MAXLEN);
	do {
		// is this the beginning of a comment
		ch = bData[bIndex];
		if (ch == '#') {
			// comment has been read
			// get all characters until a newline is found
			charCount = 0;
			while (ch != terminator && charCount < MAXLEN) {
				comment[charCount] = ch;
				++bIndex;
				++charCount;
				ch = bData[bIndex];
				cout << ch;
			}
			if ((charCount == MAXLEN) && (ch != newline)) {
				cout << "comment exceeded max length of " << MAXLEN << endl;
				exit(1);
			}
			// get the next line of data
			strcpy_s(bData, " ");
			bIndex = 0;
			fin.getline(bData, MAXLEN);
		}
		else {
			// this is not a comment
			// parse bData for image information
			charCount = 0;
			// look past whitespace
			while (bIndex < MAXLEN && isspace(bData[bIndex])) {
				++bIndex;
			}
			// may be the beginning of a decimal value
			while (bIndex < MAXLEN && isdigit(bData[bIndex]))
			{
				aNumber[charCount] = bData[bIndex];
				++bIndex;
				++charCount;
				if (charCount == MAXWIDTH)
				{
					cerr << "Maximum width of " << MAXWIDTH << " digits was exceeded.. " << endl;
					exit(1);
				}
			}

			// look at size of aNumber
			if (charCount > 0) {
				// we have image information, terminate string
				aNumber[charCount] = nullChar;
				// convert from ascii to integer
				imageInfo[infoCount] = atoi(aNumber);
				++infoCount;
				// verify input
				switch (infoCount) {
				case 1: cout << "a width of " << imageInfo[infoCount - 1] << " has been read " << endl;
					break;
				case 2: cout << " a height of " << imageInfo[infoCount - 1] << " has been read " << endl;
					break;
				case 3: cout << "maxcolor of " << imageInfo[infoCount - 1] << " has been read " << endl;
					break;
				}
			}
			else if (infoCount < 3) {
				// aNumber has 0 digits and infoCount < 3
				// we need more image information
				// get next line of data and parse for image information
				strcpy_s(bData, " ");
				bIndex = 0;
				fin.getline(bData, MAXLEN);
			}
		}
	} while (infoCount < 3 && !fin.eof());
	if (infoCount < 3) {
		cerr << "image information could not be found " << endl;
		exit(1);
	}
	// we have all of the information
	// write header to ascii file
	strcpy_s(magicNumber, "P3");
	writeHeader(fout, magicNumber, comment, imageInfo[0], imageInfo[1], imageInfo[2]);
}

void writeHeader(ofstream& fout, char magicNumber[], string comment, int w, int h, int maxPixelVal)
{
	// write image imformation to output file
	fout << magicNumber << newline;
	fout << comment << newline;
	fout << w << ' ' << h << ' ' << maxPixelVal << newline;
}

