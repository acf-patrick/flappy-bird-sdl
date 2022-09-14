# Flappy Bird
*Flappy bird* clone written in C++ with SDL2

## Install dependencies
```
sudo apt install libsdl2-dev libsdl2-image-dev libsdl2-mixer-dev
```

## Build and run
```
g++ --std=c++2a -c *.cpp && g++ *.o -lSDL2 -lSDL2_image -lSDL2_mixer -o flappy-bird
./flappy-bird
```