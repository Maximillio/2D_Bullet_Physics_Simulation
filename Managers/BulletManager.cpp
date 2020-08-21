#include "BulletManager.hpp"

BulletManager::BulletManager() noexcept {}

BulletManager::~BulletManager() noexcept
{
    mMutex.try_lock();
    mMutex.unlock();
}

void BulletManager::update(sf::Time time)
{
    mMutex.lock();
    for (auto it = mBullets.begin(); it != mBullets.end(); ++it)
    {
        it->update(time);
        if ( it->isExpired() ) mBulletsToRemove.push_back(it);
    }
    for (auto& it : mBulletsToRemove)
    {
        mBullets.erase(it);
    }
    mBulletsToRemove.clear();
    mMutex.unlock();
}

void BulletManager::fire(sf::Vector2f position, float direction, float speed, sf::Time delay, sf::Time lifetime)
{
    mMutex.lock();
    mBullets.push_back( Bullet(position, direction, speed, lifetime, delay) );
    mMutex.unlock();
}

std::list<Bullet>& BulletManager::getBullets()
{
    return mBullets;
}
