#pragma once

#include "Context.hpp"
#include "Player.hpp"
#include "ObstacleManager.hpp"
#include <SFML/Graphics/Text.hpp>
#include "MainMenu.hpp"
#include "PauseGame.hpp"
#include <SFML/Audio.hpp>

class GamePlay : public Engine::State
{
private:
    std::shared_ptr<Context> m_context;
    Player m_player;
    ObstacleManager m_obstacleManager;
    sf::Sprite m_backSprite;
    sf::Text m_scoreText;
    int m_score;
    float m_elapsedTime;

public:
    GamePlay(std::shared_ptr<Context>& context);
    ~GamePlay() {}

    void Init() override;
    void ProcessInput() override;
    void Update(const sf::Time& deltaTime) override;
    void Draw() override;


private:
    sf::SoundBuffer m_jumpBuffer;
    sf::Sound m_jumpSound; 

    bool m_spacePressed;
    bool m_mouseLeftPressed;

};
