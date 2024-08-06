// Ball1.cpp
// 时间：2024/04/28
// 作者：周咏霖
// 编译：g++.exe -g Ball1.cpp -o Ball1.exe -lmingw32 -lSDL2main -lSDL2 -mwindows
// 运行：./Ball1.exe
// 功能：一个简单的弹跳球模拟器，让小球在一个边界框内自由移动，并模拟了重力、空气阻力、摩擦力等物理效应。

#include <SDL2/SDL.h>  // 引入SDL库
#include <iostream>  // 引入输入输出流库

// 小球类（Ball），用于表示和控制小球的行为和属性
class Ball {  // 小球类，用于表示和控制小球的行为和属性
public:
    // 构造函数，用于初始化小球对象
    Ball(float x, float y, float vx, float vy, float radius, SDL_Color color)  // 初始化小球的位置、速度、半径和颜色
    : x(x), y(y), vx(vx), vy(vy), radius(radius), color(color) {}  // 使用成员初始化列表初始化小球的属性

    // 在渲染器上绘制小球的函数
    void draw(SDL_Renderer* renderer) {
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);  // 设置绘制颜色
        for (int w = 0; w < radius * 2; w++) {   // 遍历小球的宽度
            for (int h = 0; h < radius * 2; h++) {  // 遍历小球的高度
                int dx = radius - w;  // 计算x方向的偏移量
                int dy = radius - h;  // 计算y方向的偏移量
                if (dx * dx + dy * dy <= radius * radius) {  // 判断是否在小球内部
                    SDL_RenderDrawPoint(renderer, x + dx, y + dy);  // 绘制小球内部的点
                }
            }
        }
    }

    // 更新小球物理状态的函数（如位置、速度）
    void updatePhysics(float gravity, float airResistance) {
        vy += gravity; // 重力
        vx *= airResistance; // 空气阻力
        vy *= airResistance; // 空气阻力
        x += vx; // 根据速度更新位置
        y += vy; // 根据速度更新位置
    }

    // 碰撞检测和反应
    void checkCollision(const SDL_Rect& box) {
        // 右边界
        if (x + radius > box.x + box.w) {  // 判断小球是否碰到右边界
            x = box.x + box.w - radius;  // 修正位置
            vx *= -0.9f;  // 反弹并损失一些能量
        }
        // 左边界
        if (x - radius < box.x) {  // 判断小球是否碰到左边界
            x = box.x + radius;  // 修正位置
            vx *= -0.9f;  // 反弹并损失一些能量
        }
        // 下边界
        if (y + radius > box.y + box.h) {  // 判断小球是否碰到下边界
            y = box.y + box.h - radius;  // 修正位置
            vy *= -0.9f;  // 反弹并损失一些能量
            vx *= 0.98f;  // 添加一些摩擦力
        }
        // 上边界
        if (y - radius < box.y) {  // 判断小球是否碰到上边界
            y = box.y + radius;  // 修正位置
            vy *= -0.9f;  // 反弹并损失一些能量
        }
    }

    // 小球的公共属性
    float x, y; // 小球位置
    float vx, vy; // 小球速度
    float radius; // 小球半径
    SDL_Color color; // 小球颜色
};

// 框类（Box），用于表示和控制框的行为和属性
class Box {  // 框类，用于表示和控制框的行为和属性
public:
    Box(float x, float y, float width, float height, SDL_Color color)  // 初始化框的位置、尺寸和颜色
    : rectangle({static_cast<int>(x), static_cast<int>(y), static_cast<int>(width), static_cast<int>(height)}), color(color) {}  // 使用成员初始化列表初始化框的属性

    // 绘制边界框
    void draw(SDL_Renderer* renderer) {  // 在渲染器上绘制边界框
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);  // 设置绘制颜色
        SDL_RenderDrawRect(renderer, &rectangle);  // 绘制边界框
    }

    // 框的公共属性
    SDL_Rect rectangle; // SDL_Rect 结构存储边界框的位置和尺寸
    SDL_Color color; // 框颜色
};

int main(int argc, char* args[]) {  // 主函数
    // 初始化SDL视频子系统
    SDL_Init(SDL_INIT_VIDEO);

    // 创建窗口和渲染器
    SDL_Window* window = SDL_CreateWindow("Ball Simulation", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);  // 创建窗口
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);  // 创建渲染器

    // 初始化小球和框的对象
    Ball ball(200.0f, 200.0f, 15.0f, 8.0f, 15.0f, {255, 0, 0}); // 初始位置、速度、半径和颜色
    Box box(100.0f, 100.0f, 600.0f, 400.0f, {0, 0, 0}); // 初始位置、尺寸和颜色

    // 标志主循环是否应该退出
    bool quit = false;  // 标志主循环是否应该退出
    SDL_Event e;  // 事件变量

    while (!quit) {  // 主循环
        // 处理事件队列
        while (SDL_PollEvent(&e) != 0) {  // 处理事件队列
            if (e.type == SDL_QUIT) {  // 用户请求退出
                quit = true; // 用户请求退出
            }
            // 额外的事件处理可以放在这里
        }

        // 更新小球的物理状态
        ball.updatePhysics(0.1f, 0.999f);

        // 检查小球与框的碰撞
        ball.checkCollision(box.rectangle);

        // 清空屏幕
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);  // 设置背景颜色
        SDL_RenderClear(renderer);  // 清空屏幕

        // 绘制框和小球
        box.draw(renderer);  // 绘制框
        ball.draw(renderer);  // 绘制小球

        // 交换前后缓冲区，更新窗口
        SDL_RenderPresent(renderer);

        // 等待一段时间，这里是16ms左右，以便维持约60帧/秒的速率
        SDL_Delay(16);
    }

    // 销毁资源并退出SDL
    SDL_DestroyRenderer(renderer);  // 销毁渲染器
    SDL_DestroyWindow(window);  // 销毁窗口
    SDL_Quit();  // 退出SDL
    return 0;  // 返回0表示正常退出
}