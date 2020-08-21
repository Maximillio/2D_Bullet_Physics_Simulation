#include "Bullet.hpp"
#include "Constants.hpp"
#include <cmath>
#include "Controllers/ResourceController.hpp"

Bullet::Bullet(sf::Vector2<float> pos,
               float direction,
               float velocity,
               sf::Time lifetime,
               sf::Time delay) noexcept
    : Object(ResourceController::instance().getTexture(Textures::Bullet), pos),
      // To avoid having angles above 360 degrees.
      mDirection( std::fmodf(direction, 2*Constants::Pi) ),
      mVelocity(velocity),
      mLifetime(lifetime),
      mDelay(delay),
      mBounceDelay(0),
      mIsExpired(false) {}

float Bullet::getDirection() const noexcept
{
    return mDirection;
}

void Bullet::setDirection(float direction) noexcept
{
    mDirection = direction;
}

float Bullet::getVelocity() const noexcept
{
    return mVelocity;
}

void Bullet::setVelocity(float velocity) noexcept
{
    mVelocity = velocity;
}

sf::Time Bullet::getLifetime() const noexcept
{
    return mLifetime;
}

void Bullet::setLifetime(const sf::Time& lifetime) noexcept
{
    mLifetime = lifetime;
}

sf::Time Bullet::getDelay() const noexcept
{
    return mDelay;
}

void Bullet::setDelay(const sf::Time& delay) noexcept
{
    mDelay = delay;
}

bool Bullet::isExpired() const noexcept
{
    return mIsExpired;
}

void Bullet::bounce(BouncePlane bounce) noexcept
{
    if ( mBounceDelay == 0 )
    {
        switch(bounce)
        {
            case BouncePlane::Horisontal:
                mDirection = std::fmodf( ( 3*Constants::Pi - mDirection ), 2*Constants::Pi );
            break;
            case BouncePlane::Vertical:
                mDirection =  2*Constants::Pi - mDirection;
            break;
        }
        mBounceDelay = 3;
    }
    else
    {
        mBounceDelay -= 1;
    }
}

void Bullet::update(sf::Time delta) noexcept
{
    if (mLifetime > sf::Time::Zero)
    {
        // Check lifetime.
        mLifetime -= delta;
        if (mLifetime <= sf::Time::Zero)
        {
            mIsExpired = true;
            mLifetime = sf::Time::Zero;
        }
        // Check delay.
        if (mDelay > sf::Time::Zero)
        {
            if (delta < mDelay)
            {
                mDelay -= delta;
                return;
            }
            else
            {
                // In case if delay is smaller than a time step.
                delta -= mDelay;
                mDelay = sf::Time::Zero;
            }
        }
        // The Bounce delay should decay over time.
        if (mBounceDelay != 0) --mBounceDelay;
        // Position increment.
        float move = mVelocity * delta.asSeconds();
        sf::Vector2f increment = {move * ( sinf(mDirection) ), move * (- cosf(mDirection) )};
        setPoisition(getPoisition() + increment);
    }
}
