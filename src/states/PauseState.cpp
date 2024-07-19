#include <Settings.hpp>
#include <src/text_utilities.hpp>
#include <src/states/StateMachine.hpp>
#include <src/states/PauseState.hpp>

PauseState::PauseState(StateMachine* sm) noexcept
    : BaseState{sm}
{
}

void PauseState::enter(std::shared_ptr<World> _world, std::shared_ptr<Bird> _bird, bool _hardMode) noexcept
{
    hardMode = _hardMode;
    world = _world;
    bird = _bird;
    paused = true;
}
 
void PauseState::handle_inputs(const sf::Event& event) noexcept
{    
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P)
    {
        paused = true;
        if(paused)
        {
            if (hardMode)
            {
                state_machine->change_state("hard", world, bird, hardMode);
            }
            else 
            {
                state_machine->change_state("playing", world, bird, hardMode);
            }
        }
        paused = false;
    }
    if(paused && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::M)
    {            
        state_machine->change_state("title", world, bird, hardMode);
        paused = false;
    }
}

void PauseState::render(sf::RenderTarget& target) const noexcept
{    
    world->render(target);
    bird->render(target);
    render_text(target, Settings::VIRTUAL_WIDTH / 2, Settings::VIRTUAL_HEIGHT / 3, "Game Paused", Settings::FLAPPY_TEXT_SIZE, "flappy", sf::Color::White, true);
    render_text(target, Settings::VIRTUAL_WIDTH / 2,  Settings::VIRTUAL_HEIGHT / 2, "Press P to continue playing", Settings::MEDIUM_TEXT_SIZE, "font", sf::Color::White, true);
    render_text(target, Settings::VIRTUAL_WIDTH / 2, 2 * Settings::VIRTUAL_HEIGHT / 3, "Press M to return main menu", Settings::MEDIUM_TEXT_SIZE, "font", sf::Color::White, true);
}