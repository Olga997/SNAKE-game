#pragma once
#include <string>

namespace SnakeGame
{
	const std::string RESOURCES_PATH = "Resources/";

	constexpr int SCREEN_WIDTH = 800;
	constexpr int SCREEN_HIGHT = 600;
	constexpr unsigned int MODALKA_WIDTH = SCREEN_WIDTH / 2;
	constexpr unsigned int MODALKA_HIGHT = SCREEN_HIGHT / 2;
	
	constexpr float SNAKE_SIZE = 40.f;
	constexpr float INITIAL_SPEED = 100.f;

	constexpr float APPLE_SIZE = 20.f;

	constexpr int NUM_ROCK = 10;
	constexpr float ROCK_SIZE = 30.f;
}