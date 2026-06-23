#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <string>

template <typename T>
T* findByName(const std::vector<T*>& collection, const std::string& targetName) {
    for (const auto* item : collection) {
        if (item != nullptr && item->get_name() == targetName) {
            return const_cast<T*>(item);
        }
    }
    return nullptr; 
}

#endif