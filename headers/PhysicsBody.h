#ifndef PhysicsBody_h
#define PhysicsBody_h

#include <vector>
#include <SDL2/SDL.h>
#include "PVector.h"

class PhysicsBody {
	public:
		PhysicsBody(float x, float y, int rad, float mass, bool gravity = true);
		~PhysicsBody();

		PVector* getPos() const { return pos; }

		void setGravityVector(float force) const {
			PhysicsBody::gravityVector = new PVector(0, force);
		}
		void setMaxSpeed(float speed) { maxSpeed = speed; }

		bool checkCollision(PhysicsBody* body);
		void bounce(PhysicsBody* body);

		void applyForce(PVector* v);
		void applyAcceleration();

		virtual void update();
		virtual void render();

		bool gravity;
	private:
		PVector* pos;
		PVector* vel;
		PVector* accel;
		int radius;
		float mass;
		float maxSpeed;

		static PVector* gravityVector;
};

#endif