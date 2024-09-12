#include "Player.hpp"

Player::Player()
    : m_jumpHeight(-980.f),
    m_gravity(2000.f),
    m_velocityY(0.f),
    m_moveSpeed(300.f),
    m_isJumping(false),
    m_isMovingLeft(false)
{
    m_runningTexture.loadFromFile("Running.png");
    m_enemyTexture.loadFromFile("RunningEnemy.png");
}

void Player::Init()
{
    m_playerAnimation.Setters(m_runningTexture, sf::Vector2u(20, 1), sf::seconds(1.0f / 20.0f));
    m_body.setSize(sf::Vector2f(128.f, 128.f)); // Player size
    m_body.setPosition(150.f, 550.f);
    m_body.setFillColor(sf::Color::White);
    m_body.setTexture(&m_runningTexture);
}

void Player::Jump()
{
    if (!m_isJumping)
    {
        m_velocityY = m_jumpHeight;
        m_isJumping = true;
    }
}

void Player::MoveLeft()
{
    m_isMovingLeft = true;
    m_body.setTexture(&m_enemyTexture);
}

void Player::MoveRight()
{
    m_isMovingLeft = false;
    m_body.setTexture(&m_runningTexture);
}

void Player::StopMoving()
{
    m_isMovingLeft = false;
    m_body.setTexture(&m_runningTexture);
}

void Player::Update(const sf::Time& deltaTime, const sf::RectangleShape& floor)
{
    if (m_isJumping)
    {
        m_velocityY += m_gravity * deltaTime.asSeconds();
        m_body.move(0.f, m_velocityY * deltaTime.asSeconds());

        if (m_body.getGlobalBounds().intersects(floor.getGlobalBounds()))
        {
            m_body.setPosition(m_body.getPosition().x, floor.getPosition().y - m_body.getSize().y);
            m_velocityY = 0.f;
            m_isJumping = false;
        }
    }

    float movement = m_moveSpeed * deltaTime.asSeconds();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        MoveLeft();
        m_body.move(-movement, 0.f);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        MoveRight();
        m_body.move(movement, 0.f);
    }
    else
    {
        StopMoving();
    }

    // Prevent the player from going out of the window
    if (m_body.getPosition().x < 0)
    {
        m_body.setPosition(0, m_body.getPosition().y);
    }
    else if (m_body.getPosition().x + m_body.getSize().x > 1280.f)
    {
        m_body.setPosition(1280.f - m_body.getSize().x, m_body.getPosition().y);
    }

    m_playerAnimation.UpdateAnimation(0, deltaTime);
    m_body.setTextureRect(m_playerAnimation.m_displayRect);
}

void Player::Draw(sf::RenderWindow& window)
{
    window.draw(m_body);
}

const sf::RectangleShape& Player::GetBody() const
{
    return m_body;
}

sf::RectangleShape& Player::GetBody()
{
    return m_body;
}