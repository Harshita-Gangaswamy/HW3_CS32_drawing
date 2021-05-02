#include "totoro.h"

Totoro::Totoro(double x, double y, color c){
	colourMap["base"] = c;
	colourMap["white"] = color(255, 255, 255);
	colourMap["black"] = color(0, 0, 0);
	Es.push_back(make_shared<ellipse>(100, 100, 72, 75, 10.0, colourMap["base"]));
	Es.push_back(make_shared<ellipse>(100, 175, 100, 125, 10.0, colourMap["base"]));
	Es.push_back(make_shared<ellipse>(75, 200, 75, 100, 10.0, colourMap["base"]));
	Es.push_back(make_shared<ellipse>(125, 200, 75, 100, 10.0, colourMap["base"]));
	Es.push_back(make_shared<ellipse>(62, 36, 7.5, 10, 10.0, colourMap["base"]));
	Es.push_back(make_shared<ellipse>(138, 36, 7.5, 10, 10.0, colourMap["base"]));
	Es.push_back(make_shared<ellipse>(68, 60, 11.5, 10, 11.0, colourMap["white"]));
	Es.push_back(make_shared<ellipse>(132, 60, 11.5, 10, 11.0, colourMap["white"]));
	Es.push_back(make_shared<ellipse>(100, 190, 85, 100, 11.0, colourMap["white"]));
	Es.push_back(make_shared<ellipse>(70, 60, 5, 5, 12.0, colourMap["black"]));
	Es.push_back(make_shared<ellipse>(130, 60, 5, 5, 12.0, colourMap["black"]));
	Es.push_back(make_shared<ellipse>(100, 64, 16.5, 4.5, 12.0, colourMap["black"]));
	std::vector<vec2> verts1 = {vec2(64, 0), vec2(74, 34), vec2(54, 34)};
	Ps.push_back(make_shared<Polygon>(verts1, 18.0, colourMap["base"]));
	std::vector<vec2> verts2 = {vec2(136, 0), vec2(146, 34), vec2(126, 34)};
	Ps.push_back(make_shared<Polygon>(verts2, 18.0, colourMap["base"]));
	std::vector<vec2> verts3 = {vec2(100, 120), vec2(110, 130), vec2(90, 130)};
	Ps.push_back(make_shared<Polygon>(verts3, 18.0, colourMap["base"]));
	std::vector<vec2> verts4 = {vec2(130, 130), vec2(140, 140), vec2(120, 140)};
	Ps.push_back(make_shared<Polygon>(verts4, 18.0, colourMap["base"]));
	std::vector<vec2> verts5 = {vec2(70, 130), vec2(80, 140), vec2(60, 140)};
	Ps.push_back(make_shared<Polygon>(verts5, 18.0, colourMap["base"]));
	std::vector<vec2> verts6 = {vec2(150, 140), vec2(160, 150), vec2(140, 150)};
	Ps.push_back(make_shared<Polygon>(verts6, 18.0, colourMap["base"]));
	std::vector<vec2> verts7 = {vec2(50, 140), vec2(60, 150), vec2(40, 150)};
	Ps.push_back(make_shared<Polygon>(verts7, 18.0, colourMap["base"]));
	std::vector<vec2> verts8 = {vec2(115, 140), vec2(125, 150), vec2(105, 150)};
	Ps.push_back(make_shared<Polygon>(verts8, 18.0, colourMap["base"]));
	std::vector<vec2> verts9 = {vec2(85, 140), vec2(95, 150), vec2(75, 150)};
	Ps.push_back(make_shared<Polygon>(verts9, 18.0, colourMap["base"]));
	Rs.push_back(make_shared<Rect>(23, 70, 58, 70, colourMap["black"], 12.0));
	Rs.push_back(make_shared<Rect>(17, 75, 52, 75, colourMap["black"], 12.0));
	Rs.push_back(make_shared<Rect>(25, 80, 60, 80, colourMap["black"], 12.0));
	Rs.push_back(make_shared<Rect>(142, 70, 177, 70, colourMap["black"], 12.0));
	Rs.push_back(make_shared<Rect>(148, 75, 183, 75, colourMap["black"], 12.0));
	Rs.push_back(make_shared<Rect>(140, 80, 175, 80, colourMap["black"], 12.0));
	pos.setX(x);
	pos.setY(static_cast<int>(y));
	// whiskers are 1px tall, will not show if y-val is non-integer
}

Totoro::Totoro(double x, double y) :
	Totoro(x, y, color(127, 130, 128)) {}

Totoro::Totoro() : Totoro(0, 0) {}

vec2 Totoro::getPos() const {
	return pos;
}

color Totoro::getColour() const {
	return colourMap.at("base");
}

void Totoro::setPos(double x, double y){
	pos.setX(x);
	pos.setY(y);
}

color Totoro::eval(double x, double y, color background){
	color inC = background;
	double curDepth = -1;
	double res;
	//iterate through all possible equations (note 'front' determined by order in std::vector)

	for (auto eq : Es) {
		res = eq->eval(x - pos.x(), y - pos.y());
		if (res < 0 && eq->getDepth() > curDepth) {
			inC = eq->getInC();
			curDepth = eq->getDepth();
		}
	}
	for (auto rect: Rs) {
		if (rect->evalIn(x - pos.x(), y - pos.y()) && rect->getDepth() > curDepth){
			inC = rect->getInC();
			curDepth = rect->getDepth();
		}
	}

	for (auto poly:Ps) {
		if (poly->eval(x - pos.x(), y - pos.y()) && poly->getDepth() > curDepth){
			inC = poly->getInC();
			curDepth = poly->getDepth();
		}
	}

	return inC;
}


void Totoro::translate(double x, double y){
	pos.setX(pos.x() + x);
	pos.setY(pos.y() + y);
}
