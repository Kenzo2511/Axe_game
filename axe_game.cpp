#include "raylib.h"
#include <string>
#include <iostream>
using namespace std;

struct Boundary {
    int left_x;
    int right_x;
    int upper_y;
    int bottom_y;
};

// Returns the boundary of a circle
Boundary getCircleBoundary(int x, int y, int radius) {
    return { 
        x - radius, 
        x + radius, 
        y - radius, 
        y + radius 
    };
}

// Returns the boundary of a square
Boundary getSquareBoundary(int x, int y, int length) {
    return { 
        x, 
        x + length, 
        y, 
        y + length 
    };
}

// Checks if two boundaries overlap (collision)
bool checkCollision(const Boundary &circle, const Boundary &square) {
    return (square.left_x <= circle.right_x) && 
           (square.right_x >= circle.left_x) && 
           (square.upper_y <= circle.bottom_y) && 
           (square.bottom_y >= circle.upper_y);
}

// Moves the player to the right within the screen width
void moveRight(int &x, const int screenWidth) {
    if (IsKeyDown(KEY_D) && x < screenWidth) {
        x += 10;
    }
}

// Moves the player to the left within the screen width
void moveLeft(int &x, const int screenWidth) {
    if (IsKeyDown(KEY_A) && x > 0) {
        x -= 10;
    }
}

int main() {
    const int screenWidth = 800;
    const int screenHeight = 450;
    InitWindow(screenWidth, screenHeight, "Game's Window");

    // Circle parameters
    int playerX = screenWidth / 2;
    int playerY = screenHeight / 2;
    const int playerRadius = 25;

    // Axe (square) parameters
    int axeX = 500;
    int axeY = 0;
    const int axeSize = 50;
    int axeDirection = 10;

    bool gameOver = false;
    int score = 0;
    int frameCounter = 0;

    SetTargetFPS(30);

    while (!WindowShouldClose()) {
        frameCounter++;

        if (frameCounter % 50 == 0) {
            score++;
        }

        // Update boundaries
        Boundary playerBoundary = getCircleBoundary(playerX, playerY, playerRadius);
        Boundary axeBoundary = getSquareBoundary(axeX, axeY, axeSize);

        // Check for collision
        gameOver = checkCollision(playerBoundary, axeBoundary);

        BeginDrawing();
        ClearBackground(WHITE);

        if (gameOver) {
            DrawText("Game Over", screenWidth / 2 - 100, screenHeight / 2 - 30, 60, RED);
        } else {
            // Display score
            DrawText(to_string(score).c_str(), 20, 20, 60, RED);

            // Draw player (circle) and axe (square)
            DrawCircle(playerX, playerY, playerRadius, BLUE);
            DrawRectangle(axeX, axeY, axeSize, axeSize, RED);

            // Move the axe vertically
            axeY += axeDirection;
            if (axeY > screenHeight || axeY < 0) {
                axeDirection = -axeDirection;
            }

            // Move the player
            moveRight(playerX, screenWidth);
            moveLeft(playerX, screenWidth);
        }
        EndDrawing();
    }

    CloseWindow();
}
