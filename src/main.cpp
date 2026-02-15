#include <SFML/Window/ContextSettings.hpp>
#include <SFML/Window/WindowEnums.hpp>
#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/VideoMode.hpp>

#include "Vec2D.hpp"
#include "NBodySystem.hpp"

extern const bool debug = false;


const int screenW = 700;
const int screenH = 700;

int main(int argc, char* argv[]) {
  int particleCount = std::stoi(argv[1]); 

  int steps = std::stoi(argv[2]);
  const float gravConstant = 1000.0f;
  const float softening = 1e-5;
  float timeStep = 0.01f;

  NBodySystem sys(gravConstant, softening, std::pair<int,int>{screenW, screenH}, particleCount);

  //graphics
  const float shapeSize = 3.0f;
  sf::ContextSettings settings;
  settings.minorVersion = 1;
  settings.majorVersion = 2;
  sf::RenderWindow window(sf::VideoMode({screenW, screenH}), "Title", sf::Style::Default, sf::State::Windowed, settings);
  window.setFramerateLimit(300);
  sf::CircleShape shape(shapeSize);;
  shape.setFillColor(sf::Color::Blue);
  shape.setOrigin({shapeSize, shapeSize});
  sf::Clock clock;
  while(steps--) {
    window.clear();
    //refactor
    timeStep = std::min(clock.restart().asSeconds(), 0.01f);
    sys.update(timeStep);

    if(debug) std::cout << "Step " << steps << ": ";

    Vec2 momentum = {0.0f, 0.0f};
    for (int i = 0; i < particleCount; i++) {

      const std::vector<Particle>& particles = sys.getParticles();

      shape.setPosition({particles[i].pos.x, particles[i].pos.y});
      window.draw(shape);
    }

    if (debug) std::cout << "Total momentum: " << momentum.x << momentum.y << std::endl;

    window.display();


  }


  return 0;


}
