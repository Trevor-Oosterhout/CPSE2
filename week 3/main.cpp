#include <iostream>
#include <functional>
#include <SFML/Graphics.hpp>
#include <string>
#include <exception>
#include "exception.hpp"
#include "drawable.hpp"
#include "ball.hpp"
#include "rectangle.hpp"
#include "factory.hpp"
#include "picture.hpp"



int main( int argc, char *argv[] ){
	std::vector< drawable* > objects = {};
	std::ifstream input("config.txt");
	try{
		for(;;){
			objects.push_back(drawable_object_read(input));
		}
	} catch(end_of_file &){

	} catch(std::exception & error ){
		std::cout << error.what();
		return 1;
	}

	sf::RenderWindow window{ sf::VideoMode{ 640, 480 }, "SFML window" };

	while (window.isOpen()) {

		for(auto & o : objects){
			if(sf::Mouse::isButtonPressed(sf::Mouse::Left)
				&& o->contain(sf::Mouse::getPosition( window ))
			){
				while(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
					o->jump(sf::Mouse::getPosition( window ));
					window.clear();
					for(auto & o : objects){
						o->draw( window );
					}
					window.display();
				}

			}


		}

		window.clear();
		for(auto & o : objects){
			o->draw( window );
		}
		window.display();

		sf::sleep( sf::milliseconds( 20 ));

        sf::Event event;
	    while( window.pollEvent(event) ){
			if( event.type == sf::Event::Closed ){
				window.close();
			}
		}
	}
	std::ofstream output("config.txt");
	for(auto & o : objects){
		o->output_info( output );
	}
	std::cout << "Terminating application\n";
	return 0;
}
