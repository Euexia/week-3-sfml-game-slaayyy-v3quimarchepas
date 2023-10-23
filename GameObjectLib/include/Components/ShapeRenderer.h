#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include "Component.h"

class ShapeRenderer : public Component
{
public:
	ShapeRenderer();
	~ShapeRenderer() override;

	void SetColor(const sf::Color& _color) { color = _color; }

	void Render(sf::RenderWindow* _window) override;

private:
	sf::Color color = sf::Color::White;
	sf::RectangleShape* shape = nullptr;
};
