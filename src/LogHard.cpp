
#include <Settings.hpp>
#include <src/LogHard.hpp>

LogHard::LogHard(float _x, float _y) noexcept
: x{_x}, y{_y},
      top{x, y + Settings::LOG_HEIGHT, true},
      bottom{x, y + Settings::LOGS_GAP + Settings::LOG_HEIGHT, false}
{

}

bool LogHard::collides(const sf::FloatRect& rect) const noexcept
{
    return top.get_collision_rect().intersects(rect) || bottom.get_collision_rect().intersects(rect);
}

void LogHard::update(float dt) noexcept
{
    x += -Settings::MAIN_SCROLL_SPEED * dt;

    top.update(x);
    bottom.update(x);
}

void LogHard::render(sf::RenderTarget& target) const noexcept
{
    top.render(target);
    bottom.render(target);
}

bool LogHard::is_out_of_game() const noexcept
{
    return x < -Settings::LOG_WIDTH;
}

bool LogHard::update_scored(const sf::FloatRect& rect) noexcept
{
    if (scored)
    {
        return false;
    }

    if (rect.left > x + Settings::LOG_WIDTH)
    {
        scored = true;
        return true;
    }

    return false;
}

void LogHard::reset(float _x, float _y) noexcept
{
    x = _x;
    y = _y;
    scored = false;
}