#include <iostream>
#include <functional>
#include <SFML/Graphics.hpp>
#include "drawable.hpp"
#include "ball.hpp"
#include "rectangle.hpp"
#include "player.hpp"


class action {
private:
	std::function< bool() > condition;
	std::function< void() > work;
public:
	action(
	   std::function< bool() > condition,
	   std::function< void() > work
	) : condition( condition ),
		work( work )
	{}

	action(
		sf::Keyboard::Key key,
		std::function< void() > work
	) :
		condition(
			[ key ]()->bool { return sf::Keyboard::isKeyPressed( key ); }
		),
		work(work)
	{}

	action(
		sf::Mouse::Button button,
		std::function< void() > work
	) :
		condition(
			[ button ]()->bool { return sf::Mouse::isButtonPressed( button ); }
		),
		work(work)
	{}

	action(
		bool x,
		std::function< void() > work
	) :
		condition( [ x ]()->bool { return x;}
		),
		work(work)
	{}

	void operator()(){
		if( condition() ){
			work();
		}
	}
};

int main( int argc, char *argv[] ){
	std::cout << "Starting application 01-05 array of actions\n";

	sf::RenderWindow window{ sf::VideoMode{ 640, 480 }, "SFML window" };
	ball pong{sf::Vector2f{ 320.0, 240.0 }, 25, sf::Color::White};
	rectangle left{sf::Vector2f{0.0, 0.0}, sf::Vector2f{10.0, 480}, sf::Color::Cyan};
	rectangle top{sf::Vector2f{0.0, 0.0}, sf::Vector2f{640.0, 10.0}, sf::Color::Cyan};
	rectangle right{sf::Vector2f{630.0,0.0}, sf::Vector2f{10.0,480}, sf::Color::Cyan};
	rectangle bottom{sf::Vector2f{0.0,470.0}, sf::Vector2f{640.0, 10.0}, sf::Color::Cyan};
	player doos{sf::Vector2f{150.0,240.0}, sf::Vector2f{30.0,30.0}, sf::Color::Green};

	std::vector< drawable* > objects = {&pong, &left, &right, &top, &bottom, &doos};

	action actions[] = {
		action( true,				 [&](){pong.detect_collision(objects);}),
		action( sf::Keyboard::Left,  [&](){ doos.move( sf::Vector2f( -1.0,  0.0 )); }),
		action( sf::Keyboard::Right, [&](){ doos.move( sf::Vector2f( +1.0,  0.0 )); }),
		action( sf::Keyboard::Up,    [&](){ doos.move( sf::Vector2f(  0.0, -1.0 )); }),
		action( sf::Keyboard::Down,  [&](){ doos.move( sf::Vector2f(  0.0, +1.0 )); }),
		action( sf::Mouse::Left,     [&](){ doos.jump( sf::Mouse::getPosition( window )); }),
		action( true, 				 [&](){ pong.move(pong.get_speed());})
	};

	while (window.isOpen()) {
		for( auto & action : actions ){
			action();
		}

		window.clear();
		pong.draw( window );
		left.draw( window );
		top.draw( window );
		right.draw( window );
		bottom.draw( window );
		doos.draw( window );
		window.display();

		sf::sleep( sf::milliseconds( 20 ));

        sf::Event event;
	    while( window.pollEvent(event) ){
			if( event.type == sf::Event::Closed ){
				window.close();
			}
		}
	}

	std::cout << "Terminating application\n";
	return 0;
}
