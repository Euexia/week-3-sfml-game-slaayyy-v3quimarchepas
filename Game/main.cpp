#include <SFML/Graphics.hpp>

#include "GameObject.h"
#include "Scene.h"
#include "Menu.h"
#include <iostream>
#include <windows.h>
#include "SettingsMenu.h"
#include "Map.h"
#include <fstream>

class Player {
private:
    sf::Texture playerTexture;
    sf::Sprite playerSprite;
    sf::Vector2f velocity;
    const float speed = 0.2f; // Vitesse de déplacement

public:
    Player() {
        if (!playerTexture.loadFromFile("assets/player/img-player.png")) {
            std::cerr << "Erreur lors du chargement de l'image du joueur!" << std::endl;
        }
        playerSprite.setTexture(playerTexture);
        playerSprite.setPosition(sf::Vector2f(100, 100)); // position de départ
    }

    void handleInput() {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            playerSprite.move(-speed, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            playerSprite.move(speed, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            playerSprite.move(0, -speed);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            playerSprite.move(0, speed);
        }
    }

    void update() {

        // Gestion des collisions avec les bords de la fenêtre
        // Haut
        if (playerSprite.getPosition().y < 0) {
            playerSprite.setPosition(playerSprite.getPosition().x, 0);
        }
        // Bas
        if (playerSprite.getPosition().y + playerSprite.getGlobalBounds().height > WINDOW_HEIGHT) {
            playerSprite.setPosition(playerSprite.getPosition().x, WINDOW_HEIGHT - playerSprite.getGlobalBounds().height);
        }
        // Gauche
        if (playerSprite.getPosition().x < 0) {
            playerSprite.setPosition(0, playerSprite.getPosition().y);
        }
        // Droite
        if (playerSprite.getPosition().x + playerSprite.getGlobalBounds().width > WINDOW_WIDTH) {
            playerSprite.setPosition(WINDOW_WIDTH - playerSprite.getGlobalBounds().width, playerSprite.getPosition().y);
        }
    }

    void draw(sf::RenderWindow& window) {
        window.draw(playerSprite);
    }
};



class Game {
private:
    sf::RenderWindow window;
    Player player;
    Map map;
    Menu mainMenu;  // Instanciez votre menu ici
    SettingsMenu settingsMenu; // Instanciez votre menu SettingsMenu

public:
    Game() : window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "J'ai besoin d'un café help") {}

    void run() {
        int menuChoice = mainMenu.run(window);

        switch (menuChoice) {
        case 0:  // Play
            gameLoop();
            break;

        case 1:  // Settings
            settingsMenu.run(window); // Affichez le menu Settings
            run(); // Revenez au menu principal après avoir quitté le menu Settings
            break;

        case 2:  // Quit
            window.close();
            return;

        default:
            // Gérer les erreurs inattendues
            break;
        }
    }

    void gameLoop() {
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
        map.draw(window);
        player.draw(window);
        window.display();
    }
};


int main() {
    Game game;
    game.run();


    
    return 0;
}