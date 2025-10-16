#include "raylib.h"
#include "stdlib.h"
#include "stdio.h"

#define SCREEN_WIDTH 960
#define SCREEN_HEIGHT 600
#define PLATFORM_WIDTH 100
#define PLATFORM_HEIGHT 20
#define PLAYER_WIDTH 30 
#define PLAYER_HEIGHT 30
#define GRAVITY 300
#define JUMP_FORCE -400
#define MAX_PLATFORMS 10

    typedef struct {
        Rectangle rect;
        float timeLeft;
        bool active;
    } Platform;
    
    typedef struct {
        Rectangle rect;
        Vector2 velocity;
    } Player;
    
    Platform platforms[MAX_PLATFORMS];
    Player player;
    float score = 0 - 26;
    int highestPlatformY = SCREEN_HEIGHT;
    bool gameOver = false;
    
    void InitGame();
    void UpdateGame(float dt);
    void DrawGame();
    void DrawGameOver();
    void ResetPlatform(Platform* platform);
    
    
    int main (){
        InitWindow(SCREEN_WIDTH,SCREEN_HEIGHT,"Pocket Jump");
        
        InitGame();
        
        SetTargetFPS(60);
        
        while (!WindowShouldClose()){
            
            float dt = GetFrameTime();
            
            
            UpdateGame(dt);
            
            BeginDrawing();
            ClearBackground(RAYWHITE);
            
            if (gameOver){
                DrawGameOver();
            }
                else{
                    DrawGame();
                }
                EndDrawing();
            }
            CloseWindow();
            return 0;
            
    }
    
    void InitGame(){
        
        player.rect = Rectangle{SCREEN_WIDTH / 2 - PLAYER_WIDTH / 2, 40, PLAYER_WIDTH, PLAYER_HEIGHT};
        player.velocity = Vector2{0, 0};
        
        for (int i = 0; i < MAX_PLATFORMS; i++){
            ResetPlatform(&platforms[i]);
            platforms[i].rect.y = SCREEN_HEIGHT - (i + 1) * 100;
            platforms[i].active = true;
            }
        
        score = 0;
        highestPlatformY = SCREEN_HEIGHT;
        gameOver = false;
    }
        void UpdateGame(float dt){
            
            if (IsKeyPressed(KEY_SPACE) && player.velocity.y == 0){
            player.velocity.y = JUMP_FORCE;
            }
            if (IsKeyPressed(KEY_UP) && player.velocity.y == 0){
            player.velocity.y = JUMP_FORCE;
            }
            
            if (IsKeyDown(KEY_LEFT)) player.rect.x -= 200 * dt;
            if (IsKeyDown(KEY_RIGHT)) player.rect.x += 200 * dt;
            
            player.velocity.y += GRAVITY * dt;
            
            player.rect.y += player.velocity.y * dt;
            player.rect.x += player.velocity.x * dt;
            
            for(int i = 0; i < MAX_PLATFORMS; i++) {
                if (platforms[i].active && CheckCollisionRecs(player.rect, platforms[i].rect) && player.velocity.y > 0){
                    
                    player.velocity.y = 0;
                    player.rect.y = platforms[i].rect.y - PLATFORM_HEIGHT;
                    
                    platforms[i].timeLeft -= dt;
                    if(platforms[i].timeLeft <= 0){
                        platforms[i].active = false;
                    }
                }
            }
            
            if (player.rect.y > SCREEN_HEIGHT){
                gameOver = true;
            }
            
            if (player.rect.y < SCREEN_HEIGHT / 2){
                float offset = SCREEN_HEIGHT / 2 - player.rect.y;
                player.rect.y += offset;
                score += offset / 10;
                
                for(int i = 0; i < MAX_PLATFORMS; i++){
                    platforms[i].rect.y += offset;
                    
                    if(platforms[i].rect.y > SCREEN_HEIGHT){
                        ResetPlatform(&platforms[i]);
                        platforms[i].rect.y = highestPlatformY - 100;
                        highestPlatformY -= 100;
                        
                    }
                }
            }
        }
        
        void DrawGame(){
            DrawRectangleRec(player.rect, BROWN);
            
            for(int i = 0; i < MAX_PLATFORMS; i++){
                if(platforms[i].active){
                    DrawRectangleRec(platforms[i].rect, BLUE);
                }
            }
            
            DrawText(TextFormat("Current Score: %.0f", score), 10, 10, 20, BLACK);
            
        }
                    
            
            
        void ResetPlatform(Platform* platform){
            
            platform->rect = Rectangle{
                (float)GetRandomValue(0, SCREEN_WIDTH -PLATFORM_WIDTH),
                (float)GetRandomValue(-200, 0),
                (float)PLATFORM_WIDTH,
                (float)PLATFORM_HEIGHT
                
            };
            platform->timeLeft = 5.0f;
            platform->active = true;
            
        }
        void DrawGameOver(){
            DrawText("Game Over", SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 -50, 40, RED);
            DrawText(TextFormat("Final Score: %.0f", score), SCREEN_WIDTH /2 -100, SCREEN_HEIGHT / 2, 20, BLACK);
            DrawText("Press R to Try Again", SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 + 50, 20 ,DARKGRAY);
            
            if (IsKeyPressed(KEY_R)){
                InitGame();
            }
            
        }
    
        
        