#ifndef BULLET_HPP
#define BULLET_HPP

#include "Object.hpp"
#include "Types/BouncePlane.hpp"
#include "SFML/System/Time.hpp"

class Bullet : public Object
{
public:
    Bullet(sf::Vector2<float> pos       = {},
           float              direction = 0.0f,
           float              velocity  = 1.0f,
           sf::Time           lifetime  = sf::seconds(10.0f),
           sf::Time           delay     = sf::seconds(0.0f) ) noexcept;

    float getDirection() const noexcept;
    void setDirection(float direction) noexcept;
    float getVelocity() const noexcept;
    void setVelocity(float velocity) noexcept;
    sf::Time getLifetime() const noexcept;
    void setLifetime(const sf::Time& lifetime) noexcept;
    sf::Time getDelay() const noexcept;
    void setDelay(const sf::Time& delay) noexcept;
    bool isExpired() const noexcept;
    void bounce(BouncePlane bounce) noexcept;
    void update(sf::Time delta) noexcept;
private:
    /// \brief A direction is an angle in radians clockwise
    /// with 0 is pointing to the top of the screen.
    float mDirection;
    float mVelocity;
    sf::Time mLifetime;
    sf::Time mDelay;
    /// \brief Bounce delay is required to avoid multiple bounces
    /// on an adjust blocks.
    int mBounceDelay;
    /// \brief Is set when a lifetime of a bullet ran off.
    bool mIsExpired;
};

#endif // BULLET_HPP
