#pragma once
#include <iostream>
#include <vector>
#include <string>

class Kolejkapriorytetowa_kopiec
{
private:
    std::vector<std::pair<int, std::string>> heap;
    void heapify_up(int index);
    void heapify_down(int index);

public:
    void insert(const std::string& value, int priority);
    std::string extract_max();
    std::string peek() const;
    void modify_key(const std::string& value, int new_priority);
    size_t return_size() const;
    void clear(); // do testów
};

