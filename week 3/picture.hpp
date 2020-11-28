#ifndef PICTURE_HPP
#define PICTURE_HPP


#include <SFML/Graphics.hpp>
#include "drawable.hpp"
#include <string>
#include <fstream>
#include <iostream>


class picture : public drawable{
private:
    sf::Vector2f position;
    sf::Texture texture;
    sf::Sprite sprite;
    std::string file_name;

public:
    picture(sf::Vector2f position, std::string file_name):
        position{ position },
        file_name ( file_name )
    {}

    void draw( sf::RenderWindow & window ) const override{
        sf::Texture texture;
        sf::Sprite sprite;
        texture.loadFromFile( file_name );
        sprite.setTexture( texture );
        sprite.setPosition( position );
        window.draw( sprite );
    }


    sf::FloatRect collision_area() override{
        sf::Texture texture;
        sf::Sprite sprite;
        texture.loadFromFile( file_name );
        sprite.setTexture( texture );
        sprite.setPosition( position );
        return sprite.getGlobalBounds();
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
        output << "PICTURE" << " ";
        output << file_name << "\n";
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

#endif //PICTURE_HPP
