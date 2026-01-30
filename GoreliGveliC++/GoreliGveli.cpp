#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <fstream>

using namespace sf;
using namespace std;

const int width = 40;
const int height = 30;
const int size = 20;

enum Dir { STOP, LEFT, RIGHT, UP, DOWN };

struct SnakePart {
    int x, y;
};

int main() {
    srand(time(0));

    RenderWindow window(VideoMode(width * size, height * size + 60), "Snake");
    window.setFramerateLimit(60);

    RectangleShape tile(Vector2f(size - 1, size - 1));
    RectangleShape food(Vector2f(size - 1, size - 1));
    RectangleShape bonus(Vector2f(size - 1, size - 1));

    Font font;
    font.loadFromFile("arial.ttf");

    Text hud;
    hud.setFont(font);
    hud.setCharacterSize(20);
    hud.setFillColor(Color::White);
    hud.setPosition(10, height * size + 10);

    vector<SnakePart> snake;
    snake.push_back({ width / 2, height / 2 });

    vector<Vector2i> obstacles;
    for (int i = 0; i < 8; i++)
        obstacles.push_back({ rand() % width, rand() % height });

    Vector2i foodPos(rand() % width, rand() % height);
    Vector2i bonusPos;
    bool bonusActive = false;
    float bonusTimer = 0;

    Dir dir = STOP;
    bool gameOver = false;
    int score = 0;
    float delay = 0.12f;
    float timer = 0;

    int highScore = 0;
    ifstream in("highscore.txt");
    if (in) in >> highScore;
    in.close();

    Clock clock;

    while (window.isOpen()) {
        float time = clock.restart().asSeconds();
        timer += time;

        Event e;
        while (window.pollEvent(e)) {
            if (e.type == Event::Closed)
                window.close();
        }

        if (Keyboard::isKeyPressed(Keyboard::A) && dir != RIGHT) dir = LEFT;
        if (Keyboard::isKeyPressed(Keyboard::D) && dir != LEFT) dir = RIGHT;
        if (Keyboard::isKeyPressed(Keyboard::W) && dir != DOWN) dir = UP;
        if (Keyboard::isKeyPressed(Keyboard::S) && dir != UP) dir = DOWN;

        if (timer > delay && !gameOver) {
            timer = 0;

            for (int i = snake.size() - 1; i > 0; i--)
                snake[i] = snake[i - 1];

            if (dir == LEFT) snake[0].x--;
            if (dir == RIGHT) snake[0].x++;
            if (dir == UP) snake[0].y--;
            if (dir == DOWN) snake[0].y++;

            if (snake[0].x < 0 || snake[0].x >= width || snake[0].y < 0 || snake[0].y >= height)
                gameOver = true;

            for (int i = 1; i < snake.size(); i++)
                if (snake[i].x == snake[0].x && snake[i].y == snake[0].y)
                    gameOver = true;

            for (auto& o : obstacles)
                if (o.x == snake[0].x && o.y == snake[0].y)
                    gameOver = true;

            if (snake[0].x == foodPos.x && snake[0].y == foodPos.y) {
                score += 10;
                snake.push_back(snake.back());
                foodPos = { rand() % width, rand() % height };
                if (delay > 0.05f) delay -= 0.005f;
                if (rand() % 4 == 0) {
                    bonusActive = true;
                    bonusTimer = 4.f;
                    bonusPos = { rand() % width, rand() % height };
                }
            }

            if (bonusActive) {
                bonusTimer -= delay;
                if (bonusTimer <= 0) bonusActive = false;
                if (snake[0].x == bonusPos.x && snake[0].y == bonusPos.y) {
                    score += 30;
                    bonusActive = false;
                }
            }
        }

        window.clear(Color(20, 20, 20));

        tile.setFillColor(Color(0, 150, 0));
        for (int i = 1; i < snake.size(); i++) {
            tile.setPosition(snake[i].x * size, snake[i].y * size);
            window.draw(tile);
        }

        tile.setFillColor(Color::Green);
        tile.setPosition(snake[0].x * size, snake[0].y * size);
        window.draw(tile);

        tile.setFillColor(Color(80, 80, 255));
        for (auto& o : obstacles) {
            tile.setPosition(o.x * size, o.y * size);
            window.draw(tile);
        }

        food.setFillColor(Color::Red);
        food.setPosition(foodPos.x * size, foodPos.y * size);
        window.draw(food);

        if (bonusActive) {
            bonus.setFillColor((int)(bonusTimer * 10) % 2 ? Color::Yellow : Color(255, 140, 0));
            bonus.setPosition(bonusPos.x * size, bonusPos.y * size);
            window.draw(bonus);
        }

        if (score > highScore) highScore = score;
        hud.setString("Score: " + to_string(score) + "   High: " + to_string(highScore));
        window.draw(hud);

        if (gameOver) {
            Text over("GAME OVER", font, 40);
            over.setFillColor(Color::Red);
            over.setPosition(120, 200);
            window.draw(over);
        }

        window.display();
    }

    ofstream out("highscore.txt");
    out << highScore;
    out.close();

    return 0;
}

