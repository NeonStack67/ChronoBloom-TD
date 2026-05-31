#pragma once
#include <string>
#include <sqlite3.h>
#include <iostream>
#include <stdexcept>
#include <unordered_map>

struct PlantStats {
    int hp = 100;
    int damage = 20;
    int cost = 100;
    float cooldown = 7.5f;
};

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
            std::cerr << "[DataManager] Cannot open database\n";
            return;
        }

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

        const char* zSql = "SELECT name, hp, damage, speed FROM zombies;";
        sqlite3_stmt* zStmt;
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
        }

        sqlite3_close(db);
    }

    const PlantStats& getStats(const std::string& name) const {
        auto it = plantRegistry.find(name);
        if (it == plantRegistry.end()) {
            throw std::runtime_error("[DataManager] Plant not found: " + name);
        }
        return it->second;
    }

    const ZombieStats& getZombieStats(const std::string& name) const {
        auto it = zombieRegistry.find(name);
        if (it == zombieRegistry.end()) {
            throw std::runtime_error("[DataManager] Zombie not found: " + name);
        }
        return it->second;
    }

private:
    std::unordered_map<std::string, PlantStats> plantRegistry;
    std::unordered_map<std::string, ZombieStats> zombieRegistry;
};