/*
    ISPPJ1 2024
    Study Case: Flappy Bird

    Author: Alejandro Mujica
    alejandro.j.mujic4@gmail.com

    This file contains the declaration of the class Log.
*/

#pragma once

#include <SFML/Graphics.hpp>

class Log
{
public:
    Log(float _x, float _y, bool inverted) noexcept;

    sf::FloatRect get_collision_rect() const noexcept;

    void update(float _x) noexcept;

    float getY() const noexcept { return y; }

    void setY(float newY) noexcept { y = newY; }


    void render(sf::RenderTarget& target) const noexcept;

private:
    float x;
    float y;
    bool inverted;
    sf::Sprite sprite;
};