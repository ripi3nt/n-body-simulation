# CUDA N-Body Simulation

A real-time 2D gravitational N-body simulation written in **C++20**, accelerated with **CUDA**, and rendered using **SFML**.

The physics computation runs entirely on the GPU. Rendering is handled on the CPU.

---

## Overview

Each particle experiences gravitational acceleration from every other particle:
```
aᵢ = G Σⱼ ( (rⱼ - rᵢ) / (|rⱼ - rᵢ|² + ε²)^(3/2) )
```
Integration uses semi-implicit Euler:
```
v += a · dt  
x += v · dt  
```

Current implementation is **O(n²)**.

---

## Build

Requirements:
- CUDA Toolkit  
- SFML  
- C++20 compiler  
- make  

Build:
```
make
```
