#pragma once
#include <string>

namespace SnakeGame
{
	const std::string RESOURCES_PATH = "Resources/";

	const unsigned int SCREEN_WIDTH = 800;
	const unsigned int SCREEN_HEGHT = 600;
	
	constexpr float SNAKE_SIZE = 40.f;
	const unsigned int INITIAL_SNAKE_SIZE = 3;
	constexpr float INITIAL_SPEED = 100.f;

	constexpr float APPLE_SIZE = 20.f;

	constexpr int NUM_ROCK = 10;
	constexpr float ROCK_SIZE = 30.f;
}