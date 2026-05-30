#include "Zombie.h"
#include "Enums.h"
#include "GameEvent.h"
#include "ResourceManager.h"
#include "Config.h"
#include <algorithm>

// Sprite 路径
Zombie::Zombie(const std::string& textureKey, int lane, float hp, float speed, EventManager& bus)
    : Character(textureKey, lane, hp, bus), moveSpeed(speed)
{
    side = Side::Zombie;
}

// Spine 路径
Zombie::Zombie(Entity::SpineTag, const std::string& skelKey, int lane, float hp, float speed, EventManager& bus)
    : Character(Entity::SpineTag{}, skelKey, lane, hp, bus), moveSpeed(speed)
{
    side = Side::Zombie;

    // 初始化：僵尸向左走，播放 walk 动画
    if (spineComp) {
        spineComp->setFlipX(true);
        spineComp->playAnimation("idle", true, 0);
    }
}

void Zombie::update(float dt) {
    if (dying) {
        Character::update(dt);
        return;
    }

    if (!isEating) {
        moveGrid(sf::Vector2f(-moveSpeed * dt, 0.f));
    }

    // ── 动画状态驱动 ──────────────────────────────────────────────
    if (hasSpine() && spineComp) {
        if (isEating && !wasEating) {
            // 开始进食 → 切换到 attack 动画
            spineComp->playAnimation("attack", true, 0);
        } else if (!isEating && wasEating) {
            // 停止进食 → 回到 walk 动画
            spineComp->playAnimation("idle", true, 0);
        }
    }
    wasEating = isEating;
    isEating = false;

    if (timeSinceLastAttack < attackCooldown) timeSinceLastAttack += dt;

    Character::update(dt);
}

void Zombie::onCollision(Entity* other) {
    if (!other || !other->isActive()) return;

    if ((other->getSide() & Side::Plant) != 0) {
        // 不攻击正在死亡的植物
        if (auto* ch = dynamic_cast<Character*>(other)) {
            if (ch->isDying()) return;
        }
        isEating = true;
        if (timeSinceLastAttack >= attackCooldown) {
            DirectDamageData data = { other, attackDamage };
            eventBus.publish(GameEvent(EventType::ApplyDamage, data));
            timeSinceLastAttack = 0.f;
        }
    }
}

void Zombie::draw(sf::RenderWindow& window) {
    // 绘制僵尸本体（含 Spine 或 Sprite）
    Character::draw(window);

    // 绘制护甲精灵叠加（护甲始终使用 sf::Sprite，无论僵尸是否用 Spine）
    if (hasArmor()) {
        auto& armorTex = ResourceManager::getInstance().getTexture(equippedArmor->getTextureKey());
        sf::Sprite armorSprite(armorTex);
        auto texSize = armorTex.getSize();
        armorSprite.setOrigin(sf::Vector2f(texSize.x / 2.f, texSize.y / 2.f));
        float maxDim = static_cast<float>(std::max(texSize.x, texSize.y));
        float armorScale = (Grid::CELL_MIN * 0.45f) / maxDim;
        armorSprite.setScale(sf::Vector2f(armorScale, armorScale));

        // 护甲位置：基于 gridPos 计算（兼容 Sprite 和 Spine 模式）
        sf::Vector2f pos = Grid::gridToPixel(gridPos);
        armorSprite.setPosition(sf::Vector2f(pos.x, pos.y - Grid::CELL_HEIGHT * 0.55f));
        window.draw(armorSprite);
    }
}
