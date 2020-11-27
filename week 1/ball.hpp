#ifndef BALL_HPP
#define BALL_HPP

#include <SFML/Graphics.hpp>
#include "drawable.hpp"


class ball : public drawable{
private:
    sf::Vector2f position;
    float radius;
    sf::Color color;
    sf::Vector2f speed;

public:
    ball( sf::Vector2f position, float radius, sf::Color color ):
        position { position },
        radius { radius },
        color { color },
        speed( {1.0 , 1.0})

    {}

    void draw( sf::RenderWindow & window ) const{
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


    void detect_collision(std::vector< drawable *> others){
        sf::FloatRect ball_c = collision_area();
        for(auto & o : others){
            if(this != o){
                if(ball_c.intersects(o->collision_area())){
                    sf::Vector2f tempposself = position;
                    move(sf::Vector2f{1.0,0.0});
                    ball_c = collision_area();
                    if(!ball_c.intersects(o->collision_area())){
                        speed.x = speed.x * -1;
                    }
                    jump(tempposself);
                    move(sf::Vector2f{-1.0,0.0});
                    ball_c = collision_area();
                    if(!ball_c.intersects(o->collision_area())){
                        speed.x = speed.x * -1;
                    }
                    jump(tempposself);
                    move(sf::Vector2f{0.0,1.0});
                    ball_c = collision_area();
                    if(!ball_c.intersects(o->collision_area())){
                        speed.y = speed.y * -1;
                    }
                    jump(tempposself);
                    move(sf::Vector2f{0.0,-1.0});
                    ball_c = collision_area();
                    if(!ball_c.intersects(o->collision_area())){
                        speed.y = speed.y * -1;
                    }
                    jump(tempposself);
                }
            }
        }
    }


    void move( sf::Vector2f delta ){
        position += delta;
    }


    void jump( sf::Vector2f target ) {
        position = target;
    }

    sf::Vector2f get_speed(){
        return speed;
    }


};

#endif // BALL_HPP
