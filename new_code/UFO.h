#ifndef DRAWING_H
#define DRAWING_H


#include <vector>
#include <memory>
#include "ellipse.h"
#include "polygon.h"
#include "rect.h"
#include "color.h"

/// A drawing of a UFO.
/// *** IMPORTANT ***
/// If you want to use this drawing, add the 'scale' function top Rect.h, ellipse.h, and Polygon.h
/// (You can copy from our files).
class UFO {
public:
    /// Constructs a UFO drawing.
    ///
    /// center: the center of the UFO
    /// scale: scales the entire drawing by a factor
    /// depth: The depth of the UFO drawing
    ///
    /// this uses default colors.
    UFO(vec2 center, double scale = 1, double depth = 0);

    /// Constructs a UFO drawing.
    ///
    /// center: the center of the UFO
    /// scale: scales the entire drawing by a factor
    /// depth: The depth of the UFO drawing
    /// colors: a list of 5 colors of the UFO, in the following order:
    ///   - the UFO body
    ///   - the UFO dome
    ///   - the UFO hexagons
    ///   - the alien body
    ///   - the alien features
    UFO(vec2 center, double scale, double depth, const std::vector<color> &colors);

    /// Translates the UFO by a given offset
    void translate(vec2 offset);

    /// scales the UFO by a given scalar
    void scale(double scalar);

    /// Evaluates the color at the given position. If there is no color at that point, this function returns the
    /// given [background] color
    color eval(double x, double y, color background);

    /// gets the depth of the drawing
    double getDepth() const { return depth; }

private:
    double depth;
    std::vector<std::shared_ptr<ellipse>> ellipses;
    std::vector<std::shared_ptr<Polygon>> polys;
    std::vector<std::shared_ptr<Rect>> rects;
};


#endif //DRAWING_H
