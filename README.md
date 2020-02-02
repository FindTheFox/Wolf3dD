# Wolf3D
	A Wolfenstein 3D game like. Project for [42 School Paris](https://www.42.fr/) project.

## Built with
	C Language, Racasting method, SDL2 graphic library.

## Features
*	3 game in 1. Lunch with 3rd argument {wolf | asylum | maze} for different texture and setup
*	Raycasting technique : Wall.
*	FloorCasting technique : Floor and Ceilling.
*	Move in any direction {arrow | WASD}
*	Rotation {Mouse | Q E}
*	Weapon {Button Left for Shoot | Button right for Switch gun}
*	Enemy with different sprite depending on the game
*	Shadow and Fog {F}
*	Minimap {M}

## How to use

<strong>Linux</strong></br>
$>apt-get install libsdl2 libsdl2_ttf libsdl2_mixer</br>

<strong>MacOS</strong></br>
$>make SDL2</br>

<strong>after SDL2 installed</strong></br>
$>make</br>
$>./wolf3d map/name.wolf {wolf | asylum | maze}</br>

## Map Block
* 	1 : Wall
* 	2 : Player
* 	3 : Plante
* 	4 : Cage
* 	5 : Table
* 	6 : Spawner
* 	7 : Goal

## Map Exemple
1111111/n</br>
1002001/n</br>
1003001/n</br>
1004001/n</br>
1005001/n</br>
1006001/n</br>
1007001/n</br>
1111111/n</br>