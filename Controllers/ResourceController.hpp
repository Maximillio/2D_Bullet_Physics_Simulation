#ifndef RESOURCECONTROLLER_HPP
#define RESOURCECONTROLLER_HPP

#include "Types/Textures.hpp"
#include "SFML/Graphics/Texture.hpp"
#include <map>

class ResourceController
{
public:
    static ResourceController& instance() noexcept;
    bool loadTextures() noexcept;
    const sf::Texture& getTexture(Textures textureId) const noexcept;
private:
    ResourceController() noexcept;
    std::map<Textures, sf::Texture> mTextures;
};

#endif // RESOURCECONTROLLER_HPP
