#include "PeaProjectile.h"
#include "Enums.h"
#include "Config.h"

PeaProjectile::PeaProjectile(const sf::Vector2f& pos, int lane, uint32_t ownerSide, EventManager& bus)
    : Projectile("PeaProjectile", ownerSide, lane, sf::Vector2f(5.0f, 0.f), 20.f, Side::Zombie, bus)
{
    setGridPos(pos);
    // pea is smaller than a full cell: scale to 0.3 of cell size
    auto texSize = sprite.getTexture().getSize();
    float maxDim = static_cast<float>(std::max(texSize.x, texSize.y));
    float scaleFactor = (Grid::CELL_MIN * 0.3f) / maxDim;
    sprite.setScale(sf::Vector2f(scaleFactor, scaleFactor));
}
