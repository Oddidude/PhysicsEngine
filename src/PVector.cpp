#ifndef PVector_cpp
#define PVector_cpp

#include "../headers/PVector.h"

#define PI 3.14159265

PVector::PVector(float _x, float _y) : x(_x), y(_y) {}

void PVector::add(PVector* v) {
	x += v->x;
	y += v->y;
}

void PVector::subtract(PVector* v) {
	x -= v->x;
	y -= v->y;
}

void PVector::multiply(float s) {
	x *= s;
	y *= s;
}

void PVector::divide(float s) {
	x /= s;
	y /= s;
}

void PVector::rotate(float angle) {
	angle *= PI / 180.0;
	float cs = cos(angle);
	float sn = sin(angle);
	float oldX = x;
	x = x * cs - y * sn;
	y = oldX * sn + y * cs;
}

void PVector::reflect(PVector* normal) {
	PVector* n = normal->getCopy();
	n->multiply(2 * dot(n));
	subtract(n);
}

void PVector::normalize() {
	float magnitude = getMagnitude();
	if (magnitude != 0) {
		divide(magnitude);
	}
}

void PVector::inverse() {
	x *= -1;
	y *= -1;
}

float PVector::dot(PVector* v) {
	return (x * v->x) + (y * v->y);
}

float PVector::dist(PVector* v) {
	return sqrt(pow(x - v->x, 2) + pow(y - v->y, 2));
}

float PVector::getMagnitude() {
	return sqrt(x*x + y*y);
}

PVector* PVector::getCopy() {
	return new PVector(x, y);
}

#endif
