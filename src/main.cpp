#include <SFML/Window/Event.hpp>
#include <optional>
#include <string>
#include <SFML/Window/ContextSettings.hpp>
#include <SFML/Window/WindowEnums.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <iostream>
#include <vector>

#include "Vec2D.hpp"
#include "NBodySystem.hpp"
#include "Config.hpp"

float randomFloat(int max) {
  int num = rand() % max;
  return (float) num;
}


int main(int argc, char* argv[]) {
  int particleCount = std::stoi(argv[1]); 

  std::vector<Particle> particles;
  if(debug) std::cout << "Initial positions: ";
  for (int i = 0; i < particleCount; i++) {
    Particle particle = { randomFloat(screenW), randomFloat(screenH), 0, randomFloat(40) };
    particles.push_back(particle); 

    if(debug) std::cout << "{" << particles[i].pos.x << ", " << particles[i].pos.y << "}, ";
  }


  NBodySystem sys(std::pair<int,int>{screenW, screenH}, particles);

  //graphics
  const float shapeSize = 3.0f;
  sf::RenderWindow window(sf::VideoMode({screenW, screenH}), "Title", sf::Style::Default);
  window.setFramerateLimit(240);
  sf::CircleShape shape(shapeSize);;
  shape.setFillColor(sf::Color::Blue);
  shape.setOrigin({shapeSize, shapeSize});
  sf::Clock clock;

  float timeStep;
  int steps = 10000;
  while(steps--) {

    while(const std::optional event = window.pollEvent()) {

      if(event->is<sf::Event::Closed>()) {
        window.close();
      }
    }

    window.clear();

    timeStep = std::min(clock.restart().asSeconds(), 0.01f);
    sys.updateCUDA(timeStep);

    Vec2 momentum = {0.0f, 0.0f};
    const std::span<Particle>& particles = sys.getParticles();
    for (int i = 0; i < particleCount; i++) {

      shape.setPosition({particles[i].pos.x, particles[i].pos.y});
      window.draw(shape);
    }

    window.display();

  }


  return 0;


}
