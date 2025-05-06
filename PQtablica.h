#pragma once

#include <string>
#include <vector>

class PriorityQueueArray {
private:
	struct Element {
		int priority;
		size_t order;
		std::string value;
	};

	std::vector<Element> data;
	size_t insert_counter = 0;

	static bool less_than(const Element& a, const Element& b);

public:
	void insert(const std::string& value, int priority);
	std::string extract_max();
	std::string peek() const;
	void modify_key(const std::string& value, int new_priority);
	size_t return_size() const;
	void print_queue() const;
};
