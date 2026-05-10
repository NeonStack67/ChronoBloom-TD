# PVZ_QianHeShiKong (植物大战僵尸：嵌合时空)

A hardcore, data-driven *Plants vs. Zombies* remake engine built with C++ and SQLite.
（一个基于 C++ 和 SQLite 数据驱动的硬核《植物大战僵尸》重制版引擎。）

## 🌟 Core Features (核心特性)

* **Data-Driven Architecture (数据驱动架构)**: 植物与僵尸的所有数值（生命值、伤害、阳光花费、冷却等）完全脱离代码硬编码，由 SQLite 数据库 (`pvz.db`) 统一接管，实现真正的引擎级解耦。
* **Event Bus System (事件总线系统)**: 底层采用发布-订阅模式（Pub-Sub）处理游戏内事件（如受伤、生成实体、产生阳光等），彻底消除对象间的网状耦合。
* **Component-Based Armor (组件化护甲)**: 僵尸防具（如路障、铁桶）以及植物护盾（如坚果大招）均采用独立的 `Armor` 组件实现，支持动态卸载与伤害溢出计算。
* **Modern C++**: 使用 C++17 标准，大量应用智能指针 (`std::unique_ptr`, `std::shared_ptr`) 进行内存管理，告别内存泄漏。

## 🛠️ Tech Stack (技术栈)

* **Language**: C++17
* **Graphics/Audio/Window**: SFML (Simple and Fast Multimedia Library)
* **Database**: SQLite3
* **Build System**: CMake

## 🚀 How to Build (如何构建)

1. Ensure you have **CMake**, **SFML**, and **SQLite3** installed on your system.
2. Clone this repository:
   ```bash
   git clone [https://github.com/NeonStack67/PVZ_QianHeShiKong.git](https://github.com/NeonStack67/PVZ_QianHeShiKong.git)
