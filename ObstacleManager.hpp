#pragma once

#include <SFML/Graphics.hpp>
#include "Animation.hpp"
#include <vector>
#include <algorithm>
#include <cstdlib>
class ObstacleManager
{
public:
    ObstacleManager();
    ~ObstacleManager() = default;

    void Init();
    void SpawnLandObstacle();
    void SpawnFlyingObstacle();
    void SpawnSpider(); 
    void Update(const sf::Time& deltaTime);
    void Draw(sf::RenderWindow& window);
    bool CheckCollision(const sf::RectangleShape& player);
    void IncreaseSpeed(int score);
    const sf::RectangleShape& GetFloor() const;

    void getScore(int& score) { this->m_score = score;  };

private:
    void UpdateObstacles(std::vector<sf::RectangleShape>& obstacles, Animation& animation, const sf::Time& deltaTime) const;
    void UpdateSpider(std::vector<sf::RectangleShape>& obstacles, const sf::Time& deltaTime) const; 

    sf::Texture m_landTexture;
    sf::Texture m_flyingTexture;
    sf::Texture m_spiderTexture; 
    sf::RectangleShape m_floor;
    std::vector<sf::RectangleShape> m_landObstacles;
    std::vector<sf::RectangleShape> m_flyingObstacles;
    std::vector<sf::RectangleShape> m_spiderObstacles;

    float m_obstacleSpeed;
    float m_spawnTimer;
    float m_spawnInterval;
    sf::Vector2f m_obstacleSize;

    Animation m_landAnimation;
    Animation m_flyingAnimation;

    unsigned int m_score; 
};

