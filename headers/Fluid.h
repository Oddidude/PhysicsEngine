#ifndef Fluid_h
#define Fluid_h

#include "PhysicsBody.h"

class Fluid : public PhysicsBody {
	public:
		Fluid(float x, float y, int r, int g, int b, int a);

		void update();
		void render();

	private:
		int r;
		int g;
		int b;
		int a;
};

#endif
