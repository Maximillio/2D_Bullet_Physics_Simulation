#include "MainController.hpp"
// Controllers.
#include "ResourceController.hpp"
#include "CollisionController.hpp"
// Managers
#include "Managers/BulletManager.hpp"
#include "Managers/WallManager.hpp"
// SFML.
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Window/Event.hpp"
#include "SFML/System/Clock.hpp"
#include "SFML/System/Sleep.hpp"
#include "SFML/System/Thread.hpp"
// ImGui.
#include "imgui.h"
#include "imgui-SFML.h"
// General.
#include "Constants.hpp"

MainController::MainController()
    : mBulletManager(nullptr),
      mWallManager(nullptr),
      mRenderWindow(nullptr),
      mBulletDirection(Constants::MinDegree),
      mBulletVelocity(Constants::MinVelocity),
      mBulletDelay(Constants::MinDelay),
      mBulletLifetime(Constants::MaxLifetime),
      mRandomFireState(Constants::RandomFireOff),
      mErrorFile(nullptr),
      mRandomThread(nullptr)
{
    fopen_s(&mErrorFile, Constants::ErrorMessages::ErrorLogName, "w+");
    if ( !ResourceController::instance().loadTextures() )
    {
        printError(Constants::ErrorMessages::TexturesLoadFailed);
    }
    mBulletManager = new BulletManager();
    if(mBulletManager == nullptr)
    {
        printError(Constants::ErrorMessages::BulletManagerInitFailed);
        throw std::bad_alloc();
    }
    mWallManager = new WallManager();
    if(mWallManager == nullptr)
    {
        printError(Constants::ErrorMessages::WallManagerInitFailed);
        throw std::bad_alloc();
    }
}

void MainController::start()
{
    setup();
    sf::Clock deltaClock;
    // 60 FPS limit.
    sf::Time elapsedTime = sf::Time::Zero;
    while ( mRenderWindow->isOpen() )
    {
        processInput();
        // Process user input on UI;
        processUI( deltaClock.restart() );
        // Update bullets for the whole frame time to maintain integral movement.
        update(Constants::FrameTime);
        processCollisions();
        display();
        elapsedTime = deltaClock.getElapsedTime();
        // If a frame takes more than a Constants::FrameTime,
        // programm will run as fast as possible under 60 FPS.
        if (elapsedTime < Constants::FrameTime)
        {
            sf::sleep(Constants::FrameTime - elapsedTime);
        }
    }

    ImGui::SFML::Shutdown();
}

MainController::~MainController() noexcept
{
    if (mRandomThread != nullptr)
    {
        mRandomThread->terminate();
    }
    delete mRandomThread;
    delete mBulletManager;
    delete mWallManager;
    delete mRenderWindow;
    if (mErrorFile != nullptr)
    {
        fclose(mErrorFile);
    }
    delete mErrorFile;
}

void MainController::processUI(const sf::Time& delta)
{
    ImGui::SFML::Update(*mRenderWindow, delta);

    ImGui::Begin(Constants::UILabels::ControllPanel);

    if (ImGui::Button(Constants::UILabels::RegWalls))
    {
        mWallManager->regenerateWalls();
    }
    ImGui::Text(Constants::UILabels::InfoMessage);
    ImGui::Text(Constants::UILabels::BulletVar);
    ImGui::SliderInt(Constants::UILabels::BulletDir, &mBulletDirection, Constants::MinDegree, Constants::MaxDegree);
    ImGui::SliderFloat(Constants::UILabels::BulletVel, &mBulletVelocity, Constants::MinVelocity, Constants::MaxVelocity);
    ImGui::SliderFloat(Constants::UILabels::BulletDelay, &mBulletDelay, Constants::MinDelay, Constants::MaxDelay);
    ImGui::SliderFloat(Constants::UILabels::BulletLifetime, &mBulletLifetime, Constants::MinLifetime, Constants::MaxLifetime);
    if ( ImGui::Button("Toggle random fire.") )
    {
        if (mRandomThread == nullptr)
        {
            mRandomFireState = Constants::RandomFireOn;
            lauchRandomThread();
        }
        else
        {
            mRandomFireState = Constants::RandomFireOff;
            stopRandomThread();
        }
    }
    ImGui::Text("Random fire is: %s. ", mRandomFireState);
    ImGui::End();
}

void MainController::update(const sf::Time& delta) const noexcept
{
    mBulletManager->update(delta);
}

void MainController::processCollisions() noexcept
{
    for (auto& bullet : mBulletManager->getBullets() )
    {
        for ( auto& wall : mWallManager->getWalls() )
        {
            // If wall is considered destroyed, we just skip it.
            if ( wall.isDestroyed() ) continue;

            if ( CollisionController::isCollide( wall.getBoundingRect(), bullet.getBoundingRect() ) )
            {
                // Object posistion it ajusted to match it's geometrical center to have a proper bounce check.
                bullet.bounce( CollisionController::getBouncePlane( wall.getPoisition()
                                                                    + sf::Vector2f(static_cast<float>(wall.getSize().x)/2.0f, static_cast<float>(wall.getSize().y)/2.0f),
                                                                bullet.getPoisition()
                                                                    +  sf::Vector2f(static_cast<float>(bullet.getSize().x)/2.0f, static_cast<float>(bullet.getSize().y)/2.0f),
                                                                wall.getSize(),
                                                                bullet.getSize()
                                                                ) );
                wall.setDestroyed(true);
                break;
            }
        }
    }
}

void MainController::setup()
{
    mRenderWindow = new sf::RenderWindow(sf::VideoMode(Constants::ScreenWidth, Constants::ScreenHeight), Constants::UILabels::WindowTitle, sf::Style::Default);
    if (mRenderWindow != nullptr)
    {
        mRenderWindow->setVerticalSyncEnabled(true);
        ImGui::SFML::Init(*mRenderWindow);
    }
    else
    {
        printError(Constants::ErrorMessages::RenderWindowInitFailed);
        throw std::bad_alloc();
    }
}

void MainController::processInput() noexcept
{
    sf::Event event;
    while ( mRenderWindow->pollEvent(event) )
    {
        ImGui::SFML::ProcessEvent(event);

        switch(event.type)
        {
            case sf::Event::Closed:
               mRenderWindow->close();
            break;
            case sf::Event::MouseButtonPressed:
                if (event.mouseButton.button == sf::Mouse::Right)
                {
                    mBulletManager->fire( { static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y) },
                                         mBulletDirection*Constants::ToRadians,
                                         mBulletVelocity,
                                         sf::Time( sf::seconds(mBulletDelay) ),
                                         sf::Time( sf::seconds(mBulletLifetime) ) );
                }
            break;
            default:
            break;
        }
    }
}

void MainController::display() noexcept
{
    mRenderWindow->clear();

    for ( auto& wall : mWallManager->getWalls() )
    {
        mRenderWindow->draw(wall);
    }
    for ( auto& bullet : mBulletManager->getBullets() )
    {
        mRenderWindow->draw(bullet);
    }

    ImGui::SFML::Render(*mRenderWindow);
    mRenderWindow->display();
}

void MainController::printError(const char errorText[]) const noexcept
{
    if (mErrorFile != nullptr)
    {
        fprintf_s(mErrorFile, "%s", errorText);
    }
}

void MainController::lauchRandomThread() noexcept
{
    if (mRandomThread == nullptr)
    {
        mRandomThread = new sf::Thread
                        (
                            [&]()
                            {
                                srand( static_cast< unsigned int>( time(nullptr) ) );
                                while (true)
                                {
                                    sf::sleep( Constants::FrameTime * static_cast<float>( (std::rand()+30)%240 ) );
                                    mBulletManager->fire
                                            (
                                                // These values was not moved to the Constants due to their test nature.
                                                {static_cast<float>( (std::rand()%440) + 100 ), static_cast<float>( (std::rand()%240) + 300) },
                                                static_cast<float>( (std::rand())%360 ) ,
                                                static_cast<float>( (std::rand()%450) + 50 ) ,
                                                sf::seconds( static_cast<float>( (std::rand()%100)) / 10.0f ),
                                                sf::seconds( ( static_cast<float>( (std::rand()%180) + 20 ) / 10.0f ) )
                                            );
                                }
                            }
                        );
        if (mRandomThread != nullptr)
        {
            mRandomThread->launch();
        }
    }
}

void MainController::stopRandomThread() noexcept
{
    if (mRandomThread != nullptr)
    {
        mRandomThread->terminate();
        delete mRandomThread;
        mRandomThread = nullptr;
    }
}
