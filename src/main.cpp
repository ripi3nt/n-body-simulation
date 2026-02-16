#include <string>
#include <SFML/Window/ContextSettings.hpp>
#include <SFML/Window/WindowEnums.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/VideoMode.hpp>

#include "Vec2D.hpp"
#include "NBodySystem.hpp"
#include "Config.hpp"


int main(int argc, char* argv[]) {
  int particleCount = std::stoi(argv[1]); 

  NBodySystem sys(gravConstant, softening, std::pair<int,int>{screenW, screenH}, particleCount);

  //graphics
  const float shapeSize = 3.0f;
  sf::RenderWindow window(sf::VideoMode({screenW, screenH}), "Title", sf::Style::Default);
  window.setFramerateLimit(240);
  sf::CircleShape shape(shapeSize);;
  shape.setFillColor(sf::Color::Blue);
  shape.setOrigin({shapeSize, shapeSize});
  sf::Clock clock;

  float timeStep;
  while(true) {
    window.clear();

    timeStep = std::min(clock.restart().asSeconds(), 0.01f);
    sys.update(timeStep);

    Vec2 momentum = {0.0f, 0.0f};
    for (int i = 0; i < particleCount; i++) {
      const std::vector<Particle>& particles = sys.getParticles();

      shape.setPosition({particles[i].pos.x, particles[i].pos.y});
      window.draw(shape);
    }


    window.display();


  }


  return 0;


}
