#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <atomic>
#include <chrono>

std::atomic<int> COUNTER(1); // Global counter starting from 1
std::vector<int> histogram(1001, 0); // Histogram for stopping times from 0 to 1000
std::mutex histogram_mutex; // Mutex to protect access to shared resources
bool use_lock = true; // Determines if locks should be used

void compute_collatz(int num) {
    int stopping_time = 0;
    long long current = num;
    while (current != 1 && stopping_time < 1000) {
        if (current % 2 == 0) {
            current /= 2;
        } else {
            current = 3 * current + 1;
        }
        stopping_time++;
    }

    if (stopping_time >= 1000) {
        stopping_time = 1000;
    }

    if (use_lock) {
        std::lock_guard<std::mutex> lock(histogram_mutex);
        histogram[stopping_time]++;
    } else {
        histogram[stopping_time]++;
    }
}

void collatz_worker(int N) {
    while (true) {
        int num = COUNTER++;
        if (num > N) {
            break;
        }
        compute_collatz(num);
    }
}

void launch_threads(int N, int T) {
    std::vector<std::thread> threads;
    for (int i = 0; i < T; ++i) {
        threads.emplace_back(collatz_worker, N);
    }

    for (auto& thread : threads) {
        thread.join();
    }
}

void print_histogram() {
    for (int i = 0; i <= 1000; ++i) {
        if (histogram[i] > 0) {
            std::cout << i << ",frequency_of_stopping_time(" << i << ")" << std::endl;
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <N> <T> [-nolock]" << std::endl;
        return 1;
    }

    int N = std::stoi(argv[1]);
    int T = std::stoi(argv[2]);
    if (argc == 4 && std::string(argv[3]) == "-nolock") {
        use_lock = false;
    }

    auto start_time = std::chrono::high_resolution_clock::now();

    launch_threads(N, T);

    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end_time - start_time;

    print_histogram();

    std::cerr << N << "," << T << "," << elapsed.count() << std::endl;

    return 0;
}