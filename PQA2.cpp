#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <stdexcept>

class PriorityQueueArray {
private:
	struct Element {
		int priority;
		size_t order;       // kolejność wstawienia
		std::string value;
	};

	std::vector<Element> data;
	size_t insert_counter = 0;

	// porównanie
	static bool less_than(const Element& a, const Element& b) {
		if (a.priority != b.priority)
			return a.priority < b.priority;
		return a.order > b.order;
	}

public:
	// dodanie elementu
	void insert(const std::string& value, int priority) {
		std::cout << ">> Dodawanie elementu: '" << value << "' z priorytetem "
			<< priority << " (order=" << insert_counter << ")\n";
		data.push_back({ priority, insert_counter++, value });
	}

	// usunięcie i zwrócenie elementu o najwyższym priorytecie (FIFO przy tych samych)
	std::string extract_max() {
		if (data.empty()) throw std::runtime_error("Kolejka jest pusta");

		auto max_it = std::max_element(
			data.begin(), data.end(),
			[](auto& a, auto& b) { return less_than(a, b); }
		);

		std::string val = max_it->value;
		int pr = max_it->priority;
		size_t ord = max_it->order;
		std::cout << ">> Usuwanie elementu o najwiekszym priorytecie: '"
			<< val << "' (priorytet=" << pr
			<< ", order=" << ord << ")\n";

		data.erase(max_it);
		return val;
	}

	// podgląd peek
	std::string peek() const {
		if (data.empty()) throw std::runtime_error("Kolejka jest pusta");

		auto max_it = std::max_element(
			data.begin(), data.end(),
			[](auto& a, auto& b) { return less_than(a, b); }
		);

		std::cout << ">> Najwiekszy priorytet ma: '"
			<< max_it->value << "' (priorytet=" << max_it->priority
			<< ", order=" << max_it->order << ")\n";
		return max_it->value;
	}

	// zmiana priorytetu dla danego value
	void modify_key(const std::string& value, int new_priority) {
		std::cout << ">> Zmiana priorytetu elementu '" << value
			<< "' na " << new_priority << "\n";
		for (auto& e : data) {
			if (e.value == value) {
				e.priority = new_priority;
				return;
			}
		}
		throw std::runtime_error("Nie znaleziono elementu: " + value);
	}

	size_t return_size() const {
		return data.size();
	}

	// drukuj całą kolejkę
	void print_queue() const {
		std::cout << "== Stan kolejki ==\n";
		for (const auto& e : data) {
			std::cout << "   • " << e.value
				<< " (priorytet: " << e.priority
				<< ", order: " << e.order << ")\n";
		}
		std::cout << "==================\n";
	}
};
