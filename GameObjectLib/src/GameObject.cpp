#include "GameObject.h"
#include <SFML/Graphics.hpp>
#include <iostream>

void GameObject::AddComponent(Component* _component)
{
	_component->SetOwner(this);
	components.push_back(_component);
}

void GameObject::RemoveComponent(Component* _component)
{
	components.erase(std::remove(components.begin(), components.end(), _component), components.end());
}

void GameObject::Update() const
{
	for (Component* const& component : components)
	{
		component->Update();
	}
}

void GameObject::Render(sf::RenderWindow* _window) const
{
	for (Component* const& component : components)
	{
		component->Render(_window);
	}
}



class Player {
private:
    static sf::Texture playerTexture; // Déclaration de la version static de texture
    sf::Sprite playerSprite;

public:
    Player() {
        // Chargez l'image du joueur ici
        if (!playerTexture.loadFromFile("assets/player/player-pic.jpg")) {
            std::cerr << "Erreur lors du chargement de l'image du joueur!" << std::endl;
        }
        playerSprite.setTexture(playerTexture);
        playerSprite.setPosition(sf::Vector2f(100, 100)); // position de départ
    }

    void handleInput() {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            playerSprite.move(-5, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            playerSprite.move(5, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            playerSprite.move(0, -5);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            playerSprite.move(0, 5);
        }
    }

    void update() {
        // Gestion des collisions
    }

    void draw(sf::RenderWindow& window) {
        window.draw(playerSprite);
    }
};
sf::Texture Player::playerTexture; // Initialisation de la texture static

class Game {
private:
    sf::RenderWindow window;
    Player player;

public:
    Game() : window(sf::VideoMode(800, 600), "Portail Dimensionnel") {}

    void run() {
        while (window.isOpen()) {
            handleEvents();
            update();
            render();
        }
    }

    void handleEvents() {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        player.handleInput();
    }

    void update() {
        player.update();
    }

    void render() {
        window.clear();
        player.draw(window);
        window.display();
    }
};