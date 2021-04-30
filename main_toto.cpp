/* ZJW simple C++ code to write out a PPM file representing shapes */
#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include "ppmR.h"
#include "totoro.h"
#include "color.h"
#include "rect.h"
#include "ellipse.h"
#include "polygon.h"
#include "util.h"
#include <map>
#include <ctime>
#include <cstdlib>
#include "fileread.h"

using namespace std;

/*write out PPM data, using the defined implicit equation 
  interior points write a differnt color then exterior points */

void writeOut(ostream& out, ppmR& theWriter, vector<Totoro>& theGang){

	float res;
	color inC;
	bool inTrue;
	color dummy;
	color drawC;
	color background(252, 241, 210);

	//for every point in the 2D space
	for (int y=0; y < theWriter.height; y++) {
		for (int x =0; x < theWriter.width; x++) {
			inC = background;
			for(Totoro t : theGang){
				dummy = t.eval(x, y, background);
				if(dummy == background){
				} else {

					inC = dummy;
				}
			}
			theWriter.writePixel(out, x, y, inC);
		}
		theWriter.writeNewLine(out);
	}
}

/*read command line arguments and write out new ascii file of given size */
int main(int argc, char *argv[]) {

	ofstream outFile;
	int sizeX, sizeY;

	vector<Totoro> squad;
	//squad.push_back(Totoro(100, 100, color(252, 210, 236)));
	/*
	   vector<shared_ptr<ellipse> > Es;
	   vector<shared_ptr<Rect> > Rs;
	   vector<shared_ptr<Polygon> > Ps;	
	 */
	//readFile("totoro.csv", Es, Rs, Ps);


	if (argc < 4) {
		cerr << "Error format: main sizeX sizeY outfileName" << endl;
	} else {
		srand(std::time(0));
		sizeX = stoi(argv[1]);
		sizeY = stoi(argv[2]);
		int row;
		int col;
		int rowLen = 4;
		for(int i = 0; i < 8; i++){
			col = i % rowLen;
			row = i / rowLen;
			squad.push_back(Totoro(
				200 - row * 100 + col * 200, 
				270 + row * 150,
				color::random(10, 250)));

			//squad.push_back(Totoro(nicerRand(0, sizeX - 200), nicerRand(0, sizeY - 300), color::random(10, 250)));
		}
		squad.push_back(Totoro(900, 420, color(252, 210, 236)));
		ppmR theWriter(sizeX, sizeY);
		outFile.open(argv[3]);
		if (outFile) {
			cout << "writing an image of size: " << sizeX << " " << sizeY << " to: " << argv[3] << endl;
			theWriter.writeHeader(outFile);
			writeOut(outFile, theWriter, squad);
		} else {
			cout << "Error cannot open outfile" << endl;
			exit(0);
		}
	}

}
