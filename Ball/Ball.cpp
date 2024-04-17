#include <SDL2/SDL.h>
#include <stdbool.h>

typedef struct {
    float x, y;       // 小球的位置
    float vx, vy;     // 小球的速度
    int radius;       // 小球的半径
    SDL_Color color;  // 小球的颜色
} Ball;

typedef struct {
    int x, y;         // 边界框的位置
    int width, height;// 边界框的尺寸
    SDL_Color color;  // 边界框的颜色
} Box;

void initBall(Ball *ball, float x, float y, float vx, float vy, int radius, SDL_Color color) {
    ball->x = x;
    ball->y = y;
    ball->vx = vx;
    ball->vy = vy;
    ball->radius = radius;
    ball->color = color;
}

void drawBall(SDL_Renderer *renderer, Ball *ball) {
    SDL_SetRenderDrawColor(renderer, ball->color.r, ball->color.g, ball->color.b, 255);
    for (int w = 0; w < ball->radius * 2; w++) {
        for (int h = 0; h < ball->radius * 2; h++) {
            int dx = ball->radius - w;
            int dy = ball->radius - h;
            if ((dx * dx + dy * dy) <= (ball->radius * ball->radius)) {
                SDL_RenderDrawPoint(renderer, ball->x + dx, ball->y + dy);
            }
        }
    }
}

void initBox(Box *box, int x, int y, int width, int height, SDL_Color color) {
    box->x = x;
    box->y = y;
    box->width = width;
    box->height = height;
    box->color = color;
}

void drawBox(SDL_Renderer *renderer, Box *box) {
    SDL_SetRenderDrawColor(renderer, box->color.r, box->color.g, box->color.b, 255);
    SDL_Rect rect = {box->x, box->y, box->width, box->height};
    SDL_RenderDrawRect(renderer, &rect);
}

void updateBall(Ball *ball, Box *box) {
    float gravity = 0.5f; // 重力加速度
    float airResistance = 0.99f; // 空气阻力
    float friction = 0.95f; // 摩擦力
    float energyLoss = 0.9f; // 能量损失

    // 更新速度和位置
    ball->vy += gravity; // 重力影响
    ball->vx *= airResistance; // 空气阻力影响
    ball->vy *= airResistance;
    ball->x += ball->vx;
    ball->y += ball->vy;

    // 检查边界碰撞
    if (ball->x - ball->radius < box->x) {
        ball->x = box->x + ball->radius;
        ball->vx = -ball->vx * energyLoss;
    } else if (ball->x + ball->radius > box->x + box->width) {
        ball->x = box->x + box->width - ball->radius;
        ball->vx = -ball->vx * energyLoss;
    }
    if (ball->y - ball->radius < box->y) {
        ball->y = box->y + ball->radius;
        ball->vy = -ball->vy * energyLoss;
    } else if (ball->y + ball->radius > box->y + box->height) {
        ball->y = box->y + box->height - ball->radius;
        ball->vy = -ball->vy * energyLoss;
        ball->vx *= friction; // 摩擦力影响
    }
}

int main(int argc, char *argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("Ball Simulation", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    Ball ball;
    Box box;
    SDL_Color ballColor = {255, 0, 0, 255};
    SDL_Color boxColor = {0, 0, 255, 255};

    initBall(&ball, 400, 100, 2, 0, 20, ballColor);
    initBox(&box, 0, 0, 800, 600, boxColor);

    bool running = true;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        updateBall(&ball, &box);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        drawBall(renderer, &ball);
        drawBox(renderer, &box);

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}