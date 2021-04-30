#ifndef TOTORO_H
#define TOTORO_H

#include "vec2.h"
#include "color.h"
#include "rect.h"
#include "ellipse.h"
#include "polygon.h"
#include <map>
#include <memory>
#include <vector>

class Totoro {
public:
	Totoro();
	// default constructor, puts a totoro with top left corner at 0, 0

	Totoro(double x, double y);
	// constructor puts a toto with top left corner at at x, y

	Totoro(double x, double y, color c);
	// constructor puts a toto at x, y, with base colour c

	color eval(double x, double y, color background);
	// returns colour at x, y

	void translate(double x, double y);
	// "moves" toro

	vec2 getPos() const;
	// accessor: coordinates of top left corner

	color getColour() const;
	// accessor: base colour

	void setPos(double x, double y);

private:
	vec2 pos; 
	// top left corner

	color base; 
	// base colour

	std::vector<shared_ptr<ellipse> > Es;
	std::vector<shared_ptr<Rect> > Rs;
	std::vector<shared_ptr<Polygon> > Ps;
	// vectors of pointers to atomic shapes

	std::map<std::string, color> colourMap;
	// stores "base", "white", and "black"
};
#endif
