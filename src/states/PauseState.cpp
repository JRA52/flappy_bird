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
}
 
void PauseState::handle_inputs(const sf::Event& event) noexcept
{
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P)
    {
        if (hardMode == false)
        {
            state_machine->change_state("playing", world, bird, hardMode);
        }
        else 
        {
            state_machine->change_state("hard", world, bird, hardMode);
        }
        
    }
}

void PauseState::render(sf::RenderTarget& target) const noexcept
{
    
    render_text(target, Settings::VIRTUAL_WIDTH / 2, Settings::VIRTUAL_HEIGHT / 2, "Game Paused", Settings::FLAPPY_TEXT_SIZE, "flappy", sf::Color::White);
}