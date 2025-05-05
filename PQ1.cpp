#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

class PriorityQueueArray {
private:
	std::vector<std::pair<int, std::string>> data;

public:
	void insert(const std::string& value, int priority) {
		std::cout << ">> Dodaję element: '" << value << "' z priorytetem " << priority << "\n";
		data.emplace_back(priority, value);
	}

	std::string extract_max() {
		if (data.empty()) throw std::runtime_error("Kolejka jest pusta!");

		auto max_it = std::max_element(data.begin(), data.end(),
			[](const std::pair<int, std::string>& a, const std::pair<int, std::string>& b) {
				return a.first < b.first;
			});

		std::string max_value = max_it->second;
		int max_priority = max_it->first;
		std::cout << ">> Usuwam element o największym priorytecie: '" << max_value
			<< "' (priorytet " << max_priority << ")\n";

		data.erase(max_it);
		return max_value;
	}

	std::string peek() const {
		if (data.empty()) throw std::runtime_error("Kolejka jest pusta!");

		auto max_it = std::max_element(data.begin(), data.end(),
			[](const std::pair<int, std::string>& a, const std::pair<int, std::string>& b) {
				return a.first < b.first;
			});

		std::cout << ">> Największy priorytet ma: '" << max_it->second
			<< "' (priorytet " << max_it->first << ")\n";

		return max_it->second;
	}

	void modify_key(const std::string& value, int new_priority) {
		std::cout << ">> Zmieniam priorytet elementu '" << value << "' na " << new_priority << "\n";
		for (auto& elem : data) {
			if (elem.second == value) {
				elem.first = new_priority;
				return;
			}
		}
		throw std::runtime_error("Nie znaleziono elementu: " + value);
	}

	size_t return_size() const {
		return data.size();
	}

	void print_queue() const {
		std::cout << "== Stan kolejki ==\n";
		for (const auto& elem : data) {
			std::cout << "   • " << elem.second << " (priorytet: " << elem.first << ")\n";
		}
		std::cout << "==================\n";
	}
};

int main() {
	PriorityQueueArray pq;

	
	pq.insert("Task A", 5);
	pq.insert("Task B", 3);
	pq.insert("Task C", 10);
	pq.insert("Task D", 10); 

	pq.print_queue();

	pq.peek();

	pq.extract_max();
	pq.print_queue();

	pq.modify_key("Task B", 12);
	pq.print_queue();

	pq.extract_max();
	pq.print_queue();

	std::cout << ">> Rozmiar kolejki: " << pq.return_size() << "\n";

	return 0;
}
