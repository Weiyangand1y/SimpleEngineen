#include <iostream>
#include <vector>
class IDPool {
private:
    std::vector<int> pool;
    std::vector<bool> available;
    int nextAvailableIndex;

public:
    IDPool() {}
    void init(int size) {
        pool.resize(size);
        available.resize(size, true);
        for (int i = 0; i < size; ++i) {
            pool[i] = i;
        }
        nextAvailableIndex = 0;
    }

    int allocateID() {
        if (nextAvailableIndex >= pool.size()) {
            std::cerr << "Error: Pool is full." << std::endl;
            return -1; // Error: Pool is full
        }
        int id = pool[nextAvailableIndex++];
        available[id] = false;
        return id;
    }

    void releaseID(int id) {
        if (id >= 0 && id < pool.size() && !available[id]) {
            available[id] = true;
            --nextAvailableIndex;
            std::swap(pool[id], pool[nextAvailableIndex]);
        } else {
            std::cerr << "Error: Invalid ID or already released." << std::endl;
        }
    }

    int size() const {
        return (int)pool.size();
    }
};