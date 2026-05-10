#include "Wallnut.h"
#include "Armor.h"
#include "GameEvent.h"
#include "DatabaseHelper.h"

Wallnut::Wallnut(int lane, EventManager& bus)
    : Plant("Wallnut", lane, 1000.f, bus)
{
    // 从数据中心读取数值（再次注意横杠！）
    const auto& stats = DataManager::getInstance().getStats("Wallnut");

    this->hp = static_cast<float>(stats.hp);
    this->maxHp = static_cast<float>(stats.hp);
}

bool Wallnut::canBoost() const {
    return true;
}

void Wallnut::onBoost() {
    Plant::onBoost();
    boostTimer = BOOST_DURATION;
    equipArmor(std::make_unique<Armor>("WallnutShell", "Wallnut", ARMOR_HP));
}

void Wallnut::update(float dt) {
    if (isBoosted()) {
        boostTimer -= dt;
        if (boostTimer <= 0.f) {
            endBoost();
        }
    }
    Character::update(dt);
}
