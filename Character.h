#pragma once
#include "Entity.h"
#include "Armor.h"
#include "SpineComponent.h"
#include <memory>
#include <string>
#include <cstdlib>

class Character : public Entity {
protected:
    float hp;
    float maxHp;

    // hurt visual feedback
    float hurtTimer = 0.f;
    static constexpr float hurtDuration = 0.15f;

    // wink (blink) timer -- works for all Spine entities
    float winkTimer    = 0.f;
    float winkInterval = 3.f;   // overwritten with random value in Spine constructor

    // armor component: independent, composable
    std::unique_ptr<Armor> equippedArmor;

    // Spine animation component (non-null only on Spine path)
    std::unique_ptr<SpineComponent> spineComp;

    // death animation in progress (delays actual destroy)
    bool  dying      = false;
    float dyingTimer = 0.f;
    static constexpr float dyingTimeout = 3.f;

    bool hasSpine() const { return spineComp != nullptr; }

    // update helpers -- each owns one responsibility
    void updateDying(float dt);
    void updateWink(float dt);
    void updateHurt(float dt);

public:
    // Sprite path
    Character(const std::string& textureKey, int lane, float initialHp, EventManager& bus);

    // Spine path: skelKey must already be loaded in SpineManager
    Character(Entity::SpineTag, const std::string& skelKey, int lane, float initialHp, EventManager& bus);

    // Non-copyable, non-movable (holds unique_ptr members + event bus reference)
    Character(const Character&) = delete;
    Character& operator=(const Character&) = delete;
    Character(Character&&) = delete;
    Character& operator=(Character&&) = delete;

    void update(float dt) override;
    virtual void takeDamage(float amount);
    virtual void die();
    void destroy() override;

    void equipArmor(std::unique_ptr<Armor> armor);
    bool   hasArmor()  const { return equippedArmor && !equippedArmor->isDestroyed(); }
    Armor* getArmor()  const { return equippedArmor.get(); }

    void draw(sf::RenderWindow& window) override;
    void drawHUD(sf::RenderWindow& window) override;

    float getHp()    const { return hp; }
    float getMaxHp() const { return maxHp; }
    bool  isDying()  const { return dying; }
};
