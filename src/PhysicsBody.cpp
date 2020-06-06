#ifndef PhysicsBody_cpp
#define PhysicsBody_cpp

#include "../headers/Environment.h"
#include "../headers/TextureManager.h"
#include "../headers/PhysicsBody.h"

PVector* PhysicsBody::gravityVector = new PVector(0, 9.81);

PhysicsBody::PhysicsBody(float x, float y, int rad, float _mass, bool _friction, bool _gravity) {
	pos = new PVector(x - rad, y - rad);
	vel = new PVector(0, 0);
	accel = new PVector(0, 0);
	radius = rad;
	mass = _mass;
	maxSpeed = 15;
	frictionLevel = _friction ? 2 : 0;
	friction = _friction;
	gravity = _gravity;
}

PhysicsBody::~PhysicsBody() {
	delete pos;
	delete vel;
	delete accel;
}

void PhysicsBody::checkMaxSpeed() {
	if (vel->x > maxSpeed) {
		vel->x = maxSpeed;
	} else if (vel->x < -maxSpeed) {
		vel->x = -maxSpeed;
	}

	if (vel->y > maxSpeed) {
		vel->y = maxSpeed;
	} else if (vel->y < -maxSpeed) {
		vel->y = -maxSpeed;
	}
}

void PhysicsBody::applyFriction() {
	if (vel->getMagnitude() > 0) {
		switch (frictionLevel) {
			case 0:
				break;
			case 1:
				vel->multiply(0.98);
				break;
			case 2:
				vel->multiply(0.95);
				break;
			case 3:
				vel->multiply(0.90);
				break;
			default:
				vel->multiply(0.90);
				break;
		}
	}
}

bool PhysicsBody::checkCollision(PhysicsBody* body) {
	float distance = pos->dist(body->pos) - radius - body->radius;
	return distance <= 0;
}

void PhysicsBody::bounce(PhysicsBody* body) {
	PVector* normal = PVector::subtract(pos, body->pos)->normalize();

	normal->multiply(normal->dot(PVector::subtract(vel, body->vel)));

	vel->subtract(normal);
	body->vel->add(normal);
}

void PhysicsBody::unstuck(PhysicsBody* body) {
	float distance = pos->dist(body->pos);
	if (distance < radius + body->radius) {
		PVector* translation = PVector::add(this->pos, body->pos)->normalize();
		translation->multiply((radius + body->radius) - distance);
		
		this->pos->add(translation);
	}
}

void PhysicsBody::applyForce(PVector* v) {
	accel->add(v);
}

void PhysicsBody::applyAcceleration() {
	if (gravity) {
		accel->add(PhysicsBody::gravityVector);
	}

	vel->add(accel);

	if (friction) {
		applyFriction();
	}

	if (accel->getMagnitude() > 0) {
		accel->multiply(0.5);
		if (accel->getMagnitude() < 0.00005) {
			accel->subtract(accel);
		}
	}

	checkMaxSpeed();

	if (vel->getMagnitude() < 0.05) {
		vel->subtract(vel);
	}

	pos->add(vel);

	float diameter = 2 * radius;

	if (pos->x + diameter < 0) {
		pos->x = Environment::width + diameter;
	} else if (pos->x - diameter > Environment::width) {
		pos->x = -diameter;
	}
	
	if (pos->y + diameter < 0) {
		pos->y = Environment::height + diameter;
	} else if (pos->y - diameter > Environment::height) {
		pos->y = -diameter;
	}
}

void PhysicsBody::update() {
	applyAcceleration();
}

void PhysicsBody::render() {
	SDL_Rect srcRect, destRect;
	destRect.x = pos->x;
	destRect.y = pos->y;
	destRect.w = destRect.h = 2 * radius;
	TextureManager::Draw(
			TextureManager::LoadTexture("../assets/NoTexture.png"),
			srcRect,
			destRect
			);
}

#endif

