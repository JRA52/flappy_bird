# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.1.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

### Added
added pause function
added new state machine called PauseState by using P on keyboard
Added Hard Mode
Added Hard State 
The hard log was added 
Added the bird movement in X
Now the pause can be taken to main menu

### Changed
In game.cpp line 24 added the new State
In PlayingState add the funtion to change PauseState
In Settings the bird's speed constant was added
In Wolrd.hpp a function was added that changes the game mode to hard 
In World.cpp the functionality was changed to apply the hard mode 
In Bird.hpp the bird speed variable in x was added
In Bird.hpp the void moveLeft and void moveRight were added
In Bird.cpp the logic of the bird's movement in x was implemented
In Title.cpp the change of status from easy to hard was added
In LogHard.hpp variables were added for the movement of the logs
In LogHard.cpp, the logic of the movement of the logs was implemented 
In loghard.cpp the sound of the logs crashing was added
In Setting.cpp the shock sound operation was added

### FIXED
Fixed the pause for the corresponding world to render
Commented pods were removed
The audio of the collision of the logs was accommodated

