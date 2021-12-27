// PhysicsEngine.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <SFML/Graphics.hpp>
#include "FPSText.h"
#include "BoxesSim.h"
#include "SpheresSim.h"


int main() {
	const double drawFPS = 60;
	const double drawTimeStep = 1 / drawFPS;
	
	const double physicsFPS = 480;
	const double physicsTimeStep = 1 / physicsFPS;

	SpheresSim sim;
	
	FPSText fpsText;
	
	sf::RenderWindow window(sf::VideoMode(sim.width(), sim.height()), "Physics Engine");
	window.setFramerateLimit(static_cast<unsigned int>(drawFPS));

	while (window.isOpen()) {
		sf::Event event;

		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}

		for (double t = 0; t < drawTimeStep; t += physicsTimeStep)
			sim.update(physicsTimeStep);

		window.clear(sf::Color::Black);
		window.draw(sim);
		window.draw(fpsText);
		window.display();

		fpsText.nextFrame();
	}

	return 0;
}
