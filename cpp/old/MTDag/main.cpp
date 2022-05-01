#include <algorithm>
#include <atomic>
#include <chrono>
#include <functional>
#include <memory>
#include <mutex>
#include <random>
#include <thread>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include <boost/asio.hpp>
#include <spdlog/spdlog.h>

std::mutex done_mutex;
std::condition_variable condition_variable;

class Task {
public:
    Task(std::string name, std::function<void()> function) : name_(name), function_(function) {}

    void add_predecessor(Task *predecessor) {
        predecessors_.push_back(predecessor);
    }

    bool done() {
        return done_;
    }

    bool all_predecessors_done() {
        return std::all_of(predecessors_.begin(), predecessors_.end(), [](Task *task) {
            return task->done();
        });
    }

    std::string name() {
        return name_;
    }

    void execute() {
        if (!all_predecessors_done()) {
            spdlog::error("Something went horribly wrong");
            exit(1);
        }

        spdlog::info("Executing task {}", name_);
        function_();
        spdlog::info("Task {} done", name_);

        {
            std::lock_guard<std::mutex> guard{done_mutex};
            done_ = true;
        }

        condition_variable.notify_one();
    }

private:
    std::function<void()> function_;
    std::vector<Task *> predecessors_;
    std::string name_;
    bool done_ = false;
};

int random_int(int min, int max) {
    static std::random_device rd{};
    static std::mt19937 gen{rd()};
    static std::uniform_int_distribution<int> dist{min, max};
    return dist(gen);
}

int main() {
    spdlog::set_level(spdlog::level::info);
    spdlog::info("Hello World");

    std::mutex thread_pool_mutex;
    boost::asio::thread_pool thread_pool{12};
    boost::asio::post(thread_pool, []() {
        spdlog::info("Hello from thread pool!");
    });

    auto tasks = std::unordered_map<std::string, std::unique_ptr<Task>>{};

    auto thread_function = []() {
        auto iterations = random_int(500'000'000, 1'000'000'000);
        for (int i = 0; i < iterations; i++) {} 
    };

    auto add_task = [&](std::string name) {
        tasks[name] = std::make_unique<Task>(name, thread_function);
    };

    auto add_predecessor = [&](std::string name, std::string predecessor) {
        tasks[name]->add_predecessor(tasks[predecessor].get());
    };

    for (const auto &name : std::vector<std::string>{"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K"}) {
        add_task(name);
    }

    add_predecessor("K", "H");
    add_predecessor("K", "I");
    add_predecessor("K", "J");

    add_predecessor("H", "D");
    add_predecessor("I", "E");
    add_predecessor("I", "F");
    add_predecessor("J", "G");

    add_predecessor("D", "B");
    add_predecessor("E", "B");
    add_predecessor("F", "C");
    add_predecessor("G", "C");

    add_predecessor("B", "A");
    add_predecessor("C", "A");

    auto execute_task_in_thread_pool = [&](Task *task) {
        std::lock_guard<std::mutex> guard{thread_pool_mutex};

        boost::asio::post(thread_pool, [=]() {
            task->execute();
        });
    };

    std::thread scheduling_thread{[&]() {
        spdlog::info("Starting scheduling thread");

        std::unordered_set<Task *> candidates;
        for (auto &pair : tasks) {
            auto *task = pair.second.get();
            candidates.insert(task);
        }

        while (!candidates.empty()) {
            // Wait for any of the tasks having all predecessors done.
            std::unique_lock<std::mutex> lock{done_mutex};
            condition_variable.wait(lock, [&]() {
                return std::any_of(candidates.begin(), candidates.end(), [](Task *t) { return t->all_predecessors_done(); });
            });

            spdlog::info("Scheduler running");
            for (auto it = candidates.begin(); it != candidates.end();) {
                Task *task = *it;
                if (task->all_predecessors_done()) {
                    spdlog::info("Scheduling task {}", task->name());
                    execute_task_in_thread_pool(task);
                    it = candidates.erase(it);
                } else {
                    it++;
                }
            }
        }
    }};

    scheduling_thread.join();
    thread_pool.join();
    return 0;
}