#include "UFO.h"


UFO::UFO(vec2 center, double scale, double depth, const std::vector<color> &colors) : depth(depth) {
    if (colors.size() != 5) {
        throw std::runtime_error("Should supply at least 5 colors");
    }
    vec2 drawingCenter = vec2(75, 86.77);
    // BASE_UFO
    ellipses.push_back(make_shared<ellipse>(drawingCenter, vec2(73.9, 31.11), 1, colors[0]));
    // UFO_TOP
    ellipses.push_back(make_shared<ellipse>(vec2(75, 62.1), vec2(44.2, 44.2), 2, colors[1]));
    // Grey cover top
    rects.push_back(make_shared<Rect>(vec2(28.15, 77.83), vec2(91.73 + 28.15, 29.78 + 77.83), colors[0], 3));
    // Bottom of UFO TOP
    ellipses.push_back(make_shared<ellipse>(vec2(75, 77.83), vec2(41.55, 6.94), 4, colors[1]));
    // HEAD
    ellipses.push_back(make_shared<ellipse>(vec2(76.24, 58.52), vec2(21.48, 21.48), 5, colors[3]));
    // LEFT EYE
    ellipses.push_back(make_shared<ellipse>(vec2(68.55, 57.11), vec2(2.53, 2.53), 6, colors[4]));
    // RIGHT EYE
    ellipses.push_back(make_shared<ellipse>(vec2(83.47, 57.11), vec2(2.53, 2.53), 7, colors[4]));
    // NECK
    rects.push_back(make_shared<Rect>(vec2(68.39, 74.38), vec2(16.51 + 68.39, 74.38 + 10.2), colors[3], 8));
    // MOUTH
    ellipses.push_back(make_shared<ellipse>(vec2(76.65, 67.71), vec2(13.14, 1.94), 7, colors[4]));

    // HEXAGON1
    polys.push_back(make_shared<Polygon>(std::vector<vec2>{
            vec2(87.1, 102.12),
            vec2(82.45, 110.18),
            vec2(73.13, 110.18),
            vec2(68.48, 102.12),
            vec2(73.13, 94.05),
            vec2(82.45, 94.05),
    }, 30, colors[2]));
    // HEXAGON 2
    polys.push_back(make_shared<Polygon>(std::vector<vec2>{
            vec2(48.59, 100.06),
            vec2(41.35, 105.92),
            vec2(32.65, 102.57),
            vec2(31.2, 93.38),
            vec2(38.44, 87.52),
            vec2(47.13, 90.86),
    }, 30, colors[2]));
    // HEXAGON 3
    polys.push_back(make_shared<Polygon>(std::vector<vec2>{
            vec2(123.14, 90.18),
            vec2(123.14, 99.49),
            vec2(115.08, 104.15),
            vec2(107.02, 99.49),
            vec2(107.02, 90.18),
            vec2(115.08, 85.52),
    }, 30, colors[2]));


    scale *= 1.5;
    this->scale(scale);
    drawingCenter *= scale;
    translate(vec2(center.x() - drawingCenter.x(), center.y() - drawingCenter.y()));
}

UFO::UFO(vec2 center, double scale, double depth) :
        UFO(center, scale, depth, std::vector<color>{
                color(124, 124, 124),
                color(176, 219, 237),
                color(100, 36, 255),
                color(55, 188, 51),
                color(0, 0, 0)
        }) {
}
//UFO::UFO(vec2 center,double depth , double scale){}

//UFO(vec2 center,double depth , double scale, color colors[3]){}

color UFO::eval(double x, double y, color background) {
    bool inTrue = false;
    double curDepth = -1;
    color inC;
    float res;
    for (auto eq : ellipses) {
        if (eq->eval(x, y) < 0 && eq->getDepth() > curDepth) {
            inC = eq->getInC();
            inTrue = true;
            curDepth = eq->getDepth();
        }
    }
    for (auto rect: rects) {
        if (rect->evalIn(x, y) && rect->getDepth() > curDepth) {
            inC = rect->getInC();
            inTrue = true;
            curDepth = rect->getDepth();
        }
    }
    for (auto poly: polys) {
        if (poly->eval(x, y) && poly->getDepth() > curDepth) {
            inC = poly->getInC();
            inTrue = true;
            curDepth = poly->getDepth();
        }
    }

    if (inTrue) {
        return inC;
    } else {
        return background;
    }
}

void UFO::translate(vec2 offset) {
    for (const auto &item : ellipses) {
        item->translate(offset);
    }
    for (const auto &item : rects) {
        item->translate(offset);
    }
    for (const auto &item : polys) {
        item->translate(offset);
    }
}

void UFO::scale(double scalar) {
    for (const auto &item : ellipses) {
        item->scale(scalar);
    }
    for (const auto &item : rects) {
        item->scale(scalar);
    }
    for (const auto &item : polys) {
        item->scale(scalar);
    }
}


