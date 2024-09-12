#include "ObstacleManager.hpp"
#include "Animation.hpp"

ObstacleManager::ObstacleManager() 
: m_obstacleSpeed(200.f), m_spawnTimer(0.f), m_spawnInterval(2.f), m_obstacleSize(90.f, 90.f), m_score(0)
{
    m_landTexture.loadFromFile("RunningEnemy.png");
    m_flyingTexture.loadFromFile("FlyingEnemy.png");
    m_spiderTexture.loadFromFile("Spider.png"); 
    // Initialize animations
    m_landAnimation.Setters(m_landTexture, sf::Vector2u(20, 1), sf::seconds(1.0f / 20.0f));
    m_flyingAnimation.Setters(m_flyingTexture, sf::Vector2u(11, 1), sf::seconds(1.0f / 20.0f));


}

void ObstacleManager::Init()
{
    m_landObstacles.clear();
    m_flyingObstacles.clear();

    m_obstacleSpeed = 200.f;

    m_floor.setSize(sf::Vector2f(1280.f, 110.f));
    m_floor.setFillColor(sf::Color::Transparent);
    m_floor.setPosition(0.f, 670.f);
}

void ObstacleManager::SpawnLandObstacle()
{
    sf::RectangleShape obstacle(m_obstacleSize);
    obstacle.setFillColor(sf::Color::Green);
    obstacle.setPosition(1280.f, 670.f - m_obstacleSize.y);
    obstacle.setTexture(&m_landTexture);
    m_landObstacles.push_back(obstacle);
}

void ObstacleManager::SpawnFlyingObstacle()
{
    sf::RectangleShape obstacle(m_obstacleSize);
    obstacle.setFillColor(sf::Color::Red);
    obstacle.setPosition(1280.f, 300.f);
    obstacle.setTexture(&m_flyingTexture);
    m_flyingObstacles.push_back(obstacle);
}

void ObstacleManager::SpawnSpider()
{
    sf::RectangleShape spider(m_obstacleSize);
    spider.setFillColor(sf::Color::Red);
    float randomX = static_cast<float>(rand() % static_cast<int>(1280.f - m_obstacleSize.x));
    spider.setPosition(randomX, -m_obstacleSize.y); 
    spider.setTexture(&m_spiderTexture); 
    m_spiderObstacles.push_back(spider);
}


void ObstacleManager::UpdateObstacles(std::vector<sf::RectangleShape>& obstacles, Animation& animation, const sf::Time& deltaTime) const
{
    for (auto& obstacle : obstacles)
    {
        obstacle.move(-m_obstacleSpeed * deltaTime.asSeconds(), 0.f);

        animation.UpdateAnimation(0, deltaTime);
        obstacle.setTextureRect(animation.m_displayRect);
    }

    obstacles.erase(std::remove_if(obstacles.begin(), obstacles.end(), [](const sf::RectangleShape& obstacle) {
        return obstacle.getPosition().x + obstacle.getSize().x < 0.f;
        }), obstacles.end());
}

void ObstacleManager::UpdateSpider(std::vector<sf::RectangleShape>& obstacles, const sf::Time& deltaTime) const
{
    for (auto& obstacle : obstacles)
    {
        obstacle.move(0.f, m_obstacleSpeed * deltaTime.asSeconds()); 
    }

    obstacles.erase(std::remove_if(obstacles.begin(), obstacles.end(), [](const sf::RectangleShape& obstacle) {
        return obstacle.getPosition().y > 720.f; 
        }), obstacles.end());
}


void ObstacleManager::Update(const sf::Time& deltaTime)
{
    m_spawnTimer += deltaTime.asSeconds();
    if (m_spawnTimer >= m_spawnInterval)
    {
        int randValue = rand() % 3; 
        if (randValue == 0)
        {
            SpawnLandObstacle();
        }
        else if (randValue == 1)
        {
            SpawnFlyingObstacle();
        }
        else if (randValue == 2)
        {
            SpawnSpider();
        }
        m_spawnTimer = 0.f;
    }

    UpdateObstacles(m_landObstacles, m_landAnimation, deltaTime);
    UpdateObstacles(m_flyingObstacles, m_flyingAnimation, deltaTime);
    UpdateSpider(m_spiderObstacles, deltaTime);
}




void ObstacleManager::Draw(sf::RenderWindow& window)
{
    window.draw(m_floor);

    for (const auto& obstacle : m_landObstacles)
    {
        window.draw(obstacle);
    }

    for (const auto& obstacle : m_flyingObstacles)
    {
        window.draw(obstacle);
    }
    for (const auto& obstacle : m_spiderObstacles)
    {
        window.draw(obstacle); 
    }
}

bool ObstacleManager::CheckCollision(const sf::RectangleShape& player)
{
    for (const auto& obstacle : m_landObstacles)
    {
        if (player.getGlobalBounds().intersects(obstacle.getGlobalBounds()))
        {
            return true;
        }
    }

    for (const auto& obstacle : m_flyingObstacles)
    {
        if (player.getGlobalBounds().intersects(obstacle.getGlobalBounds()))
        {
            return true;
        }
    }

    for (const auto& obstacle : m_spiderObstacles)
    {
        if (player.getGlobalBounds().intersects(obstacle.getGlobalBounds()))
        {
            return true;
        }
    }

    return false;
}


void ObstacleManager::IncreaseSpeed(int score)
{
    this->m_score = score; 
    float baseSpeed = 200.f;
    float speedIncrement = 10.f;

    m_obstacleSpeed = baseSpeed + score * speedIncrement;
}

const sf::RectangleShape& ObstacleManager::GetFloor() const
{
    return m_floor;
}
