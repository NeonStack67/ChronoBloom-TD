#include "NormalZombie.h"
#include "DatabaseHelper.h"

NormalZombie::NormalZombie(int lane, EventManager& bus)
// ���Ź̶�Ϊ "NormalZombie"
// Ѫ������Ϊ 200.f
// �ƶ��ٶȼ���Ϊ 20.f��ÿ�������ƶ� 20 ���أ�
    : Zombie("NormalZombie", lane, 200.f, 0.5f, bus)
{
    // 【新增】从数据中心读取真实的僵尸数据
    const auto& stats = DataManager::getInstance().getZombieStats("NormalZombie");

    this->hp = static_cast<float>(stats.hp);
    this->maxHp = static_cast<float>(stats.hp);
    this->moveSpeed = stats.speed;
    this->attackDamage = static_cast<float>(stats.damage);
    setSpriteScaleMultiplier(1.5f);
}