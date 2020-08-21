#ifndef MAINCONTROLLER_HPP
#define MAINCONTROLLER_HPP

#include <iostream>

class BulletManager;
class WallManager;
namespace sf
{
    class RenderWindow;
    class Time;
    class Thread;
}

class MainController
{
public:
    MainController();
    void start();
    ~MainController() noexcept;
private:
    void setup();
    void processInput() noexcept;
    void processUI(const sf::Time& delta);
    void update(const sf::Time& delta) const noexcept;
    void processCollisions() noexcept;
    void display() noexcept;
    void printError(const char errorText[]) const noexcept; 
    void lauchRandomThread() noexcept;
    void stopRandomThread() noexcept;
private:
    // Managers.
    BulletManager* mBulletManager;
    WallManager* mWallManager;
    // Display objects.
    sf::RenderWindow* mRenderWindow;
    // UI variables.
    int mBulletDirection;
    float mBulletVelocity;
    float mBulletDelay;
    float mBulletLifetime;
    const char* mRandomFireState;
    // File outputs.
    FILE* mErrorFile;
    /// \brief A thread to call BulletManager::fire at random moments of time.
    sf::Thread* mRandomThread;
};

#endif // MAINCONTROLLER_HPP
