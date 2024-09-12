#pragma once
#include "Context.hpp"
#include "MainMenu.hpp"
class PauseGame : public Engine::State
{
private:

	std::shared_ptr<Context> m_context; 
	sf::Text m_pauseTitle; 

	unsigned int m_currentScore; 

	sf::Text m_resumeButton;
	sf::Text m_exitButton;
	sf::Text m_restartButton; 

	bool m_isResumeButtonSelected;
	bool m_isResumeButtonPressed; 

	bool m_isRestartButtonSelected;
	bool m_isRestartButtonPressed;

	bool m_isExitButtonSelected;
	bool m_isExitButtonPressed;

public:
	PauseGame(std::shared_ptr<Context>& context, int Score);
	~PauseGame(); 

	void Init() override;
	void ProcessInput() override;
	void Update(const sf::Time& deltaTime) override;
	void Draw() override;

};

