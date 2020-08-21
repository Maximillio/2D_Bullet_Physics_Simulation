#ifndef WALL_HPP
#define WALL_HPP

#include "Object.hpp"

class Wall : public Object
{
public:
    Wall(sf::Vector2f pos = {}) noexcept;
    bool isDestroyed() const noexcept;
    void setDestroyed(bool isDestroyed) noexcept;
protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
    bool mIsDestroyed;
};

#endif // WALL_HPP
