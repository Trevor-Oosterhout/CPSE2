#ifndef BALL_HPP
#define BALL_HPP

#include <SFML/Graphics.hpp>
#include "drawable.hpp"
#include <fstream>


class ball : public drawable{
private:
    sf::Vector2f position;
    float radius;
    sf::Color color;

public:
    ball( sf::Vector2f position, float radius, sf::Color color ):
        position { position },
        radius { radius },
        color { color }

    {}

    void draw( sf::RenderWindow & window ) const override{
        sf::CircleShape circle;
    	circle.setRadius(radius);
    	circle.setPosition(position);
        circle.setFillColor(color);
    	window.draw(circle);
    }

    sf::FloatRect collision_area() override{
        sf::CircleShape circle;
    	circle.setRadius(radius);
    	circle.setPosition(position);
        return circle.getGlobalBounds();
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
        output << "CIRCLE" << " ";
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
        output << radius << '\n';
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

#endif // BALL_HPP
