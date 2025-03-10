#include <Settings.hpp>
#include <src/text_utilities.hpp>
#include <src/states/StateMachine.hpp>
#include <src/states/HardState.hpp>

HardState::HardState(StateMachine* sm) noexcept
    : BaseState{sm}
{

}

void HardState::enter(std::shared_ptr<World> _world, std::shared_ptr<Bird> _bird, bool _hardMode) noexcept
{    
    hardMode = true;
    _world->mode(hardMode);
    world = _world;

    if (_bird == nullptr)
    {
        world->reset(true);
        score = 0;
        bird = std::make_shared<Bird>(
            Settings::VIRTUAL_WIDTH / 2 - Settings::BIRD_WIDTH / 2, Settings::VIRTUAL_HEIGHT / 2 - Settings::BIRD_HEIGHT / 2,
            Settings::BIRD_WIDTH, Settings::BIRD_HEIGHT
        );
    }
    else if(_bird == nullptr)
    {
        bird = _bird;
        bird->reset(Settings::VIRTUAL_WIDTH / 2 - Settings::BIRD_WIDTH / 2, Settings::VIRTUAL_HEIGHT / 2 - Settings::BIRD_HEIGHT / 2);
    }
    else
    {
        bird = _bird;
    }
}

void HardState::handle_inputs(const sf::Event& event) noexcept
{
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
    {
        bird->jump();
    }
    
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::A)
    {
        bird->moveLeft();    
    }
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::D)
    {
        bird->moveRight();
    }
    
    if(event.key.code == sf::Keyboard::P)
    {        
        state_machine->change_state("pause", world, bird, hardMode);        
    }
}

void HardState::update(float dt) noexcept
{
    bird->update(dt);
    world->update(dt);

    if (world->collides(bird->get_collision_rect()))
    {
        Settings::sounds["explosion"].play();
        Settings::sounds["hurt"].play();
        
        state_machine->change_state("count_down", world, bird, hardMode);
        
        return;
    }

    if (world->update_scored(bird->get_collision_rect()))
    {
        ++score;
        Settings::sounds["score"].play();
    }
}

void HardState::render(sf::RenderTarget& target) const noexcept
{
    world->render(target);
    bird->render(target);
    render_text(target, 20, 10, "Score: " + std::to_string(score), Settings::FLAPPY_TEXT_SIZE, "flappy", sf::Color::White);
}