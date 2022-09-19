// AUTHOR:		Mikhail Jacques
// PROJECT:		Fun
// DOCUMENT:	None
// DESCRIPTION: This file defines a class that simulates a task

#include <chrono>
#include <thread>
#include <iostream>
#include "task.h"
#include "random.h"

#define EXECUTION_DURATION_LOWER_LIMIT 1000  // Milliseconds
#define EXECUTION_DURATION_UPPER_LIMIT 3000  // Milliseconds

// This function adds task dependency on another task
void Task::add_child(Task* task)
{
    m_children.push_back(task);
}

// This function simulates execution duration of a task
void Task::execute(void)
{
    std::cout << "Task: " << m_id << " is executing\n";

    std::this_thread::sleep_for(std::chrono::milliseconds(Random::Get().Range(EXECUTION_DURATION_LOWER_LIMIT, EXECUTION_DURATION_UPPER_LIMIT)));

    std::cout << "Task: " << m_id << " is completed\n";

    mark_completed();
}

// This function sets the status of the task as completed
void Task::mark_completed(void)
{
    m_completed_sts = true;
}

// This function checks to see whether the status of the task is completed
bool Task::is_completed(void) const
{
    return m_completed_sts;
}

// This function checks to see whether all the dependee tasks (children) have completed their 
// respective executions so that the depender task in question (parent) may start running
bool Task::is_ready_to_execute(void) const
{
    if (m_children.empty() == false)
    {
        for (const Task* child : m_children)
        {
            if (child->is_completed() == false)
                return false;
        }
    }

    return true;
}