#pragma once
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Text.hpp"
#include "SFML/Window/Event.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
namespace Engine
{
	class InputManager
	{
	private:

	public:
		InputManager(); 
		~InputManager();
		bool m_isSpriteHover(const sf::Text& object, sf::RenderWindow& window);
		bool m_isSpriteClicked(const sf::Text& object, sf::Mouse::Button button, sf::RenderWindow& window);

		sf::Vector2i GetMousePosition(sf::RenderWindow& window);
	};
}