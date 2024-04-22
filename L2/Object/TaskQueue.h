#pragma once
#include <queue>
#include <memory>
#include <chrono>
class Task {
public:
    virtual void execute() = 0;
};

class TaskQueue {
protected:
    std::queue<std::unique_ptr<Task>> m_tasks;
public:
    void add_task(std::unique_ptr<Task> task){
        m_tasks.push(std::move(task));
    }
};

class WorkQueue : public TaskQueue {

};

class ReadyQueue : public TaskQueue {
public:
    void add_task_to_work_queue(std::unique_ptr<Task> task){
        m_tasks.push(std::move(task));
    }
};

class TimeCutQueue : public TaskQueue {
public:
    int time_threshold=50;
    int count=1;
    int acc=1;

    int run_count=0;
    void execute_for_a_time(){
        if(m_tasks.size()==0){
            return;
        }
        auto start = std::chrono::high_resolution_clock::now();
        while (m_tasks.size() > 0){
            if(std::chrono::high_resolution_clock::now()-start>std::chrono::milliseconds(time_threshold)){
                count=acc;
                break;
            }else{
                auto start2 = std::chrono::high_resolution_clock::now();
                m_tasks.front()->execute();
                m_tasks.pop();
                auto end2 = std::chrono::high_resolution_clock::now();
                std::cout << "execute_for_a_time:" << std::chrono::duration_cast<std::chrono::milliseconds>(end2-start2).count() << std::endl;
                }
        }
        run_count++;
        if(m_tasks.size()==0){
            std::cout << "run_count:" << run_count << std::endl;
        }
    }//execute_for_a_time
};

class TimeCountDownQueue : public TaskQueue {
public:
    int time_down=50;
    void exectute(){
        if(time_down-- >0){
            while (m_tasks.size() > 0){
                m_tasks.front()->execute();
                m_tasks.pop();
            }
        }
    }
};