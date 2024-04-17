// Ball.cpp
// 时间：2024/04/18
// 作者：周咏霖
// 功能：一个简单的弹跳球模拟器，让小球在一个边界框内自由移动，并模拟了重力、空气阻力、摩擦力等物理效应，且可以通过方向键控制小球。

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct {
    float x, y;        // 小球的位置
    float vx, vy;      // 小球的速度
    float radius;      // 小球的半径
    SDL_Color color;   // 小球的颜色
} Ball;

void drawBall(SDL_Renderer* renderer, Ball* ball) {
    SDL_SetRenderDrawColor(renderer, ball->color.r, ball->color.g, ball->color.b, 255);
    // 绘制小球
    for (int w = 0; w < ball->radius * 2; w++) {
        for (int h = 0; h < ball->radius * 2; h++) {
            int dx = ball->radius - w; // 水平距离中心的偏移
            int dy = ball->radius - h; // 垂直距离中心的偏移
            if (dx*dx + dy*dy <= ball->radius*ball->radius) {
                SDL_RenderDrawPoint(renderer, ball->x + dx, ball->y + dy);
            }
        }
    }
}

typedef struct {
    float x, y;         // 框的位置
    float width, height;// 框的尺寸
    SDL_Color color;    // 框的颜色
} Box;

void drawBox(SDL_Renderer* renderer, Box* box) {
    SDL_SetRenderDrawColor(renderer, box->color.r, box->color.g, box->color.b, 255);
    SDL_Rect rect = { (int)box->x, (int)box->y, (int)box->width, (int)box->height };
    SDL_RenderDrawRect(renderer, &rect);
}

int main(int argc, char* args[]) {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("Ball Simulation", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    Ball ball = {400, 300, 50, -55, 15, {255, 0, 0}}; // 添加初始速度 vx = 50, vy = -55
    Box box = {100, 100, 600, 400, {0, 0, 0}};

    bool quit = false;
    SDL_Event e;
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            } else if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_UP:    ball.vy -= 1; break;
                    case SDLK_DOWN:  ball.vy += 1; break;
                    case SDLK_LEFT:  ball.vx -= 1; break;
                    case SDLK_RIGHT: ball.vx += 1; break;
                }
            }
        }

        // 模拟物理效应
        ball.vy += 0.1; // 微弱的重力加速度，模拟自然下落效应
        ball.vx *= 0.99; // 空气阻力
        ball.vy *= 0.99; // 空气阻力
        ball.x += ball.vx;
        ball.y += ball.vy;

        // 边界碰撞检测
        if (ball.x + ball.radius > box.x + box.width) {
            ball.x = box.x + box.width - ball.radius;
            ball.vx *= -0.8;
        }
        if (ball.x - ball.radius < box.x) {
            ball.x = box.x + ball.radius;
            ball.vx *= -0.8;
        }
        if (ball.y + ball.radius > box.y + box.height) {
            ball.y = box.y + box.height - ball.radius;
            ball.vy *= -0.8; // 能量损失和反弹
            ball.vx *= 0.95; // 摩擦力
        }
        if (ball.y - ball.radius < box.y) {
            ball.y = box.y + ball.radius;
            ball.vy *= -0.8;
        }

        // 清屏
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        // 绘制
        drawBox(renderer, &box);
        drawBall(renderer, &ball);

        // 更新屏幕
        SDL_RenderPresent(renderer);
        SDL_Delay(16); // 约60帧每秒
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}