OBJS = build/main.o build/Mission.o build/Spaceship.o build/Environment.o build/PIDController.o
HEADERS = src/core/Mission.h src/world/Spaceship.h src/world/Environment.h src/control/PIDController.h
CC = g++
COMPILER_FLAGS = -w
LINKER_FLAGS = -lSDL2 -lSDL2_image


build/main.o: src/main.cpp $(HEADERS)
	$(CC) -c $(COMPILER_FLAGS) $< -o $@

build/Mission.o: src/core/Mission.cpp src/core/Mission.h
	$(CC) -c $(COMPILER_FLAGS) $< -o $@

build/Spaceship.o: src/world/Spaceship.cpp src/world/Spaceship.h
	$(CC) -c $(COMPILER_FLAGS) $< -o $@

build/Environment.o: src/world/Environment.cpp src/world/Environment.h
	$(CC) -c $(COMPILER_FLAGS) $< -o $@

build/PIDController.o: src/control/PIDController.cpp src/control/PIDController.h
	$(CC) -c $(COMPILER_FLAGS) $< -o $@

Spaceship_Landing_Control_2D: $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $@


# make all
all: Spaceship_Landing_Control_2D

# make clean
clean:
	rm -f $(OBJS) Spaceship_Landing_Control_2D
