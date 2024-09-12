#include "GamePlay.hpp"

GamePlay::GamePlay(std::shared_ptr<Context>& context)
    : m_context(context), m_score(0), m_elapsedTime(0.f), m_spacePressed(false), m_mouseLeftPressed(false)
{
    m_jumpBuffer.loadFromFile("JumpSE.wav");
    m_jumpSound.setBuffer(m_jumpBuffer);
}


void GamePlay::Init()
{
    m_context->m_assets->AddTexture(Texture::GameBackground, "BackGround.png");
    m_backSprite.setTexture(m_context->m_assets->GetTexture(Texture::GameBackground));

    m_player.Init();
    m_obstacleManager.Init();

    float windowWidth = static_cast<float>(m_context->m_window->getSize().x);
    float windowHeight = static_cast<float>(m_context->m_window->getSize().y);

    m_context->m_assets->AddFont(Font::MAIN_FONT, "AntonSC-Regular.ttf");
    m_scoreText.setFont(m_context->m_assets->GetFont(Font::MAIN_FONT));
    m_scoreText.setCharacterSize(80);
    m_scoreText.setFillColor(sf::Color::White);
    m_scoreText.setString("Score: 0");
    m_scoreText.setOrigin(m_scoreText.getLocalBounds().width / 2, m_scoreText.getLocalBounds().height / 2);
    m_scoreText.setPosition(windowWidth / 2.0f, windowHeight / 2.0f - 270);
}


void GamePlay::ProcessInput()
{
    sf::Event event;
    while (m_context->m_window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            m_context->m_window->close();
        }
        else if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Space)
            {
                if (!m_spacePressed) 
                {
                    m_jumpSound.play();
                    m_player.Jump();
                    m_spacePressed = true; 
                }
            }
            else if (event.key.code == sf::Keyboard::A)
            {
                m_player.MoveLeft();
            }
            else if (event.key.code == sf::Keyboard::D)
            {
                m_player.MoveRight();
            }
            else if (event.key.code == sf::Keyboard::Escape)
            {
                m_context->m_states->Add(std::make_unique<PauseGame>(m_context, m_score));
            }
        }
        else if (event.type == sf::Event::KeyReleased)
        {
            if (event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::D)
            {
                m_player.StopMoving();
            }
            else if (event.key.code == sf::Keyboard::Space)
            {
                m_spacePressed = false;
            }
        }
        else if (event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                if (!m_mouseLeftPressed) 
                {
                    m_jumpSound.play();
                    m_player.Jump();
                    m_mouseLeftPressed = true; 
                }
            }
        }
        else if (event.type == sf::Event::MouseButtonReleased)
        {
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                m_mouseLeftPressed = false; // Reset mouse left button pressed flag
            }
        }
    }
}



void GamePlay::Update(const sf::Time& deltaTime)
{
    m_player.Update(deltaTime, m_obstacleManager.GetFloor());
    m_obstacleManager.Update(deltaTime);

    m_elapsedTime += deltaTime.asSeconds();
    if (m_elapsedTime >= 1.f)
    {
        m_score++;
        m_scoreText.setString("Score: " + std::to_string(m_score));
        m_elapsedTime = 0.f;
    }
    m_obstacleManager.getScore(m_score); 
    m_obstacleManager.IncreaseSpeed(m_score);

    if (m_obstacleManager.CheckCollision(m_player.GetBody()))
    {
        m_context->m_states->Add(std::make_unique<MainMenu>(m_context, m_score), true);
    }
}

void GamePlay::Draw()
{
    m_context->m_window->clear();
    m_context->m_window->draw(m_backSprite);
    m_player.Draw(*m_context->m_window);
    m_obstacleManager.Draw(*m_context->m_window);
    m_context->m_window->draw(m_scoreText);

    m_context->m_window->display();
}
