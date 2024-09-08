#include "raylib.h"

struct Boundary{
    int left_x;
    int right_x;
    int upper_y;
    int bottom_y;
};

// Function to get the boundary of a circle
Boundary getCircleBound(int circle_x, int circle_y, int circle_radius){
    return { 
        circle_x - circle_radius, 
        circle_x + circle_radius, 
        circle_y - circle_radius, 
        circle_y + circle_radius 
    };
}

// Function to get the boundary of a rectangle (square in your case)
Boundary getRectangleBound(int rectangle_x, int rectangle_y, int rectangle_length){
    return { 
        rectangle_x, 
        rectangle_x + rectangle_length, 
        rectangle_y, 
        rectangle_y + rectangle_length 
    };
}

// Function to check collision between two boundaries
bool hasCollision(const Boundary &circleBound, const Boundary &rectangleBound){
    return (rectangleBound.left_x <= circleBound.right_x) && 
           (rectangleBound.right_x >= circleBound.left_x) && 
           (rectangleBound.upper_y <= circleBound.bottom_y) && 
           (rectangleBound.bottom_y >= circleBound.upper_y);
}

// Function to move the player to the right
void moveRight(int &x, const int width){
    if (IsKeyDown(KEY_D) && x < width){
        x += 10;
    }
}

// Function to move the player to the left
void moveLeft(int &x, const int width){
    if (IsKeyDown(KEY_A) && x > 0){
        x -= 10;
    }
}

int main(){
    const int width = 800;
    const int height = 450;
    InitWindow(width, height, "Game's window");

    // Circle parameters
    int circle_x = 400;
    int circle_y = 225;
    const int circle_radius = 25;

    // Axe (rectangle) parameters
    int axe_x = 500;
    int axe_y = 0;
    const int axe_length = 50;
    int direction = 10;

    bool collision_with_axe = false;

    SetTargetFPS(30);

    while(!WindowShouldClose()){
        // Update boundaries
        Boundary circleBound = getCircleBound(circle_x, circle_y, circle_radius);
        Boundary rectangleBound = getRectangleBound(axe_x, axe_y, axe_length);

        // Check for collision
        collision_with_axe = hasCollision(circleBound, rectangleBound);

        BeginDrawing();
        ClearBackground(WHITE);

        if (collision_with_axe){
            DrawText("Game over", 400, 200, 60, RED);
        }
        else{
            // Draw circle and rectangle
            DrawCircle(circle_x, circle_y, circle_radius, BLUE);
            DrawRectangle(axe_x, axe_y, axe_length, axe_length, RED);

            // Move axe vertically
            axe_y += direction;

            if (axe_y > height || axe_y < 0){
                direction = -direction;
            }

            // Move circle
            moveRight(circle_x, width);
            moveLeft(circle_x, width);
        }
        EndDrawing();
    }

    CloseWindow();
}
