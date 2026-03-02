#include "CudaManager.hpp"
#include "Particle.hpp"
#include "kernel.hpp"
#include "Vec2D.hpp"
#include "Config.hpp"

//extern __shared__ Vec2 sharedAccs[];

__device__ void moveParticle(Particle* data, Vec2* accs, const int countG, float timeDelta) {
  const int i = threadIdx.x;

    data[i].vel.x += accs[i].x * timeDelta;
    data[i].vel.y += accs[i].y * timeDelta;
    data[i].pos.x += data[i].vel.x * timeDelta;
    data[i].pos.y += data[i].vel.y * timeDelta;
}

__device__ void calculateAcc(Particle* data,const int countG, Vec2* output) {
  const int first = threadIdx.x;
  for (int second = 0; second < countG; second++) {

    if(first == second) continue;
    float vecx = data[second].pos.x - data[first].pos.x;
    float vecy = data[second].pos.y - data[first].pos.y;
    float distBetween = sqrtf(vecx*vecx + vecy*vecy + softening*softening);
    float distBetween3 = distBetween*distBetween*distBetween;
    output[first].x += (vecx * gravConstant) / (distBetween3);
    output[first].y += (vecy * gravConstant) / (distBetween3);
  }

  /*
  __syncthreads();
  if(threadIdx.x == 0) {
    for (int i = 0; i < countG; i++) {
      output[i].x = sharedAccs[i].x;
      output[i].y = sharedAccs[i].y;
    }
  }
  */
}

__device__ void checkBounds(Particle* data, const int countG) {
  const int i = threadIdx.x;

  if(data[i].pos.x < 0 || data[i].pos.x > screenW) {
    data[i].vel.x *= -1;
  }
  if(data[i].pos.y < 0 || data[i].pos.y > screenH) {
    data[i].vel.y *= -1;
  }
}

__global__ void update(Particle* particles,const int countG, float timeDelta, Vec2* accs) {
  calculateAcc(particles, countG, accs);
  __syncthreads();
  moveParticle(particles, accs, countG, timeDelta);
  checkBounds(particles, countG);
}



void* mallocGPU(size_t size) {
  void* adr;
  cudaMalloc(&adr, size);

  return adr;
}

void freeGPU(void* addr) {
  cudaFree(addr);
}

void CudaManager::updateParticles(float timeDelta) {
  update<<<1, this->particleCount>>>(this->particles, this->particleCount, timeDelta, this->accs);
  cudaDeviceSynchronize();
}

void CudaManager::copyParticleFromGPU(Particle* output) {
  cudaMemcpy(output, this->particles, this->particleCount * sizeof(Particle), cudaMemcpyKind::cudaMemcpyDeviceToHost);
}

void CudaManager::copyParticleToGPU(Particle* data) {
  cudaError_t err = cudaMemcpy(this->particles, data, this->particleCount * sizeof(Particle), cudaMemcpyKind::cudaMemcpyHostToDevice);
}
