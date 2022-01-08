#include"Pixel.h"
#include"ImageFunctions.h"
#include<iostream>
#include<fstream>
#include<string>
using namespace std;
int main()
{
	char filename[300];
	int info[1];
	ifstream bar("C:\\Users\\user\\Desktop\\New folder (8)\\in");
	ofstream foo;
	foo.open("C:\\Users\\user\\Desktop\\New folder (8)\\out");
	string K;
	openIOFiles(bar, foo, filename, K);

	string temp = K;

	cout << temp;

	ofstream outputfile;
	outputfile.open("C:\\Users\\user\\Desktop\\New folder (8)\\out\\" + temp);
	if (!outputfile) {
		cout << "cannot open output file: bye" << endl;
	}
	vector<vector<Pixel> > image;

	convertP6ToP3(bar, outputfile, image, info);

	cout << "\n p6 to p3 successfully converted and the file saved in following directory  \n ";
	cout << "C:\\Users\\user\\Desktop\\New folder(8)\\out\\" + temp;
	cout << "\n * press 1 for applying smooth filter \n * press 2 for applying sharp filter \n * press 3 for applying edge detection filter";

	string comment = "# normal p3";

	char type = '0';

	cin >> type;
while (type != '5')
{

	
	if (type == '1')
	{
		ofstream output;
		output.open("C:\\Users\\user\\Desktop\\New folder (8)\\out\\smooth" + temp);
		if (!output) {
			cout << "cannot open output file: bye" << endl;
		}

		smooth(image);
		writeP3Image(output, image, comment, 255);
		cout << "\n p3 successfully applied smooth filter and the file saved in following directory  \n ";
		cout << "C:\\Users\\user\\Desktop\\New folder(8)\\out\\smooth" + temp;

	}
	else if (type == '2')
	{
		ofstream output1;
		output1.open("C:\\Users\\user\\Desktop\\New folder (8)\\out\\sharp" + temp);
		if (!output1) {
			cout << "cannot open output file: bye" << endl;
		}

		sharpen(image);
		writeP3Image(output1, image, comment, 255);

		cout << "\n p3 successfully applied sharpen filter and the file saved in following directory  \n ";
		cout << "C:\\Users\\user\\Desktop\\New folder(8)\\out\\sharp" + temp;
	}
	else if (type == '3')
	{
		ofstream output2;
		output2.open("C:\\Users\\user\\Desktop\\New folder (8)\\out\\edgedetection" + temp);
		if (!output2) {
			cout << "cannot open output file: bye" << endl;
		}

		edgeDetection(image);
		writeP3Image(output2, image, comment, 255);

		cout << "\n p3 successfully applied edgedetection filter and the file saved in following directory  \n ";
		cout << "C:\\Users\\user\\Desktop\\New folder(8)\\out\\edgedetection" + temp;
	}
	else
	{
		cout << "\n \t press the right key or press 5 to quit ";

	}
	cin >> type;

}
		
	

	
	system("pause");
	return 0;
}