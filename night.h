#ifndef NIGHT_H
#define NIGHT_H
#include <vector>
#include <memory>
#include "ellipse.h"
#include "rect.h"
#include "polygon.h"
#include "color.h"

class night
{
public:
	night(vector<shared_ptr<ellipse> > inM, vector<shared_ptr<Polygon> > inS, vector<shared_ptr<Rect> > inG,
		  vector<shared_ptr<ellipse> > inMoun, vector<shared_ptr<ellipse> > inP, vector<shared_ptr<ellipse> > inC1,
		  vector<shared_ptr<ellipse> > inC2)
	{
		moon = inM, stars = inS, ground = inG, mountains = inMoun, path = inP, cloud1 = inC1, cloud2 = inC2;
	}

	color eval(int x, int y, color background)
	{
		float res;
		color inC;
		bool inTrue = false;
		double curDepth = -1.0;
		for (auto obj : moon)
		{
			//evaluate the head
			res = obj->eval(x, y);
			if (res < 0 && obj->getDepth() > curDepth)
			{
				inC = obj->getInC();
				inTrue = true;
				curDepth = obj->getDepth();
			}
		}
		for (auto obj : mountains)
		{
			//evaluate the head
			res = obj->eval(x, y);
			if (res < 0 && obj->getDepth() > curDepth)
			{
				inC = obj->getInC();
				inTrue = true;
				curDepth = obj->getDepth();
			}
		}
		for (auto obj : cloud1)
		{
			//evaluate the head
			res = obj->eval(x, y);
			if (res < 0 && obj->getDepth() > curDepth)
			{
				inC = obj->getInC();
				inTrue = true;
				curDepth = obj->getDepth();
			}
		}
		for (auto obj : cloud2)
		{
			//evaluate the head
			res = obj->eval(x, y);
			if (res < 0 && obj->getDepth() > curDepth)
			{
				inC = obj->getInC();
				inTrue = true;
				curDepth = obj->getDepth();
			}
		}
		for (auto obj : path)
		{
			//evaluate the head
			res = obj->eval(x, y);
			if (res < 0 && obj->getDepth() > curDepth)
			{
				inC = obj->getInC();
				inTrue = true;
				curDepth = obj->getDepth();
			}
		}
		for (auto rect : ground)
		{
			if (rect->evalIn(x, y) && rect->getDepth() > curDepth)
			{
				inC = rect->getInC();
				inTrue = true;
				curDepth = rect->getDepth();
			}
		}
		for (auto poly : stars)
		{
			if (poly->eval(x, y) && poly->getDepth() > curDepth)
			{
				inC = poly->getInC();
				inTrue = true;
				curDepth = poly->getDepth();
			}
		}
		if (inTrue)
		{
			return inC;
		}
		else
			return background;
	}
	//getter
	vector<shared_ptr<ellipse> > getMoon() {return moon;}
	vector<shared_ptr<Polygon> > getStars() {return stars;}
	vector<shared_ptr<Rect> > getGround() {return ground;}
	vector<shared_ptr<ellipse> > getMountains() {return mountains;}
	vector<shared_ptr<ellipse> > getCloud1() {return cloud1;}
	vector<shared_ptr<ellipse> > getCloud2() {return cloud2;}
	vector<shared_ptr<ellipse> > getPath() {return path;}
	//setter
	void setMoon(vector<shared_ptr<ellipse> > Moon) {moon = Moon;}
	void setStars(vector<shared_ptr<Polygon> > Stars) {stars = Stars;}
	void setGround(vector<shared_ptr<Rect> > Ground) {ground = Ground;}
	void setMountains(vector<shared_ptr<ellipse> > Mountains) {mountains = Mountains;}
	void setCloud1(vector<shared_ptr<ellipse> > Cloud1) {cloud1 = Cloud1;}
	void setCloud2(vector<shared_ptr<ellipse> > Cloud2) {cloud2 = Cloud2;}
	void setPath(vector<shared_ptr<ellipse> > Path) {path = Path;}
	//translater
	night& translate(vec2 inC)
	{
		for(unsigned int i=0;i<stars.size();i++)
		{
			stars.at(i)->translate(inC);
		}
		for(unsigned int j=0;j<cloud1.size();j++)
		{
			cloud1.at(j)->translate(inC);
		}
		for(unsigned int k=0;k<cloud2.size();k++)
		{
			cloud2.at(k)->translate(inC);
		}
		return *this;
	}
private:
	vector<shared_ptr<ellipse> > moon;
	vector<shared_ptr<Polygon> > stars;
	vector<shared_ptr<Rect> > ground;
	vector<shared_ptr<ellipse> > mountains;
	vector<shared_ptr<ellipse> > cloud1;
	vector<shared_ptr<ellipse> > cloud2;
	vector<shared_ptr<ellipse> > path;
};

#endif