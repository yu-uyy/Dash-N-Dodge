#include "InputManager.hpp"



Engine::InputManager::InputManager()
{
}

Engine::InputManager::~InputManager()
{
}

bool Engine::InputManager::m_isSpriteClicked(const sf::Text& object, sf::Mouse::Button button, sf::RenderWindow& window)
{
    if (sf::Mouse::isButtonPressed(button))
    {
        sf::FloatRect objectRect = object.getGlobalBounds();
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        if (objectRect.contains(static_cast<sf::Vector2f>(mousePos)))
            return true;
    }
    return false;
}

bool Engine::InputManager::m_isSpriteHover(const sf::Text& object, sf::RenderWindow& window)
{
    sf::FloatRect objectRect = object.getGlobalBounds();
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    return objectRect.contains(static_cast<sf::Vector2f>(mousePos));
}



sf::Vector2i Engine::InputManager::GetMousePosition(sf::RenderWindow& window)
{
    return sf::Mouse::getPosition(window);
}


