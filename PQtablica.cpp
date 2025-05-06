#include "PriorityQueueArray.h"
#include <iostream>
#include <algorithm>
#include <stdexcept>

bool PriorityQueueArray::less_than(const Element& a, const Element& b) {
	if (a.priority != b.priority)
		return a.priority < b.priority;
	return a.order > b.order;
}

// Dodawanie elementu
void PriorityQueueArray::insert(const std::string& value, int priority) {
	std::cout << ">> Dodawanie elementu: '" << value << "' z priorytetem "
		<< priority << " (order=" << insert_counter << ")\n";
	data.push_back({ priority, insert_counter++, value });
}

// Usunięcie elementu o najwyższym priorytecie
std::string PriorityQueueArray::extract_max() {
	if (data.empty()) throw std::runtime_error("Kolejka jest pusta");

	auto max_it = std::max_element(
		data.begin(), data.end(),
		[](const Element& a, const Element& b) { return less_than(a, b); }
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

// Podgląd elementu o najwyższym priorytecie
std::string PriorityQueueArray::peek() const {
	if (data.empty()) throw std::runtime_error("Kolejka jest pusta");

	auto max_it = std::max_element(
		data.begin(), data.end(),
		[](const Element& a, const Element& b) { return less_than(a, b); }
	);

	std::cout << ">> Najwiekszy priorytet ma: '"
		<< max_it->value << "' (priorytet=" << max_it->priority
		<< ", order=" << max_it->order << ")\n";
	return max_it->value;
}

// Zmiana priorytetu dla elementu
void PriorityQueueArray::modify_key(const std::string& value, int new_priority) {
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

// Zwrócenie liczby elementów
size_t PriorityQueueArray::return_size() const {
	return data.size();
}

// Wypisanie zawartości kolejki
void PriorityQueueArray::print_queue() const {
	std::cout << "== Stan kolejki ==\n";
	for (const auto& e : data) {
		std::cout << "   • " << e.value
			<< " (priorytet: " << e.priority
			<< ", order: " << e.order << ")\n";
	}
	std::cout << "==================\n";
}
