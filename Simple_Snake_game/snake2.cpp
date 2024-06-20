#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <thread>
#include <conio.h>

using namespace std;

const int width = 20;
const int height = 20;

enum class eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };

struct SnakeSegment {
  int x;
  int y;
};

bool gameOver;
eDirection dir;
vector<SnakeSegment> snake;
int fruitX, fruitY;
int score;

void Setup() {
  gameOver = false;
  dir = eDirection::STOP;
  snake.clear();

  // Place the snake in the center
  snake.push_back({width / 2, height / 2});
  snake.push_back({width / 2 - 1, height / 2});

  // Generate a random fruit position
  fruitX = rand() % width;
  fruitY = rand() % height;

  score = 0;
}

void Draw() {
  system("cls"); // Clear the screen (Windows specific)

  // Draw the top border
  for (int i = 0; i < width + 2; ++i) {
    cout << "#";
  }
  cout << endl;

  // Draw the game board
  for (int i = 0; i < height; ++i) {
    for (int j = 0; j < width; ++j) {
      bool isSnake = false;
      for (const SnakeSegment& segment : snake) {
        if (segment.x == j && segment.y == i) {
          cout << "o";
          isSnake = true;
          break;
        }
      }
      if (!isSnake) {
        if (j == fruitX && i == fruitY) {
          cout << "F";
        } else {
          cout << " ";
        }
      }
    }
    cout << endl;
  }

  // Draw the bottom border
  for (int i = 0; i < width + 2; ++i) {
    cout << "*";
  }
  cout << endl;

  // Display score
  cout << "Score: " << score << endl;
}

void Input() {
  if (_kbhit()) {
    char key = _getch();
    switch (key) {
      case 'a':
        if (dir != eDirection::RIGHT) {
          dir = eDirection::LEFT;
        }
        break;
      case 'd':
        if (dir != eDirection::LEFT) {
          dir = eDirection::RIGHT;
        }
        break;
      case 'w':
        if (dir != eDirection::DOWN) {
          dir = eDirection::UP;
        }
        break;
      case 's':
        if (dir != eDirection::UP) {
          dir = eDirection::DOWN;
        }
        break;
      case 'x':
        gameOver = true;
        break;
    }
  }
}

void Logic() {
  SnakeSegment newHead;
  newHead.x = snake.front().x;
  newHead.y = snake.front().y;

  // Update head position based on direction
  switch (dir) {
    case eDirection::LEFT:
      newHead.x--;
      break;
    case eDirection::RIGHT:
      newHead.x++;
      break;
    case eDirection::UP:
      newHead.y--;
      break;
    case eDirection::DOWN:
      newHead.y++;
      break;
  }

  // Check for collisions with walls
  gameOver = newHead.x < 0 || newHead.x >= width || newHead.y < 0 || newHead.y >= height;

  // Check for collisions with tail
  for (int i = 1; i < snake.size(); ++i) {
    if (snake[i].x == newHead.x && snake[i].y == newHead.y) {
      gameOver = true;
      break;
    }
  }

  // Check for eating the fruit
  if (newHead.x == fruitX && newHead.y == fruitY) {
    score += 10;
    fruitX = rand() % width;
    fruitY = rand() % height;
  }
}
int main()
{
    Setup();
    while (!gameOver)
    {
        Draw();
        Input();
        Logic();
        _sleep(30);
    }
    return 0;
}