#ifndef POLYGON_H
#define POLYGON_H

class Polygon {
public:
	virtual double area() const = 0;
};

// the types of the class factories
typedef Polygon* create_t(double side_length);

#endif
