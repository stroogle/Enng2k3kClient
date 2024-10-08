#include <iostream>
#include <queue>
#include <string>

class JobQueue {
private:
    std::queue<std::string> jobs; 

public:
    void addJob(const std::string& job) {
        jobs.push(job);
    }

    // Pop the most recent job from the queue
    std::string popMessage() {
        if (!jobs.empty()) {
            std::string job = jobs.front();
            jobs.pop();
            return job;
        }
        return ""; // Return an empty string if no job is available
    }
    
    bool isJobAvailable() const {
        return !jobs.empty();
    }
};