#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <sstream>
#include <map>
#include <chrono>
#include <thread>
#include "C:\Users\dimak\CLionProjects\lab2_1\sequence\LinkedList.h"  // Включаем вашу реализацию LinkedList

class GUI {
public:
    GUI() {
        // Создание окна
        window.create(sf::VideoMode(800, 600), "Linked List GUI");
        window.setFramerateLimit(60);

        // Загрузка шрифта
        if (!font.loadFromFile("C:\\Users\\dimak\\CLionProjects\\lab2_1\\fonts\\arial.ttf")) {
            std::cerr << "Error loading font!" << std::endl;
        }

        // Настройка текста информации
        infoText.setFont(font);
        infoText.setCharacterSize(18);
        infoText.setFillColor(sf::Color::White);
        infoText.setPosition(20, 520);

        sf::Color color(0,0,0);
        // Поле для ввода данных
        inputBox.setSize(sf::Vector2f(200, 30));
        inputBox.setPosition(20, 470);
        inputBox.setFillColor(sf::Color::White);
        inputText.setFont(font);
        inputText.setCharacterSize(18);
        inputText.setFillColor(color);
        inputText.setPosition(25, 475);

        // Кнопки

        setupButton(addStartButton, addStartText, "Add to Start", 30, 60);
        setupButton(addEndButton, addEndText, "Add to End", 30, 110);
        setupButton(insertButton, insertText, "Insert at Index", 30, 160);
        setupButton(deleteButton, deleteText, "Delete at Index", 30, 210);
        setupButton(getElementButton, getElementText, "Get Element", 30, 260);
        setupButton(displayButton, displayText, "Display List", 30, 310);
        setupButton(clearButton, clearText, "Clear List", 30, 360);
        setupButton(exitButton, exitText, "Exit", 30, 410);
    }

    void run() {
        while (window.isOpen()) {
            processEvents();
            render();
        }
    }

private:
    sf::RenderWindow window;
    sf::Font font;
    sf::Text infoText;
    sf::RectangleShape inputBox;
    sf::Text inputText;
    std::string userInput;

    // Кнопки и текст кнопок
    sf::RectangleShape addStartButton, addEndButton, insertButton, deleteButton, getElementButton, displayButton, clearButton, exitButton;
    sf::Text addStartText, addEndText, insertText, deleteText, getElementText, displayText, clearText, exitText;

    LinkedList<int> list;  // Экземпляр вашего списка

    // Структура для хранения состояния кнопок
    struct ButtonState {
        bool isClicked = false;
        sf::Color originalColor;
        sf::Color clickedColor;
    };
    std::map<sf::RectangleShape*, ButtonState> buttonStates;

    void processEvents() {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode == '\b') {
                    if (!userInput.empty())
                        userInput.pop_back();
                } else if (event.text.unicode < 128) {
                    userInput += static_cast<char>(event.text.unicode);
                }
                inputText.setString(userInput);
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                if (isButtonClicked(addStartButton, event.mouseButton.x, event.mouseButton.y)) {
                    handleAddToStart();
                    changeButtonColor(addStartButton, sf::Color::Green);
                } else if (isButtonClicked(addEndButton, event.mouseButton.x, event.mouseButton.y)) {
                    handleAddToEnd();
                    changeButtonColor(addEndButton, sf::Color::Green);
                } else if (isButtonClicked(insertButton, event.mouseButton.x, event.mouseButton.y)) {
                    handleInsertAtIndex();
                    changeButtonColor(insertButton, sf::Color::Green);
                } else if (isButtonClicked(deleteButton, event.mouseButton.x, event.mouseButton.y)) {
                    handleDeleteAtIndex();
                    changeButtonColor(deleteButton, sf::Color::Green);
                } else if (isButtonClicked(getElementButton, event.mouseButton.x, event.mouseButton.y)) {
                    handleGetElementAtIndex();
                    changeButtonColor(getElementButton, sf::Color::Green);
                } else if (isButtonClicked(displayButton, event.mouseButton.x, event.mouseButton.y)) {
                    handleDisplayList();
                    changeButtonColor(displayButton, sf::Color::Green);
                } else if (isButtonClicked(clearButton, event.mouseButton.x, event.mouseButton.y)) {
                    handleClearList();
                    changeButtonColor(clearButton, sf::Color::Green);
                } else if (isButtonClicked(exitButton, event.mouseButton.x, event.mouseButton.y)) {
                    window.close();
                }
            }
        }
    }

    void setupButton(sf::RectangleShape &button, sf::Text &buttonText, const std::string &text, float x, float y) {
        button.setSize(sf::Vector2f(150, 30));
        button.setPosition(x, y);
        button.setFillColor(sf::Color::Blue);

        buttonText.setFont(font);
        buttonText.setString(text);
        buttonText.setCharacterSize(16);
        buttonText.setFillColor(sf::Color::White);
        buttonText.setPosition(x + 10, y + 5);

        // Запоминаем состояние кнопки
        buttonStates[&button] = { false, sf::Color::Blue, sf::Color::Green };
    }

    bool isButtonClicked(const sf::RectangleShape &button, float x, float y) {
        return button.getGlobalBounds().contains(x, y);
    }

    void changeButtonColor(sf::RectangleShape &button, const sf::Color &color) {
        button.setFillColor(color);

        // Запускаем поток для возврата цвета через 300 мс
        std::thread([this, &button]() {
            std::this_thread::sleep_for(std::chrono::milliseconds(300));
            button.setFillColor(buttonStates[&button].originalColor);
        }).detach();
    }

    void handleAddToStart() {
        int value = std::stoi(userInput);
        list.prepend(value);
        infoText.setString("Element added to start");
        userInput.clear();
        inputText.setString(userInput);
    }

    void handleAddToEnd() {
        int value = std::stoi(userInput);
        list.append(value);
        infoText.setString("Element added to end");
        userInput.clear();
        inputText.setString(userInput);
    }

    void handleInsertAtIndex() {
        std::istringstream iss(userInput);
        int value, index;
        iss >> value >> index;
        list.insertAt(value, index);
        infoText.setString("Element inserted at index " + std::to_string(index));
        userInput.clear();
        inputText.setString(userInput);
    }

    void handleDeleteAtIndex() {
        int index = std::stoi(userInput);
        list.removeAt(index);
        infoText.setString("Element at index " + std::to_string(index) + " deleted");
        userInput.clear();
        inputText.setString(userInput);
    }

    void handleGetElementAtIndex() {
        int index = std::stoi(userInput);
        int value = list.get(index);
        infoText.setString("Element at index " + std::to_string(index) + ": " + std::to_string(value));
        userInput.clear();
        inputText.setString(userInput);
    }

    void handleDisplayList() {
        std::ostringstream oss;
        oss << "List: [";
        for (int i = 0; i < list.getLength(); i++) {
            oss << list.get(i);
            if (i < list.getLength() - 1)
                oss << ", ";
        }
        oss << "]";
        infoText.setString(oss.str());
    }

    void handleClearList() {
        list.clear();
        infoText.setString("List cleared");
    }

    void render() {
        window.clear(sf::Color::Black);

        // Рисование кнопок
        drawButton(addStartButton, addStartText);
        drawButton(addEndButton, addEndText);
        drawButton(insertButton, insertText);
        drawButton(deleteButton, deleteText);
        drawButton(getElementButton, getElementText);
        drawButton(displayButton, displayText);
        drawButton(clearButton, clearText);
        drawButton(exitButton, exitText);

        // Поле ввода
        window.draw(inputBox);
        window.draw(inputText);

        // Вывод информации
        window.draw(infoText);

        window.display();
    }

    void drawButton(sf::RectangleShape &button, sf::Text &buttonText) {
        window.draw(button);
        window.draw(buttonText);
    }
};

int main() {
    GUI gui;
    gui.run();
    return 0;
}
