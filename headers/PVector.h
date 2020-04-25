#ifndef Vector_h
#define Vector_h

#include <math.h>

class PVector {
	public:
		PVector(float _x, float _y);

		float x;
		float y;

		PVector* add(PVector* v);
		PVector* subtract(PVector* v);
		PVector* multiply(float s);
		PVector* divide(float s);
		PVector* rotate(float angle);
		PVector* reflect(PVector* normal);
		PVector* normalize();
		PVector* inverse();

		float dot(PVector* v);
		float dist(PVector* v);

		float getMagnitude();
		PVector* getCopy();

		static PVector* add(PVector* v, PVector* v2) {
			PVector* vCopy = v->getCopy();
			return vCopy->subtract(v2);
		}

		static PVector* subtract(PVector* v, PVector* v2) {
			PVector* vCopy = v->getCopy();
			return vCopy->subtract(v2);
		}

		static PVector* multiply(PVector* v, float s) {
			PVector* vCopy = v->getCopy();
			return vCopy->multiply(s);
		}

		static PVector* divide(PVector* v, float s) {
			PVector* vCopy = v->getCopy();
			return vCopy->divide(s);
		}

		static PVector* rotate(PVector* v, float angle) {
			PVector* vCopy = v->getCopy();
			return vCopy->rotate(angle);
		}

		static PVector* normalise(PVector* v) {
			PVector* vCopy = v->getCopy();
			return vCopy->normalize();
		}

		static PVector* inverse(PVector* v) {
			PVector* vCopy = v->getCopy();
			return vCopy->inverse();
		}
};

#endif
