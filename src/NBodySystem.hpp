#include <span>
#include <vector>
#include "CudaManager.hpp"
#include "Particle.hpp"

class NBodySystem {

  public: 
    NBodySystem(const std::pair<int, int> fieldSize, std::vector<Particle>& particles);
    void update(float timeDelta);
    void updateCUDA(float timeDelta);
    const std::span<Particle>& getParticles();

  private:
    const std::pair<int, int> fieldSize;
    CudaManager manager;
    std::span<Particle> particles;
    std::vector<Vec2> computeAccelarations();
};
