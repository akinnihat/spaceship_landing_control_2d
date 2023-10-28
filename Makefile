
EXE = Spaceship_Landing_Control_2D
SOURCES = src/main.cpp
SOURCES += src/core/Mission.cpp src/world/Spaceship.cpp src/world/Environment.cpp src/control/PIDController.cpp
SOURCES += imgui.cpp imgui_draw.cpp imgui_tables.cpp imgui_widgets.cpp
SOURCES += src/imgui/imgui_impl_sdl2.cpp  src/imgui/imgui_impl_sdlrenderer2.cpp 
OBJDIR = build
$(shell mkdir -p $(OBJDIR))
OBJS = $(addprefix $(OBJDIR)/, $(addsuffix .o, $(basename $(notdir $(SOURCES)))))

CC = g++
COMPILER_FLAGS = -w -std=c++11 -I -Ibackends -g -Wall -Wformat `sdl2-config --cflags`
LINKER_FLAGS = -lSDL2 -lSDL2_image -lGL -ldl `sdl2-config --libs`

build/main.o: src/main.cpp 
	$(CXX) $(CXXFLAGS) -c -o $@ $<

build/%.o:src/core/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

build/%.o:src/control/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

build/%.o:src/world/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

build/%.o:src/imgui/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# make all
all: $(EXE)

$(EXE): $(OBJS)
	$(CC) -o $@ $^ $(COMPILER_FLAGS) $(LINKER_FLAGS)
	@echo Build complete

# make clean
clean:
	rm -f $(OBJS) $(EXE)
