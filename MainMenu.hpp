#pragma once
#include "Context.hpp"
#include "SFML/Graphics/Text.hpp"
#include "SFML/Window/Event.hpp"
#include "GamePlay.hpp"
#include "SFML/Audio.hpp"
#include "fstream"

class MainMenu : public Engine::State
{
private:
    std::shared_ptr<Context> m_context;
    sf::Text m_gameTitle;
    sf::Text m_playButton;
    sf::Text m_exitButton;
    sf::Text m_finalScoreText; 
    sf::Text m_musicButton;
    sf::Text m_highScoreText; 

    bool m_isAudioPaused;

    bool m_isPlayButtonSelected;
    bool m_isPlayButtonPressed;
    bool m_isMusicButtonPresseed; 

    bool m_isExitButtonSelected;
    bool m_isMusicButtonSelected; 
    
    int m_finalScore;
    int m_highScore; 

public:
    MainMenu(std::shared_ptr<Context>& context, int finalScore = 0);
    ~MainMenu() {}

    void Init() override;
    void ProcessInput() override;
    void Update(const sf::Time& deltaTime) override;
    void Draw() override;
    void SaveHighScore() const; 
    void LoadHighScore(); 
    void UpdateHighScore(int newScore); 
private:
    sf::Sprite m_bgSprite;
};