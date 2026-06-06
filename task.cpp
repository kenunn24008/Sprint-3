#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>

class Task {
private:
    std::string description;
    bool isComplete;

public:
    // Constructor
    Task(std::string desc, bool complete = false) {
        description = desc;
        isComplete = complete;
    }

    // Getters and Setters
    std::string getDescription() const { return description; }
    bool getStatus() const { return isComplete; }
    
    void markAsComplete() { 
        isComplete = true; 
    }

    // Formats the task string for saving to a file
    std::string toFileString() const {
        return description + "|" + (isComplete ? "1" : "0");
    }
};