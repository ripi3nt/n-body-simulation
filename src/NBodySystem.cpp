#include <utility>
#include <iostream>
#include <vector>
#include <cmath>

#include "CudaManager.hpp"
#include "Vec2D.hpp"
#include "Particle.hpp"
#include "NBodySystem.hpp"
#include "Config.hpp"


NBodySystem::NBodySystem(const std::pair<int, int> fieldSize, std::vector<Particle>& particles) : fieldSize(fieldSize), manager(particles) {
  this->particles = std::span(particles);
}

void NBodySystem::update(float timeDelta) {
  std::vector<Vec2> acc = computeAccelarations();

  Vec2 momentum = {0,0};
  for(int i = 0; i < particles.size(); i++) {
    particles[i].vel += acc[i] * timeDelta;
    particles[i].pos += particles[i].vel * timeDelta;
    momentum += particles[i].vel;
    if(debug) std::cout << "{" << particles[i].pos.x << ", " << particles[i].pos.y << "}, ";
  }
  if (debug) std::cout << "Total momentum: " << momentum.x << momentum.y << std::endl;

  //handle collisions between particles
}

const std::span<Particle>& NBodySystem::getParticles() {
  return particles;
}

std::vector<Vec2> NBodySystem::computeAccelarations() {
  const int size = particles.size();
  std::vector<Vec2> accs;
  for(int i = 0; i < size; i++) {
    Vec2 currAcc = {0.0f, 0.0f};
    for(int j = 0; j < size; j++) {
      if(i == j) continue;
      Vec2 vecBetween = particles[j].pos - particles[i].pos;
      float distBetween = std::sqrt(vecBetween.x*vecBetween.x + vecBetween.y*vecBetween.y + softening*softening);
      currAcc += (vecBetween * gravConstant) / (distBetween*distBetween*distBetween);
    }
    accs.push_back(currAcc);

    if(particles[i].pos.x < 0 || particles[i].pos.x > fieldSize.first) {
      particles[i].vel.x = -particles[i].vel.x;
    }
    else if(particles[i].pos.y < 0 || particles[i].pos.y > fieldSize.second) {
      particles[i].vel.y = -particles[i].vel.y;
    }
  }

  return accs;
}

void NBodySystem::updateCUDA(float timeDelta) {
  manager.updateParticles(timeDelta);

  particles = manager.getParticles();
}
