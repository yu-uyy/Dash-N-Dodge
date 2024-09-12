#include "PauseGame.hpp"

PauseGame::PauseGame(std::shared_ptr<Context>& context, int Score) : m_context(context) , m_currentScore(Score),
m_isExitButtonPressed(false), m_isExitButtonSelected(false), m_isResumeButtonSelected(false), m_isResumeButtonPressed(false), m_isRestartButtonPressed(false),
m_isRestartButtonSelected(false)
{

}

PauseGame::~PauseGame()
{
}

void PauseGame::Init()
{
    m_resumeButton.setFont(m_context->m_assets->GetFont(Font::MAIN_FONT));
    m_exitButton.setFont(m_context->m_assets->GetFont(Font::MAIN_FONT)); 
    m_restartButton.setFont(m_context->m_assets->GetFont(Font::MAIN_FONT));

    float windowWidth = static_cast<float>(m_context->m_window->getSize().x);
    float windowHeight = static_cast<float>(m_context->m_window->getSize().y);

    // Initialize the Resume Button
    m_resumeButton.setCharacterSize(70);
    m_resumeButton.setString("Resume");
    m_resumeButton.setOrigin(m_resumeButton.getLocalBounds().width / 2, m_resumeButton.getLocalBounds().height / 2);
    m_resumeButton.setPosition(windowWidth / 2, (windowHeight / 2) - 50);

    // Initialize the Restart Button
    m_restartButton.setCharacterSize(60);
    m_restartButton.setString("Restart");
    m_restartButton.setOrigin(m_restartButton.getLocalBounds().width / 2, m_restartButton.getLocalBounds().height / 2);
    m_restartButton.setPosition(windowWidth / 2, (windowHeight / 2) + 50);

    // Initialize the Exit Button
    m_exitButton.setCharacterSize(50);
    m_exitButton.setString("Exit");
    m_exitButton.setOrigin(m_exitButton.getLocalBounds().width / 2, m_exitButton.getLocalBounds().height / 2);
    m_exitButton.setPosition(windowWidth / 2, (windowHeight / 2) + 150);

}

void PauseGame::ProcessInput()
{
	sf::Event event; 
	while (m_context->m_window->pollEvent(event))
	{
        if (event.type == sf::Event::Closed)
        {
            m_context->m_window->close();
        }
        else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
        {
            if (m_context->m_mouseInput->m_isSpriteClicked(m_resumeButton, sf::Mouse::Left, *m_context->m_window))
            {
                m_isResumeButtonPressed = true;
            }
            else if (m_context->m_mouseInput->m_isSpriteClicked(m_exitButton, sf::Mouse::Left, *m_context->m_window))
            {
                m_isExitButtonPressed = true; 
            }
            else if (m_context->m_mouseInput->m_isSpriteClicked(m_restartButton, sf::Mouse::Left, *m_context->m_window))
            {
                m_isRestartButtonPressed = true;
            }
        }

	}

    m_isResumeButtonSelected = m_context->m_mouseInput->m_isSpriteHover(m_resumeButton, *m_context->m_window);
    m_isExitButtonSelected = m_context->m_mouseInput->m_isSpriteHover(m_exitButton, *m_context->m_window);
    m_isRestartButtonSelected = m_context->m_mouseInput->m_isSpriteHover(m_restartButton, *m_context->m_window); 
}

void PauseGame::Update(const sf::Time& deltaTime)
{
    if (m_isResumeButtonPressed)
    {
        m_context->m_states->PopCurrent(); 
    }

    if (m_isRestartButtonPressed)
    {
        m_context->m_states->Add(std::make_unique<GamePlay>(m_context), true);
        m_context->m_states->PopCurrent();
        m_context->m_states->ProcessStateChange();
    }
    else if (m_isExitButtonPressed)
    {

        m_context->m_states->Add(std::make_unique<MainMenu>(m_context), true);
        m_context->m_states->PopCurrent();
        m_context->m_states->ProcessStateChange();
    }
}

void PauseGame::Draw()
{
    if (m_isResumeButtonSelected)
    {
        m_resumeButton.setFillColor(sf::Color::Yellow);
    }
    else
    {
        m_resumeButton.setFillColor(sf::Color::White);
    }
    if (m_isRestartButtonSelected)
    {
        m_restartButton.setFillColor(sf::Color::Yellow);
    }

    else
    {
        m_restartButton.setFillColor(sf::Color::White);
    }

    if (m_isExitButtonSelected)
    {
        m_exitButton.setFillColor(sf::Color::Yellow);
    }
    else
    {
        m_exitButton.setFillColor(sf::Color::White);
    }
    m_context->m_window->draw(m_resumeButton);
    m_context->m_window->draw(m_restartButton); 
    m_context->m_window->draw(m_exitButton);

    m_context->m_window->display(); 
}
