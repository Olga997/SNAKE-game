#include "Rock.h"
#include "Settings.h"
#include "Game.h"
#include <cassert>

namespace SnakeGame
{
	void InitRock(Rock& rock)
	{
		//rock.position = GetRandomPositionOnScreen(SCREEN_WIDTH, SCREEN_HIGHT);

		assert(rock.texture.loadFromFile(RESOURCES_PATH + "\\Rock.png"));

		//Init rocks sprite
		rock.sprite.setTexture(rock.texture);
		SetSpriteSize(rock.sprite, ROCK_SIZE, ROCK_SIZE);
		SetSpriteRelativeOrigin(rock.sprite, 0.5f, 0.5f);
	}
	void DrawRock(Rock& rock, sf::RenderWindow& window)
	{
		rock.sprite.setPosition(rock.position.x, rock.position.y);
		window.draw(rock.sprite);
	}
}