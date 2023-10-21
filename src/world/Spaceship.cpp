#include "Spaceship.h"

void Spaceship::spawnSpaceship(int x, int y, SDL_Texture* texture)
{
	m_X = x;
	m_Y = y;
	m_State = State::FREEFALL;
	m_Texture = texture;

	printf("Spaceship has been spawned at (%f, %f) \n", m_X, m_Y);
}

void Spaceship::move(int dx, int dy)
{
	// Horizontal
	if (dx < 0) { m_State = State::MANEUVER_NEG_X; }
	else if (dx == 0) { m_State = State::FREEFALL; }
	else { m_State = State::MANEUVER_POS_X; }

	if (abs(dx) < 120.0) { dx = 0; }
	else if (abs(dx) > abs(X_MANEUVER_LIMIT)) 
	{ 
		if (dx > 0) { dx = X_MANEUVER_LIMIT; }
		else { dx = -X_MANEUVER_LIMIT; }
	}
	m_X = m_X + dx;

	// Vertical
	if (dy > Y_MANEUVER_LIMIT) { dy = Y_MANEUVER_LIMIT; }
	m_Y = m_Y + dy;
}

int Spaceship::getX()
{
	return m_X;
}

int Spaceship::getY()
{
	return m_Y;
}

SDL_Texture* Spaceship::getTexture()
{
	return m_Texture;
}

void Spaceship::setState(State state)
{
	m_State = state;
}

State Spaceship::getState()
{
	return m_State;
}
