#include <iostream>
#include <cstdlib>
#include <ctime>
#include <SFML/Graphics.hpp>
#include <string>
#include <cmath>

enum Difficulty { EASY, MEDIUM, HARD };
Difficulty chosenDifficulty = EASY;
bool isCorrect = true;

bool runQuiz(sf::RenderWindow& window) {
    srand(static_cast<unsigned int>(time(0)));
    std::string choice;
    switch (chosenDifficulty) {
        case EASY: choice = "Easy"; break;
        case MEDIUM: choice = "Medium"; break;
        case HARD: choice = "Hard"; break;
        default: std::cerr << "Invalid difficulty choice!" << std::endl; return false;
    }

    int num1 = std::rand() % 10 + 3, num2 = std::rand() % 10 + 1, num3 = std::rand() % 10 + 1;
    int num4 = std::rand() % 3 + 1, num5 = std::rand() % 5 + 1, num6 = std::rand() % 10 + 1;

    int inputans;
    if (choice == "Easy") {
        std::cout << num1 << " + " << num2 << " + " << num3 << " = ";
        int ans = num1 + num2 + num3;
        std::cin >> inputans;
        if (inputans == ans) {
            std::cout << "Correct!\n";
            isCorrect = true;
            system("./animation");
            return true;
        } else {
            std::cout << "Incorrect.\n";
            isCorrect = false;
        }
    } else if (choice == "Medium") {
        std::cout << num1 << " * " << num6 << " = ";
        int ans = num1 * num6;
        std::cin >> inputans;
        if (inputans == ans) {
            std::cout << "Correct!\n";
            isCorrect = true;
            system("./animation");
            return true;
        } else {
            std::cout << "Incorrect.\n";
            isCorrect = false;
        }
    } else if (choice == "Hard") {
        std::cout << num5 << " ^ " << num4 << " = ";
        int ans = pow(num5, num4);
        std::cin >> inputans;
        if (inputans == ans) {
            std::cout << "Correct!\n";
            isCorrect = true;
            system("./animation");
            return true;
        } else {
            std::cout << "Incorrect.\n";
            isCorrect = false;
        }
    } else {
        std::cout << "Invalid choice.\n";
        isCorrect = false;
    }
    return false;
}

void optdisplayed() {
    std::cout << "Welcome to our game: Are You a Math-lete!\n";
    std::cout << "Instructions:\n";
    std::cout << "1) At the start of the game, you will be asked to select one of three difficulties: Easy, Medium, or Hard.\n";
    std::cout << "   - Easy: Simple addition and/or subtraction problems.\n";
    std::cout << "   - Medium: Multiplication and/or division problems.\n";
    std::cout << "   - Hard: Exponents and more complex problems.\n";
    std::cout << "2) After selecting a difficulty, you will be given a math problem to solve.\n";
    std::cout << "3) If you solve the math problem correctly, you will get the opportunity to score a goal.\n";
    std::cout << "4) To score a goal, you will direct an arrow to aim the ball and shoot it into a moving goal.\n";
    std::cout << "   - The goal will be moving side to side.\n";
    std::cout << "   - If you get the ball into the goal, you will earn a point.\n";
    std::cout << "5) Every time you score a point, the process will reset, and you will face a new math problem.\n";
    std::cout << "6) Continue solving problems and scoring goals to earn as many points as possible.\n";
    std::cout << "Good luck and have fun!\n";
    std::cout << "Press Enter to continue.\n";
    std::cin.get();
}

void runApp() {
    sf::RenderWindow renderWindow(sf::VideoMode(900, 600), "SFML Clickable Options");

    sf::Texture texture;
    if (!texture.loadFromFile("difscreen.jpg")) {
        std::cerr << "Failed to load texture 'difscreen.jpg'!" << std::endl;
        return;
    }

    sf::Sprite background(texture);
    float scaleX = static_cast<float>(renderWindow.getSize().x) / texture.getSize().x;
    float scaleY = static_cast<float>(renderWindow.getSize().y) / texture.getSize().y;
    background.setScale(scaleX, scaleY);

    sf::Font font;
    if (!font.loadFromFile("Freedom-10eM.ttf")) {
        std::cerr << "Failed to load font 'Freedom-10eM.ttf'!" << std::endl;
        return;
    }

    sf::Text loseText;
    loseText.setFont(font);
    loseText.setCharacterSize(50);
    loseText.setFillColor(sf::Color::Red);
    loseText.setString("You Lose");
    loseText.setPosition(300, 250);

    sf::FloatRect easyButtonRect(50.f, 280.f, 200.f, 50.f);
    sf::FloatRect mediumButtonRect(300.f, 280.f, 200.f, 50.f);
    sf::FloatRect hardButtonRect(550.f, 280.f, 200.f, 50.f);

    bool gameRunning = true;

    while (renderWindow.isOpen() && gameRunning) {
        sf::Event event;
        while (renderWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                renderWindow.close();
            } else if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePosition = sf::Mouse::getPosition(renderWindow);
                if (easyButtonRect.contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y))) {
                    chosenDifficulty = EASY;
                    std::cout << "Easy option clicked!" << std::endl;
                    if (!runQuiz(renderWindow)) {
                        renderWindow.clear();
                        renderWindow.draw(loseText);
                        renderWindow.display();
                        gameRunning = false;
                    }
                } else if (mediumButtonRect.contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y))) {
                    chosenDifficulty = MEDIUM;
                    std::cout << "Medium option clicked!" << std::endl;
                    if (!runQuiz(renderWindow)) {
                        renderWindow.clear();
                        renderWindow.draw(loseText);
                        renderWindow.display();
                        gameRunning = false;
                    }
                } else if (hardButtonRect.contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y))) {
                    chosenDifficulty = HARD;
                    std::cout << "Hard option clicked!" << std::endl;
                    if (!runQuiz(renderWindow)) {
                        renderWindow.clear();
                        renderWindow.draw(loseText);
                        renderWindow.display();
                        gameRunning = false;
                    }
                }
            }
        }

        renderWindow.clear();
        renderWindow.draw(background);
        renderWindow.display();
    }
}

int main() {
    optdisplayed();
    runApp();
    return 0;
}