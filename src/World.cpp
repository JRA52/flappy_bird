/*
    ISPPJ1 2024
    Study Case: Flappy Bird

    Author: Alejandro Mujica
    alejandro.j.mujic4@gmail.com

    This file contains the definition of the class World.
*/

#include <Settings.hpp>
#include <src/World.hpp>

World::World(bool _generate_logs) noexcept
    : generate_logs{_generate_logs}, background{Settings::textures["background"]}, ground{Settings::textures["ground"]},
      logs{}, logsHard{}, rng{std::default_random_engine{}()}
{
    ground.setPosition(0, Settings::VIRTUAL_HEIGHT - Settings::GROUND_HEIGHT);
    std::uniform_int_distribution<int> dist(0, 80);
    last_log_y = -Settings::LOG_HEIGHT + dist(rng) + 20;
}

void World::reset(bool _generate_logs) noexcept
{            
    generate_logs = _generate_logs;
    if (hardMode)
    {
        for (auto logHard_pair: logsHard)
        {
            logHard_factory.remove(logHard_pair);
        }
        for (auto log_pair: logs)
        {
            log_factory.remove(log_pair);
        }      
        logs.clear();
        logsHard.clear();
    }
    else
    {
        for (auto log_pair: logs)
        {
            log_factory.remove(log_pair);
        }
        logs.clear();
    }
}

bool World::collides(const sf::FloatRect& rect) const noexcept
{
    if (rect.top + rect.height >= Settings::VIRTUAL_HEIGHT)
    {
        return true;
    }

    if (hardMode)
    {        
        for (auto logHard_pair: logsHard)
        {
            if (logHard_pair->collides(rect))
            {
                return true;
            }
        }
        for (auto log_pair: logs)
        {
            if (log_pair->collides(rect))
            {
                return true;
            }
        }
    }
    else
    {        
        for (auto log_pair: logs)
        {
            if (log_pair->collides(rect))
            {
                return true;
            }
        }
    }
    return false;
}

bool World::update_scored(const sf::FloatRect& rect) noexcept
{
    if (hardMode)
    {
        for (auto logHard_pair: logsHard)
            if (logHard_pair->update_scored(rect))
            {
                return true;
            }
        for (auto log_pair: logs)
        {
            if (log_pair->update_scored(rect))
            {
                return true;
            }
        }
    }
    else
    {
        for (auto log_pair: logs)
        {
            if (log_pair->update_scored(rect))
            {
                return true;
            }
        }
    }
    return false;
}

void World::update(float dt) noexcept
{
    background_x += -Settings::BACK_SCROLL_SPEED * dt;

    if (background_x <= -Settings::BACKGROUND_LOOPING_POINT)
    {
        background_x = 0;
    }

    background.setPosition(background_x, 0);

    ground_x += -Settings::MAIN_SCROLL_SPEED * dt;

    if (ground_x <= -Settings::VIRTUAL_WIDTH)
    {
        ground_x = 0;
    }

    if (hardMode)
    {
        if (generate_logs)
        {
            logs_spawn_timer += dt;

            if (logs_spawn_timer >= Settings::TIME_TO_SPAWN_LOGS)
            {
                std::uniform_real_distribution<float> distTime{-1 , 0};
                logs_spawn_timer = distTime(rng);
                std::uniform_int_distribution<int> distHard{0 , 13};
                std::uniform_int_distribution<int> dist{-20 - static_cast<int> (distHard(rng)) * 2 , 20 + static_cast<int> (distHard(rng)) * 25};
                float y = std::max(-Settings::LOG_HEIGHT + 10, std::min(last_log_y + dist(rng), Settings::VIRTUAL_HEIGHT + 90 - Settings::LOG_HEIGHT));

                last_log_y = y;

                logsHard.push_back(logHard_factory.create(Settings::VIRTUAL_WIDTH, y));
                logs.push_back(log_factory.create(Settings::VIRTUAL_WIDTH, y));
            }
        }

        ground.setPosition(ground_x, Settings::VIRTUAL_HEIGHT - Settings::GROUND_HEIGHT);

        int aux = RandBetween( 1, 2 );
        if(aux%2 == 0)
            for (auto it = logsHard.begin(); it != logsHard.end(); )
            {
                if ((*it)->is_out_of_game())
                {
                    auto logHard_pair = *it;
                    logHard_factory.remove(logHard_pair);
                    it = logsHard.erase(it);
                    
                }
                else
                {
                    (*it)->update(dt);
                    ++it;
                }
            }
            
            for (auto it = logs.begin(); it != logs.end(); )
            {
                if ((*it)->is_out_of_game())
                {
                    auto log_pair = *it;
                    log_factory.remove(log_pair);
                    it = logs.erase(it);
                    
                }
                else
                {
                    (*it)->update(dt);
                    ++it;
                }
            }
    }
    else
    {
        if (generate_logs)
        {
            logs_spawn_timer += dt;

            if (logs_spawn_timer >= Settings::TIME_TO_SPAWN_LOGS)
            {
                logs_spawn_timer = 0.f;

                std::uniform_int_distribution<int> dist{-20, 20};
                float y = std::max(-Settings::LOG_HEIGHT + 10, std::min(last_log_y + dist(rng), Settings::VIRTUAL_HEIGHT + 90 - Settings::LOG_HEIGHT));

                last_log_y = y;

                logs.push_back(log_factory.create(Settings::VIRTUAL_WIDTH, y));
            }
        }

        ground.setPosition(ground_x, Settings::VIRTUAL_HEIGHT - Settings::GROUND_HEIGHT);

        for (auto it = logs.begin(); it != logs.end(); )
        {
            if ((*it)->is_out_of_game())
            {
                auto log_pair = *it;
                log_factory.remove(log_pair);
                it = logs.erase(it);
                
            }
            else
            {
                (*it)->update(dt);
                ++it;
            }
        }
    }
}

void World::render(sf::RenderTarget& target) const noexcept
{
    target.draw(background);
    
    if (hardMode)
    {
        for (const auto& log_pair: logs)
        {
            log_pair->render(target);
        }
        for (const auto& logHard_pair: logsHard)
        {
            logHard_pair->render(target);
        }
    }
    else
    {
        for (const auto& log_pair: logs)
        {
            log_pair->render(target);
        }
    }

    target.draw(ground);    
}

void World::mode(bool mode)
{
    hardMode = mode;
}