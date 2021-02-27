#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include <iostream>
#include <tuple>
#include <cmath>

template<class T>
struct TTriangle {
	/* Cords of left bottom corner, side */
	std::pair<T, T> Cord;
	T Side;

	TTriangle(const std::pair<T, T> & cord, T side) : Cord(cord), Side(side) {}
};

template<class T>
T CalcSquare(const TTriangle<T> & Tri) {
	return Tri.Side * Tri.Side * pow(3, 0.5) / 4;
}

template<class T>
std::ostream & operator << (std::ostream & out, const TTriangle<T> & tri) {
	out << "Triangle {";
	out << std::pair<T, T>(tri.Cord.first, tri.Cord.second) << ", ";
	out << std::pair<T, T>(tri.Cord.first + 0.5 * tri.Side, tri.Cord.second + tri.Side * (std::pow(3, 0.5) / 2)) << ", ";
	out << std::pair<T, T>(tri.Cord.first + tri.Side, tri.Cord.second);
	out << "}";
	return out;
}

template<class T1, class T2>
std::ostream & operator << (std::ostream & out, const std::pair<T1, T2> & p) {
	out << "(" << p.first << ", " << p.second << ")";
	return out;
}

#endif
