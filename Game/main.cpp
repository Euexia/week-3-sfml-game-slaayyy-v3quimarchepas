#include <SFML/Graphics.hpp>

#include "GameObject.h"
#include "Scene.h"

int main()
{
	Scene scene;

	GameObject* player = scene.CreateDummyGameObject("Player", 200.f, sf::Color::Red);

	GameObject* enemy = scene.CreateDummyGameObject("Enemy", 400.f, sf::Color::Blue);

	auto window = new sf::RenderWindow(sf::VideoMode(600, 600), "SFML Engine");

	while (window->isOpen())
	{
		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window->close();
			if (event.type == sf::Event::KeyPressed)
				if (event.key.code == sf::Keyboard::Space)
					player->SetPosition(player->GetPosition() + Maths::Vector2f::Right);
		}

		scene.Update();
		window->clear(sf::Color::Black);
		scene.Render(window);
		window->display();
	}

	return 0;
}
