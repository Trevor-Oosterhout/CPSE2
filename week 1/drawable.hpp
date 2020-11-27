#ifndef DRAWABLE_HPP
#define DRAWABLE_HPP

#include <SFML/Graphics.hpp>


class drawable {
protected:



public:
    virtual void draw(sf::RenderWindow & window) const;
    virtual sf::FloatRect collision_area() = 0;

};





#endif // DRAWABLE_HPP
