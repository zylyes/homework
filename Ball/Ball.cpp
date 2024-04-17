#include <GL/glut.h>
#include "glfw3.h"
#include <math.h>
#include <stdio.h>

// 定义重力常数
#define GRAVITY -9.8
// 定义时间步长
#define TIME_STEP 0.01
// 定义空气阻力系数
#define AIR_RESISTANCE 0.99
// 定义摩擦力系数
#define FRICTION 0.95
// 定义能量损耗系数
#define ENERGY_LOSS 0.9

typedef struct {
    float x, y;       // 位置
    float vx, vy;     // 速度
    float radius;     // 半径
} Ball;

typedef struct {
    float x, y;       // 位置
    float width, height;  // 宽度和高度
} Box;

Ball ball;
Box box;

void init() {
    // 初始化小球
    ball.x = 0.5;
    ball.y = 0.5;
    ball.vx = 0.0;
    ball.vy = 0.0;
    ball.radius = 0.05;

    // 初始化边界框
    box.x = 0.0;
    box.y = 0.0;
    box.width = 1.0;
    box.height = 1.0;

    // 设置背景颜色为白色
    glClearColor(1.0, 1.0, 1.0, 1.0);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // 绘制边界框
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(box.x, box.y);
    glVertex2f(box.x + box.width, box.y);
    glVertex2f(box.x + box.width, box.y + box.height);
    glVertex2f(box.x, box.y + box.height);
    glEnd();

    // 绘制小球
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i++) {
        float theta = i * M_PI / 180.0;
        glVertex2f(ball.x + ball.radius * cos(theta), ball.y + ball.radius * sin(theta));
    }
    glEnd();

    glutSwapBuffers();
}

void update(int value) {
    // 更新小球位置和速度
    ball.vy += GRAVITY * TIME_STEP;
    ball.vx *= AIR_RESISTANCE;
    ball.vy *= AIR_RESISTANCE;
    ball.x += ball.vx * TIME_STEP;
    ball.y += ball.vy * TIME_STEP;

    // 检测与边界的碰撞
    if (ball.x - ball.radius < box.x || ball.x + ball.radius > box.x + box.width) {
        ball.vx = -ball.vx * ENERGY_LOSS;
        ball.x = (ball.x - ball.radius < box.x) ? box.x + ball.radius : box.x + box.width - ball.radius;
    }
    if (ball.y - ball.radius < box.y || ball.y + ball.radius > box.y + box.height) {
        ball.vy = -ball.vy * ENERGY_LOSS;
        ball.y = (ball.y - ball.radius < box.y) ? box.y + ball.radius : box.y + box.height - ball.radius;
    }

    glutPostRedisplay();
    glutTimerFunc(10, update, 0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Ball Simulation");
    init();
    glutDisplayFunc(display);
    glutTimerFunc(10, update, 0);
    glutMainLoop();
    return 0;
}