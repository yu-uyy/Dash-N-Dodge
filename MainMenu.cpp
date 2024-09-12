#include "MainMenu.hpp"

MainMenu::MainMenu(std::shared_ptr<Context>& context, int finalScore)
    : m_context(context), m_isPlayButtonSelected(false), m_isPlayButtonPressed(false),
    m_isExitButtonSelected(false), m_finalScore(finalScore), m_isMusicButtonSelected(false),
    m_isMusicButtonPresseed(false), m_isAudioPaused(false) 
{
    LoadHighScore(); 
    UpdateHighScore(finalScore); 
}


void MainMenu::Init()
{
    float windowWidth = static_cast<float>(m_context->m_window->getSize().x);
    float windowHeight = static_cast<float>(m_context->m_window->getSize().y);

    m_context->m_assets->AddTexture(Texture::MainMenu, "MainMenu.png"); 
    m_bgSprite.setTexture(m_context->m_assets->GetTexture(Texture::MainMenu)); 
    m_bgSprite.setOrigin(static_cast<float>(m_bgSprite.getLocalBounds().width / 2.0f), static_cast<float>(m_bgSprite.getLocalBounds().height / 2.0f));
    m_bgSprite.setPosition(windowWidth / 2, (windowHeight / 2));
    m_bgSprite.setScale(1.f, 1.13f); 

    m_context->m_assets->AddFont(Font::MAIN_FONT, "AntonSC-Regular.ttf");
    m_gameTitle.setFont(m_context->m_assets->GetFont(Font::MAIN_FONT));

    // Game Title
    m_gameTitle.setCharacterSize(100);
    m_gameTitle.setString("Dash N Dodge");
    m_gameTitle.setOrigin(m_gameTitle.getLocalBounds().width / 2, m_gameTitle.getLocalBounds().height / 2);
    m_gameTitle.setPosition(windowWidth / 2, (windowHeight / 2) - 250);


    // Play Button
    m_playButton.setFont(m_context->m_assets->GetFont(Font::MAIN_FONT));
    m_playButton.setCharacterSize(70);
    m_playButton.setString("Play");
    m_playButton.setOrigin(m_playButton.getLocalBounds().width / 2, m_playButton.getLocalBounds().height / 2);
    m_playButton.setPosition(windowWidth / 2, (windowHeight / 2) - 50);

    // Exit Button
    m_exitButton.setFont(m_context->m_assets->GetFont(Font::MAIN_FONT));
    m_exitButton.setCharacterSize(60);
    m_exitButton.setString("Exit");
    m_exitButton.setOrigin(m_exitButton.getLocalBounds().width / 2, m_exitButton.getLocalBounds().height / 2);
    m_exitButton.setPosition(windowWidth / 2, (windowHeight / 2) + 70);

    //High Score Text
    m_highScoreText.setFont(m_context->m_assets->GetFont(Font::MAIN_FONT));
    m_highScoreText.setCharacterSize(50);
    m_highScoreText.setFillColor(sf::Color::White);
    m_highScoreText.setString("High Score: " + std::to_string(m_highScore));
    m_highScoreText.setOrigin(m_highScoreText.getLocalBounds().width / 2, m_highScoreText.getLocalBounds().height / 2);
    m_highScoreText.setPosition(windowWidth / 2, (windowHeight / 2) + 200);

    
    // Final Score Text
    m_finalScoreText.setFont(m_context->m_assets->GetFont(Font::MAIN_FONT));
    m_finalScoreText.setCharacterSize(50);
    m_finalScoreText.setFillColor(sf::Color::White);
    m_finalScoreText.setString("Final Score: " + std::to_string(m_finalScore));
    m_finalScoreText.setOrigin(m_finalScoreText.getLocalBounds().width / 2, m_finalScoreText.getLocalBounds().height / 2);
    m_finalScoreText.setPosition(windowWidth / 2, (windowHeight / 2) + 300);



    // Music Button
    m_musicButton.setFont(m_context->m_assets->GetFont(Font::MAIN_FONT));
    m_musicButton.setCharacterSize(60);
    m_musicButton.setString("Music");
    m_musicButton.setOrigin(m_musicButton.getLocalBounds().width / 2, m_musicButton.getLocalBounds().height / 2);
    m_musicButton.setPosition(windowWidth / 2 - 500, (windowHeight / 2));

}

void MainMenu::ProcessInput()
{
    sf::Event event;
    while (m_context->m_window->pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            m_context->m_window->close();
            
            break;

        case sf::Event::MouseButtonPressed:
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                if (m_context->m_mouseInput->m_isSpriteClicked(m_playButton, sf::Mouse::Left, *m_context->m_window))
                {
                    m_isPlayButtonPressed = true;
                }
                else if (m_context->m_mouseInput->m_isSpriteClicked(m_exitButton, sf::Mouse::Left, *m_context->m_window))
                {
                    m_context->m_states->PopAll();

                }
                else if (m_context->m_mouseInput->m_isSpriteClicked(m_musicButton, sf::Mouse::Left, *m_context->m_window))
                {
                    if (m_isAudioPaused)
                    {
                        m_context->m_bgMusic->play(); 
                        m_isAudioPaused = false;
                    }
                    else
                    {
                        m_context->m_bgMusic->pause(); 
                        m_isAudioPaused = true;
                    }
                }
            }
            break;
        }
    }

    // Update button selection
    m_isPlayButtonSelected = m_context->m_mouseInput->m_isSpriteHover(m_playButton, *m_context->m_window);
    m_isExitButtonSelected = m_context->m_mouseInput->m_isSpriteHover(m_exitButton, *m_context->m_window);
    m_isMusicButtonSelected = m_context->m_mouseInput->m_isSpriteHover(m_musicButton, *m_context->m_window);
}


void MainMenu::Update(const sf::Time& deltaTime)
{
    if (m_isPlayButtonPressed)
    {
        m_context->m_states->Add(std::make_unique<GamePlay>(m_context), true);
        m_context->m_states->PopCurrent();
        m_context->m_states->ProcessStateChange();
    }
}

void MainMenu::Draw()
{
    m_context->m_window->clear();

    m_context->m_window->draw(m_bgSprite); 

    m_context->m_window->draw(m_gameTitle);

    if (m_isPlayButtonSelected)
    {
        m_playButton.setFillColor(sf::Color::Yellow);
    }
    else
    {
        m_playButton.setFillColor(sf::Color::White);
    }

    if (m_isExitButtonSelected)
    {
        m_exitButton.setFillColor(sf::Color::Yellow);
    }
    else
    {
        m_exitButton.setFillColor(sf::Color::White);
    }

    if (m_isMusicButtonSelected)
    {
        m_musicButton.setFillColor(sf::Color::Yellow);
    }
    else
    {
        m_musicButton.setFillColor(sf::Color::White);
    }


    m_context->m_window->draw(m_playButton);
    m_context->m_window->draw(m_exitButton);
    m_context->m_window->draw(m_musicButton); 
    m_context->m_window->draw(m_highScoreText); 
    m_context->m_window->draw(m_finalScoreText); 

    m_context->m_window->display();
}

void MainMenu::SaveHighScore() const
{
    std::ofstream file("highscore.txt");
    if (file.is_open())
    {
        file << m_highScore;
        file.close();
    }
    else
    {
        //std::cerr << "Failed to open highscore file for writing." << std::endl;
    }
}

void MainMenu::LoadHighScore()
{
    std::ifstream file("highscore.txt");
    if (file.is_open())
    {
        file >> m_highScore;
        file.close();
    }
    else
    {
        //std::cerr << "Failed to open highscore file for reading." << std::endl;
        m_highScore = 0; //Setting default high score.
    }
}


void MainMenu::UpdateHighScore(int newScore)
{
    if (newScore > m_highScore)
    {
        m_highScore = newScore;
        SaveHighScore();
    }
}


