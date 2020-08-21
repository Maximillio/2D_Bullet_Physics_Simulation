#include "ResourceController.hpp"
#include "Constants.hpp"

ResourceController::ResourceController() noexcept
{
    // To return as an empty texture for an invalid texture Id in mTextures function.
    mTextures.insert( {Textures::None, {} } );
}

ResourceController& ResourceController::instance() noexcept
{
    static ResourceController controller;
    return controller;
}

bool ResourceController::loadTextures() noexcept
{
    bool ret = true;

    sf::Texture textureBase;
    // Load wall texture.
    ret = textureBase.loadFromFile(Constants::TexturesPath::Wall);
    mTextures.insert( {Textures::Wall, textureBase} );
    // Load bullet texture.
    ret = textureBase.loadFromFile(Constants::TexturesPath::Bullet);
    mTextures.insert( {Textures::Bullet, textureBase} );

    return ret;
}

const sf::Texture& ResourceController::getTexture(Textures textureId) const noexcept
{
    if ( mTextures.find(textureId) != mTextures.cend() )
    {
        return mTextures.at(textureId);
    }
    return mTextures.at(Textures::None);
}
