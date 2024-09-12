#include "Game.hpp"
#include "MainMenu.hpp"

Game::Game() : m_context(std::make_shared<Context>())
{
    m_context->m_window->create(sf::VideoMode(1280, 720), "Dash N Dodge", sf::Style::Resize);
    //m_context->m_states->Add(std::make_unique<MainMenu>(m_context));
    m_context->m_states->Add(std::make_unique<SplashScreen>(m_context));
}

Game::~Game() 
{
}

void Game::Run()
{


    if (!m_context->m_bgMusic->openFromFile("GameBGAudio.wav"))
    {

    }
    m_context->m_bgMusic->setLoop(true);
    m_context->m_bgMusic->play();

    sf::Clock clock;
    sf::Time timeSinceLastFrame = sf::Time::Zero;

    while (m_context->m_window->isOpen())
    {
        timeSinceLastFrame += clock.restart();

        while (timeSinceLastFrame > TIME_PER_FRAME)
        {
            timeSinceLastFrame -= TIME_PER_FRAME;

            m_context->m_states->ProcessStateChange();

            if (!m_context->m_states->IsEmpty())
            {
                m_context->m_states->GetCurrent()->ProcessInput();
                m_context->m_states->GetCurrent()->Update(TIME_PER_FRAME);
                m_context->m_states->GetCurrent()->Draw();
            }
            else
            {
                m_context->m_window->close();
            }
        }
    }
} //Game.cpp