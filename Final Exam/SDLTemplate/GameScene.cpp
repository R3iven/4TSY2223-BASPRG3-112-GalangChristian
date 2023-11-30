#include "GameScene.h"

GameScene::GameScene()
{
	// Register and add game objects on constructor
	player = new Player();
	this->addGameObject(player);

	points = 0;
}

GameScene::~GameScene()
{
	delete player;
}

void GameScene::start()
{
	Scene::start();
	// Initialize any scene logic here

	initFonts();
}

void GameScene::draw()
{
	prepareScene();

	// Draw the background
	drawBackground("gfx/background.png");

	Scene::draw();

	drawText(110, 10, 255, 255, 255, TEXT_CENTER, "POINTS: %03d", points);

	if (player->getIsAlive() == false)
	{
		drawText(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 255, 255, 255, TEXT_CENTER, "GAME OVER!");
	}

	presentScene();
}

void GameScene::update()
{
	Scene::update();

	for (size_t i = 0; i < tails.size(); ++i)
	{
		if (i == 0)
		{
			// set position of the first tail to the player
			tails[i]->setPosition(player->getPositionX(), player->getPositionY());
			tails[0]->setDirection(player->getDirection());  // Set the tail direction to player direction
		}
		else
		{
			// for later tails, follow the position of the previous tail
			int prevX = tails[i - 1]->getPositionX();
			int prevY = tails[i - 1]->getPositionY();
			tails[i]->setPosition(prevX, prevY);
			std::cout << "test" << std::endl;
		}
	}

	// Draw the updated tail positions
	for (auto& tail : tails) {
		tail->draw();
	}

	doSpawnFruitLogic();
	doCollisionLogic();
}

void GameScene::doSpawnFruitLogic()
{
	if (spawnedFruit.empty())
	{
		Fruit* fruit = new Fruit();
		this->addGameObject(fruit);

		fruit->setPosition(20 + rand() % SCREEN_WIDTH - fruit->getWidth(), 20 + rand() % SCREEN_HEIGHT - fruit->getWidth());
		spawnedFruit.push_back(fruit);
	}
}

void GameScene::despawnFruit(Fruit* fruit)
{
	int index = -1;
	for (int i = 0; i < spawnedFruit.size(); i++)
	{
		// if the pointer matches
		if (fruit == spawnedFruit[i])
		{
			index = i;
			break;
		}
	}

	// if any match is found
	if (index != -1)
	{
		spawnedFruit.erase(spawnedFruit.begin() + index);
		delete fruit;
	}
}


void GameScene::spawnTail()
{
	tail* newTail = new tail();
	tails.push_back(newTail);

	this->addGameObject(newTail);
}

void GameScene::moveTail(int x, int y)
{
	tail* newTail = new tail();
	newTail->setPosition(x, y);
	newTail->setDirection(player->getDirection());  // set tail direction to player direction
	tails.push_back(newTail);
	this->addGameObject(newTail);
}

void GameScene::doCollisionLogic()
{
	//check for collisions
	for (int i = 0; i < objects.size(); i++)
	{
		// cast to bullet
		Fruit* fruit = dynamic_cast<Fruit*>(objects[i]);

		// check if the cast was success, if object[i] is a fruit
		if (fruit != NULL)
		{
			int collision = checkCollision(
				player->getPositionX(), player->getPositionY(), player->getWidth(), player->getHeight(),
				fruit->getPositionX(), fruit->getPositionY(), fruit->getWidth(), fruit->getHeight()
			);

			if (collision == 1)
			{
				despawnFruit(fruit);
				moveTail(player->getPositionX(), player->getPositionY());  // spawn new tail when collecting fruit
				points++;
				break;
			}
		}
	}

	// out of bounds
	if (player->getPositionX() < 0 || player->getPositionX() >= SCREEN_WIDTH - player->getWidth() ||
		player->getPositionY() < 0 || player->getPositionY() >= SCREEN_HEIGHT - player->getHeight())
	{
		player->Dead();
	}
}