#pragma once
#include <SFML/Graphics/RenderWindow.hpp>

#include "GameObject.h"

class Scene
{
public:
	Scene() = default;
	virtual ~Scene() = default;

	void Update();
	void Render(sf::RenderWindow* _window);

	GameObject* CreateGameObject(const std::string& _name);

	GameObject* CreateDummyGameObject(const std::string& name, float position, const sf::Color color);

private:
	std::vector<GameObject*> gameObjects;
};
