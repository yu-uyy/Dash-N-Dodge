#pragma once
#include <SFML/Graphics.hpp>

class Collision
{
public:
    static bool CheckCollision(const sf::RectangleShape& rect1, const sf::RectangleShape& rect2);
};
