#ifndef _POLYGONS_H_
#define _POLYGONS_H_

#include <iostream>
#include <cmath>
#include <cassert>
#include "utilities.h"

class Polygon {
public:
	Polygon() {
		name = "";
		numSides = 0;
	}
	Polygon(const std::string &n, const std::vector<Point> &points) {
		name = n;
		numSides = points.size();
		for(unsigned int i = 0; i < numSides; i++) {
			vertices.push_back(points[i]);
		}
	}
	virtual std::string getName() { return name; }
	bool HasAllEqualSides() {
		double len = DistanceBetween(vertices[0], vertices[numSides-1]);
		for(unsigned int i = 0; i < numSides - 1; i++) {
			if(!EqualSides(len, DistanceBetween(vertices[i], vertices[i + 1]))) {
				return false;
			}
		}
		return true;
	}
	unsigned int NumEqualSides() {
		unsigned int count = 0;
		double len = DistanceBetween(vertices[0], vertices[numSides-1]);
		for(unsigned int i = 0; i < numSides - 1; i++) {
			if(!EqualSides(len, DistanceBetween(vertices[i], vertices[i + 1]))) {
				count++;
			}
		}
		return count;
	}
protected:
	std::string name;
	unsigned int numSides;
	std::vector<Point> vertices;
};

class Triangle: public Polygon {
public:
	Triangle() {
		Polygon();
	}
	Triangle(const std::string &n, const std::vector<Point> &points) {
		name = n;
		numSides = points.size();
		if(numSides != 3) {
			throw 1;
		}
		for(unsigned int i = 0; i < numSides; i++) {
			vertices.push_back(points[i]);
		}
	}
};

class IsoscelesTriangle: public Triangle {
public:
	IsoscelesTriangle() {
		// Triangle();
	}
	IsoscelesTriangle(const std::string &n, const std::vector<Point> &points) {
		name = n;
		numSides = points.size();
		if(numSides != 3) {
			throw 1;
		}
		for(unsigned int i = 0; i < numSides; i++) {
			vertices.push_back(points[i]);
		}
		if(NumEqualSides() != 1) {
			throw 1;
		}
	}
};

class EquilateralTriangle: public IsoscelesTriangle {
public:
	EquilateralTriangle() {
		// Triangle();
	}
	EquilateralTriangle(const std::string &n, const std::vector<Point> &points) {
		name = n;
		numSides = points.size();
		if(numSides != 3) {
			throw 1;
		}
		for(unsigned int i = 0; i < numSides; i++) {
			vertices.push_back(points[i]);
		}
		if(!HasAllEqualSides()) {
			throw 1;
		}
	}
};

class Quadrilateral: public Polygon {
public:
	Quadrilateral() {
		// Polygon();
	}
	Quadrilateral(const std::string &n, const std::vector<Point> &points) {
		name = n;
		numSides = points.size();
		if(numSides != 4) {
			throw 1;
		}
		for(unsigned int i = 0; i < numSides; i++) {
			vertices.push_back(points[i]);
		}
	}
};

class Rectangle: public Quadrilateral {
public:
	Rectangle() {
		// Polygon();
	}
	Rectangle(const std::string &n, const std::vector<Point> &points) {
		name = n;
		numSides = points.size();
		if(numSides != 4) {
			throw 1;
		}
		for(unsigned int i = 0; i < numSides; i++) {
			vertices.push_back(points[i]);
		}
		if(!RightAngle(Angle(vertices[0], vertices[1], vertices[2]))
			|| !RightAngle(Angle(vertices[1], vertices[2], vertices[3]))
			|| !RightAngle(Angle(vertices[2], vertices[3], vertices[0]))
			|| !RightAngle(Angle(vertices[3], vertices[0], vertices[1]))) {
			throw 1;
		}
		if(!EqualSides(DistanceBetween(vertices[0], vertices[1]), DistanceBetween(vertices[2], vertices[3]))
			|| !EqualSides(DistanceBetween(vertices[1], vertices[2]), DistanceBetween(vertices[0], vertices[3]))) {
			throw 1;
		}
	}
};

class Square: public Rectangle {
public:
	Square() {
		// Rectangle();
	}
	Square(const std::string &n, const std::vector<Point> &points) {
		name = n;
		numSides = points.size();
		if(numSides != 4) {
			throw 1;
		}
		for(unsigned int i = 0; i < numSides; i++) {
			vertices.push_back(points[i]);
		}
		if(!HasAllEqualSides()) {
			throw 1;
		}
		if(!RightAngle(Angle(vertices[0], vertices[1], vertices[2]))
			|| !RightAngle(Angle(vertices[1], vertices[2], vertices[3]))
			|| !RightAngle(Angle(vertices[2], vertices[3], vertices[0]))
			|| !RightAngle(Angle(vertices[3], vertices[0], vertices[1]))) {
			throw 1;
		}
	}
};

#endif