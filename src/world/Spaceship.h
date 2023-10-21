#ifndef SPACESHIP_HEADER_FILE
#define SPACESHIP_HEADER_FILE

#include <SDL2/SDL.h>
#include <string>

const float X_MANEUVER_LIMIT{7.0};
const float Y_MANEUVER_LIMIT{8.0};

enum class State
{
	MANEUVER_POS_X,
	MANEUVER_NEG_X,
	FREEFALL,
	LANDED
};

class Spaceship {
private:
	int m_X;
	int m_Y;
	State m_State;
	SDL_Texture* m_Texture;

public:
	void spawnSpaceship(int x, int y, SDL_Texture* texture);
	void move(int dx, int dy);
	int getX();
	int getY();
	SDL_Texture* getTexture();
	void setState(State state);
	State getState();
};

#endif