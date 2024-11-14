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

// Computes a Collatz sequence using the provided piecewise formula f(n) for given integer n
void compute_collatz(int num) {
    int stopping_time = 0;
    long long current = num;

    // Default max stopping time of 1000
    while (current != 1 && stopping_time < 1000) {
        if (current % 2 == 0) {
            current /= 2;
        } else {
            current = 3 * current + 1;
        }
        stopping_time++;
    }

    // Uses thread locking for shared histogram if enabled (True by default)
    if (use_lock) {
        std::lock_guard<std::mutex> lock(histogram_mutex);
        histogram[stopping_time]++;
    } else {
        histogram[stopping_time]++;
    }
}

// Main thread function for computing Collatz stopping times for values in range [1,N]
void collatz_worker(int N) {
    while (true) {
        int num = COUNTER++;
        if (num > N) {
            break;
        }
        compute_collatz(num);
    }
}

// Initializes a vector of T number of threads and joins them to await their completion
void launch_threads(int N, int T) {
    std::vector<std::thread> threads;
    for (int i = 0; i < T; ++i) {
        threads.emplace_back(collatz_worker, N);
    }

    for (auto& thread : threads) {
        thread.join();
    }
}

// Outputs the stopping times and their respective stored frequencies
void print_histogram() {
    for (int i = 0; i <= 1000; ++i) {
        if (histogram[i] > 0) {
            std::cout << i << ",frequency_of_stopping_time(" << histogram[i] << ")" << std::endl;
        }
    }
}

int main(int argc, char* argv[]) {
    // Ensures sufficient argument count for program execution
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <N> <T> [-nolock]" << std::endl;
        return 1;
    }

    // Initializes argument variables
    int N = std::stoi(argv[1]);
    int T = std::stoi(argv[2]);
    if (argc == 4 && std::string(argv[3]) == "-nolock") {
        use_lock = false;
    }

    // Stores the system time at the beginning of the Collatz calculation
    auto start_time = std::chrono::high_resolution_clock::now();

    launch_threads(N, T);

    // Finds the system time at the end of the Collatz calculation and calculates the elapsed time
    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end_time - start_time;

    print_histogram();

    // Outputs a final line listing the argument variables and the elapsed time
    std::cerr << N << "," << T << "," << elapsed.count() << std::endl;

    return 0;
}