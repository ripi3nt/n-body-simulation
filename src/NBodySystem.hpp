#include <vector>
#include "Particle.hpp"

class NBodySystem {

  public: 
    NBodySystem(const float gravConstant, const float softening, const std::pair<int, int> fieldSize, const int particleCount);
    void update(float timeDelta);
    const std::vector<Particle>& getParticles();

  private:
    const float gravConstant;
    const float softening;
    const std::pair<int, int> fieldSize;
    std::vector<Particle> particles;
    float randomFloat(int max);
    std::vector<Vec2> computeAccelarations();
};
