// Programmed by Hayden Baer on March 8, 2024
// Compiled and ran on M3 Pro
// Compile command = g++ passwordGenerator.cpp -o passwordGenerator
// Run command = ./passwordGenerator

// All necessary libraries
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

// Global variables

// A collection of all current generated words for password
std::vector<std::string> currentPhrase;

// Filepath for word library - feel free to use your own!
// The program assumes that there is only one words per line
std::string filepath = "lib.txt";

// Current line read of text file
std::string line;

// Current input from user as a string
std::string input;

void getWordsFromLibrary(std::vector<std::string> words, int numberOfWords) {

    // Proceed if input is not -1... if input is -1 program should stop
    if (numberOfWords != -1) {
        std::ifstream file(filepath);

        // Iterate through text file and save words if successful in opening file
        if (file.is_open()) {
            while (getline(file, line)) {
                words.push_back(line);
            }

            // Seed the random number generator with the current time
            std::srand(static_cast<unsigned int>(std::time(nullptr)));

            // Iterate through only if it can produce a unique password with no repeating words
            if ((words.size() / 2) >= numberOfWords) {
                for (int i = 0; i < numberOfWords; i++) {
                    int randomNumber;
                    do {
                        // Generate a random number between 0 and the size of words vector - 1
                        randomNumber = std::rand() % words.size();
                    } while (std::find(currentPhrase.begin(), currentPhrase.end(), words[randomNumber]) != currentPhrase.end());
                    
                    currentPhrase.push_back(words[randomNumber]);
                    std::cout << currentPhrase[i];
                }
            } else {
                // Give error message if a password without repeating words cannot be generated
                std::cout << "Not enough words in lib.txt to generate password.";
            }

            std::cout << "\n";

        } else {
            // Throw error if text file cannot be opened
            std::cout << "Error opening text file!\n";
        }
        file.close();   
    }
}

// Function prompts user to enter a number and handles incorrect input
int userPrompt() {
    std::cout << "\nPlease enter the number of words in the phrase: ";
    std::cin >> input;

    if (input == "exit") {
        return -1;
    }

    // If input is greater than 0 generate password
    else if (std::stoi(input) > 0) {
        std::cout << "The result phrase: ";

        return std::stoi(input);
    }
    // If input is not greater than 0 or "exit" use 2 words as default
    else {
        std::cout << "\nError with user input, using 2 words as default\n";
        std::cout << "The result phrase: ";

        // If not positve int, use two words as default option
        return 2;
    }
}

int main() {

    // Loop while user has used exit command
    while (input != "exit") {
        std::vector<std::string> words;
        int numberOfWords = userPrompt();
        getWordsFromLibrary(words, numberOfWords);
    }

    return 0;
}