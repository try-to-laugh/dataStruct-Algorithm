#include<iostream>
#include<unordered_map>
#include<queue>
#include<functional>



namespace haffman_code {
	struct Node {
		char letter = '\0';
		int size = 0;
		Node* left = nullptr;
		Node* right = nullptr;

		Node(Node* left, Node* right) {
			this->size = left->size + right->size;
			this->left = left;
			this->right = right;
		}

		Node(char letter, int size) {
			this->letter = letter;
			this->size = size;
			this->left = nullptr;
			this->right = nullptr;
		}
	};

	Node* join_node(Node* left, Node* right) {
		return new Node(left, right);
	}

	void left_order(Node* current_node, std::unordered_map<char, std::string>& container, std::string code) {
		if (current_node == nullptr) {
			return;
		}

		if (current_node->letter != '\0') {
			std::string this_letter_code = code;
			container.insert(std::make_pair(current_node->letter, this_letter_code));
		}
		left_order(current_node->left, container, code + '0');
		left_order(current_node->right, container, code + '1');
	}

	auto code(std::string input_string) -> std::string
	{
		if(input_string.empty()) {
			return "";
		}
		
		std::unordered_map<char, int> temp;
		for (char letter : input_string) {
			auto iter = temp.find(letter);
			if (iter != temp.end()) {
				iter->second++;
			}
			else {
				temp.insert(std::make_pair(letter, 1));
			}
		}


		auto cmp = [](const Node* first, const Node* second) -> bool {
			return first->size > second->size;
		};
		std::priority_queue<Node*, std::vector<Node*>, decltype(cmp)> heap(cmp);

		for (auto iter = temp.begin(); iter != temp.end(); iter++) {
			heap.push(new Node(iter->first, iter->second));
		}


		if (heap.size() == 1) {
			std::string outputString;
			for (int i = 0; i < input_string.size(); i++) {
				outputString += "0";
			}
			return outputString;
		}

		while (heap.size() > 1) {
			Node* left = heap.top(); heap.pop();
			Node* right = heap.top(); heap.pop();
			Node* head = join_node(left, right);
			heap.push(head);
		}

		std::unordered_map<char, std::string> letter_with_code;
		Node* head = heap.top();
		left_order(head, letter_with_code, "");

		std::string output_code;
		for (char letter : input_string) {
			const auto find_iter = letter_with_code.find(letter);
			output_code += find_iter->second;
		}

		return output_code;
	}
};

int main() {
	std::string input_string;
	std::cin >> input_string;
	std::cout << haffman_code::code(input_string) << '\n';
	return 0;
}
