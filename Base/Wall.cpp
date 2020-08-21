#include "Wall.hpp"
#include "Controllers/ResourceController.hpp"

Wall::Wall(sf::Vector2f pos) noexcept
    : Object(ResourceController::instance().getTexture(Textures::Wall), pos),
      mIsDestroyed(false) {}

void Wall::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (!mIsDestroyed)
    {
        Object::draw(target, states);
    }
}

bool Wall::isDestroyed() const noexcept
{
    return mIsDestroyed;
}

void Wall::setDestroyed(bool isDestroyed) noexcept
{
    mIsDestroyed = isDestroyed;
}
