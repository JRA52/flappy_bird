# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.1.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

### Added
added pause function
added new state machine called PauseState by using P on keyboard
se añadio el modo duro
se añadio el estado duro 
se añadio el tronco duro aaahhhh
se añadio el movimiento del pajaro en x
Ahora el pause se puede ir a main menu

### Changed
In game.cpp line 24 added the new State
In PlayingState add the funtion to change PauseState
En Settings se agrego la constante de velocidad del pajaro
En Wolrd.hpp se añadio una funcion que me cambia el modo de juego a dificil 
En World.cpp se cambio el funcionamineto para aplicar el modo dificil 
En Bird.hpp se añadio la variable de velocidad en x del pajaro
En Bird.hpp se añadieron los void moveLeft y void moveRight
En Bird.cpp se implemento la logica del movimiento del pajaro en x
En Title.cpp se añadio el cambio de estado de facil a dificil
En LogHard.hpp se añadieron variables para el del movimiento de los troncos
En LogHard.cpp se implemento la logica del movimiento de los troncos 
En loghard.cpp se añadio el sonido de choque de los troncos 

### FIXED
Se arreglo la pausa para que renderice el mundo correspondiente
se quitaron vainas comentadas


