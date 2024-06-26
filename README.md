# 弹跳球模拟器

欢迎使用弹跳球模拟器，本项目提供两个版本的模拟器：一个使用`pygame`库构建，另一个使用`SDL2`库实现。这些模拟器展示了小球在一个固定的矩形框内，受到重力、摩擦力和空气阻力等物理效应作用下的动态行为。

- [开发信息](#开发信息)
- [特性概述](#特性概述)
- [安装指导](#安装指导)
- [使用说明](#使用说明)
- [文件说明](#文件说明)
- [程序结构](#程序结构)
- [未来工作](#未来工作)
- [许可与支持](#许可与支持)
- [团队与贡献](#团队与贡献)

## 开发信息

- **语言**: Python (使用`pygame`), C++ (使用`SDL2`)
- **开发者**: 周咏霖
- **日期**: 2024年4月14日 (`pygame`), 2024年4月18日 (`SDL2`)

## 特性概述

- **物理效应**: 包括重力影响、空气阻力、摩擦力模拟和能量损耗。
  - **重力影响**：小球具有垂直下落的行为，模拟真实世界中的重力效应。
  - **空气阻力**：小球在移动过程中会受到空气阻力的影响，影响其速度和加速度。
  - **摩擦力模拟**：当小球与边界底部接触时，小球会受到摩擦力的作用，进而改变其运动状态。
  - **能量损耗**：在与边界的碰撞过程中，小球会损失部分能量，这使得每次弹跳的高度逐渐减小。
- **用户交互**: (`SDL2`版本) 使用键盘方向键（上下左右）来控制小球的速度。
- **图形界面**: 实时可视化界面展示物理模拟过程，用户可以直观地观察到模拟中的物理现象。
- **边界碰撞**: 小球触及边界时发生反弹，速度和方向按物理定律调整。

## 安装指导

### 对于`pygame`版本：

为了运行这个模拟器，你需要先安装`pygame`库。确保你的计算机已经安装了Python，并且版本至少为3.x。可以通过以下命令安装`pygame`库：

```bash
pip install pygame
```

**注意**：如果你使用的是Linux或macOS，可能需要在命令前加上`sudo`用于获取权限。

### 对于`SDL2`版本：

安装`SDL2`库的方法取决于操作系统：

- **Ubuntu/Linux**:
  ```bash
  sudo apt-get install libsdl2-dev
  ```

- **macOS**（使用Homebrew）:
  ```bash
  brew install sdl2
  ```

- **Windows**:
  从SDL的官方网站下载开发库，并配置路径。

### 编译`SDL2`程序：

使用g++进行编译。确保在编译命令中包含SDL2的链接器选项：

```bash
g++.exe -g Ball.cpp -o Ball.exe -lmingw32 -lSDL2main -lSDL2 -mwindows
```

## 使用说明

### 运行`pygame`版本：

使用命令行切换到包含`Ball.py`的目录，执行以下命令启动程序：

```bash
python Ball.py
```

**程序操作**：模拟器启动后不需要任何用户输入，小球会自动开始在框内弹跳。

  例子：

    参数：

    gravity = 0.1   重力加速度

    energy_loss_coeff = 0.8   反弹能量损失系数

    friction_coeff = 0.02   摩擦系数

    air_resistance_coeff = 0.001   空气阻力系数

  运行演示：

  ![image](https://github.com/zylyes/homework/blob/main/Ball%20python/Ball1.gif)

**退出模拟器**：当你想退出模拟器时，简单地关闭图形界面窗口即可。

### 运行`SDL2`版本：

在编译完成后，运行生成的可执行文件：

```bash
./Ball.exe
```

**程序操作**：

运行程序后，小球将在窗口中自动弹跳。

  例子：
  
    参数：
    
    ball.vy += 0.1; // 微弱的重力加速度，模拟自然下落效应
    
    ball.vx *= 0.999; // 空气阻力
    
    ball.vy *= 0.999; // 空气阻力

    ball.vx *= -0.8;  // 反弹并损失能量

    ball.vx *= 0.98; // 摩擦力

  运行演示：

  ![image](https://github.com/zylyes/homework/blob/main/Ball%20C%2B%2B/Ball2.gif)

使用键盘的方向键来控制小球的移动。
  - **↑ 键**：增加向上的速度。
  - **↓ 键**：增加向下的速度。
  - **← 键**：增加向左的速度。
  - **→ 键**：增加向右的速度。

  例子：
  
    操作：
    
    ↑ ↑ ↓ ↓ → → ← ← 

  运行演示：

  ![image](https://github.com/zylyes/homework/blob/main/Ball%20C%2B%2B/Ball3.gif)

## 文件说明

### 对于`pygame`版本：
- `Ball.py`：主程序文件，包含小球和边界框的定义及游戏循环。

### 对于`SDL2`版本：
- `Ball.cpp`：主程序文件，包含小球和边界框的定义及游戏循环。

## 程序结构

### 对于`pygame`版本：
程序主要包含以下几个部分：

1. `Ball` 类：用于创建小球对象，包含了小球的位置、半径、速度和颜色以及绘制小球的方法。
2. `Box` 类：用于创建边界框对象，定义了框的位置、大小和颜色以及绘制边界框的方法。
3. `pygame` 时间循环：程序的主循环，处理事件和更新小球位置及状态。
4. 碰撞检测：检查小球是否达到边界，并相应改变速度方向和大小，模仿物理中的能量损失。

### 对于`SDL2`版本：
程序主要包含以下几个部分：

1. `Ball` 类/结构体：存储小球的位置、速度、半径和颜色信息。
2. `Box` 类/结构体：存储边界框的位置、尺寸和颜色信息。
3. 图形绘制：`drawBall`和`drawBox`函数负责在屏幕上绘制小球和边界框。
4. 主循环：处理事件和更新状态。

## 未来工作

- 增加用户界面，显示速度、位置等信息。
- 支持多球模拟，增加互动性。
- 优化物理模型，提升模拟真实性。

## 许可与支持

本软件是开源项目，使用前请确保遵守相关许可条款。如有问题或建议，请联系开发者或通过项目Issue页面反馈。

欢迎代码和功能的贡献，感谢您的使用和支持，希望本模拟器能帮助您更深入了解物理现象。

## 团队与贡献

目前这个项目由我个人维护。如果你有兴趣贡献代码或提供功能建议，非常欢迎你的加入！

感谢使用本模拟器，希望你在使用过程中有所获得，并对其中的物理现象有更深入的了解。
