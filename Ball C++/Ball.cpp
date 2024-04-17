// Ball.cpp
// 时间：2024/04/18
// 作者：周咏霖
// 功能：一个简单的弹跳球模拟器，让小球在一个边界框内自由移动，并模拟了重力、空气阻力、摩擦力等物理效应，且可以通过方向键控制小球。

#include <SDL2/SDL.h>   // 包含SDL库的头文件
#include <stdio.h>       // 包含标准输入输出库的头文件
#include <stdbool.h>     // 包含bool类型的头文件

typedef struct {
    float x, y;        // 小球的位置
    float vx, vy;      // 小球的速度
    float radius;      // 小球的半径
    SDL_Color color;   // 小球的颜色
} Ball;  // 定义了一个名为Ball的结构体，用来表示小球的属性

void drawBall(SDL_Renderer* renderer, Ball* ball) {
    SDL_SetRenderDrawColor(renderer, ball->color.r, ball->color.g, ball->color.b, 255);
    // 设置绘制颜色为小球的颜色

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
}  // 绘制小球的函数，使用SDL库中的函数来绘制一个以小球中心为圆心，半径为radius的小球

typedef struct {
    float x, y;         // 框的位置
    float width, height; // 框的尺寸
    SDL_Color color;     // 框的颜色
} Box;  // 定义了一个名为Box的结构体，用来表示框的属性

void drawBox(SDL_Renderer* renderer, Box* box) {
    SDL_SetRenderDrawColor(renderer, box->color.r, box->color.g, box->color.b, 255);
    // 设置绘制颜色为框的颜色

    SDL_Rect rect = { (int)box->x, (int)box->y, (int)box->width, (int)box->height };
    // 创建一个SDL_Rect结构体，表示框的位置和尺寸

    SDL_RenderDrawRect(renderer, &rect);
}  // 绘制框的函数，使用SDL库中的函数来绘制一个以框的左上角为起点，宽度为width，高度为height的矩形框

int main(int argc, char* args[]) {
    SDL_Init(SDL_INIT_VIDEO);  // 初始化SDL视频子系统

    // 创建窗口和渲染器
    SDL_Window* window = SDL_CreateWindow("Ball Simulation", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // 初始化小球和框
    Ball ball = {400, 300, 50, -55, 15, {255, 0, 0}}; // 添加初始速度 vx = 50, vy = -55
    Box box = {100, 100, 600, 400, {0, 0, 0}};

    bool quit = false;
    SDL_Event e;
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;  // 当接收到退出事件时，退出主循环
            } else if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_UP:    ball.vy -= 1; break;  // 按下上箭头键，小球向上移动
                    case SDLK_DOWN:  ball.vy += 1; break;  // 按下下箭头键，小球向下移动
                    case SDLK_LEFT:  ball.vx -= 1; break;  // 按下左箭头键，小球向左移动
                    case SDLK_RIGHT: ball.vx += 1; break;  // 按下右箭头键，小球向右移动
                }
            }
        }

        // 模拟物理效应
        ball.vy += 0.1; // 微弱的重力加速度，模拟自然下落效应
        ball.vx *= 0.999; // 空气阻力
        ball.vy *= 0.999; // 空气阻力
        ball.x += ball.vx;
        ball.y += ball.vy;

        // 边界碰撞检测
        if (ball.x + ball.radius > box.x + box.width) {
            ball.x = box.x + box.width - ball.radius;
            ball.vx *= -0.8;  // 反弹并损失能量
        }
        if (ball.x - ball.radius < box.x) {
            ball.x = box.x + ball.radius;
            ball.vx *= -0.8;  // 反弹并损失能量
        }
        if (ball.y + ball.radius > box.y + box.height) {
            ball.y = box.y + box.height - ball.radius;
            ball.vy *= -0.8; // 反弹并损失能量
            ball.vx *= 0.98; // 摩擦力
        }
        if (ball.y - ball.radius < box.y) {
            ball.y = box.y + ball.radius;
            ball.vy *= -0.8;  // 反弹并损失能量
        }

        // 清屏
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        // 绘制
        drawBox(renderer, &box);  // 绘制框
        drawBall(renderer, &ball);  // 绘制小球

        // 更新屏幕
        SDL_RenderPresent(renderer);
        SDL_Delay(16); // 约60帧每秒
    }

    // 释放资源并退出
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}