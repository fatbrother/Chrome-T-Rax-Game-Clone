# Chrome T-Rax Game Clone

## Description

This is a clone of the T-Rax game that is available on Google Chrome when you are offline. The game is built using C++ and the SFML library. The game is a 2D side scroller where the player controls a T-Rex that has to jump over cacti and avoid flying pterodactyls. The game is endless and the player's score is based on how long they can survive.

## How to Play

Player controls are simple. The player can press the spacebar to jump and the down arrow key to duck. The player can also press the up arrow key to jump and the down arrow key

## How to build and run

### Linux

1. Clone the repository
2. Install SFML with vcpgk
3. Run the following commands in the terminal:

```bash
cd path/to/repo
./build.sh
```

4. Run the executable:

```bash
./build/bin/main
```

### Windows

1. Clone the repository
2. Install SFML
3. Check the compiler path in the ```.vscode/tasks.json``` file
4. Run ```ctrl + shift + b``` to build the project
5. Run the executable

## Screenshots

![Screenshot 1](./screenshots/start.png)
![Screenshot 2](./screenshots/run.png)
![Screenshot 3](./screenshots/dead.png)
