# Snake Game

Install at least one of the libraries:  
  * NCurses  
  * SDL2  
  * freeglut  

Or compile without libs for linux.

```
sudo apt install libncurses5-dev libsdl2-dev freeglut3-dev
```

Compile:

```
mkdir build
cd build
cmake ..
make
```

Run:

```
cd src

./snake-ncurses
or
./snake-sdl
or
./snake-glut
or 
./snake-nolib-lnx
```

## Screenshots

![](screenshots/snake-ncurses.png)
![](screenshots/snake-sdl.png)
