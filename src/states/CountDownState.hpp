/*
    ISPPJ1 2024
    Study Case: Flappy Bird

    Author: Alejandro Mujica
    alejandro.j.mujic4@gmail.com

    This file contains the declaration of the class CountDownBaseState.
*/

#pragma once

#include <src/World.hpp>
#include <src/states/BaseState.hpp>

class CountDownState: public BaseState
{
public:
    CountDownState(StateMachine* sm) noexcept;

    void enter(std::shared_ptr<World> _world = nullptr, std::shared_ptr<Bird> _bird = nullptr, bool _hardMode = false) noexcept override;

    void update(float dt) noexcept override;

    void render(sf::RenderTarget& target) const noexcept override;

private:
    std::shared_ptr<World> world;
    std::shared_ptr<Bird> bird;
    bool hardMode;
    int counter{3};
    float timer{0.f};
};
