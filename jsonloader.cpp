#include "jsonloader.h"
#include <fstream>
#include <iostream>
#include <algorithm> // For std::shuffle
#include <random>    // For random number generation

std::vector<Question> loadFinalExam(const std::vector<std::string> &jsonFiles) {
    std::vector<Question> finalQuestions;

    for (const auto &filePath : jsonFiles) {
        std::ifstream file(filePath);
        if (!file.is_open()) {
            std::cerr << "Error: Could not open file " << filePath << "\n";
            continue;
        }

        json questBook;
        try {
            file >> questBook;

            // Safely loop through quests and gather questions
            if (questBook.contains("quests") && questBook["quests"].is_array()) {
                for (const auto &quest : questBook["quests"]) {
                    if (quest.contains("questions") && quest["questions"].is_array()) {
                        for (const auto &q : quest["questions"]) {
                            finalQuestions.emplace_back(
                                q.value("question", "Missing question"),
                                q.value("options", std::vector<std::string>()),
                                q.value("correct", -1)
                            );
                        }
                    }
                }
            }
        } catch (const json::exception &e) {
            std::cerr << "JSON Parsing Error in file " << filePath << ": " << e.what() << "\n";
        }
    }

    // Shuffle the questions for randomness
    std::random_device rd;                          // Random number generator
    std::mt19937 rng(rd());                         // Seeded random engine
    std::shuffle(finalQuestions.begin(), finalQuestions.end(), rng);

    return finalQuestions;
}






std::vector<Question> loadQuestionsFromJSON(const std::string &filePath) {
    std::vector<Question> questions;
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Error: Cannot open file " << filePath << "\n";
        return questions;
    }

    json data;
    file >> data;

    // Ensure data contains "quests"
    if (!data.contains("quests") || !data["quests"].is_array()) {
        std::cerr << "Error: JSON format invalid or 'quests' is missing.\n";
        return questions;
    }

    // Loop through each quest in "quests" and extract "questions"
    for (const auto &quest : data["quests"]) {
        if (quest.contains("questions") && quest["questions"].is_array()) {
            for (const auto &q : quest["questions"]) {
                questions.emplace_back(
                    q["question"].get<std::string>(),
                    q["options"].get<std::vector<std::string>>(),
                    q["correct"].get<int>()
                );
            }
        } else {
            std::cerr << "Warning: Missing 'questions' in one of the quests.\n";
        }
    }

    return questions;
}
