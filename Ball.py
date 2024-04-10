import pygame

# 初始化pygame
pygame.init()

# 设置窗口大小和标题
screen_width = 60
screen_height = 600
screen = pygame.display.set_mode((screen_width, screen_height))
pygame.display.set_caption("小球弹跳模拟")

# 定义颜色
BLACK = (0, 0, 0)
RED = (255, 0, 0)

# 小球属性
ball_radius = 30
ball_x = screen_width // 2
ball_y = screen_height // 2
ball_speed_y = -12  # 初始速度向上
gravity = 0.1  # 重力加速度
energy_loss = 0.9  # 碰撞能量损失系数

# 时钟对象
clock = pygame.time.Clock()

# 主循环
running = True
start_ticks = pygame.time.get_ticks()  # 开始时间

while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

    # 计算总运行时间
    seconds = (pygame.time.get_ticks() - start_ticks) / 1000
    if seconds > 40:
        running = False

    # 更新小球位置
    ball_y += ball_speed_y
    ball_speed_y += gravity

    # 检测小球与边界的碰撞
    if ball_y >= screen_height - ball_radius:
        ball_y = screen_height - ball_radius
        ball_speed_y = -ball_speed_y * energy_loss
    elif ball_y <= ball_radius:
        ball_y = ball_radius
        ball_speed_y = -ball_speed_y * energy_loss

    # 清屏
    screen.fill((255, 255, 255))

    # 画边界
    pygame.draw.rect(screen, BLACK, pygame.Rect(0, 0, screen_width, screen_height), 1)

    # 画小球
    pygame.draw.circle(screen, RED, (ball_x, int(ball_y)), ball_radius)

    # 更新屏幕
    pygame.display.flip()

    # 控制游戏帧率
    clock.tick(60)

pygame.quit()