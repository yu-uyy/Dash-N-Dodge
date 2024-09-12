#pragma once
#include "Context.hpp"
#include "StateManager.hpp"
#include "MainMenu.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Window/Event.hpp"
class SplashScreen : public Engine::State
{
private:
	std::shared_ptr<Context> m_context; 
	
	sf::Sprite m_splashBackground; 
	sf::Sprite m_spriteSplash; 

	float splashTime; 
	sf::Clock m_clock;
	bool drawBloodSplash() const; 

public:
	SplashScreen(std::shared_ptr<Context>& context); 
	~SplashScreen() { }


	void Init() override;
	void ProcessInput() override;
	void Update(const sf::Time& deltaTime) override;
	void Draw() override;

};//SplashScreen.hpp

