#include "Card.h"
#include "ResourceManager.h"
#include "Config.h"

Card::Card(const std::string& plantType, const std::string& displayName,
           int sunCost, const std::string& plantTextureKey,
           const std::string& cardBgTextureKey, float cooldown)
    : plantType(plantType),
      displayName(displayName),
      sunCost(sunCost),
      plantTextureKey(plantTextureKey),
      cardBgTextureKey(cardBgTextureKey),
      cooldownDuration(cooldown)
{
}

void Card::update(float dt) {
    if (cooldownTimer > 0.f) {
        cooldownTimer -= dt;
        if (cooldownTimer < 0.f) cooldownTimer = 0.f;
    }
}

void Card::startCooldown() {
    cooldownTimer = cooldownDuration;
}

void Card::draw(sf::RenderWindow& window, sf::Vector2f position, sf::Vector2f size) {
    auto& resMgr = ResourceManager::getInstance();

    // draw card background
    sf::Sprite bgSprite(resMgr.getTexture(cardBgTextureKey));
    auto bgTexSize = bgSprite.getTexture().getSize();
    bgSprite.setScale(sf::Vector2f(size.x / bgTexSize.x, size.y / bgTexSize.y));
    bgSprite.setPosition(position);
    window.draw(bgSprite);

    // draw plant icon (upper portion of card)
    float iconAreaHeight = size.y * 0.55f;
    float iconPadding = 4.f;
    float iconMaxW = size.x - iconPadding * 2.f;
    float iconMaxH = iconAreaHeight - iconPadding;

    sf::Sprite iconSprite(resMgr.getTexture(plantTextureKey));
    auto iconTexSize = iconSprite.getTexture().getSize();
    float iconScale = std::min(iconMaxW / iconTexSize.x, iconMaxH / iconTexSize.y);
    iconSprite.setScale(sf::Vector2f(iconScale, iconScale));
    float iconW = iconTexSize.x * iconScale;
    float iconH = iconTexSize.y * iconScale;
    iconSprite.setPosition(sf::Vector2f(
        position.x + (size.x - iconW) / 2.f,
        position.y + iconPadding + (iconAreaHeight - iconPadding - iconH) / 2.f
    ));
    window.draw(iconSprite);

    // draw sun cost (bottom-left of card)
    auto& font = resMgr.getFont("default");
    sf::Text costText(font, std::to_string(sunCost), 10u);
    costText.setFillColor(sf::Color::Yellow);
    costText.setOutlineColor(sf::Color::Black);
    costText.setOutlineThickness(1.f);
    costText.setPosition(sf::Vector2f(position.x + 3.f, position.y + iconAreaHeight));
    window.draw(costText);

    // draw plant name (bottom of card, below cost)
    sf::Text nameText(font, displayName, 8u);
    nameText.setFillColor(sf::Color::White);
    nameText.setOutlineColor(sf::Color::Black);
    nameText.setOutlineThickness(0.5f);
    sf::FloatRect nameBounds = nameText.getLocalBounds();
    nameText.setPosition(sf::Vector2f(
        position.x + (size.x - nameBounds.size.x) / 2.f - nameBounds.position.x,
        position.y + size.y - 16.f
    ));
    window.draw(nameText);

    // draw cooldown overlay if on cooldown
    if (!isReady() && cooldownDuration > 0.f) {
        float ratio = cooldownTimer / cooldownDuration;
        sf::RectangleShape overlay(sf::Vector2f(size.x, size.y * ratio));
        overlay.setFillColor(sf::Color(0, 0, 0, 128));
        overlay.setPosition(position);
        window.draw(overlay);
    }

    // draw selection highlight
    if (selected) {
        sf::RectangleShape highlight(size);
        highlight.setFillColor(sf::Color(255, 255, 255, 60));
        highlight.setOutlineColor(sf::Color(255, 255, 100));
        highlight.setOutlineThickness(2.f);
        highlight.setPosition(position);
        window.draw(highlight);
    }
}
