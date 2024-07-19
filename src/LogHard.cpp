
#include <Settings.hpp>
#include <src/LogHard.hpp>

LogHard::LogHard(float _x, float _y) noexcept
    : x{_x}, y{_y}, topVy{25.0f}, bottomVy{25.0f}, topMovingDown{true}, bottomMovingUp{true},
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
   
    if (topMovingDown)
    {    
        top.setY(top.getY() + topVy * dt);
        if (top.getY() >= bottom.getY()) 
        {
            topMovingDown = false;
            Settings::sounds["crash"].play();
            y1 = top.getY();
        }        
    }
    else
    {        
        top.setY(top.getY() - topVy * dt);
        if (top.getY() <= y1 - Settings::LOGS_GAP/2 - 15)
        {
            topMovingDown = true; 
        }
    }

   
    if (bottomMovingUp)
    {        
        bottom.setY(bottom.getY() - bottomVy * dt);
        if (bottom.getY() <= top.getY()) 
        {
            bottomMovingUp = false;
            y2 = bottom.getY();
        }
    }
    else
    {
        bottom.setY(bottom.getY() + bottomVy * dt);
        if (bottom.getY() >= y2 + Settings::LOGS_GAP/2 + 15) 
        {
            bottomMovingUp = true;
        }
    }

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