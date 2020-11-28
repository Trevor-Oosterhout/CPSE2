#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include <SFML/Graphics.hpp>
#include "drawable.hpp"
#include <fstream>


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


    void draw( sf::RenderWindow & window ) const override{
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


    bool contain( const sf::Vector2f & p ) override{
        sf::FloatRect hitbox = collision_area();
        return hitbox.contains(p.x, p.y);
    }

    bool contain( const sf::Vector2i & p) override{
        sf::FloatRect hitbox = collision_area();
        sf::Vector2f r = {
           static_cast< float >(p.x),
           static_cast< float >(p.y)};
         return hitbox.contains(r.x, r.y);
    }


    void output_info( std::ostream& output ) override{
        output << "(" << position.x << "," << position.y << ")" << " ";
        output << "RECTANGLE" << " ";
        const struct { const char * name; sf::Color col; } colors[]{
            { "yellow", sf::Color::Yellow },
            { "red", sf::Color::Red },
            { "blue", sf::Color::Blue },
            { "black", sf::Color::Black },
            { "white", sf::Color::White },
            { "green", sf::Color::Green },
            { "magenta", sf::Color::Magenta },
            { "cyan", sf::Color::Cyan },
            { "transparent", sf::Color::Transparent }
        };
        for( auto const & c : colors ){
            if( c.col == color){
                output << c.name << " ";
            }
        }
        output << "(" << size.x << "," << size.y << ")" << "\n";
    }


    void move( sf::Vector2f delta ) override{
        position += delta;
    }


    void jump( sf::Vector2f target ) override{
        position = target;
    }

    void jump( sf::Vector2i target ) override{
        jump( sf::Vector2f{
            static_cast< float >(target.x),
            static_cast< float >(target.y)
        });
    }

    sf::Vector2f get_position() override{
        return position;
    }

};


#endif // RECTANGLE_HPP
