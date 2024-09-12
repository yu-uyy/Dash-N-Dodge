#include "Animation.hpp"
#include <SFML/Graphics/Texture.hpp>
#include <iostream>

Animation::Animation()
    : m_totalTime(sf::Time::Zero), m_currentImage(0, 0)
{
}

Animation::~Animation()
{
}

void Animation::Setters(const sf::Texture& texture, sf::Vector2u imageCount, sf::Time switchTime)
{
    m_texture = texture;
    m_imageCount = imageCount;
    m_switchTime = switchTime;

    m_displayRect.width = texture.getSize().x / imageCount.x;
    m_displayRect.height = texture.getSize().y / imageCount.y;
}

void Animation::UpdateAnimation(int row, sf::Time deltaTime)
{
    m_currentImage.y = row;
    m_totalTime += deltaTime;

    if (m_totalTime >= m_switchTime)
    {
        m_totalTime -= m_switchTime;
        m_currentImage.x++;

        if (m_currentImage.x >= m_imageCount.x)
            m_currentImage.x = 0;
    }

    m_displayRect.top = m_currentImage.y * m_displayRect.height;
    m_displayRect.left = m_currentImage.x * m_displayRect.width;

    
}

