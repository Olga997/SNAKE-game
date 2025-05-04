#pragma once
#include "SFML/Graphics.hpp"
#include <list>

namespace SnakeGame
{
	//Text
	enum class Orientation
	{
		Horizontal,
		Vertical
	};
	enum class Alignment
	{
		Min, 
		Middle,
		Max 
	};
	//Menu
	struct MenuItem
	{
		sf::Text text;
		sf::Text hintText; 
		Orientation childrenOrientation = Orientation::Vertical;
		Alignment childrenAlignment = Alignment::Min;
		float childrenSpacing;

		sf::Color selectedColor = sf::Color::Yellow;
		sf::Color deselectedColor = sf::Color::White;

		bool isEnabled = true;
		std::vector<MenuItem*> children;

		MenuItem* parent = nullptr;
	};

	struct Menu
	{
		MenuItem rootItem;
		MenuItem* selectedItem = nullptr;
	};

	sf::Vector2f GetTextOrigin(const sf::Text& text, const sf::Vector2f& relativePosition);
	void DrawTextList(sf::RenderWindow& window, const std::vector<sf::Text*>& items, float spacing, Orientation orientation, Alignment alignment, const sf::Vector2f& position, const sf::Vector2f& origin);

	void InitMenuItem(MenuItem& menu);
	void SelectMenuItem(Menu& menu, MenuItem* item);
	bool SelectPreviousMenuItem(Menu& menu);
	bool SelectNextMenuItem(Menu& menu);
	bool ExpandSelectedItem(Menu& menu);
	bool CollapseSelectedItem(Menu& menu);

	MenuItem* GetCurrentMenuContext(Menu& menu);

	void DrawMenu(Menu& menu, sf::RenderWindow& window, sf::Vector2f position, sf::Vector2f origin);
}
