
// g++ -o rabbithole main.cpp jsonloader.cpp questbook.cpp

#include "json.hpp"
#include "jsonloader.h"  // Includes loadQuestionsFromJSON
#include "questbook.h"   // Includes QuestBook and Question classes
#include <iostream>
#include <vector>
#include <string>
#include <algorithm> // For std::shuffle
#include <random>    // For random number generation

using json = nlohmann::json;

int main() {
    // Paths to all QuestBook JSON files
    std::vector<std::string> jsonFiles = {
        // Basic QuestBooks
        "questbooks/basic/physics.json",
        "questbooks/basic/biology.json",
        "questbooks/basic/chemistry.json",
        "questbooks/basic/psychology.json",
        "questbooks/basic/history.json",
        "questbooks/basic/philosophy.json",
        "questbooks/basic/mathematics.json",
        "questbooks/basic/computerscience.json",

        // Interdisciplinary QuestBooks
        "questbooks/interdisciplinary/physics_chemistry.json",
        "questbooks/interdisciplinary/physics_biology.json",
        "questbooks/interdisciplinary/physics_computerscience.json",
        "questbooks/interdisciplinary/physics_history.json",
        "questbooks/interdisciplinary/physics_mathematics.json",
        "questbooks/interdisciplinary/physics_philosophy.json",
        "questbooks/interdisciplinary/physics_psychology.json",
        "questbooks/interdisciplinary/chemistry_biology.json",
        "questbooks/interdisciplinary/chemistry_computerscience.json",
        "questbooks/interdisciplinary/chemistry_history.json",
        "questbooks/interdisciplinary/chemistry_mathematics.json",
        "questbooks/interdisciplinary/chemistry_philosophy.json",
        "questbooks/interdisciplinary/chemistry_psychology.json",
        "questbooks/interdisciplinary/biology_computerscience.json",
        "questbooks/interdisciplinary/biology_history.json",
        "questbooks/interdisciplinary/biology_mathematics.json",
        "questbooks/interdisciplinary/biology_philosophy.json",
        "questbooks/interdisciplinary/biology_psychology.json",
        "questbooks/interdisciplinary/computerscience_history.json",
        "questbooks/interdisciplinary/computerscience_philosophy.json",
        "questbooks/interdisciplinary/computerscience_psychology.json",
        "questbooks/interdisciplinary/history_philosophy.json",
        "questbooks/interdisciplinary/history_psychology.json",
        "questbooks/interdisciplinary/mathematics_computerscience.json",
        "questbooks/interdisciplinary/mathematics_history.json",
        "questbooks/interdisciplinary/mathematics_philosophy.json",
        "questbooks/interdisciplinary/mathematics_psychology.json",
        "questbooks/interdisciplinary/psychology_philosophy.json"
    };

    std::vector<QuestBook> questBooks;

    // Load each QuestBook
    for (const auto &filePath : jsonFiles) {
        std::string title = filePath.substr(filePath.find_last_of("/\\") + 1);
        title = title.substr(0, title.find(".json")); // Extract title from file name

        QuestBook qb(title);
        auto questions = loadQuestionsFromJSON(filePath);
        for (const auto &q : questions) {
            qb.addQuestion(q);
        }
        questBooks.push_back(qb);
    }

    // User menu
    std::cout << "=== Welcome to the QuestBooks Program ===\n";
    std::cout << "1. Start an individual QuestBook\n";
    std::cout << "2. Take the Final Assorted Exam (100 Questions)\n";
    std::cout << "Choose an option: ";

    int choice;
    std::cin >> choice;

    if (choice == 1) {
        // Let user pick which QuestBook to start
        std::cout << "\nAvailable QuestBooks:\n";
        for (size_t i = 0; i < questBooks.size(); ++i) {
            std::cout << i + 1 << ". " << questBooks[i].getTitle() << "\n";
        }
        std::cout << "Enter the number of the QuestBook you want to start: ";
        
        int bookChoice;
        std::cin >> bookChoice;

        if (bookChoice >= 1 && bookChoice <= (int)questBooks.size()) {
            questBooks[bookChoice - 1].start();
        } else {
            std::cout << "Invalid choice. Returning to main menu...\n";
        }

    } else if (choice == 2) { 
    // Combine all questions into a single Final Exam
    QuestBook finalExam("The Assorted Exam");
    
    // Gather all questions from all questBooks
    std::vector<Question> allQuestions;
    for (const auto &qb : questBooks) {
        for (const auto &q : qb.getQuestions()) {
            allQuestions.push_back(q);
            if (allQuestions.size() >= 100) break;
        }
        if (allQuestions.size() >= 100) break;
    }

    // Shuffle the questions for randomness
    std::random_device rd;  
    std::mt19937 rng(rd()); // Seeded random engine
    std::shuffle(allQuestions.begin(), allQuestions.end(), rng);

    // Add shuffled questions to the finalExam
    for (const auto &q : allQuestions) {
        finalExam.addQuestion(q);
    }

    // Start the Final Exam
    finalExam.start();
} else {
    std::cout << "Invalid option. Exiting program...\n";
}


    std::cout << "\nThank you for playing! Goodbye.\n";
    return 0;
}














/*

#include "json.hpp" // Include the JSON library
#include <string>
#include <iostream>
#include <vector>
#include <limits>
#include <filesystem>
#include <fstream>

using json = nlohmann::json;
namespace fs = std::filesystem;

// Quest class to store individual quest information
class Quest {
public:
    std::string description;
    std::string question;
    std::vector<std::string> options;
    int correctIndex;

    Quest(std::string desc, std::string quest, std::vector<std::string> opts, int correct)
        : description(desc), question(quest), options(opts), correctIndex(correct) {}
};

// QuestBook class to manage a collection of quests
class QuestBook {
private:
    std::string title;
    std::vector<Quest> quests;

public:
    QuestBook(std::string t) : title(t) {}

    void addQuest(const Quest &q) {
        quests.push_back(q);
    }

    void start() {
        std::cout << "\nWelcome to the QuestBook: " << title << "!\n";
        for (size_t i = 0; i < quests.size(); ++i) {
            presentQuest(quests[i], i + 1);
        }
        award();
    }

    std::string getTitle() const {
        return title;
    }
private:
    void presentQuest(const Quest &q, int number) {
        std::cout << "\n--- Quest " << number << " ---\n";
        std::cout << q.description << "\n\n" << q.question << "\n";
        for (size_t i = 0; i < q.options.size(); ++i) {
            std::cout << i + 1 << ". " << q.options[i] << "\n";
        }

        int choice;
        while (true) {
            std::cout << "Choose an option (1-" << q.options.size() << "): ";
            std::cin >> choice;
            if (choice - 1 == q.correctIndex) {
                std::cout << "Correct!\n";
                break;
            } else {
                std::cout << "That's not correct. Try again.\n";
            }
        }
    }

    void award() {
        std::cout << "\nCongratulations! You completed all quests in: " << title << "!\n";
    }
};

// Function to load quests from a JSON file
std::vector<Quest> loadQuestsFromJSON(const std::string &filePath) {
    std::vector<Quest> quests;
    std::ifstream file(filePath);

    if (!file.is_open()) {
        std::cerr << "Error: Could not open file: " << filePath << "\n";
        return quests;
    }

    try {
        json questData;
        file >> questData;

        // Iterate through the quests array
        for (const auto &questBlock : questData["quests"]) {
            std::string questTitle = questBlock["title"];
            std::string questDescription = questBlock["description"];

            // Access the nested 'questions' array
            for (const auto &q : questBlock["questions"]) {
                quests.emplace_back(
                    questTitle + " - " + q["question"].get<std::string>(), // Combine title + question
                    q["question"].get<std::string>(),
                    q["options"].get<std::vector<std::string>>(),
                    q["correct"].get<int>()
                );
            }
        }
    } catch (const std::exception &e) {
        std::cerr << "Error parsing JSON in file " << filePath << ": " << e.what() << "\n";
    }

    return quests;
}


// Function to discover all JSON files in a directory
std::vector<std::string> discoverJSONFiles(const std::string &directory) {
    std::vector<std::string> jsonFiles;
    for (const auto &entry : fs::directory_iterator(directory)) {
        if (entry.path().extension() == ".json") {
            jsonFiles.push_back(entry.path().string());
        }
    }
    return jsonFiles;
}

int main() {
    std::vector<std::string> basicQuestBooks = discoverJSONFiles("questbooks/basic");
    std::vector<std::string> interdisciplinaryQuestBooks = discoverJSONFiles("questbooks/interdisciplinary");

    std::vector<QuestBook> questBooks;

    // Load Basic QuestBooks
    for (const auto &filePath : basicQuestBooks) {
        std::string title = fs::path(filePath).stem().string();
        QuestBook qb(title);
        auto quests = loadQuestsFromJSON(filePath);
        for (const auto &quest : quests) {
            qb.addQuest(quest);
        }
        questBooks.push_back(qb);
    }

    // Load Interdisciplinary QuestBooks
    for (const auto &filePath : interdisciplinaryQuestBooks) {
        std::string title = fs::path(filePath).stem().string();
        QuestBook qb(title);
        auto quests = loadQuestsFromJSON(filePath);
        for (const auto &quest : quests) {
            qb.addQuest(quest);
        }
        questBooks.push_back(qb);
    }

    // Interactive Subject Selection
    std::cout << "Select your QuestBook to start:\n";
    for (size_t i = 0; i < questBooks.size(); ++i) {
        std::cout << i + 1 << ": " << questBooks[i].getTitle() << "\n";
    }

    int choice;
    while (true) {
        std::cout << "Enter the number of your chosen QuestBook: ";
        std::cin >> choice;

        if (choice >= 1 && choice <= (int)questBooks.size()) {
            questBooks[choice - 1].start();
            break;
        } else {
            std::cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}


*/

