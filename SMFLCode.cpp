#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
    sf::RenderWindow renderWindow(sf::VideoMode(900, 600), "SFML Clickable Options");

    sf::Texture texture;
    if (!texture.loadFromFile("difscreen.jpg")) {
        std::cerr << "Failed to load texture 'difscreen.jpg'!" << std::endl;
        return 1; // Exit the program with an error code
    }

    sf::Sprite background(texture);


    float scaleX = static_cast<float>(renderWindow.getSize().x) / texture.getSize().x;
    float scaleY = static_cast<float>(renderWindow.getSize().y) / texture.getSize().y;
    background.setScale(scaleX, scaleY);

 
    sf::FloatRect easyButtonRect(50.f, 280.f, 200.f, 50.f);
    sf::FloatRect mediumButtonRect(300.f, 280.f, 200.f, 50.f);
    sf::FloatRect hardButtonRect(550.f, 280.f, 200.f, 50.f);

    bool isEasyClicked = false;
    bool isMediumClicked = false;
    bool isHardClicked = false;

    while (renderWindow.isOpen()) {
        sf::Event event;
        while (renderWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                renderWindow.close();
            else if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePosition = sf::Mouse::getPosition(renderWindow);

                // Check if mouse click is inside each button's rectangle
                if (easyButtonRect.contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y))) {
                    isEasyClicked = true;
                } else if (mediumButtonRect.contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y))) {
                    isMediumClicked = true;
                } else if (hardButtonRect.contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y))) {
                    isHardClicked = true;
                }
            }
        }

       
        if (isEasyClicked) {
            std::cout << "Easy option clicked!" << std::endl;
            isEasyClicked = false;
        } else if (isMediumClicked) {
            std::cout << "Medium option clicked!" << std::endl;
            isMediumClicked = false; // Reset click state
           
        } else if (isHardClicked) {
            std::cout << "Hard option clicked!" << std::endl;
            isHardClicked = false; // Reset click state
           
        }

       
        renderWindow.clear();

       
        renderWindow.draw(background);

       
        renderWindow.display();
    }

    return 0;
}