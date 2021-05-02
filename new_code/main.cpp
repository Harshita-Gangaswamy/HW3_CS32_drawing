/* ZJW simple C++ code to write out a PPM file representing shapes */

#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <map>
#include <ctime>
#include <cstdlib>
#include "ppmR.h"
#include "color.h"
#include "rect.h"
#include "ellipse.h"
#include "polygon.h"
#include "util.h"
#include "UFO.h"
#include "night.h"
#include "totoro.h"
#include <string>

using namespace std;


/*write out PPM data, using the defined implicit equation
  interior points write a differnt color then exterior points */

//This is getting so ugly, so glad we get to fix it soon
void writeOut(ostream &out, ppmR &theWriter,
              const vector<shared_ptr<ellipse>> &IEs, const vector<shared_ptr<Rect>> &Rs,
              const vector<shared_ptr<Polygon>> &Ps, const vector<shared_ptr<UFO>> &Ds, night scene, vector<Totoro>& theGang) {

    float res;
    color inC;
    color background(12, 34, 56);
    color dummy;
    //color drawC;
    bool inTrue = false;
    double curDepth = -1.0;

    //for every point in the 2D space
    	//for every point in the 2D space
	// for (int y = 0; y < theWriter.height; y++)
	// {
	// 	for (int x = 0; x < theWriter.width; x++)
	// 	{
	// 		theWriter.writePixel(out, x, y, scene.eval(x,y,color(12, 34, 56)));
	// 	}
	// 	theWriter.writeNewLine(out);
	// }

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
            for(Totoro t : theGang){
				dummy = t.eval(x, y, background);
				if(dummy == background){} else {
					inC = dummy;
					inTrue = true;
				}
			}

            if (inTrue) {
                theWriter.writePixel(out, x, y, inC);
            } else {
                //theWriter.writePixel(out, x, y, background);
                theWriter.writePixel(out, x, y, scene.eval(x,y,color(12, 34, 56)));
			}
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
    theDrawings.push_back(make_shared<UFO>(vec2(150, 200), 1, 0, colors));
    theDrawings.push_back(make_shared<UFO>(vec2(750, 350), 1, 2));
    theDrawings.push_back(make_shared<UFO>(vec2(720, 250), 1.5, 1));

	//stars
	vector<shared_ptr<Polygon> > thePolys;
	vector<vec2> star1;
	star1.push_back(vec2(25, 25));
	star1.push_back(vec2(30, 20));
	star1.push_back(vec2(35, 25));
	star1.push_back(vec2(30, 30));
	thePolys.push_back(make_shared<Polygon>(star1, 5, color(255, 215, 0)));

	vector<vec2> star2;
	star2.push_back(vec2(100, 80));
	star2.push_back(vec2(105, 75));
	star2.push_back(vec2(110, 80));
	star2.push_back(vec2(105, 85));
	thePolys.push_back(make_shared<Polygon>(star2, 5, color(255, 215, 0)));

	vector<vec2> star3;
	star3.push_back(vec2(800, 70));
	star3.push_back(vec2(805, 65));
	star3.push_back(vec2(810, 70));
	star3.push_back(vec2(805, 75));
	thePolys.push_back(make_shared<Polygon>(star3, 5, color(255, 215, 0)));

	vector<vec2> star4;
	star4.push_back(vec2(700, 90));
	star4.push_back(vec2(705, 85));
	star4.push_back(vec2(710, 90));
	star4.push_back(vec2(705, 95));
	thePolys.push_back(make_shared<Polygon>(star4, 5, color(255, 215, 0)));

	vector<vec2> star5;
	star5.push_back(vec2(300, 300));
	star5.push_back(vec2(305, 295));
	star5.push_back(vec2(310, 300));
	star5.push_back(vec2(305, 305));
	thePolys.push_back(make_shared<Polygon>(star5, 5, color(255, 215, 0)));

	//big stars
	vector<vec2> bigstar1;
	bigstar1.push_back(vec2(280, 50));
	bigstar1.push_back(vec2(287, 42));
	bigstar1.push_back(vec2(295, 35));
	bigstar1.push_back(vec2(303, 42));
	bigstar1.push_back(vec2(310, 50));
	bigstar1.push_back(vec2(303, 58));
	bigstar1.push_back(vec2(295, 65));
	bigstar1.push_back(vec2(287, 58));
	thePolys.push_back(make_shared<Polygon>(bigstar1, 5, color(255, 215, 0)));

	vector<vec2> bigstar2;
	bigstar2.push_back(vec2(50, 100));
	bigstar2.push_back(vec2(57, 92));
	bigstar2.push_back(vec2(65, 85));
	bigstar2.push_back(vec2(73, 92));
	bigstar2.push_back(vec2(80, 100));
	bigstar2.push_back(vec2(73, 108));
	bigstar2.push_back(vec2(65, 115));
	bigstar2.push_back(vec2(57, 108));
	thePolys.push_back(make_shared<Polygon>(bigstar2, 5, color(255, 215, 0)));
	//Moon
	vector<shared_ptr<ellipse> > moon;
	vector<color> moonC;
	moonC.push_back(color(255, 247, 205));
	moonC.push_back(color(255, 243, 179));
	moonC.push_back(color(255, 239, 154));
	moonC.push_back(color(255, 235, 129));
	moonC.push_back(color(255, 231, 103));
	moonC.push_back(color(255, 227, 78));
	moonC.push_back(color(255, 223, 52));
	moonC.push_back(color(255, 219, 26));
	moonC.push_back(color(255, 215, 1));
	double sizeC = 70;
	double sizeLC = 46;
	for (int i = 0; i < 9; i++)
	{
		moon.push_back(make_shared<ellipse>(1000, 100, sizeC, sizeC, i, moonC[i]));
		sizeC -= 3;
	}
	for (int j = 19; j > 10; j--)
	{
		moon.push_back(make_shared<ellipse>(984, 86, sizeLC, sizeLC, j, moonC[19 - j]));

		sizeLC += 1;
	}
	moon.push_back(make_shared<ellipse>(975, 75, 50, 50, 20, color(12, 34, 56)));
	moon.push_back(make_shared<ellipse>(975, 75, 50, 50, 20, color(12, 34, 56)));
	moon.push_back(make_shared<ellipse>(950, 60, 40, 40, 20, color(12, 34, 56)));


	//mountains
	vector<shared_ptr<ellipse> > Mountain;
	vector<color> Mountain_color;
	Mountain_color.push_back(color(153, 153, 0));
	Mountain_color.push_back(color(102, 51, 0));

	Mountain.push_back(make_shared<ellipse>(vec2(400,480),vec2(400,150),0,Mountain_color[1]));
	Mountain.push_back(make_shared<ellipse>(vec2(1040,480),vec2(240,120),0,Mountain_color[0]));


	//Grassland
	double Road_Width = 200;
    double Road_Position = 550;
    color Road_Color(70, 80, 90);
    color Land_Color(63, 98, 21);
	vector<shared_ptr<Rect>> ground;
	vector<shared_ptr<ellipse>> path;
    ground.push_back(make_shared<Rect>(vec2(0,480), vec2(1280,720), Land_Color, 1));
    ground.push_back(make_shared<Rect>(vec2(Road_Position,480), vec2(Road_Position+Road_Width, 1280), Road_Color, 2));
    path.push_back(make_shared<ellipse>(vec2(Road_Position+36, 540), vec2(70, 70), 3, Road_Color));
    path.push_back(make_shared<ellipse>(vec2(Road_Position-36, 660), vec2(70, 70), 4, Land_Color));
    path.push_back(make_shared<ellipse>(vec2(Road_Position+Road_Width+36, 540), vec2(70, 70), 4, Land_Color));
    path.push_back(make_shared<ellipse>(vec2(Road_Position+Road_Width-36, 660), vec2(70, 70), 3, Road_Color));

    //cloud1
	vector<shared_ptr<ellipse>> cloud1;
    color cloud_c(169,169,169);
    cloud1.push_back(make_shared<ellipse>(vec2(250, 185),vec2(75,35),4,cloud_c));
    cloud1.push_back(make_shared<ellipse>(vec2(250, 215),vec2(25,25),4,cloud_c));
    cloud1.push_back(make_shared<ellipse>(vec2(250, 155),vec2(25,25),4,cloud_c));
    cloud1.push_back(make_shared<ellipse>(vec2(215, 215),vec2(25,25),4,cloud_c));
    cloud1.push_back(make_shared<ellipse>(vec2(215, 155),vec2(25,25),4,cloud_c));
    cloud1.push_back(make_shared<ellipse>(vec2(285, 215),vec2(25,25),4,cloud_c));
    cloud1.push_back(make_shared<ellipse>(vec2(285, 155),vec2(25,25),4,cloud_c));

	//cloud2
	vector<shared_ptr<ellipse> > cloud2;
	cloud2.push_back(make_shared<ellipse>(900,230,30,30,color(169,169,169)));
	cloud2.push_back(make_shared<ellipse>(875,200,30,30,color(169,169,169)));
	cloud2.push_back(make_shared<ellipse>(830,200,30,30,color(169,169,169)));
	cloud2.push_back(make_shared<ellipse>(785,200,30,30,color(169,169,169)));
	cloud2.push_back(make_shared<ellipse>(760,230,30,30,color(169,169,169)));
	cloud2.push_back(make_shared<ellipse>(785,260,30,30,color(169,169,169)));
	cloud2.push_back(make_shared<ellipse>(830,260,30,30,color(169,169,169)));
	cloud2.push_back(make_shared<ellipse>(875,260,30,30,color(169,169,169)));
	cloud2.push_back(make_shared<ellipse>(830,230,100,30,color(169,169,169)));

	night a(moon,thePolys,ground,Mountain,path,cloud1,cloud2);

    vector<Totoro> squad;

    if (argc < 4) {
        cerr << "Error format: a.out sizeX sizeY outfileName" << endl;
    } else {
        srand(std::time(0)); //t

        sizeX = stoi(argv[1]);
        sizeY = stoi(argv[2]);
        int row;
		int col;
		int rowLen = 4;
		for(int i = 0; i < 2; i++){
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
            writeOut(outFile, theWriter, theEllipses, theRects, thePolygons, theDrawings, a, squad);
        } else {
            cout << "Error cannot open outfile" << endl;
            exit(0);
        }
    }

}
