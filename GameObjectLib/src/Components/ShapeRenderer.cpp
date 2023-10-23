#include "Components/ShapeRenderer.h"
#include "SFML/Graphics/Shape.hpp"

ShapeRenderer::ShapeRenderer()
{
	shape = new sf::RectangleShape();
}

ShapeRenderer::~ShapeRenderer()
{
	delete shape;
	shape = nullptr;
}

void ShapeRenderer::Render(sf::RenderWindow* _window)
{
	Component::Render(_window);

	const auto position = GetOwner()->GetPosition();
	shape->setPosition(position.x, position.y);
	shape->setSize(sf::Vector2f(200.f, 200.f));
	shape->setFillColor(color);

	_window->draw(*shape);
}
