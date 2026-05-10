#include "Entity.h"
#include "ResourceManager.h"
#include "Config.h"

Entity::Entity(const std::string& textureKey, int l, EventManager& bus)
    : sprite(ResourceManager::getInstance().getTexture(textureKey)),
    active(true),
    side(Side::None),
    category(0),
    lane(l),
    gridPos(0.f, 0.f),
    eventBus(bus)
{
    // center sprite origin and scale to fit one cell
    auto texSize = sprite.getTexture().getSize();
    sprite.setOrigin(sf::Vector2f(texSize.x / 2.f, texSize.y / 2.f));

    float maxDim = static_cast<float>(std::max(texSize.x, texSize.y));
    float scaleFactor = Grid::CELL_MIN / maxDim;
    sprite.setScale(sf::Vector2f(scaleFactor, scaleFactor));
}

void Entity::syncSprite() {
    sf::Vector2f pixel = Grid::gridToPixel(gridPos);
    sprite.setPosition(pixel);
}

void Entity::setSpriteScaleMultiplier(float mult) {
    auto texSize = sprite.getTexture().getSize();
    float maxDim = static_cast<float>(std::max(texSize.x, texSize.y));
    float scaleFactor = (Grid::CELL_MIN * mult) / maxDim;
    sprite.setScale(sf::Vector2f(scaleFactor, scaleFactor));
}
