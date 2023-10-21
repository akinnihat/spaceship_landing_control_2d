#include "Environment.h"

void Environment::createEnvironment(float gravity, SDL_Texture* texture)
{
	m_Gravity = gravity;
	m_Texture = texture; 
}

float Environment::getEffectingGravity()
{
	return m_Gravity;
}

SDL_Texture* Environment::getTexture()
{
	return m_Texture;
}
