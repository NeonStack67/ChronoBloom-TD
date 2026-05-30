#include "NormalZombie.h"
#include "DatabaseHelper.h"

NormalZombie::NormalZombie(int lane, EventManager& bus)
    : Zombie(Entity::SpineTag{}, "NormalZombie", lane, 200.f, 0.5f, bus)
{
    const auto& stats = DataManager::getInstance().getZombieStats("NormalZombie");

    this->hp = static_cast<float>(stats.hp);
    this->maxHp = static_cast<float>(stats.hp);
    this->moveSpeed = stats.speed;
    this->attackDamage = static_cast<float>(stats.damage);
}
