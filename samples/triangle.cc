#include "polygon.h"
#include <cmath>

class Triangle : public Polygon {
	double side_length;
public:
	Triangle(double side_length) : side_length(side_length) {}
	virtual double area() const {
		return (sqrt(3.0) / 4.0) * (side_length * side_length);
	}
};


// the class factories

extern "C" Polygon* create(double side_length) {
    return new Triangle(side_length);
}
