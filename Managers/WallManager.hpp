#ifndef WALLMANAGER_HPP
#define WALLMANAGER_HPP

#include "Base/Wall.hpp"
#include <list>

class WallManager
{
public:
    WallManager() noexcept;
    void regenerateWalls() noexcept;
    std::list<Wall>& getWalls() noexcept;
private:
    std::list<Wall> mWalls;
};

#endif // WALLMANAGER_HPP
