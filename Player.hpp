#pragma once

#include <SFML/Graphics.hpp>
#include "Animation.hpp"

class Player
{
private:
    sf::RectangleShape m_body;
    sf::Texture m_runningTexture;
    sf::Texture m_enemyTexture;
    Animation m_playerAnimation;
    float m_jumpHeight;
    float m_gravity;
    float m_velocityY;
    float m_moveSpeed;
    bool m_isJumping;
    bool m_isMovingLeft;

public:
    Player();
    ~Player() {}

    void Init();
    void Jump();
    void MoveLeft();
    void MoveRight();
    void StopMoving();
    void Update(const sf::Time& deltaTime, const sf::RectangleShape& floor);
    void Draw(sf::RenderWindow& window);
    const sf::RectangleShape& GetBody() const;
    sf::RectangleShape& GetBody();
};