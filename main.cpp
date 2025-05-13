#include <iostream> 
#include <vector> 
#include <string>
#include <algorithm>
#include <fstream>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <chrono>
using namespace std;

class physics_object {
public:
    physics_object() = default;

    void add_force(float amount_of_force) {
       current_acting_force = amount_of_force;         
    }

    void update(double time_delta) {
        // move the object each frame.
        // this means you have to update the velocity of it, and get a new position
        // after this is done, you should update where it is located on the screen.


        auto accel = current_acting_force * mass * time_delta;
        velocity = velocity + accel;

        vertical_velocity += gravity * time_delta;

        position_x = position_x + (velocity * time_delta); // we need to multiply velocity by time delta else its m/s
        position_y += vertical_velocity * time_delta;

        velocity -= velocity * friction_coeff * time_delta; // reduce speed cuz friction
    }

    auto get_vec2(){

        auto val = sf::Vector2(position_x, position_y);

        return val;
    }
    void check_edge_collision(double time_delta, float window_width, float window_height){ // check if the ball collides with the edges of the window

        if (position_x + 100.f > window_width) {
            position_x = window_width - 100.f;
            velocity *= -restitution_coeff;
        }

        if (position_x < 0) {
            position_x = 0;
            velocity *= -restitution_coeff;
        }

        if (position_y + 100.f > window_height) {
            position_y = window_height - 100.f;
            vertical_velocity *= -restitution_coeff;
        }

        if (position_y < 0) {
            position_y = 0;
            vertical_velocity *= -restitution_coeff;
        }
    }

    void check_object_collision(double time_delta, float rectangle_x, float rectangle_y, float rectangle_width, float rectangle_height){

        if (position_x + 100.f > rectangle_x){
            position_x = rectangle_x - 100.f;
            velocity *= -restitution_coeff;
        }

        if (position_y + 100.f > rectangle_y){
            position_y = rectangle_y - 100.f;
            vertical_velocity *= -restitution_coeff;
        }

    }

    float current_acting_force = 0;
    float position_x = 0;
    float position_y = 0;
    float velocity = 0;
    float vertical_velocity = 0;
    float mass = 10; // how much it weighs
    float friction_coeff = 0.1; // how much to reduce velocity as it slides
    float restitution_coeff = 0.7;  // how much to reduce velocity when it hits something
    float gravity = 9.8;

};


int WinMain(){

    sf::RenderWindow window(sf::VideoMode({800,600}), "Physics Engine");
    const sf::Font font("ui_resources/arial.ttf");

    auto physics_ball = physics_object();

    sf::Text log_x(font, "x: " + std::to_string(physics_ball.position_x), 20);
    log_x.setFillColor(sf::Color::Black);
    log_x.setPosition(sf::Vector2f(5.f, 20.f));

    sf::Text log_y(font, "y: " + std::to_string(physics_ball.position_y), 20);
    log_y.setFillColor(sf::Color::Black);
    log_y.setPosition(sf::Vector2f(5.f, 40.f));

    sf::CircleShape ball(50.f);
    ball.setFillColor(sf::Color::Blue);
    ball.setPosition(physics_ball.get_vec2());

    sf::RectangleShape barrier_obj({100.f, 40.f});
    barrier_obj.setFillColor(sf::Color::Red);
    barrier_obj.setPosition({500.f, 500.f});

    auto timestep = chrono::high_resolution_clock::now(); 


    while (window.isOpen()){
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>()){
                window.close();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)){
                physics_ball.add_force(5.f);
            }
        }

        auto timenow = chrono::high_resolution_clock::now();
        chrono::duration<double> elapsed_time = timenow - timestep;
        timestep = timenow;
        double time_delta = elapsed_time.count(); // time since last frame
        physics_ball.check_edge_collision(time_delta, window.getSize().x, window.getSize().y);
        physics_ball.check_object_collision(time_delta,barrier_obj.getPosition().x, barrier_obj.getPosition().y, barrier_obj.getSize().x, barrier_obj.getSize().y);


        physics_ball.update(time_delta);
        ball.setPosition(physics_ball.get_vec2());

        log_x.setString("x: " + std::to_string(physics_ball.position_x));
        log_y.setString("y: " + std::to_string(physics_ball.position_y));

        window.clear(sf::Color::White); // set bg colour to white

        window.draw(ball);
        window.draw(log_x);
        window.draw(log_y);
        window.draw(barrier_obj);

        window.display();
    }


    return 0;
}