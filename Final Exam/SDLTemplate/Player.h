#pragma once
#include "Direction.h"
#include "GameObject.h"
#include "common.h"
#include "draw.h"
#include "SoundManager.h"
#include "tail.h"
#include <vector>

class Player :
    public GameObject
{
public:
	Direction getDirection() const 
	{
		return currentDirection;
	}
	~Player();
	void start();
	void update();
	void draw();

	int getPositionX();
	int getPositionY();

	int getWidth();
	int getHeight();

	bool getIsAlive();
	void Dead();

private:
	Direction currentDirection;
	Direction lastDirection;
	SDL_Texture* texture;

	int x;
	int y;
	int width;
	int height;
	int speed;
	int boost;
	bool isAlive;
};

