#pragma once
#include <vector>
#include <span>
#include "Particle.hpp"

struct ParticleCuda {
  float posx;
  float posy;
  float velx;
  float vely;
};

class CudaManager {
  Particle* particles;
  const int particleCount;
  Vec2* accs;

  private:
    void copyParticleFromGPU(Particle* output);
    void copyParticleToGPU(Particle* output);
  
  public:
    CudaManager(std::vector<Particle>& particles);
    ~CudaManager();
    std::span<Particle> getParticles();
    void updateParticles(float timeDelta);
};
