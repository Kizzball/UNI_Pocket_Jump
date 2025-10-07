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
if (IsKeyPressed(KEY_SPACE) && player.velocity.y == 0) //jump only if on floor and press space
{player.velocity.y = JUMP_FORCE;}

//Player controls code
if (IsKeyDown(KEY_LEFT)) player.rect.x -= 200 * dt;
if (IsKeyDown(KEY_RIGHT)) player.rect.x += 200 * dt;

//Gravity for the player
player.velocity.y += GRAVITY *dt;

//Update the player's position based on velocity?????
player.rect.y += player.velocity.y *dt;
player.rect.x += player.velocity.x *dt;

//remove unseen platforms?!?!------- maybe broken
If (platform.rect > SCREEN_HEIGHT ){
    platforms[i].active = false;}

//collsions with platforms for player
for (int i = 0; i < MAX_PLATFORM; 1++ {
    if (platforms[i].active && CheckCollisionRes(player.rect,platforms[i].rect) && player.velocity.y > 0){
    // stops player phasing
    player.velocity.y = 0
    player.rect.y = platforms[i].rect.y - PLAYER_HEIGHT;} //player position adjustment?????
}
//ending screen when fall
If(player.rect.y > SCREEN_HEIGHT){
    gameOver = true;
}

//Scroll feature
If (player.rect.y < SCREEN_HEIGHT / 2){
    float offset = SCREEN_HEIGHT / 2 - player.rect.y;
    player.rect.y +=- offset;
    score += offset / 10;
    
    for (int i = 0; i < MAX_PLATFORM; i++){
        platforms[i].rect.y += offset;
        // reset platforms if they move off the bottom of the screen
        if(platforms[i].rect.y > SCREEN_HEIGHT){
            ResetPlatform(&platforms[i]);
            platforms[i]rect.y =highestPlatformY - 100; 
            highestPlatformY -= 100;

        }
    }

}
void DrawGame(){
    DrawRectangleRec(player.rect, RED);

    //Makes the platform appearance
    for (int i = 0; i < MAX_PLATFORM; i++){
        If(platforms[i].active){
            DrawRectangleRec(platforms[i].rect, DARKGRAY);
        }
    }
    //score text
    DrawText()
}