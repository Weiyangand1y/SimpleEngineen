#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <map>
template<typename T>
class MyDatabase {
private:
    std::map<std::string, T> records;
public:
    using Func=std::function<void(T&)>;
    // 创建记录
    template<typename Func>
    void insert(std::string key,Func initializer) {
        T newRecord;
        initializer(newRecord);
        records[key]=newRecord;
    }


    void select_by_key(const std::string& id,std::function<void(T& record)> callback){
        auto it = records.find(id);
        if(it == records.end()){
            T empty;
            callback(empty);
            return;
        }
        callback(it->second);
    }


    void select_all(std::function<void(T& record)> callback) {
        std::for_each(records.begin(), records.end(), [&](auto& record) {
            callback(record.second);
        });
    }
    template<typename Condition>
    void select_one(Condition condition,Func callback){
        for(auto& [key,record]:records){
            if(condition(record)){
                callback(record);
                break;
            }
        }
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
    template<typename Condition>
    void delete_where(Condition condition) {
        auto it = std::remove_if(records.begin(), records.end(), [&](const auto& record) {
            return condition(record);
        });
        records.erase(it, records.end());
    }

    void delete_by_id(const std::string& key) {
        records.erase(key);
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