#include "Kolejkapriorytetowa_kopiec.h"
#include <stdexcept>
#include <algorithm>

void Kolejkapriorytetowa_kopiec::heapify_up(int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (heap[index].first <= heap[parent].first) break;
        std::swap(heap[index], heap[parent]);
        index = parent;
    }
}// Poprawia w³aœciowoœæ kopca gdy dodajemy now¹ wartoœæ powtarza siê dopóki priorytet aktualnego elementu nie jest wiêkszy ni¿ rodzic

void Kolejkapriorytetowa_kopiec::heapify_down(int index) {
    int size = heap.size();
    while (true) {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int largest = index;

        if (left < size && heap[left].first > heap[largest].first)
            largest = left;
        if (right < size && heap[right].first > heap[largest].first)
            largest = right;

        if (largest == index) break;

        std::swap(heap[index], heap[largest]);
        index = largest;
    }
}// Poprawia w³aœciwoœc kopca gdy usuwamy najwiêkszy element i wykonuje siê dopóki aktualny element jest mniejszy od któregoœ z dzieci

void Kolejkapriorytetowa_kopiec::insert(const std::string& value, int priority) {
    heap.emplace_back(priority, value);
    heapify_up(heap.size() - 1);
}// dodaje na koniec kopca nowy element jako liœæ

std::string Kolejkapriorytetowa_kopiec::extract_max() {
    if (heap.empty()) throw std::runtime_error("Heap is empty!");

    std::string max_value = heap[0].second;
    heap[0] = heap.back();
    heap.pop_back();
    heapify_down(0);

    return max_value;
}// zwraca najwiêksz¹ wartoœæ w kopcu czyli wartoœæ na pozycji 0 po czym zalepia t¹ dziurê ostatnim elementem i wykonuje heapify down

std::string Kolejkapriorytetowa_kopiec::peek() const {
    if (heap.empty()) throw std::runtime_error("Heap is empty!");
    return heap[0].second;
}// zwraca wartoœæ najwiêkszego elementu kopca, który znajdujê siê na pierwsze pozycji pojemnika

void Kolejkapriorytetowa_kopiec::modify_key(const std::string& value, int new_priority) {
    for (size_t i = 0; i < heap.size(); ++i) {
        if (heap[i].second == value) {
            int old_priority = heap[i].first;
            heap[i].first = new_priority;
            if (new_priority > old_priority) heapify_up(i);
            else heapify_down(i);
            return;
        }
    }
    throw std::runtime_error("Element not found: " + value);
}// szuka odpowiedniego elemntu i zmienia jego priorytet i zale¿nie od zmiany poprawia kopiec funkcjami heapify

size_t Kolejkapriorytetowa_kopiec::return_size() const {
    return heap.size();
}// zwraca rozmiar stryktury w czasie O(1)

void Kolejkapriorytetowa_kopiec::clear() {
    heap.clear();
}// usuwa ca³¹ zawartoœæ struktury