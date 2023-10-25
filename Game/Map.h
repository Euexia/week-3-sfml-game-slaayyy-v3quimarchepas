#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <nlohmann/json.hpp>
#include <fstream>



class Map {
private:
    sf::Texture tileset;
    const int TILE_SIZE = 32; // suppose que chaque tuile a une taille de 32x32
    int tiles[20][15]{}; // tableau 2D représentant la carte, ajustez la taille selon vos besoins

public:
    Map(){};
    Map(const std::string& jsonFilePath) {
        // Chargement du tileset
        if (!tileset.loadFromFile("assets/tiles/Grass.png")) {
            std::cerr << "Erreur lors du chargement du tileset!" << std::endl;
        }

        // Chargez le fichier JSON
        std::ifstream jsonFile("assets/tiles/map.json");
        if (!jsonFile.is_open()) {
            std::cerr << "Erreur lors de l'ouverture du fichier JSON" << std::endl;
            return;
        }

        nlohmann::json root;
        jsonFile >> root;

        // Vérifiez que le fichier JSON a le bon format et extrayez les données pour initialiser votre carte.
        for (int i = 0; i < 20; ++i) {
            for (int j = 0; j < 15; ++j) {
                // Exemple : supposons que le fichier JSON contienne un tableau "mapData" d'entiers.
                int tileValue = root["mapData"][i][j].get<int>();
                tiles[i][j] = tileValue;

            }
        }
    

        // Initialisation de la matrice de la carte
        // (Ici, je remplis la carte avec des 0, mais vous pouvez la remplir avec les indices de vos tuiles)
        for (int i = 0; i < 20; ++i) {
            for (int j = 0; j < 15; ++j) {
                tiles[i][j] = 0;
            }
        }
    }

    void draw(sf::RenderWindow& window) {
        for (int i = 0; i < 20; ++i) {
            for (int j = 0; j < 15; ++j) {
                sf::Sprite tileSprite(tileset);
                tileSprite.setTextureRect(sf::IntRect(tiles[i][j] * TILE_SIZE, 0, TILE_SIZE, TILE_SIZE));
                tileSprite.setPosition(i * TILE_SIZE, j * TILE_SIZE);
                window.draw(tileSprite);
            }
        }
    }

    // Ajoutez d'autres méthodes comme la gestion des collisions si nécessaire
};

