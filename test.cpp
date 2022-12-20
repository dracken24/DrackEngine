#include "OnyXEngine/include/raylib.h"
#include "pong.h"

// Variable globales
Vector2 ball = {600.0f, 400.0f};
Vector2 p1 = {10.0f, 350.0f};      // Pos x P1
Vector2 p2 = {1175.0f, 350.0f};    // Pos x P2
MaxMin move_p1 = {450.0f, 350.0f}; // Limits Y collision P1
MaxMin move_p2 = {450.0f, 350.0f}; // Limits Y collision P2
int ct = -1;
int ct_start = 0;
float ct_down = 0;
void draw_start(Texture2D background);

// Fonctions
void draw_end(int point_p1, int point_p2);
void draw_start(Texture2D background);
void game_logic_p1(void);
void game_logic_p2(void);
void playeur_ctrl(void);
void restart_game(void);
void move_on_hit(void);

int main()
{
    int point_p1 = 0;
    int point_p2 = 0;
    InitWindow(1200, 800, "PONG V.42");
    Texture2D background = LoadTexture("terrain_pong_01.png");

    SetTargetFPS(60);

    while (!IsKeyDown(KEY_ESCAPE))
    {
        draw_start(background);
        playeur_ctrl();
        if (IsKeyPressed(KEY_SPACE))
            ct_start = 1;

        // Count points
        if (ball.x == -50)
            point_p2 += 1;
        if (ball.x == 1250)
            point_p1 += 1;

        // Game logic begin
        if (ct == -1) // P1
            game_logic_p1();
        if (ct == 1) // P2
            game_logic_p2();

        if (ct_start == 0)
            DrawText("Press space to begin", 400, 300, 40, (Color){230, 41, 55, 255});
        draw_end(point_p1, point_p2);
    }
    UnloadTexture(background);
    return 0;
}

void playeur_ctrl(void)
{
    if (IsKeyDown(KEY_W) && p1.y >= 8)
    {
        p1.y -= 5;
        move_p1.max -= 5;
        move_p1.min -= 5;
    }
    if (IsKeyDown(KEY_S) && p1.y <= 690)
    {
        p1.y += 5;
        move_p1.min += 5;
        move_p1.max += 5;
    }
    if (IsKeyDown(KEY_UP) && p2.y >= 8)
    {
        p2.y -= 5;
        move_p2.max -= 5;
        move_p2.min -= 5;
    }
    if (IsKeyDown(KEY_DOWN) && p2.y <= 690)
    {
        p2.y += 5;
        move_p2.max += 5;
        move_p2.min += 5;
    }
}

void move_on_hit(void)
{
    if (IsKeyDown(KEY_S))
    {
        ct_down += 1.5;
        if (ct_down < 0)
            ct_down = 0;
    }
    if (IsKeyDown(KEY_W))
    {
        ct_down -= 1.5;
        if (ct_down > 0)
            ct_down = 0;
    }
    if (IsKeyDown(KEY_DOWN))
    {
        ct_down += 1.5;
        if (ct_down < 0)
            ct_down = 0;
    }
    if (IsKeyDown(KEY_UP))
    {
        ct_down -= 1.5;
        if (ct_down > 0)
            ct_down = 0;
    }
}

void restart_game(void)
{
    ball.x = 600;
    ct_down = 0;
    ball.y = 400;
    ct_start = 0;
}

void draw_start(Texture2D background)
{
    BeginDrawing();
    ClearBackground(GetColor(0x052c46ff));
    DrawTexture(background, 0, 0, (Color){255, 255, 255, 255});
    DrawCircle(ball.x, ball.y, 15, (Color){230, 41, 55, 255});     // ball
    DrawRectangle(p1.x, p1.y, 15, 100, (Color){230, 41, 55, 255}); // p1
    DrawRectangle(p2.x, p2.y, 15, 100, (Color){230, 41, 55, 255}); // p2
}

void draw_end(int point_p1, int point_p2)
{
    DrawText("Pong rebuilt by Nadia/nadesjar42", 10, 10, 20, (Color){230, 41, 55, 255});
    DrawText(TextFormat("SCORE P1: %i", point_p1), 40, 770, 20, (Color){230, 41, 55, 255});
    DrawText(TextFormat("SCORE P2: %i", point_p2), 1020, 760, 20, (Color){230, 41, 55, 255});
    EndDrawing();
}

void game_logic_p1(void)
{
    if ((ball.x >= 10 && ball.x <= 30) && (ball.y >= move_p1.min && ball.y <= move_p1.max))
    {
        move_on_hit();
        ct = 1;
    }

    // Deplacement horizontale
    if (ct_start == 1)
        ball.x = ball.x - 10;

    if (ball.x < -200)
        restart_game();

    // Move balle up/down logic
    if (ct_down != 0)
        ball.y += ct_down;

    // Collision haut/bas
    if (ball.y > 792)
        ct_down *= -1;
    else if (ball.y < 8)
        ct_down *= -1;
}

void game_logic_p2(void)
{
    if ((ball.x >= 1170 && ball.x <= 1190) && (ball.y >= move_p2.min && ball.y <= move_p2.max))
    {
        move_on_hit();
        ct = -1;
    }

    // Deplacement horizontale
    if (ct_start == 1)
        ball.x = ball.x + 10;

    if (ball.x > 1400)
        restart_game();

    // Move balle up/down logic
    if (ct_down != 0)
        ball.y += ct_down;

    // Collision haut/bas
    if (ball.y > 792)
        ct_down *= -1;
    else if (ball.y < 8)
        ct_down *= -1;
}