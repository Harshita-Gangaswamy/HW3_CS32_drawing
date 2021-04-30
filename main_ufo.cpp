/* ZJW simple C++ code to write out a PPM file representing shapes */

#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include "ppmR.h"
#include "color.h"
#include "rect.h"
#include "ellipse.h"
#include "polygon.h"
#include "util.h"
#include "UFO.h"

using namespace std;


/*write out PPM data, using the defined implicit equation
  interior points write a differnt color then exterior points */

//This is getting so ugly, so glad we get to fix it soon
void writeOut(ostream &out, ppmR &theWriter,
              const vector<shared_ptr<ellipse>> &IEs, const vector<shared_ptr<Rect>> &Rs,
              const vector<shared_ptr<Polygon>> &Ps, const vector<shared_ptr<UFO>> &Ds) {

    float res;
    color inC;
    color background(12, 34, 56);
    bool inTrue = false;
    double curDepth = -1.0;

    //for every point in the 2D space
    for (int y = 0; y < theWriter.height; y++) {
        for (int x = 0; x < theWriter.width; x++) {

            inTrue = false;
            curDepth = -1;
            //iterate through all possible equations
            for (auto eq : IEs) {
                res = eq->eval(x, y);
                if (res < 0 && eq->getDepth() > curDepth) {
                    inC = eq->getInC();
                    inTrue = true;
                    curDepth = eq->getDepth();
                }
            }
            /* compare my ret.h with yours */
            for (const auto &rect: Rs) {
                if (rect->getDepth() > curDepth && rect->evalIn(x, y)) {
                    inC = rect->getInC();
                    inTrue = true;
                    curDepth = rect->getDepth();
                }
            }

            //loop through any polygons
            for (const auto &poly: Ps) {
                if (poly->getDepth() > curDepth && poly->eval(x, y)) {
                    inC = poly->getInC();
                    inTrue = true;
                    curDepth = poly->getDepth();
                }
            }
            //loop through Drawings
            for (const auto &draw: Ds) {
                color drawC;
                if (draw->getDepth() > curDepth && !((drawC = draw->eval(x, y, background)) == background)) {
                    inTrue = true;
                    inC = drawC;
                    curDepth = draw->getDepth();
                }
            }
            if (inTrue) {
                theWriter.writePixel(out, x, y, inC);
            } else
                theWriter.writePixel(out, x, y, background);
        }
        theWriter.writeNewLine(out);
    }
}


/*read command line arguments and write out new ascii file of given size */
int main(int argc, char *argv[]) {

    ofstream outFile;
    int sizeX, sizeY;

    vector<shared_ptr<ellipse>> theEllipses;
    vector<shared_ptr<Rect>> theRects;
    vector<shared_ptr<Polygon>> thePolygons;
    vector<shared_ptr<UFO>> theDrawings;

    const vector<color> colors = vector<color>{
            color(255, 124, 124),
            color(176, 219, 237),
            color(200, 136, 255),
            color(55, 188, 51),
            color(40, 100, 40)
    };
    theDrawings.push_back(make_shared<UFO>(vec2(150, 250), 1, 0, colors));
    theDrawings.push_back(make_shared<UFO>(vec2(750, 400), 1, 2));
    theDrawings.push_back(make_shared<UFO>(vec2(720, 300), 1.5, 1));


    if (argc < 4) {
        cerr << "Error format: a.out sizeX sizeY outfileName" << endl;
    } else {
        sizeX = stoi(argv[1]);
        sizeY = stoi(argv[2]);
        ppmR theWriter(sizeX, sizeY);
        outFile.open(argv[3]);
        if (outFile) {
            cout << "writing an image of size: " << sizeX << " " << sizeY << " to: " << argv[3] << endl;
            theWriter.writeHeader(outFile);
            writeOut(outFile, theWriter, theEllipses, theRects, thePolygons, theDrawings);
        } else {
            cout << "Error cannot open outfile" << endl;
            exit(0);
        }
    }

}
