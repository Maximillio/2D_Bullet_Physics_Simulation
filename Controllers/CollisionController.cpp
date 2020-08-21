#include "CollisionController.hpp"

CollisionController::CollisionController()
{

}

bool CollisionController::isCollide(const sf::FloatRect& wall, const sf::FloatRect& bullet) noexcept
{
    return wall.intersects(bullet);
}

BouncePlane CollisionController::getBouncePlane(const sf::Vector2f& wall,
                                                const sf::Vector2f& bullet,
                                                const sf::Vector2u& wallSize,
                                                const sf::Vector2u& bulletSize) noexcept
{
    // Distance between centers.
    float a = std::abs(wall.x - bullet.x);
    // Maximum distance between centers where a horisontal collision might occur.
    float b = wallSize.x/2.0f - bulletSize.x/2.0f;
    if (a <= b)
    {
        return BouncePlane::Horisontal;
    }
    else
    {
        return BouncePlane::Vertical;
    }
}
