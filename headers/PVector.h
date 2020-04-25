#ifndef Vector_h
#define Vector_h

#include <math.h>

class PVector {
	public:
		PVector(float _x, float _y);

		float x;
		float y;

		void add(PVector* v);
		void subtract(PVector* v);
		void multiply(float s);
		void divide(float s);
		void rotate(float angle);
		void reflect(PVector* normal);
		void normalize();
		void inverse();

		float dot(PVector* v);
		float dist(PVector* v);

		float getMagnitude();
		PVector* getCopy();

		static PVector* add(PVector* v, PVector* v2) {
			PVector* vCopy = v->getCopy();
			vCopy->subtract(v2);
			return vCopy;
		}

		static PVector* subtract(PVector* v, PVector* v2) {
			PVector* vCopy = v->getCopy();
			vCopy->subtract(v2);
			return vCopy;
		}

		static PVector* multiply(PVector* v, float s) {
			PVector* vCopy = v->getCopy();
			vCopy->multiply(s);
			return vCopy;
		}

		static PVector* divide(PVector* v, float s) {
			PVector* vCopy = v->getCopy();
			vCopy->divide(s);
			return vCopy;
		}

		static PVector* rotate(PVector* v, float angle) {
			PVector* vCopy = v->getCopy();
			vCopy->rotate(angle);
			return vCopy;
		}

		static PVector* normalise(PVector* v) {
			PVector* vCopy = v->getCopy();
			vCopy->normalize();
			return vCopy;
		}

		static PVector* inverse(PVector* v) {
			PVector* vCopy = v->getCopy();
			vCopy->inverse();
			return vCopy;
		}
};

#endif
