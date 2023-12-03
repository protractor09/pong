# pragma once
#include <SFML/Graphics.hpp>
#include "main.hpp"






class paddle{

sf::RectangleShape paddle_shape;

float speed=200;

sf::Vector2f paddle_Position;

public:

paddle(float paddlex, float paddley);

sf::RectangleShape get_paddle_shape();
sf::FloatRect get_paddle_position();

void updatepaddle1(sf::Time dt);

void updatepaddle2(sf::Time dt);

bool handlecollision();



};