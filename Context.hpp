#pragma once
#include <memory>
#include <SFML/Graphics/RenderWindow.hpp>

#include "AssetManager.hpp"
#include "StateManager.hpp"
#include "InputManager.hpp"
#include "Animation.hpp"
#include <SFML/Audio.hpp>
namespace Font
{
    enum FontID
    {
        MAIN_FONT = 0
    };
}

namespace Texture
{
    enum TextureID
    {
        SplashBackground,
        SplashScreenSplash,
        MainMenu,
        Player,
        GameBackground

    };
}

struct Context
{
    std::unique_ptr<sf::Music> m_bgMusic; 
    std::unique_ptr<Engine::AssetManager> m_assets;
    std::unique_ptr<Engine::StateManager> m_states;
    std::unique_ptr<Engine::InputManager> m_mouseInput;
    std::unique_ptr<sf::RenderWindow> m_window;

    Context()
        : m_assets(std::make_unique<Engine::AssetManager>()),
        m_states(std::make_unique<Engine::StateManager>()),
        m_mouseInput(std::make_unique<Engine::InputManager>()), 
        m_bgMusic(std::make_unique<sf::Music>()), 
        m_window(std::make_unique<sf::RenderWindow>(sf::VideoMode(1280, 720), "Dash N Dodge", sf::Style::Resize))
    {
    }
};


