#include <SDL2/SDL.h>
#include <stdbool.h>
#include <math.h>

// 窗口尺寸
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

// 小球属性
const int BALL_RADIUS = 15;
float ball_x = WINDOW_WIDTH / 2;
float ball_y = BALL_RADIUS;
float ball_vx = 100; // 水平速度
float ball_vy = 0; // 垂直速度

// 物理常数
const float GRAVITY = 980; // 重力加速度 (pixels/s^2)
const float AIR_RESISTANCE = 0.1; // 空气阻力
const float FRICTION = 0.8; // 摩擦系数
const float ENERGY_LOSS = 0.9; // 碰撞能量损失

void applyPhysics(float delta_time) {
    // 应用重力
    ball_vy += GRAVITY * delta_time;

    // 应用空气阻力
    ball_vx *= (1 - AIR_RESISTANCE * delta_time);
    ball_vy *= (1 - AIR_RESISTANCE * delta_time);

    // 更新位置
    ball_x += ball_vx * delta_time;
    ball_y += ball_vy * delta_time;

    // 边界碰撞检测
    if (ball_x < BALL_RADIUS) {
        ball_x = BALL_RADIUS;
        ball_vx = -ball_vx * ENERGY_LOSS;
    } else if (ball_x > WINDOW_WIDTH - BALL_RADIUS) {
        ball_x = WINDOW_WIDTH - BALL_RADIUS;
        ball_vx = -ball_vx * ENERGY_LOSS;
    }

    if (ball_y < BALL_RADIUS) {
        ball_y = BALL_RADIUS;
        ball_vy = -ball_vy * ENERGY_LOSS;
    } else if (ball_y > WINDOW_HEIGHT - BALL_RADIUS) {
        ball_y = WINDOW_HEIGHT - BALL_RADIUS;
        ball_vy = -ball_vy * ENERGY_LOSS;
        ball_vx *= FRICTION; // 应用摩擦力
    }
}

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("Ball Simulation",
                                          SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                          WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    bool running = true;
    SDL_Event event;
    Uint32 last_time = SDL_GetTicks(), current_time;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        current_time = SDL_GetTicks();
        float delta_time = (current_time - last_time) / 1000.0f;
        last_time = current_time;

        applyPhysics(delta_time);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_Rect ball = { (int)(ball_x - BALL_RADIUS), (int)(ball_y - BALL_RADIUS), BALL_RADIUS * 2, BALL_RADIUS * 2 };
        SDL_RenderFillRect(renderer, &ball);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}