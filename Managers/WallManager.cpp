#include "WallManager.hpp"

WallManager::WallManager() noexcept
{
    // Create wall segments.
    float xPosition = 64.0f;
    float yPosition = 64.0f;
    for (int i = 0; i < 7; ++i)
    {
        mWalls.push_back( Wall( {xPosition, yPosition} ) );
        xPosition += 64.0f;
    }
}

void WallManager::regenerateWalls() noexcept
{
    for(auto& wall : mWalls)
    {
        wall.setDestroyed(false);
    }
}

std::list<Wall>& WallManager::getWalls() noexcept
{
    return mWalls;
}
