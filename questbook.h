#ifndef QUESTBOOK_H
#define QUESTBOOK_H

#include <string>
#include <vector>
#include <iostream>
#include <limits>


// Define a Question structure
struct Question {
    std::string question;
    std::vector<std::string> options;
    int correct;

    Question(const std::string &q, const std::vector<std::string> &opts, int c)
        : question(q), options(opts), correct(c) {}
};

// QuestBook Class
class QuestBook {
private:
    std::string title;
    std::vector<Question> questions;

public:
    QuestBook(std::string t) : title(t) {}

    void addQuestion(const Question &q) {
        questions.push_back(q);
    }

    void start();                             // Start the QuestBook
    std::string getTitle() const;             // Get the title
    const std::vector<Question>& getQuestions() const;

private:
    void presentQuestion(const Question &q, int number);
    int getUserChoice(int maxOption);
    void displayResults(int score, int total);
};

#endif // QUESTBOOK_H

