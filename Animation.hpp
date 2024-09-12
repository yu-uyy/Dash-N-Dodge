#pragma once
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Sprite.hpp>

class Animation
{
private:
    sf::Texture m_texture;
    sf::Vector2u m_imageCount;
    sf::Vector2u m_currentImage;

    sf::Time m_totalTime;
    sf::Time m_switchTime;

public:
    sf::IntRect m_displayRect;

    Animation();
    ~Animation();

    void Setters(const sf::Texture& texture, sf::Vector2u imageCount, sf::Time switchTime);
    void UpdateAnimation(int row, sf::Time deltaTime);
};
