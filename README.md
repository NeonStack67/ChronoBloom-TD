# ChronoBloom TD（嵌合时空塔防）

ChronoBloom TD is a C++/SFML tower-defense prototype inspired by classic lane-based strategy games.

本项目是一个使用 C++17、SFML 和 SQLite 构建的塔防游戏原型。  
它不是官方 Plants vs. Zombies 重制版，也不是商业项目，而是一个用于学习游戏架构、数据驱动设计、事件系统和 C++ 项目组织的个人学习项目。

## Core Idea（项目目标）

The goal of this project is to build a small but extensible tower-defense engine.

项目主要目标：

- 使用 C++17 组织游戏对象、植物、敌人、卡牌和地图逻辑
- 使用 SFML 实现窗口、图像、输入和基础渲染
- 使用 SQLite 管理植物、敌人、卡牌等游戏数据
- 尝试事件总线、组件化护甲、数据驱动架构等游戏开发概念
- 通过一个可运行的项目练习 C++ 工程能力

## Features（当前特性）

- Data-driven unit configuration using SQLite
- Basic plant and enemy data loading
- Card and card bar system
- Component-based armor prototype
- C++17 smart pointer usage
- SFML-based graphics/window foundation
- CMake build system

## Tech Stack（技术栈）

- Language: C++17
- Graphics / Window: SFML
- Database: SQLite3
- Build System: CMake

## Project Status（项目状态）

This project is currently an early-stage learning prototype.

当前项目仍处于早期学习阶段，重点不是做出完整商业游戏，而是逐步完成：

- 游戏窗口与资源加载
- 植物与敌人的基础逻辑
- 卡牌系统
- 简单关卡流程
- 数据库驱动的属性配置
- 可维护的 C++ 项目结构

## How to Build（如何构建）

Make sure you have the following dependencies installed:

- CMake
- SFML
- SQLite3
- A C++17 compatible compiler

Clone this repository:

```bash
git clone git@github.com:NeonStack67/ChronoBloom-TD.git
cd ChronoBloom-TD

Create a build directory:

mkdir build
cd build

Configure and build:

cmake ..
cmake --build .
```
Run the executable generated in the build directory.



## Disclaimer (声明)

This project is a fan-made, non-commercial learning project created for studying C++, SFML, SQLite, and game architecture.

It is not affiliated with, endorsed by, sponsored by, or connected to PopCap, EA, or the official Plants vs. Zombies franchise.

All related trademarks, names, and assets belong to their respective owners.

本项目仅用于学习 C++、SFML、SQLite 和游戏开发架构，不用于商业用途。

本项目与 PopCap、EA 或官方《Plants vs. Zombies》系列没有任何隶属、授权、赞助或合作关系。

所有相关商标、名称和素材版权归其各自所有者所有。