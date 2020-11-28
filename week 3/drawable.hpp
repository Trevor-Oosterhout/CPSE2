#ifndef DRAWABLE_HPP
#define DRAWABLE_HPP

#include <SFML/Graphics.hpp>
#include <fstream>


class drawable {
protected:



public:
    virtual void draw(sf::RenderWindow & window) const = 0;
    virtual sf::FloatRect collision_area() = 0;
    virtual bool contain( const sf::Vector2f & p) = 0;
    virtual bool contain( const sf::Vector2i & p) = 0;
    virtual void output_info( std::ostream& output ) = 0;
    virtual void jump( sf::Vector2f target ) = 0;
    virtual void move( sf::Vector2f delta ) = 0;
    virtual void jump( sf::Vector2i target ) = 0;
    virtual sf::Vector2f get_position() = 0;

};





#endif // DRAWABLE_HPP
