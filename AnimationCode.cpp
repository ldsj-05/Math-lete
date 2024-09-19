//CODE FOR ANIMATION.CPP 
#include <SFML/Graphics.hpp>
#include <cmath>

const float PI = 3.14159265;

int main() {
    //Generate window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Soccer Kick Visualization");

   //Check for texture existence 
    sf::Texture personTexture;
    if (!personTexture.loadFromFile("ball.png")) {
        return EXIT_FAILURE;
    }
    
    //Generate the person texture with position 
    sf::Sprite personSprite(personTexture);
    personSprite.setPosition(350, 140);
    personSprite.setScale(0.5f, 0.5f);

    //Generate a goal with its position
    sf::RectangleShape goal(sf::Vector2f(450, 100));
    goal.setFillColor(sf::Color(100, 100, 100));
    goal.setPosition(175, 500);

    //Generate the arrow with its position
    sf::RectangleShape arrow(sf::Vector2f(100, 5));
    arrow.setFillColor(sf::Color::Red);
    arrow.setOrigin(0, 2.5);
    arrow.setPosition(400, 300);

    float angle = 45.0;
    float angleIncrement = 0.1;

    //Check for font in files
    sf::Font font;
    if (!font.loadFromFile("Freedom-10eM.ttf")) {
        return EXIT_FAILURE;
    }




    //Set you win text and position
    sf::Text winText("YOU WIN", font, 155);
    winText.setFillColor(sf::Color::Yellow);
    winText.setPosition(20, 220);
  
    //Set game initialization text 
    sf::Text shootText("Press Enter to Shoot", font, 30);
    shootText.setFillColor(sf::Color::White);
    shootText.setPosition(210, 500);

    bool gameWon = false;

    //Checks for game state
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
                gameWon = true;
            }
        }

        window.clear(sf::Color::Green);

        if (gameWon) {
            window.draw(winText);
        } else {
            angle += angleIncrement;
            if (angle > 135 || angle < 45) {
                angleIncrement = -angleIncrement;
            }
            arrow.setRotation(angle);

            window.draw(personSprite);
            window.draw(goal);
            window.draw(arrow);
            window.draw(shootText);
        }

        window.display();
    }

    return EXIT_SUCCESS;
}