
#pragma once

#include <src/Bird.hpp>
#include <src/World.hpp>
#include <src/states/BaseState.hpp>

class PauseState: public BaseState
{
public:
    PauseState(StateMachine* sm) noexcept;

    void enter(std::shared_ptr<World> _world , std::shared_ptr<Bird> _bird, bool _hardMode) noexcept  override;

    void handle_inputs(const sf::Event& event) noexcept override;

    void render(sf::RenderTarget& target) const noexcept override;

private:
    std::shared_ptr<World> world;
    std::shared_ptr<Bird> bird;
    int score {0};
    bool hardMode;
    bool paused;
};