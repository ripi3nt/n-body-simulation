#include "CudaManager.hpp"
#include "Particle.hpp"
#include "kernel.hpp"


CudaManager::CudaManager(std::vector<Particle>& particles) : particleCount(particles.size()) {

  this->particles = (Particle*)mallocGPU(particleCount * sizeof(Particle));
  this->accs = (Vec2*)mallocGPU(particleCount * sizeof(Vec2));

  copyParticleToGPU(particles.data());


  }

CudaManager::~CudaManager() {
  freeGPU(this->particles);
  freeGPU(this->accs);
}

std::span<Particle> CudaManager::getParticles() {
  static Particle* copiedParticles = new Particle[this->particleCount]();

  copyParticleFromGPU(copiedParticles);

  return std::span<Particle>(copiedParticles, this->particleCount);
}
/*
CudaManager::CudaManager(const int size) : particleCount(size) {
  this->particles = new ParticleCuda[size * sizeof(Particle)]; 
  initMemory(size);

}


void CudaManager::setParticles(const std::vector<Particle>& particles) {
   for(int i = 0; i < particles.size(); i++) {
    this->particles[i].posx = particles[i].pos.x;
    this->particles[i].posy = particles[i].pos.y;
    this->particles[i].velx = particles[i].vel.x;
    this->particles[i].vely = particles[i].vel.y;
  }

  copyParticlesToGPU();

}*/
