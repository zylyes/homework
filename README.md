# Ball.py
时间:2024/04/17
作者:周咏霖
#
这是一个简单的弹跳球模拟器，它允许你在一个边界框内自由移动一个小球，并模拟了重力、空气阻力和摩擦力等物理效应。
#
#安装:
# 1.确保你已经安装了pygame库。如果没有，你可以使用pip安装:
#   ```
#   pip install pygame
#   ```
# 2.运行这个文件，不需要任何其他依赖项。
#
#使用:
# 1.运行这个程序，它将启动一个窗口，显示一个边界框和一个小球。
# 2.你可以使用键盘的箭头键来控制小球的移动。
# 3.当小球接触到边界框的顶部、底部、左侧或右侧时，它将反弹回来。
# 4.你可以通过改变`GRAVITY`、`RESISTANCE`和`SPEED`变量的值来调整模拟的物理效应。
#
#示例:
# 1. ```
#   GRAVITY = 0
#   RESISTANCE = 0.95
#   SPEED = 5
#   ```
#   这将使小球在没有重力的情况下移动，空气阻力为95%,速度为5。
#
# 2. ```
#   GRAVITY = 1
#   RESISTANCE = 1
#   SPEED = 10
#   ```
#   这将使小球在有重力的情况下移动，空气阻力为100%,速度为10。
#
#贡献:
#周咏霖-编写了这个简单的弹跳球模拟器。

为了更好地理解和使用这个代码，你可以阅读以下内容:

1. `pygame`库:这是一个用于开发2D游戏的库，它提供了一系列的函数和类，用于处理游戏的图形、声音和输入等。
2. `math`库:这个库提供了许多数学函数，如`degrees`和`atan2`，用于处理角度和反正切。
3. `sys`模块:这个模块提供了一些系统相关的功能，如`exit()`函数，用于退出程序。
4.物理效应:在这个代码中，你可以调整`GRAVITY`(重力)、`RESISTANCE`(空气阻力)和`SPEED`(速度)变量的值，以改变模拟的物理效应。

希望这个readme能帮助你更好地理解和使用这个代码。
