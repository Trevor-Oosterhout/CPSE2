#ifndef PLAYER_HPP
#define PLAYER_HPP


class player : public drawable{
private:
    sf::Vector2f position, size;
    sf::Color color;


public:
    player( sf::Vector2f position, sf::Vector2f size, sf::Color color ):
        position { position },
        size { size },
        color { color }
    {}

    void draw(sf::RenderWindow & window ) const override{
        sf::RectangleShape rectangle( size );
        rectangle.setPosition( position );
        rectangle.setFillColor( color );
        window.draw( rectangle );
    }


    void move( sf::Vector2f delta ){
        position += delta;
    }


    void jump( sf::Vector2f target ) {
           position = target;
    }

    void jump( sf::Vector2i target ){
        jump( sf::Vector2f{
            static_cast< float >(target.x),
            static_cast< float >(target.y)
        });
    }

    sf::FloatRect collision_area() override{
        sf::RectangleShape rectangle( size );
        rectangle.setPosition( position );
        return rectangle.getGlobalBounds();
    }


};


#endif // PLAYER_HPP
