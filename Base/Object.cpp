#include "Object.hpp"
#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/Graphics/Texture.hpp"

Object::Object(const sf::Texture& texture, sf::Vector2f pos) noexcept
    : mSprite(texture), mPosition(pos)
{
    mSprite.setPosition(mPosition);
}

void Object::setPoisition(sf::Vector2f pos) noexcept
{
    mPosition = pos;
    mSprite.setPosition(pos);
}

sf::Vector2f Object::getPoisition() const noexcept
{
    return mPosition;
}

sf::Vector2u Object::getSize() const noexcept
{
    return mSprite.getTexture()->getSize();
}

sf::FloatRect Object::getBoundingRect() const noexcept
{
    return sf::FloatRect( mPosition.x,
                         mPosition.y,
                         static_cast<float>(mSprite.getTexture()->getSize().x),
                         static_cast<float>(mSprite.getTexture()->getSize().y) );
}

void Object::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(mSprite, states);
}

