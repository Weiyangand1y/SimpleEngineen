#include <random>

class RandomGenerator {
public:
    RandomGenerator() : m_randomEngine(std::random_device()()) {}

    // 生成一个在[min, max]范围内的随机整数
    int getRandomInt(int min, int max) {
        std::uniform_int_distribution<int> distribution(min, max);
        return distribution(m_randomEngine);
    }

    // 生成一个在[min, max]范围内的随机浮点数
    float getRandomFloat(float min, float max) {
        std::uniform_real_distribution<float> distribution(min, max);
        return distribution(m_randomEngine);
    }

private:
    std::mt19937 m_randomEngine;
};