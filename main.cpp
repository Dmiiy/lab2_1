#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics/Text.hpp>
#include <iostream>
#include <memory>

using namespace sf;

// Structure for storing data of a radio button
struct RadioButton {
    RectangleShape shape;
    Text text;
    bool selected;
};

int main() {
    // Initialize the window
    RenderWindow window(VideoMode(800, 600), "SFML Radio Buttons and Smart Pointers");

    // Load the font
    Font font;
    if (!font.loadFromFile("C:\\Users\\dimak\\CLionProjects\\lab2_1\\fonts\\arial.ttf")) { // Replace "arial.ttf" with your font
        std::cerr << "Error loading font!" << std::endl;
        return 1;
    }

    // Create radio buttons
    RadioButton radioButtons[3];
    radioButtons[0].shape.setSize(Vector2f(20, 20));
    radioButtons[0].shape.setFillColor(Color::White);
    radioButtons[0].shape.setOutlineColor(Color::Black);
    radioButtons[0].shape.setOutlineThickness(1);
    radioButtons[0].shape.setPosition(100, 50);
    radioButtons[0].text.setFont(font);
    radioButtons[0].text.setString("Option 1 (Unique_ptr)");
    radioButtons[0].text.setCharacterSize(16);
    radioButtons[0].text.setFillColor(Color::Black);
    radioButtons[0].text.setPosition(radioButtons[0].shape.getPosition().x + radioButtons[0].shape.getSize().x + 10,
                                     radioButtons[0].shape.getPosition().y);
    radioButtons[0].selected = false;

    radioButtons[1].shape.setSize(Vector2f(20, 20));
    radioButtons[1].shape.setFillColor(Color::White);
    radioButtons[1].shape.setOutlineColor(Color::Black);
    radioButtons[1].shape.setOutlineThickness(1);
    radioButtons[1].shape.setPosition(100, 100);
    radioButtons[1].text.setFont(font);
    radioButtons[1].text.setString("Option 2 (Shared_ptr)");
    radioButtons[1].text.setCharacterSize(16);
    radioButtons[1].text.setFillColor(Color::Black);
    radioButtons[1].text.setPosition(radioButtons[1].shape.getPosition().x + radioButtons[1].shape.getSize().x + 10,
                                     radioButtons[1].shape.getPosition().y);
    radioButtons[1].selected = false;

    radioButtons[2].shape.setSize(Vector2f(20, 20));
    radioButtons[2].shape.setFillColor(Color::White);
    radioButtons[2].shape.setOutlineColor(Color::Black);
    radioButtons[2].shape.setOutlineThickness(1);
    radioButtons[2].shape.setPosition(100, 150);
    radioButtons[2].text.setFont(font);
    radioButtons[2].text.setString("Option 3 (Weak_ptr)");
    radioButtons[2].text.setCharacterSize(16);
    radioButtons[2].text.setFillColor(Color::Black);
    radioButtons[2].text.setPosition(radioButtons[2].shape.getPosition().x + radioButtons[2].shape.getSize().x + 10,
                                     radioButtons[2].shape.getPosition().y);
    radioButtons[2].selected = false;

    // Create input field
    RectangleShape inputField(Vector2f(200, 30));
    inputField.setFillColor(Color::White);
    inputField.setOutlineColor(Color::Black);
    inputField.setOutlineThickness(1);
    inputField.setPosition(100, 200);

    Text inputText;
    inputText.setFont(font);
    inputText.setString("Enter a number");
    inputText.setCharacterSize(16);
    inputText.setFillColor(Color::Black);
    inputText.setPosition(inputField.getPosition().x + 5, inputField.getPosition().y + 5);

    // Create "Create" button
    RectangleShape createButton(Vector2f(100, 30));
    createButton.setFillColor(Color::Green);
    createButton.setOutlineColor(Color::Black);
    createButton.setOutlineThickness(1);
    createButton.setPosition(350, 200);

    Text createText;
    createText.setFont(font);
    createText.setString("Create");
    createText.setCharacterSize(16);
    createText.setFillColor(Color::White);
    createText.setPosition(createButton.getPosition().x + 25, createButton.getPosition().y + 5);

    // Create "Delete" button
    RectangleShape deleteButton(Vector2f(100, 30));
    deleteButton.setFillColor(Color::Red);
    deleteButton.setOutlineColor(Color::Black);
    deleteButton.setOutlineThickness(1);
    deleteButton.setPosition(350, 250);

    Text deleteText;
    deleteText.setFont(font);
    deleteText.setString("Delete");
    deleteText.setCharacterSize(16);
    deleteText.setFillColor(Color::White);
    deleteText.setPosition(deleteButton.getPosition().x + 25, deleteButton.getPosition().y + 5);

    // Create output information window
    RectangleShape outputWindow(Vector2f(400, 100));
    outputWindow.setFillColor(Color::White);
    outputWindow.setOutlineColor(Color::Black);
    outputWindow.setOutlineThickness(1);
    outputWindow.setPosition(100, 300);

    Text outputText;
    outputText.setFont(font);
    outputText.setString("Information will be displayed here.");
    outputText.setCharacterSize(16);
    outputText.setFillColor(Color::Black);
    outputText.setPosition(outputWindow.getPosition().x + 5, outputWindow.getPosition().y + 5);

    // Variables for storing data
    std::string inputValue;
    std::shared_ptr<int> sharedPtr;
    std::unique_ptr<int> uniquePtr;
    std::weak_ptr<int> weakPtr;

    // Timer for button click effect
    Clock buttonClickTimer;
    float buttonClickDuration = 0.2f; // Duration of the button click effect in seconds

    // Main game loop
    while (window.isOpen()) {
        Event event;
        sf::Color LightGreen(0, 238, 144);
        sf::Color LightRed(2, 71, 76);
        sf::Color LightGray(1, 211, 211);
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }

            // Handle mouse click events
            if (event.type == Event::MouseButtonPressed) {
                // Check if any radio button is clicked
                for (int i = 0; i < 3; ++i) {
                    if (radioButtons[i].shape.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                        // Deselect other radio buttons
                        for (int j = 0; j < 3; ++j) {
                            radioButtons[j].selected = (i == j);
                        }
                        // Mark the selected button
                        radioButtons[i].shape.setFillColor(LightGray);
                    } else {
                        // Reset the color of unselected radio buttons
                        radioButtons[i].shape.setFillColor(Color::White);
                    }
                }

                // Check if the "Create" button is clicked
                if (createButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    // Start button click timer
                    buttonClickTimer.restart();
                    // Set the button color to light green
                    createButton.setFillColor(LightGreen);

                    // Check if a radio button is selected
                    bool selected = false;
                    for (int i = 0; i < 3; ++i) {
                        if (radioButtons[i].selected) {
                            selected = true;
                            break;
                        }
                    }

                    // Check if the input value is a valid number
                    bool validInput = true;
                    try {
                        int number = std::stoi(inputValue);
                    } catch (const std::exception& e) {
                        validInput = false;
                    }

                    if (selected && validInput) {
                        try {
                            int number = std::stoi(inputValue);
                            if (radioButtons[0].selected) {
                                uniquePtr.reset(new int(number));
                                outputText.setString("Unique pointer created.");
                            } else if (radioButtons[1].selected) {
                                sharedPtr.reset(new int(number));
                                outputText.setString("Shared pointer created.");
                            } else if (radioButtons[2].selected) {
                                weakPtr = std::weak_ptr<int>(sharedPtr); // Example of using Weak_ptr
                                outputText.setString("Weak pointer created.");
                            }
                        } catch (const std::exception& e) {
                            outputText.setString("Error creating a pointer.");
                        }
                    } else if (!selected) {
                        outputText.setString("Select a pointer type.");
                    } else if (!validInput) {
                        outputText.setString("Enter a valid number.");
                    }
                }

                // Check if the "Delete" button is clicked
                if (deleteButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    // Start button click timer
                    buttonClickTimer.restart();
                    // Set the button color to light red
                    deleteButton.setFillColor(LightRed);
                    uniquePtr.reset();
                    sharedPtr.reset();
                    weakPtr.reset();
                    outputText.setString("Memory successfully cleared.");

                    // ... (rest of the delete button logic) ...
                }
            }

            // Handle keyboard input events
            if (event.type == Event::TextEntered) {
                // Input text into the input field
                if (event.text.unicode >= '0' && event.text.unicode <= '9' || event.text.unicode == '-') {
                    inputValue += static_cast<char>(event.text.unicode);
                    inputText.setString(inputValue);
                } else if (event.text.unicode == '\b' && !inputValue.empty()) {
                    inputValue.pop_back();
                    inputText.setString(inputValue);
                }
            }
        }

        // Update button colors based on click timer
        float clickTime = buttonClickTimer.getElapsedTime().asSeconds();
        if (clickTime < buttonClickDuration) {
            // If the timer is less than the duration, keep the button color changed

            if (createButton.getFillColor() == LightGreen) {
                createButton.setFillColor(Color::Green); // Reset to original green
            } else if (deleteButton.getFillColor() == LightRed) {
                deleteButton.setFillColor(Color::Red); // Reset to original red
            }
        }


        // Clear the window
        window.clear(Color::White);

        // Draw elements
        for (int i = 0; i < 3; ++i) {
            window.draw(radioButtons[i].shape);
            window.draw(radioButtons[i].text);
        }

        window.draw(inputField);
        window.draw(inputText);

        window.draw(createButton);
        window.draw(createText);

        window.draw(deleteButton);
        window.draw(deleteText);

        window.draw(outputWindow);
        window.draw(outputText);

        // Update the window
        window.display();
    }

    return 0;
}
