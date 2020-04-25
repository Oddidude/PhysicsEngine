#ifndef PhysicsBody_cpp
#define PhysicsBody_cpp

#include "../headers/Environment.h"
#include "../headers/TextureManager.h"
#include "../headers/PhysicsBody.h"

PVector* PhysicsBody::gravityVector = new PVector(0, 9.81);

PhysicsBody::PhysicsBody(float x, float y, int rad, float _mass, bool _gravity) {
	pos = new PVector(x, y);
	vel = new PVector(0, 0);
	accel = new PVector(0, 0);
	radius = rad;
	mass = _mass;
	maxSpeed = 15;
	gravity = _gravity;
}

PhysicsBody::~PhysicsBody() {
	delete pos;
	delete vel;
	delete accel;
}

bool PhysicsBody::checkCollision(PhysicsBody* body) {
	float distance = pos->dist(body->getPos()) - radius - body->radius;
	return distance < 1;
}

void PhysicsBody::bounce(PhysicsBody* body) {
	PVector* normal = PVector::subtract(pos, body->pos);
	normal->normalize();

	normal->multiply(normal->dot(PVector::subtract(vel, body->vel)));

	vel->subtract(normal);
	body->vel->add(normal);
}

void PhysicsBody::applyForce(PVector* v) {
	accel->add(v);
}

void PhysicsBody::applyAcceleration() {
	if (gravity) {
		accel->add(PhysicsBody::gravityVector);
	}

	vel->add(accel);
	/**
	 * | Friction |
	 * v          v
	 *
	if (vel->getMagnitude() > 0) {
		vel->multiply(0.97);
		if (vel->getMagnitude() < 0.005) {
			vel->subtract(vel);
		}
	}
	*/

	if (accel->getMagnitude() > 0) {
		accel->multiply(0.5);
		if (accel->getMagnitude() < 0.00005) {
			accel->subtract(accel);
		}
	}

	if (vel->getMagnitude() > maxSpeed) {
		float limiter = vel->getMagnitude() / maxSpeed;
		vel->divide(limiter);
	}

	pos->add(vel);

	float diameter = 2 * radius;

	if (pos->x + diameter < 0) {
		pos->x = Environment::width + diameter;
	}
	if (pos->x - diameter > Environment::width) {
		pos->x = -diameter;
	}
	
	if (pos->y + diameter < 0) {
		pos->y = Environment::height + diameter;
	}
	if (pos->y - diameter > Environment::height) {
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

