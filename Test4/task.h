// AUTHOR:		Mikhail Jacques
// PROJECT:		Fun
// DOCUMENT:	None
// DESCRIPTION: This file declares a class that simulates a task

#pragma once

#include <list>

class Task
{
public:

    explicit Task(unsigned int id) : m_id(id) {};
    void add_child(Task* task);
    void execute(void);
    bool is_completed(void) const;
    bool is_ready_to_execute(void) const;

private:

    void mark_completed(void);
    unsigned int m_id;
    bool m_completed_sts = false;
    std::list<Task*> m_children;
};
