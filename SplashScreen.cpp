#include "SplashScreen.hpp"

bool SplashScreen:: drawBloodSplash() const
{
	return splashTime >= 2.5;
}

SplashScreen::SplashScreen(std::shared_ptr<Context>& context) : m_context(context), splashTime(0.f)
{
	
}

void SplashScreen::Init()
{
	m_context->m_assets->AddTexture(Texture::SplashBackground, "SplashBackground.png");
	m_context->m_assets->AddTexture(Texture::SplashScreenSplash, "BloodSplash.png");
	m_splashBackground.setTexture(m_context->m_assets->GetTexture(Texture::SplashBackground)); 
	m_spriteSplash.setTexture(m_context->m_assets->GetTexture(Texture::SplashScreenSplash)); 

	m_spriteSplash.setScale(0.7f, 0.7f); 
	m_spriteSplash.setOrigin((m_spriteSplash.getLocalBounds().width / 2), (m_spriteSplash.getLocalBounds().height / 2));
	m_spriteSplash.setPosition((float)(m_context->m_window->getSize().x) / 2, ((float)(m_context->m_window->getSize().y) / 2) + 100 );
}

void SplashScreen::ProcessInput()
{
	sf::Event event;
	while (m_context->m_window->pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			m_context->m_window->close();
			break;
		}
	}
}

void SplashScreen::Update(const sf::Time& deltaTime)
{
	splashTime = m_clock.getElapsedTime().asSeconds();

	if (splashTime >= 3)
	{
		m_context->m_states->Add(std::make_unique<MainMenu>(m_context), true);
		m_context->m_states->PopCurrent();
		m_context->m_states->ProcessStateChange(); 
	}
}

void SplashScreen::Draw()
{
	m_context->m_window->clear();
	m_context->m_window->draw(m_splashBackground);
	if (drawBloodSplash())
		m_context->m_window->draw(m_spriteSplash); 
	m_context->m_window->display();
}//SplashScreen.cpp
