#ifndef MISSION_HEADER_FILE
#define MISSION_HEADER_FILE

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_opengl.h>
#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_sdl2.h"
#include "../imgui/imgui_impl_sdlrenderer2.h"
#include "../world/Spaceship.h"
#include "../world/Environment.h"
#include "../control/PIDController.h"


class Mission
{
private:
	Spaceship m_Spaceship;
	Environment m_Environment;
	SDL_Texture* m_TargetFlag;
	PIDController m_PIDControllerHorizontal;
	PIDController m_PIDControllerVertical;
	SDL_Window* m_Window;
	SDL_GLContext m_GLContext;
	SDL_Renderer* m_Renderer;
	//ImGuiIO& m_io;
	int m_MouseY{0};
	int m_MouseX{0};
	
	void initSpaceship(SDL_Texture* texture);
	void initEnvironment(float gravity, SDL_Texture *texture);
	bool initVisuals();
	void updateSpaceship(double dt);
	void draw();
	void runMission();
	void initFlag();
	SDL_Texture* initTexture(std::string path);

public:
	Mission();
	~Mission();
	void start();
};


#endif