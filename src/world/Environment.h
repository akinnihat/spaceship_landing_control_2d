#ifndef ENVIRONMENT_HEADER_FILE
#define ENVIRONMENT_HEADER_FILE

#include <SDL2/SDL.h>

class Environment 
{
private:
	float m_Gravity;
	SDL_Texture *m_Texture;

public:
	void createEnvironment(float gravity, SDL_Texture* texture);
	float getEffectingGravity();
	SDL_Texture* getTexture();
};

#endif