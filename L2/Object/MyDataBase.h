#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
template<typename T>
class MyDatabase {
private:
    std::vector<T> records;
public:
    // 创建记录
    template<typename Func>
    void insert(Func initializer) {
        T newRecord;
        initializer(newRecord);
        records.push_back(newRecord);
    }

    // 读取记录
    // SELECT * FROM records WHERE condition
    template<typename Condition>
    void select_where(Condition condition, std::vector<T>* result_ptr=nullptr) {
        std::for_each(records.begin(), records.end(), [&](auto& record) {
            if (condition(record)) {
                if(result_ptr)result_ptr->push_back(record);
            }
        });
    }

    void select_all(std::function<void(T& record)> callback) {
        std::for_each(records.begin(), records.end(), [&](auto& record) {
            callback(record);
        });
    }

    // 更新记录
    template <typename Container, typename Condition, typename Updater>
    void update_where(Container& records, Condition condition, Updater updater) {
        std::for_each(records.begin(), records.end(), [&](auto& record) {
            if (condition(record)) {
                updater(record);
            }
        });
    }

    // 删除记录
    // 删除记录
    template<typename Condition>
    void delete_where(Condition condition) {
        auto it = std::remove_if(records.begin(), records.end(), [&](const auto& record) {
            return condition(record);
        });
        records.erase(it, records.end());
    }
    
    // 联表查询
    // template<typename Func>
    // void join(Func predicate, std::function<void(const Record&, const Record&, JoinRecord&)> resultBuilder) {
    //     for (const auto& record1 : records1) {
    //         for (const auto& record2 : records2) {
    //             if (predicate(record1, record2)) {
    //                 JoinRecord joinRecord;
    //                 resultBuilder(record1, record2, joinRecord);
    //                 // 输出联表查询结果
    //                 std::cout << "JoinRecord: " << joinRecord.id << " - " << joinRecord.name << " - " << joinRecord.extraInfo << std::endl;
    //             }
    //         }
    //     }
    // }
};