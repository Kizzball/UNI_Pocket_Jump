#include "raylib.h"
#include "stdlib.h"
#include "stdio.h"

#define SCREEN_WIDTH 960
#define SCREEN_HEIGHT 600
#define PLATFORM_WIDTH 700
#define PLATFORM_HEIGHT 100
#define PLAYER_WIDTH 30 
#define PLAYER_HEIGHT 50
#define GRAVITY 300
#define JUMP_FORCE -400
#define MAX_PLATFORM 10


typedef struct {
    Rectangle rect;
        bool active;
    } Platform;
typedef struct{
    Rectangle rect;
    Vector2 velocity;
    } Player;
Platform platforms[MAX_PLATFORM];
Player player;
float score = 0;
int highestPlatformY = SCREEN_HEIGHT;
bool gameOver = false

void initGame();
void UpdateGame(float dt);
void DrawGame();
void DrawGameOver();
void ResetPlatform(Platforms* platform);

int main(void) {     
    const int screenWidth = 960; //Screen Width
    const int screenHeight = 600; //s

    InitWindow(screenWidth, screenHeight, "pocket jump");
    
     
    SetTargetFPS(60);// the frame rate
    
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        float dt = GetFrameTime();
        // Update
        UpdateGame(dt);
        // Draw
        
        BeginDrawing();
            ClearBackground(RAYWHITE);
            if (gameOver){
                DrawGameOver();// making the the game over screen
            } else{
                DrawGame();
            }
           
        EndDrawing();
        
    }

    // De-Initialization
    
    CloseWindow();        // Close window and OpenGL context
    

    return 0;

void initGame(){
   // starting point and moving speed when standing still
    player.rect = Rectangle{SCREEN_WIDTH / 2- PLAYER_WIDTH /2,40, PLATFORM_WIDTH, PLAYER_HEIGHT};
    player.velocity =Vector2{0,0};

    //platform creation
    for(int i = 0; i < MAX_PLATFORM; i++) {
        ResetPlatform(&platforms[i]); //RANDOM CORDS
        platforms[i].rect.y =SCREEN_HEIGHT - (i + 1) * 100; //vetical placement
        platforms[i].active =true //actived all platforms????
    }
    //Reseting scores and state in the game
    score = 0;
    highestPlatformY = SCREEN_HEIGHT;
    gameOver =false;
    }



//Function to update the game logic each frame???????
void UpdateGame(float dt)
//player jump code 
if (IsKeyPressed(KEY_space) && player.velocity.y == 0) //jump only if on floor and press space
{
    player.velocity.y = JUMP_FORCE;
}


 