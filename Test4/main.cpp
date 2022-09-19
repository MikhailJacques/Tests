// AUTHOR:		Mikhail Jacques
// PROJECT:		Fun
// DOCUMENT:	None
// DESCRIPTION: This file executes the application

// APPLICATION DESCRIPTION:
// Given a list of interdependent tasks this program attempts to execute all the tasks unless it determines 
// that there is a circular dependency between the tasks in which case it prints an error message and terminates.
// Each task in the list has a list of dependencies on other tasks, e.g Tasks {1, 2, 3, 4, 5}: 1->2, 2->3, 3->4, 3->5, 5->4

// MJ TODO: To be continued
// Assuming that the function task.execute() is an asynchronous call, synchronize the code so that 
// the tasks will be executed in parallel without race conditions, while preserving tasks dependencies.
//
// 1. You have synchronization primitives available.
// 2. task.execute() calls callback(task) {} function upon completion.
// 3. Different tasks may have different time to complete.
// 4. Try to come with synchronization that will give the fastest execution time.
//
//ekhaitzi@akamai.com

// #include <mutex>
#include <vector>
#include <string>
#include <iostream>

#include "task.h"

void read_user_input(bool& circular_dependency_flag);
void execute_tasks(std::vector<Task>& tasks);
//void callback(Task) { }

int main(int argc, char** argv)
{
    bool circular_dependency_flag = false;

    read_user_input(circular_dependency_flag);

    // Create and initialize a collection of independent tasks
    std::vector<Task> tasks{ Task(1), Task(2), Task(3), Task(4), Task(5) };

    // Create task interdependencies WITHOUT circular dependency
    if (circular_dependency_flag == false)
    { 
        // Tasks {1, 2, 3, 4, 5}: 1->2, 2->3, 3->4, 3->5, 5->4
        tasks[0].add_child(&tasks[1]);
        tasks[1].add_child(&tasks[2]);
        tasks[2].add_child(&tasks[3]);
        tasks[2].add_child(&tasks[4]);
        tasks[4].add_child(&tasks[3]);
    }
    else // Create task interdependencies WITH circular dependency
    {
        // Tasks {1, 2, 3, 4, 5}: 1->2, 2->3, 3->4, 4->5, 5->1
        tasks[0].add_child(&tasks[1]);
        tasks[1].add_child(&tasks[2]);
        tasks[2].add_child(&tasks[3]);
        tasks[3].add_child(&tasks[4]);
        tasks[4].add_child(&tasks[0]);
    }

    execute_tasks(tasks);

    return 0;
}


// This function executes the interdependent tasks
// In case of a circular dependency the function prints an error message and terminates
void execute_tasks(std::vector<Task>& tasks)
{
    size_t completed_tasks_cnt = 0;
    size_t uncompleted_tasks_cnt = 0;
    size_t max_num_of_iterations = tasks.size() * tasks.size();

    while (completed_tasks_cnt < tasks.size())
    {
        for (Task& task : tasks)
        {
            if (task.is_completed() == true)
                continue;

            if (task.is_ready_to_execute() == true)
            {
                task.execute();
                completed_tasks_cnt++;
            }
            else
            {
                if (++uncompleted_tasks_cnt >= max_num_of_iterations)
                {
                    std::cout << "Circular dependency exists\n";
                    completed_tasks_cnt = tasks.size();
                    break;
                }
            }
        }
    }
}

// This function reads user input
void read_user_input(bool& circular_dependency_flag)
{
    bool go = false;
    std::string user_input;

    std::cout << "Valid options: \n"
        << "    good\n"                 // circular dependency absent
        << "    bad\n\n";               // circular dependency present

    std::cout << "Enter your choice: \n";
    getline(std::cin, user_input);

    do
    {
        if (user_input.compare("good") == 0)
        {
            go = true;
            circular_dependency_flag = false;
        }
        else if (user_input.compare("bad") == 0)
        {
            go = true;
            circular_dependency_flag = true;
        }
        else
        {
            std::cout << "\nInvalid entry! Please try again.\n"
                << "Valid options: \n"
                << "    good\n"
                << "    bad\n"
                << "Enter your choice:\n";
        }

        if (go == false)
            getline(std::cin, user_input);

    } while (go == false);
}