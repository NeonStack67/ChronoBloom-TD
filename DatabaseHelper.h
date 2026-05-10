#pragma once
#include <string>
#include <sqlite3.h>
#include <iostream>
#include <unordered_map>

struct PlantStats {
    int hp = 100;
    int damage = 20;
    int cost = 100;
    float cooldown = 7.5f;
};

// 【修复缺失 1】：在这里定义僵尸的数据结构！没有它编译器就会报 unknown type name
struct ZombieStats {
    int hp = 200;
    int damage = 10;
    float speed = 0.5f;
};

class DataManager {
public:
    static DataManager& getInstance() {
        static DataManager instance;
        return instance;
    }

    void loadAllData() {
        sqlite3* db;
        if (sqlite3_open("pvz.db", &db) != SQLITE_OK) {
            std::cerr << "无法打开数据库\n";
            return;
        }

        // --- 1. 加载植物数据 ---
        const char* sql = "SELECT name, hp, damage, cost, cooldown FROM plants;";
        sqlite3_stmt* stmt;
        if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
            while (sqlite3_step(stmt) == SQLITE_ROW) {
                std::string name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
                PlantStats s;
                s.hp = sqlite3_column_int(stmt, 1);
                s.damage = sqlite3_column_int(stmt, 2);
                s.cost = sqlite3_column_int(stmt, 3);
                s.cooldown = static_cast<float>(sqlite3_column_double(stmt, 4));
                plantRegistry[name] = s;
            }
            sqlite3_finalize(stmt);
        }

        // --- 2. 加载僵尸数据 ---
        const char* zSql = "SELECT name, hp, damage, speed FROM zombies;";
        sqlite3_stmt* zStmt;
        // 【修复缺失 2】：加上这个 if 和 while 循环，真正把僵尸数据从数据库读进内存！
        if (sqlite3_prepare_v2(db, zSql, -1, &zStmt, nullptr) == SQLITE_OK) {
            while (sqlite3_step(zStmt) == SQLITE_ROW) {
                std::string name = reinterpret_cast<const char*>(sqlite3_column_text(zStmt, 0));
                ZombieStats zs;
                zs.hp = sqlite3_column_int(zStmt, 1);
                zs.damage = sqlite3_column_int(zStmt, 2);
                zs.speed = static_cast<float>(sqlite3_column_double(zStmt, 3));
                zombieRegistry[name] = zs;
            }
            sqlite3_finalize(zStmt);
            std::cout << "DataManager: 成功从数据库加载了植物与僵尸数据！\n";
        }

        sqlite3_close(db);
    }

    const PlantStats& getStats(const std::string& name) const {
        if (plantRegistry.find(name) == plantRegistry.end()) {
            std::cerr << "\n[严重错误] 数据库中找不到植物: " << name << "！请检查 pvz.db 的 plants 表！\n" << std::endl;
            exit(-1);
        }
        return plantRegistry.at(name);
    }

    const ZombieStats& getZombieStats(const std::string& name) const {
        if (zombieRegistry.find(name) == zombieRegistry.end()) {
            std::cerr << "\n[严重错误] 数据库中找不到僵尸: " << name << "！请检查 pvz.db\n" << std::endl;
            exit(-1);
        }
        return zombieRegistry.at(name);
    }

private:
    std::unordered_map<std::string, PlantStats> plantRegistry;
    std::unordered_map<std::string, ZombieStats> zombieRegistry;
};