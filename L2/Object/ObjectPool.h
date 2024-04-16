#include <iostream>
#include <vector>
#include <stdexcept>

template<typename T>
class ObjectPool {
private:
    std::vector<T*> pool;
    std::vector<bool> available;

public:
    ObjectPool(size_t size) : pool(size), available(size, true) {}

    T* acquire() {
        for (size_t i = 0; i < available.size(); ++i) {
            if (available[i]) {
                available[i] = false;
                return pool[i];
            }
        }
        throw std::runtime_error("No objects available in the pool.");
    }

    void release(const T* obj) {
        for (size_t i = 0; i < pool.size(); ++i) {
            if (pool[i] == obj) {
                if (available[i]) {
                    throw std::invalid_argument("Object is already released.");
                }
                available[i] = true;
                return;
            }
        }
        throw std::invalid_argument("Object does not belong to this pool.");
    }
};