#pragma once
#include <any>
#include <SFML/Graphics.hpp>
#include <string>
#include "Enums.h"

class Entity;

// --- 1. ����ʵ��������� ---
struct SpawnEventData {
    std::string entityType;  // ��ͼ���ţ��� "PeaProjectile"����ֱ��ȥ ResourceManager ��ͼ
    sf::Vector2f position;   // ��������
    int lane;                // ���ں�����������
    uint32_t side;           // ��Ӫ���� Side::Plant��
};

// --- 2. ���徫׼����������磺�ӵ����У� ---
struct DirectDamageData {
    Entity* target;          // Ŀ����˭���Ѱ�����˵�ָ��ֱ�ӽ���ȥ��
    float damage;            // �۶���Ѫ
};

// --- 3. ��Χ�˺��������磺ӣ��ը���������˺��� ---
struct DamageEventData {
    sf::FloatRect targetArea; // ��ը��Χ����
    float damage;             // �˺���ֵ
    uint32_t targetMask;      // ���Ŀ�����루ը˭����
};

// --- 4. ���������ʵ������ͨ���� ---
struct EntityDeadData {
    Entity* entity;          // ˭���ˣ������ⲿ��ѯ���ߵ������Ӫ��
    sf::Vector2f position;   // �������ˣ��������ϵͳ����ҡ���Чϵͳ��������
};

// --- 6. ProduceSun ---
struct ProduceSunData {
    sf::Vector2f pixelPos;
    int value;
};

// --- 7. CollectResource ---
struct CollectResourceData {
    int value;
};

struct BoostEventData {
    int col;
    int row;
};

struct GameEvent {
    EventType type;      // Ƶ��
    std::any data;       // ���ݰ�����������������κ�һ�� struct��
    uint32_t senderId;   // ������ID����Ϊ0����ϵͳ���ͻ�׷�٣�

    GameEvent(EventType t, std::any d = {}, uint32_t sender = 0)
        : type(t), data(d), senderId(sender) {
    }
};