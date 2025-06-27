#ifndef JSONLOADER_H
#define JSONLOADER_H

#include "questbook.h" // Include QuestBook and Quest classes
#include "json.hpp"    // Include nlohmann::json library
#include <string>
#include <vector>

using json = nlohmann::json;

// Function to load questions for the Final Exam
std::vector<Question> loadFinalExam(const std::vector<std::string> &jsonFiles);
std::vector<Question> loadQuestionsFromJSON(const std::string &filePath);
#endif // JSONLOADER_H
