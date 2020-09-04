#include <iostream>
#include <vector>
#include <algorithm>


class heap_sort {
public:
	void sort(std::vector<int>& _array) {
		heap_size = _array.size();
		for (int i = heap_size / 2; i >= 0; i--) {
			shift_down(i,_array);
		}

		for (int i = _array.size() - 1; i > 0; i--) {
			std::swap(_array[i], _array[0]);
			heap_size--;
			shift_down(0, _array);
		}
	}
private:
	int shift_down(int index, std::vector<int>& _array) {
		int next_left = 2 * index + 1;
		int next_right = 2 * index + 2;
		if (next_right < heap_size) {
			int max_son = std::max(_array[next_left], _array[next_right]);
			if (max_son > _array[index]) {
				if (max_son == _array[next_left]) {
					std::swap(_array[index], _array[next_left]);
					return shift_down(next_left, _array);
				}
				std::swap(_array[index], _array[next_right]);
				return shift_down(next_right, _array); 
			}
		}
		else if (next_left < heap_size && _array[next_left] > _array[index]) {
			std::swap(_array[index], _array[next_left]);
			return shift_down(next_left, _array);
		}
		return index;
	}

	size_t heap_size;
};

bool test(std::vector<int>& _array) {
	for (int i = 0; i < _array.size() - 1; i++) {
		if (_array[i] > _array[i + 1]) {
			return false;
		}
	}
	return true;
}

int main() {
	return 0;
}