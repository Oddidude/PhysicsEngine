#ifndef PhysicsBody_h
#define PhysicsBody_h

#include <vector>
#include <SDL2/SDL.h>
#include "PVector.h"

class PhysicsBody {
	public:
		PhysicsBody(float x=0, float y=0, int rad=1, float _mass=0, bool friction=true, bool _gravity=true);
		~PhysicsBody();

		PVector* getPos() const { return pos; }
		int getRadius() const { return radius; }

		void setGravityVector(float force) const {
			delete PhysicsBody::gravityVector;
			PhysicsBody::gravityVector = NULL;
			PhysicsBody::gravityVector = new PVector(0, force);
		}
		void toggleGravity() { gravity = !gravity; }

		float getMaxSpeed() const { return maxSpeed; }
		void setMaxSpeed(float speed) { maxSpeed = speed < 0 ? 0 : speed; }
		void checkMaxSpeed();

		PVector* getCentre() const { return pos->add(new PVector(radius, radius)); }

		void setFrictionLevel(int level) { frictionLevel = level; }
		void applyFriction();

		bool checkCollision(PhysicsBody* body);
		void bounce(PhysicsBody* body);

		void unstuck(PhysicsBody* body);

		void applyForce(PVector* v);
		void applyAcceleration();

		virtual void update();
		virtual void render();

	private:
		PVector* pos;
		PVector* vel;
		PVector* accel;
		int radius;
		float mass;
		float maxSpeed;

		bool friction;
		int frictionLevel;

		bool gravity;

		static PVector* gravityVector;
};

#endif
