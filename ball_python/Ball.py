# Ball.py
# 时间：2024/04/14
# 作者：周咏霖
# 功能：一个简单的弹跳球模拟器，让小球在一个边界框内自由移动，并模拟了重力、空气阻力、摩擦力等物理效应。

import pygame  # 导入pygame库
import sys  # 导入sys模块
from math import degrees, atan2  # 从math库中导入degrees和atan2函数

# 初始化 pygame
pygame.init()  # 初始化pygame

# 窗口大小设置
WIDTH, HEIGHT = 800, 600  # 设置窗口的宽度和高度
screen = pygame.display.set_mode((WIDTH, HEIGHT))  # 创建窗口对象
pygame.display.set_caption("弹跳球模拟器")  # 设置窗口标题为'弹跳球模拟器'

# 定义颜色
WHITE = (255, 255, 255)  # 白色
BLUE = (0, 0, 255)  # 蓝色
RED = (255, 0, 0)  # 红色


# 定义小球类
class Ball:
    def __init__(self, x, y, radius, velocity, color=RED):
        self.x = x  # 小球的x坐标
        self.y = y  # 小球的y坐标
        self.radius = radius  # 小球的半径
        self.velocity = velocity  # 小球的速度
        self.color = color  # 小球的颜色

    def draw(self, surface):
        angle = degrees(atan2(self.velocity[1], self.velocity[0]))  # 计算旋转角度
        rotated_ball = pygame.transform.rotate(
            pygame.Surface((self.radius * 2, self.radius * 2)), angle
        )  # 创建旋转后的小球表面
        rotated_ball.set_colorkey((0, 0, 0))  # 设置透明色
        rotated_ball.fill((0, 0, 0))  # 填充背景色
        pygame.draw.circle(
            rotated_ball, self.color, (self.radius, self.radius), self.radius
        )  # 在旋转后的表面上绘制小球
        surface.blit(
            rotated_ball, (self.x - self.radius, self.y - self.radius)
        )  # 在屏幕上绘制旋转后的小球

    def move(self, gravity, air_resistance_coeff, friction_coeff, box_bottom):
        self.x += self.velocity[0]  # 更新小球的x坐标
        self.y += self.velocity[1]  # 更新小球的y坐标
        self.velocity[1] += gravity  # 更新小球的垂直速度，受到重力的影响

        # 空气阻力
        air_resistance_x = (
            air_resistance_coeff * self.velocity[0] ** 2
        )  # X轴方向的空气阻力
        air_resistance_y = (
            air_resistance_coeff * self.velocity[1] ** 2
        )  # Y轴方向的空气阻力
        # 对于X轴
        if self.velocity[0] > 0:
            self.velocity[0] -= air_resistance_x  # 减小X轴方向的速度
        elif self.velocity[0] < 0:
            self.velocity[0] += air_resistance_x  # 增加X轴方向的速度
        # 对于Y轴
        if self.velocity[1] > 0:
            self.velocity[1] -= air_resistance_y  # 减小Y轴方向的速度
        elif self.velocity[1] < 0:
            self.velocity[1] += air_resistance_y  # 增加Y轴方向的速度

        # 摩擦力 - 当小球在地面上时应用于x方向
        if (
            self.y + self.radius >= box_bottom - 1
            and abs(self.velocity[1]) <= min_vertical_speed
        ):
            if abs(self.velocity[0]) > min_horizontal_speed:
                self.velocity[0] -= (
                    friction_coeff if self.velocity[0] > 0 else -friction_coeff
                )  # 减小水平速度
            else:
                self.velocity[0] = 0  # 水平速度为0


# 定义边界框
class Box:
    def __init__(self, x, y, width, height, color=BLUE):
        self.rect = pygame.Rect(x, y, width, height)  # 创建矩形对象
        self.color = color  # 边界框的颜色

    def draw(self, surface):
        pygame.draw.rect(
            surface, self.color, self.rect, 2
        )  # 在表面上绘制边界框，线宽为2


# 时钟对象，用于控制帧速率
clock = pygame.time.Clock()  # 创建时钟对象

# 参数配置
gravity = 0.09  # 重力加速度
energy_loss_coeff = 0.98  # 反弹能量损失系数
friction_coeff = 0.00  # 摩擦系数
air_resistance_coeff = 0.0001  # 空气阻力系数
min_vertical_speed = 0.51  # 垂直方向停止的最小速度
min_horizontal_speed = 0.01  # 水平方向停止的最小速度

# 创建球和边界框
ball = Ball(
    WIDTH // 2, HEIGHT // 2, 13, [12, -17]
)  # 创建小球对象，初始位置在屏幕中心，半径为10，速度为[40, -55]
box = Box(
    (WIDTH - 600) // 2, (HEIGHT - 400) // 2, 600, 400
)  # 创建边界框对象，位于屏幕中心，宽度为600，高度为400

running = True
while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:  # 如果点击关闭窗口按钮
            running = False  # 结束主循环

    # 移动小球
    ball.move(
        gravity, air_resistance_coeff, friction_coeff, box.rect.bottom
    )  # 根据物理规则移动小球

    # 边界框碰撞
    if ball.y + ball.radius >= box.rect.bottom:  # 如果小球与底部边界碰撞
        ball.velocity[1] = (
            -ball.velocity[1] * energy_loss_coeff
        )  # 垂直速度反弹并损失能量
        ball.y = box.rect.bottom - ball.radius  # 更新小球位置到边界上
        if abs(ball.velocity[0]) > min_horizontal_speed:  # 如果水平速度大于最小值
            ball.velocity[0] -= (
                friction_coeff if ball.velocity[0] > 0 else -friction_coeff
            )  # 减小水平速度
        else:
            ball.velocity[0] = 0  # 水平速度为0

    # 停止垂直方向的弹跳
    if (
        abs(ball.velocity[1]) < min_vertical_speed
        and ball.y + ball.radius >= box.rect.bottom - 1
    ):  # 如果垂直速度小于最小值且小球在底部边界上
        ball.velocity[1] = 0  # 垂直速度为0

    # 左右边界碰撞
    if (
        ball.x - ball.radius <= box.rect.left or ball.x + ball.radius >= box.rect.right
    ):  # 如果小球与左右边界碰撞
        ball.velocity[0] = (
            -ball.velocity[0] * energy_loss_coeff
        )  # 水平速度反弹并损失能量
        if ball.x < box.rect.left + ball.radius:  # 如果小球在左边界内
            ball.x = box.rect.left + ball.radius  # 更新小球位置到左边界上
        elif ball.x > box.rect.right - ball.radius:  # 如果小球在右边界内
            ball.x = box.rect.right - ball.radius  # 更新小球位置到右边界上

    # 上边界碰撞
    if ball.y - ball.radius <= box.rect.top:  # 如果小球与顶部边界碰撞
        ball.velocity[1] = (
            -ball.velocity[1] * energy_loss_coeff
        )  # 垂直速度反弹并损失能量
        ball.y = box.rect.top + ball.radius  # 更新小球位置到顶部边界上

    # 清屏
    screen.fill(WHITE)  # 用白色填充屏幕

    # 绘制球和边界框
    ball.draw(screen)  # 绘制小球
    box.draw(screen)  # 绘制边界框

    # 更新屏幕
    pygame.display.flip()  # 更新显示

    # 控制帧率
    clock.tick(60)  # 控制帧率为60帧每秒

pygame.quit()  # 退出pygame
sys.exit()  # 退出程序
