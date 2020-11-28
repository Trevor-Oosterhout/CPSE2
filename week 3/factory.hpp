#ifndef FACTORY_HPP
#define FACTORY_HPP


#include <iostream>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <string>
#include "drawable.hpp"
#include "ball.hpp"
#include "rectangle.hpp"
#include "picture.hpp"


std::ifstream & operator>>( std::ifstream & input, sf::Color & rhs ){
    std::string s;
    input >> s;
    const struct { const char * name; sf::Color color; } colors[]{
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

    for( auto const & color : colors ){
        if( color.name == s ){
            rhs = color.color;
            return input;
        }
    }

    if( s == "" ){
        throw end_of_file();
    }

    throw unknown_color( s );
}


std::ifstream & operator>>( std::ifstream & input, sf::Vector2f & rhs ){
    char c;
    if( ! ( input >> c )){ throw end_of_file(); }

    if( c != '(' ){ throw invalid_position( c ); }

    if( ! ( input >> rhs.x )){ throw end_of_file();}

    if( ! ( input >> c )){ throw end_of_file(); }

    if( ! ( input >> rhs.y )){ throw end_of_file(); }

    if( ! ( input >> c )){ throw end_of_file(); }

    if( c != ')' ){ throw invalid_position( c ); }

    return input;
}

drawable * drawable_object_read( std::ifstream & input ){
    sf::Vector2f position;
    std::string drawable_name;
    sf::Color color;
    float radius;
    sf::Vector2f size;
    std::string file_name;
    input >> position >> drawable_name;

    if( drawable_name == "CIRCLE" ){
        input >> color >> radius;
        return new ball(position, radius, color);
    }
    else if ( drawable_name == "RECTANGLE"){
        input >> color >> size;
        return new rectangle(position, size, color);
    }
    else if( drawable_name == "PICTURE" ){
        input >> file_name;
        return new picture(position, file_name);
    }
    else if ( drawable_name == ""){
        throw end_of_file();
    }

    throw unknown_shape( drawable_name );

}


#endif // FACTORY_HPP
