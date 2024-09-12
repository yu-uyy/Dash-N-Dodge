#include "Collision.hpp"

bool Collision::CheckCollision(const sf::RectangleShape& rect1, const sf::RectangleShape& rect2)
{
    return rect1.getGlobalBounds().intersects(rect2.getGlobalBounds());
}
