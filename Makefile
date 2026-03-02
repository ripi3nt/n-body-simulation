sim: 
	nvcc -O0 -g -G -std=c++20 -o ./out/sim.out ./src/*.cpp ./src/kernel.cu -L/opt/cuda/lib64 -lcuda -lcudart -lsfml-graphics -lsfml-window -lsfml-system
