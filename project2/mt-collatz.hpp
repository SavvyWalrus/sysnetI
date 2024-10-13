#ifndef MT_COLLATZ_HPP
#define MT_COLLATZ_HPP

#include <vector>
#include <mutex>
#include <atomic>

// Global variables
extern std::atomic<int> COUNTER;
extern std::vector<int> histogram;
extern std::mutex histogram_mutex;
extern bool use_lock;

// Function declarations
void compute_collatz(int num);
void collatz_worker(int N);
void launch_threads(int N, int T);
void print_histogram();

#endif // MT_COLLATZ_HPP