#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
#include "task.cpp"


// function declerations
void loadTasksFromFile(std::vector<Task>& tasks, const std::string& filename);
void saveTasksToFile(const std::vector<Task>& tasks, const std::string& filename);
void displayMenu();
void viewTasks(const std::vector<Task>& tasks);
void addTask(std::vector<Task>& tasks);
void removeTask(std::vector<Task>& tasks);
void markTaskComplete(std::vector<Task>& tasks);

int main() {
    std::vector<Task> todoList;
    const std::string filename = "student_tasks.txt";
    int choice = 0;

    // Load existing tasks at startup
    loadTasksFromFile(todoList, filename);

    std::cout << "=========================================\n";
    std::cout << "   Welcome to the To Do List Tracker     \n";
    std::cout << "=========================================\n";

    while (choice != 5) {
        displayMenu();
        std::cout << "Enter your choice (1-5): ";
        
        // Handle non-integer inputs
        if (!(std::cin >> choice)) {
            std::cout << "Invalid input. Please enter a number.\n";
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }
        std::cin.ignore();

        if (choice == 1) {
            viewTasks(todoList);
        } 
        else if (choice == 2) {
            addTask(todoList);
            saveTasksToFile(todoList, filename); // Auto-save
        } 
        else if (choice == 3) {
            markTaskComplete(todoList);
            saveTasksToFile(todoList, filename); // Auto-save
        } 
        else if (choice == 4) {
            removeTask(todoList);
            saveTasksToFile(todoList, filename); // Auto-save
        } 
        else if (choice == 5) {
            std::cout << "\nSaving your tasks... Goodbye!\n";
        } 
        else {
            std::cout << "Invalid choice. Please select an option between 1 and 5.\n";
        }
    }

    return 0;
}

// displays the user interface menu
void displayMenu() {
    std::cout << "\n--- Main Menu ---\n";
    std::cout << "1. View Tasks\n";
    std::cout << "2. Add Task\n";
    std::cout << "3. Mark Task as Complete\n";
    std::cout << "4. Remove Task\n";
    std::cout << "5. Exit\n";
}

// displays current tasks
void viewTasks(const std::vector<Task>& tasks) {
    std::cout << "\n--- Your Current Tasks ---\n";
    
    if (tasks.empty()) {
        std::cout << "Your to-do list is empty!\n";
        return;
    }

    for (size_t i = 0; i < tasks.size(); ++i) {
        std::string status = tasks[i].getStatus() ? "[X]" : "[ ]";
        std::cout << i + 1 << ". " << status << " " << tasks[i].getDescription() << "\n";
    }
}

// adds a new task to the collection
void addTask(std::vector<Task>& tasks) {
    std::string description;
    std::cout << "Enter task description (e.g., 'Study for CSE Exam'): ";
    std::getline(std::cin, description);
    
    if (!description.empty()) {
        tasks.push_back(Task(description));
        std::cout << "Task successfully added!\n";
    } else {
        std::cout << "Task description cannot be empty.\n";
    }
}

// updates a specific task's boolean flag to true
void markTaskComplete(std::vector<Task>& tasks) {
    viewTasks(tasks);
    if (tasks.empty()) return;

    int index;
    std::cout << "Enter the number of the task to mark complete: ";
    std::cin >> index;

    if (index > 0 && static_cast<size_t>(index) <= tasks.size()) {
        tasks[index - 1].markAsComplete();
        std::cout << "Task marked complete.\n";
    } else {
        std::cout << "Invalid task number.\n";
    }
}

// deletes an entry from the collection
void removeTask(std::vector<Task>& tasks) {
    viewTasks(tasks);
    if (tasks.empty()) return;

    int index;
    std::cout << "Enter the number of the task you want to remove: ";
    std::cin >> index;

    if (index > 0 && static_cast<size_t>(index) <= tasks.size()) {
        tasks.erase(tasks.begin() + (index - 1));
        std::cout << "Task removed successfully.\n";
    } else {
        std::cout << "Invalid task number.\n";
    }
}

// reads data from a file back into the STL container
void loadTasksFromFile(std::vector<Task>& tasks, const std::string& filename) {
    std::ifstream inFile(filename);
    if (!inFile) {
        return;
    }

    std::string line;
    while (std::getline(inFile, line)) {
        size_t delimiterPos = line.find('|');
        if (delimiterPos != std::string::npos) {
            std::string desc = line.substr(0, delimiterPos);
            std::string statusStr = line.substr(delimiterPos + 1);
            bool isComplete = (statusStr == "1");
            
            tasks.push_back(Task(desc, isComplete));
        }
    }
    inFile.close();
}

// writes task items to a file persistent data storage
void saveTasksToFile(const std::vector<Task>& tasks, const std::string& filename) {
    std::ofstream outFile(filename);
    if (!outFile) {
        std::cerr << "Error updating persistent storage file.\n";
        return;
    }

    for (const auto& task : tasks) {
        outFile << task.toFileString() << "\n";
    }
    outFile.close();
}