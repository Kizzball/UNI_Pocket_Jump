#include "raylib.h"
#include "stdlib.h"
#include "stdio.h"
typedef struct {
        Rectangle rect;
        Vector2 velocity;
    Player;
}
int main(void) {     
    const int screenWidth = 960; //Screen Width
    const int screenHeight = 600; //s

    InitWindow(screenWidth, screenHeight, "pocket dodge");
    
     
    SetTargetFPS(60);// the frame rate
    
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        // Draw
        
        BeginDrawing();
            ClearBackground(RAYWHITE);
            if (gameover){
                DrawGameOver();// maikng the the game over screen
            }
            DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
        EndDrawing();
        
    }

    // De-Initialization
    
    CloseWindow();        // Close window and OpenGL context
    

    return 0;