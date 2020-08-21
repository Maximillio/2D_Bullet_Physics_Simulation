#ifndef BULLETMANAGER_HPP
#define BULLETMANAGER_HPP

#include "Base/Bullet.hpp"
#include "SFML/System/Time.hpp"
#include "SFML/System/Vector2.hpp"
#include <list>
#include <mutex>

class BulletManager
{
public:
    BulletManager() noexcept;
    ~BulletManager() noexcept;
    void update(sf::Time time);
    /// \brief Creates a new bullet with a provided parameters.
    /// \details \param direction is expected in radians.
    void fire(sf::Vector2f position, float direction, float speed, sf::Time delay, sf::Time lifetime);
    std::list<Bullet>& getBullets();
private:
    std::list<Bullet> mBullets;
    std::list<std::list<Bullet>::iterator> mBulletsToRemove;
    std::mutex mMutex;
};

#endif // BULLETMANAGER_HPP
