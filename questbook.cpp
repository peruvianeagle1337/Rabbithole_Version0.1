#include "questbook.h"

void QuestBook::start() {
    std::cout << "\n=== " << title << " ===\n";
    int score = 0;

    for (size_t i = 0; i < questions.size(); ++i) {
        presentQuestion(questions[i], i + 1);
        int choice = getUserChoice(questions[i].options.size());
        if (choice - 1 == questions[i].correct) {
            std::cout << "Correct!\n";
            ++score;
        } else {
            std::cout << "Wrong! Correct answer: " 
                      << questions[i].options[questions[i].correct] << "\n";
        }
    }

    displayResults(score, questions.size());
}

std::string QuestBook::getTitle() const {
    return title;
}

const std::vector<Question>& QuestBook::getQuestions() const {
    return questions;
}

void QuestBook::presentQuestion(const Question &q, int number) {
    std::cout << "\nQuestion " << number << ": " << q.question << "\n";
    for (size_t i = 0; i < q.options.size(); ++i) {
        std::cout << i + 1 << ". " << q.options[i] << "\n";
    }
}

int QuestBook::getUserChoice(int maxOption) {
    int choice;
    while (true) {
        std::cout << "Choose an option (1-" << maxOption << "): ";
        std::cin >> choice;
        if (std::cin.fail() || choice < 1 || choice > maxOption) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Try again.\n";
        } else {
            break;
        }
    }
    return choice;
}

void QuestBook::displayResults(int score, int total) {
    std::cout << "\nYour Score: " << score << " / " << total << "\n";
    if (score >= 0.9 * total) std::cout << "Grade: A (Excellent!)\n";
    else if (score >= 0.8 * total) std::cout << "Grade: B (Great Job!)\n";
    else if (score >= 0.7 * total) std::cout << "Grade: C (Good Effort!)\n";
    else if (score >= 0.6 * total) std::cout << "Grade: D (Needs Improvement)\n";
    else std::cout << "Grade: F (Try Again)\n";
}
