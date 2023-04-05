# Twini-Golf SFML
This is clone of TwiniGolf which is created in SFML.It based on this [repo](https://github.com/PolyMarsDev/Twini-Golf) and [yt](https://www.youtube.com/watch?v=iEn0ozP-jxc&ab_channel=PolyMars)

## Screenshot
![Image](https://user-images.githubusercontent.com/28188300/222953464-29a078e1-2df0-4ec9-b7c7-3bad2d1998c5.gif)

### Installing
A step by step series  that tell you how to get a execute project.

1) Using Qt

Get it from GitHub
```
git clone git@github.com:Przemekkkth/TwiniGolfSFML.git
```
Compile
```
qmake && make
```

2) Using CMake

```
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
```
```
cd build/
```
```
make -j4
```
```
cp -r ../res/ .
```
You can copy res directory using other method ie by GUI. Next, you can play it.

### Control

|     Key       | Action        |
| ------------- | ------------- |
| up arrow, z             | select next, previous  |
| down arrow         | move down  |
| SPACE, ENTER             | activate  |
| Left mouse button           | activate ball  |
| Move mouse            | set angle, power  |
| Right mouse button           | hit ball  |
| Backspace           | back to menu  |

## Addons
* [SFML](https://www.sfml-dev.org/) - page of SFML project
* [Github](https://github.com/PolyMarsDev) - page of author twini golf on github
* [Sound effect](https://www.kenney.nl/) - kenney.nl
* [Font](https://www.dafont.com/craftron-gaming.d6128) - page of author on dafont.com
* [yt](https://youtu.be/yet749PrGvQ) - gameplay
