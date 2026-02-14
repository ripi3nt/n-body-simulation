#include <cmath>
#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>

#include <SFML/Graphics.hpp>


const bool debug = true;

struct Vec2 {
  float x;
  float y;

  Vec2& operator+=(const Vec2& vec2) {
    x += vec2.x; 
    y += vec2.y; 
    return *this;
  }

  Vec2& operator-=(const Vec2& vec2) {
    x -= vec2.x; 
    y -= vec2.y; 
    return *this;
  }

  Vec2 operator-(const Vec2& vec) {
    return {x - vec.x, y - vec.y};
  }

  Vec2 operator+(const Vec2& vec) {

    return {vec.x + x, vec.y + y};
  }

  Vec2 operator=(const Vec2& vec) {
    return {vec.x, vec.y};
  }

  Vec2 operator*(float s) {
    return { x * s, y * s};
  }

  Vec2 operator/(float s) {
    return { x / s, y / s};
  }
};

struct Particle {
  Vec2 pos;
  Vec2 vel;
};

float randomFloat() {
  int num = rand() % 50;
  return (float) num;
}

int main(int argc, char* argv[]) {
  int particleCount = std::stoi(argv[1]); 
  std::vector<Particle> particles;

  if(debug) std::cout << "Initial positions: ";
  for (int i = 0; i < particleCount; i++) {
    Particle particle = { randomFloat(), randomFloat(), 0, randomFloat() };
    particles.push_back(particle); 

    if(debug) std::cout << "{" << particles[i].pos.x << ", " << particles[i].pos.y << "}, ";
  }

  std::cout << std::endl;

  int steps = std::stoi(argv[2]);
  const float gravConstant = 100.0f;
  const float softening = 1e-5;
  const float timeStep = 0.01f;

  while(steps--) {
    std::vector<Vec2> newVel;
    for(int i = 0; i < particleCount; i++) {
      Vec2 currVel = {0.0f, 0.0f};
      for(int j = 0; j < particleCount; j++) {
        if(i == j) continue;
        Vec2 vecBetween = particles[j].pos - particles[i].pos;
        float distBetween = std::sqrt(vecBetween.x*vecBetween.x + vecBetween.y*vecBetween.y + softening*softening);
        currVel += (vecBetween * gravConstant) / (distBetween*distBetween*distBetween);
      }
      newVel.push_back(currVel);
    }

    if(debug) std::cout << "Step " << steps << ": ";

    Vec2 momentum = {0.0f, 0.0f};
    for (int i = 0; i < particleCount; i++) {
      particles[i].vel += newVel[i] * timeStep;
      particles[i].pos += particles[i].vel * timeStep;
      momentum += particles[i].vel;
      if(debug) std::cout << "{" << particles[i].pos.x << ", " << particles[i].pos.y << "}, ";
    }

    if (debug) std::cout << "Total momentum: " << momentum.x << momentum.y << std::endl;



  }


  return 0;


}
