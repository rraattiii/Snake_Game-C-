# Snake Game (SFML / C++)

A classic **Snake game** built in **C++ using SFML**, featuring obstacles, bonus food, increasing difficulty, and a persistent high score system.

##  Features

- Classic snake movement and growth
- Food and **bonus food** (limited-time, higher score)
- Randomly generated **obstacles**
- Increasing speed as the snake grows
- Score and **high score saved to file**
- Simple HUD and game-over screen

##  Controls

| Key | Action |
|----|--------|
| **W** | Move Up |
| **A** | Move Left |
| **S** | Move Down |
| **D** | Move Right |
| Close Window | Exit Game |

##  Gameplay Rules

- Eat **red food** to grow and gain **+10 points**
- Occasionally, **bonus food** appears:
  - Blinks
  - Disappears after a few seconds
  - Gives **+30 points**
- Hitting:
  - Walls  
  - Your own body  
  - Obstacles  
  ends the game
- Game speed increases gradually

##  High Score

- High score is stored in a file called `highscore.txt`
- Automatically loads on startup and saves on exit

##  Requirements

- **C++17 or newer**
- **SFML 2.5+**
- A font file:
  - `arial.ttf` must be in the executable directory

## 🔧 Build Instructions

### Linux / macOS
```bash
g++ main.cpp -o snake -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
./snake
