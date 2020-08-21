#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP
#include "SFML/System/Time.hpp"
namespace Constants
{
    constexpr float Pi =  3.14159265358979323846f;
    const sf::Time FrameTime = sf::microseconds(12500);
    constexpr float ToRadians = Pi/180.0f;
    // Direction slider.
    constexpr int MinDegree = 0;
    constexpr int MaxDegree = 359;
    // Velocity slider.
    constexpr float MinVelocity = 20.0f;
    constexpr float MaxVelocity = 500.0f;
    // Delay slider.
    constexpr float MinDelay = 0.0f;
    constexpr float MaxDelay = 20.0f;
    // Lifetime slider.
    constexpr float MinLifetime = 1.0f;
    constexpr float MaxLifetime = 30.0f;
    // Random fire states.
    constexpr char RandomFireOff[] = "OFF";
    constexpr char RandomFireOn[] = "ON";
    // Screen resolution.
    constexpr unsigned int ScreenWidth = 800;
    constexpr unsigned int ScreenHeight = 640;
    namespace TexturesPath
    {
        constexpr char Wall[] = "Resources/Wall.jpg";
        constexpr char Bullet[] = "Resources/Bullet.png";
    }
    namespace UILabels
    {
        constexpr char WindowTitle[] = "Simulator";
        constexpr char ControllPanel[] = "Control panel";
        constexpr char RegWalls[] = "Regenerate walls";
        constexpr char InfoMessage[] = "Right click on the screen to create bullet with parameters:";
        constexpr char BulletVar[] = "Bullet variables:";
        constexpr char BulletDir[] = "- direction";
        constexpr char BulletVel[] = "- velocity";
        constexpr char BulletDelay[] = "- delay";
        constexpr char BulletLifetime[] = "- lifetime";
    }
    namespace ErrorMessages
    {
        constexpr char ErrorLogName[] = "ErrorLog.txt";
        constexpr char TexturesLoadFailed[] = "Unable to load some textures.\r\n";
        constexpr char BulletManagerInitFailed[] = "Unable to initialize a memory for a Bullet manager.\r\n";
        constexpr char WallManagerInitFailed[] = "Unable to initialize a memory for a Wall manager.\r\n";
        constexpr char RenderWindowInitFailed[] = "Unable to initialize a memory for a Render window.\r\n";
    }
}
#endif // CONSTANTS_HPP
