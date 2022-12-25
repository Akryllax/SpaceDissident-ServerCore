# SpaceDissident_ServerCore

This is intended to be a game server at some point in the future. For now, I am laying the foundation :)

## Build

`mkdir build && cd build && cmake .. && make`

## Recommended build commands

`cmake -DCMAKE_CXX_COMPILER_LAUNCHER=ccache .. -GNinja && ninja -j 8`

## Tests
There are some GTests to help with the funcionality :D