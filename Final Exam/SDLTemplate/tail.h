#pragma once
#include "GameObject.h"
#include "Direction.h"
#include "common.h"
#include "draw.h"
#include "SoundManager.h"
#include "util.h"
#include "Player.h"
#include <vector>
#include <deque>

class tail : public GameObject
{

public:
	tail();
	~tail();
	void start();

	void setDirection(Direction dir);

	void update();
	void draw();

	void setPosition(int xPos, int yPos);

	int getPositionX();
	int getPositionY();

	int getWidth();
	int getHeight();


private:
	SDL_Texture* texture;
	Mix_Chunk* sound;
	int x;
	int y;

	int width;
	int height;
	int speed;

	int moveDelay;
	int currentDelay;

	Direction currentDirection;
	std::deque<std::pair<int, int>> tailPositions;  // store the previous positions of the tail
};

