#include <iostream> 
#include <vector> 
#include <string>
#include <algorithm>
#include <fstream>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
using namespace std;

class physics_object {
public:
    physics_object() = default;

    void add_force(float amount_of_force) {
                
    }

    void update(double time_delta) {
        // move the object each frame.
        // this means you have to update the velocity of it, and get a new position
        // after this is done, you should update where it is located on the screen.



    }
    float position_x = 0;
    float position_y = 0; // can just ignore this if you are doing 1d only
    float velocity = 0;
    float mass = 0; // how much it weighs
    float friction_coeff = 0.1; // how much to reduce velocity as it slides
    float restitution_coeff = 0.05;  // how much to reduce velocity when it hits something

};


int WinMain(){

    sf::RenderWindow window(sf::VideoMode({800,600}), "Physics Engine");


    while (window.isOpen()){
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>()){
                window.close();
            }
        }
    }

    window.clear(sf::Color::White); // set bg colour to white

    window.display();

    return 0;
}