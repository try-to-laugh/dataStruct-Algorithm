#include <algorithm>
#include <cstddef>
#include <iostream>
#include <vector>

int get_length_of_longest_divisible_subsequence(const std::vector<int>& numbers) {
	std::vector<int> max_lenght;
	int result_max = 0;
	for (int i = 0; i < numbers.size(); i++) {
		int temp_max_lenght = 0;
		for (int j = i - 1; j >= 0; j--) {
			if (numbers[i] % numbers[j] == 0 && temp_max_lenght < max_lenght[j]) {
				temp_max_lenght = max_lenght[j];
			}
		}
		temp_max_lenght++;
		max_lenght.push_back(temp_max_lenght);
		result_max = (result_max > temp_max_lenght) ? result_max : temp_max_lenght;
	}
	return result_max;
}

int main(void) {
	size_t number_count;
	std::cin >> number_count;
	std::vector<int> numbers(number_count);
	for (auto& number : numbers) {
		std::cin >> number;
	}

	std::cout << get_length_of_longest_divisible_subsequence(numbers) << std::endl;
}