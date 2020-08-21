#ifndef COLLISIONCONTROLLER_HPP
#define COLLISIONCONTROLLER_HPP

#include <SFML/Graphics/Rect.hpp>
#include "Types/BouncePlane.hpp"

class CollisionController
{
public:
    static bool isCollide(const sf::FloatRect& wall, const sf::FloatRect& bullet) noexcept;
    static BouncePlane getBouncePlane(const sf::Vector2f& wall,
                               const sf::Vector2f& bullet,
                               const sf::Vector2u& wallSize,
                               const sf::Vector2u& bulletSize) noexcept;
private:
    CollisionController();
};

#endif // COLLISIONCONTROLLER_HPP
