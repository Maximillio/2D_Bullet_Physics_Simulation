#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/System/Vector2.hpp"

namespace sf
{
    class Texture;
}

class Object : public sf::Drawable
{
public:
    Object(const sf::Texture& texture, sf::Vector2f pos = {}) noexcept;
    sf::Vector2f getPoisition() const noexcept;
    sf::Vector2u getSize() const noexcept;
    sf::FloatRect getBoundingRect() const noexcept;
    void setPoisition(sf::Vector2f pos) noexcept;
protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
    void checkAndFixSize() noexcept;
private:
    sf::Sprite mSprite;
    sf::Vector2<float> mPosition;
};

#endif // OBJECT_HPP
