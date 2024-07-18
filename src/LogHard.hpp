#pragma once

#include <src/Bird.hpp>
#include <src/Log.hpp>

class LogHard
{
public:
    LogHard(float _x, float _y) noexcept;

    bool collides(const sf::FloatRect& rect) const noexcept;

    void update(float dt) noexcept;

    void render(sf::RenderTarget& target) const noexcept;

    bool is_out_of_game() const noexcept;

    bool update_scored(const sf::FloatRect& rect) noexcept;

    void reset(float _x, float _y) noexcept;

private:
    float x;
    float y;
    Log top;
    Log bottom;

    float logHard;

    bool scored{false};
};