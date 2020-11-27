#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include <SFML/Graphics.hpp>
#include "drawable.hpp"


class rectangle : public drawable{
private:
    sf::Vector2f position, size;
    sf::Color color;


public:
    rectangle(sf::Vector2f position, sf::Vector2f size, sf::Color color ):
        position { position },
        size { size },
        color { color }
    {}


    void draw( sf::RenderWindow & window ) const{
        sf::RectangleShape rectangle( size );
        rectangle.setPosition( position );
        rectangle.setFillColor( color );
        window.draw( rectangle );
    }


    sf::FloatRect collision_area() override{
        sf::RectangleShape rectangle( size );
        rectangle.setPosition( position );
        return rectangle.getGlobalBounds();
    }




};


#endif // RECTANGLE_HPP
