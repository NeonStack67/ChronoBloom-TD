#include "Entity.h"
#include "ResourceManager.h"
#include "Config.h"

// Sprite 路径：从 ResourceManager 获取纹理，初始化 sprite
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
    auto texSize = sprite->getTexture().getSize();
    sprite->setOrigin(sf::Vector2f(texSize.x / 2.f, texSize.y / 2.f));

    float maxDim = static_cast<float>(std::max(texSize.x, texSize.y));
    float scaleFactor = Grid::CELL_MIN / maxDim;
    sprite->setScale(sf::Vector2f(scaleFactor, scaleFactor));
}

// Spine 路径：不加载任何纹理，sprite 保持 nullopt
Entity::Entity(SpineTag, int l, EventManager& bus)
    : sprite(std::nullopt),
    active(true),
    side(Side::None),
    category(0),
    lane(l),
    gridPos(0.f, 0.f),
    eventBus(bus)
{
}

sf::Vector2f Entity::getPixelPosition() const {
    if (sprite.has_value()) {
        return sprite->getPosition();
    }
    return Grid::gridToPixel(gridPos);
}

sf::FloatRect Entity::getBounds() const {
    if (sprite.has_value()) {
        return sprite->getGlobalBounds();
    }
    // Spine 模式：基于 gridPos 返回格子大小的近似矩形
    sf::Vector2f center = Grid::gridToPixel(gridPos);
    return sf::FloatRect(
        center - sf::Vector2f(Grid::CELL_MIN * 0.5f, Grid::CELL_MIN * 0.5f),
        sf::Vector2f(Grid::CELL_MIN, Grid::CELL_MIN)
    );
}

void Entity::syncSprite() {
    if (!sprite.has_value()) return;
    sf::Vector2f pixel = Grid::gridToPixel(gridPos);
    sprite->setPosition(pixel);
}

void Entity::setSpriteScaleMultiplier(float mult) {
    if (!sprite.has_value()) return;
    auto texSize = sprite->getTexture().getSize();
    float maxDim = static_cast<float>(std::max(texSize.x, texSize.y));
    float scaleFactor = (Grid::CELL_MIN * mult) / maxDim;
    sprite->setScale(sf::Vector2f(scaleFactor, scaleFactor));
}

void Entity::draw(sf::RenderWindow& window) {
    if (sprite.has_value()) {
        window.draw(*sprite);
    }
}

