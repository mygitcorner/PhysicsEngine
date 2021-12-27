#include "SpheresSim.h"
#include "RigidBall.h"
#include "RigidWall.h"
#include "RigidBox.h"

SpheresSim::SpheresSim()
	: Simulation(800, 800)
{
	std::list<RigidBall*> balls = {
		new RigidBall({ 200, 200 }, { 800, 100 }, 15, 1),
		new RigidBall({ 300, 200 }, { 700, -300 }, 15, 1),
		new RigidBall({ 200, 300 }, { -500, 500 }, 15, 1),
		new RigidBall({ 300, 300 }, { -600, -200 }, 15, 1)
	};
	for (auto& ball : balls)
		addBody(ball);

	std::list<RigidWall*> walls = {
		new RigidWall({ width(), height() / 2 }, { -1, 0 }, height()),
		new RigidWall({ width() / 2, height() }, { 0, -1 }, width()),
		new RigidWall({ 0, height() / 2 }, { 1, 0 }, height()),
		new RigidWall({ width() / 2, 0 }, { 0, 1 }, width())
	};
	for (auto& wall : walls)
		addBody(wall);

	//m/3(w^2+h^2)
	double momentOfInertia = 4 / 3 * (100 * 100 + 50 * 50);

	RigidBox* box1 = new RigidBox({ 250, 400 }, 100, 50);
	box1->setMass(4);
	box1->setMomentOfInertia(momentOfInertia);
	box1->setVelocity({ -200, 0 });
	box1->setAngularVelocity(0);
	addBody(box1);

	RigidBox* box2 = new RigidBox({ 550, 400 }, 100, 50);
	box2->setMass(4);
	box2->setMomentOfInertia(momentOfInertia);
	box2->setVelocity({ 200, 0 });
	box2->setAngularVelocity(0);
	addBody(box2);

	RigidBox* box3 = new RigidBox({ 550, 200 }, 100, 50);
	box3->setMass(4);
	box3->setMomentOfInertia(momentOfInertia);
	box3->setVelocity({ 400, 400 });
	box3->setAngularVelocity(0);
	box3->setAngle(3.1415 / 4);
	addBody(box3);
}
