#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Card {
public:
    Card(const std::string& plantType, const std::string& displayName,
         int sunCost, const std::string& plantTextureKey,
         const std::string& cardBgTextureKey, float cooldown = 5.f);

    void update(float dt);
    void draw(sf::RenderWindow& window, sf::Vector2f position, sf::Vector2f size);

    const std::string& getPlantType() const { return plantType; }
    const std::string& getDisplayName() const { return displayName; }
    int getSunCost() const { return sunCost; }

    bool isReady() const { return cooldownTimer <= 0.f; }
    bool canUse(int currentSun) const { return isReady() && currentSun >= sunCost; }
    void startCooldown();

    bool isSelected() const { return selected; }
    void setSelected(bool sel) { selected = sel; }

private:
    std::string plantType;
    std::string displayName;
    int sunCost;
    std::string plantTextureKey;
    std::string cardBgTextureKey;

    float cooldownTimer = 0.f;
    float cooldownDuration = 5.f;
    bool selected = false;
};
