#include<iostream>
#include<vector>
#include<exception>



class splay_tree {
public:

	std::vector<int> to_vector() {
		std::vector<int> temp;
		_in_oder(this->head, temp);
		return temp;
	}

	bool insert(int data) {
		Node* new_node = _insert(this->head, data);
		if (new_node != nullptr) {
			this->head = _splay(new_node);
			this->size++;
			return true;
		}
		return false;
	}

	bool find(int to_find) {
		Node* new_node = _find(this->head, to_find);
		if (new_node != nullptr) {
			this->head = _splay(new_node);
			return true;
		}
		return false;
	}

	int at(size_t position) {
		if (position >= this->size) {
			std::out_of_range e("out of range spay_tree::at(invalid arg)");
		}
		_splay(_at(head, position + 1));
		return head->value;
	}

	long long sum_index_range(size_t first_position, size_t second_position) {
		if (first_position >= second_position || second_position > size) {
			std::out_of_range e("out_of_range   splay_tree::segment_sum(invalid arg)");
			throw e;
		}
		return _s_iRange(first_position + 1, second_position);
	}

	int get_max() {
		if (size == 0) {
			std::out_of_range new_exception("splay_tree::get_max(invalid parametr) tree is empty");
			throw new_exception;
		}
		_splay(_get_max(head));
		return head->value;
	}

	int get_min() {
		if (size == 0) {
			std::out_of_range new_exception("splay_tree::get_min(invalid parametr) tree is empty");
			throw new_exception;
		}
		_splay(_get_min(head));
		return head->value;
	}

	bool erase(int element) {
		if (find(element)) {
			_delete_head();
			this->size--;
			return true;
		}
		return false;
	}

	long long sum_values_range(int first, int second) {
		if (first > second) {
			std::invalid_argument new_exception("splay_tree::sum_between(invalid parametr)");
			throw new_exception;
		}
		return this->_sum_vRange(first, second);
	}


private:
	struct Node {
		int value = 0;
		Node* parent = nullptr;
		Node* right = nullptr;
		Node* left = nullptr;
		long long sum = 0;
		size_t subtree_size = 1;

		Node(int value_) {
			this->value = value_;
			this->sum = value_;
		}

		static void set_parent(Node* current_node, Node* parent_node) {
			if (current_node == nullptr) {
				return;
			}
			current_node->parent = parent_node;
		}

		static size_t get_tree_size(Node* current_node) {
			return (current_node == nullptr) ? 0 : current_node->subtree_size;
		}

		static long long get_key_sum(Node* current_node) {
			return (current_node == nullptr) ? 0 : current_node->sum;
		}
	};

	long long _sum_vRange(int first, int second) {

		bool l_flag = false;
		bool r_flag = false;

		long long result =  Node::get_key_sum(head);

		Node* left_bound = _find_left_bound(head, first);
		if (left_bound != nullptr) {
			_splay(left_bound);
			result -= Node::get_key_sum(this->head->left);
			l_flag = true;
		}

		Node* right_bound = _find_right_bound(head, second);
		if (right_bound != nullptr && l_flag) {
			_splay(right_bound);
			result -= Node::get_key_sum(this->head->right);
			r_flag = true;
		}
		
		return (r_flag && l_flag) ? result : 0;
	}

	Node* _find_left_bound(Node* current_node, int bound) {
		if (current_node == nullptr || current_node->value == bound) {
			return current_node;
		}
		else if (current_node->value > bound) {
			Node* next_bound = _find_left_bound(current_node->left, bound);
			return (next_bound == nullptr) ? current_node : next_bound;
		}
		return _find_left_bound(current_node->right, bound);
	}

	Node* _find_right_bound(Node* current_node, int bound) {
		if (current_node == nullptr || current_node->value == bound) {
			return current_node;
		}
		else if (current_node->value < bound) {
			Node* next_bound = _find_right_bound(current_node->right, bound);
			return (next_bound == nullptr) ? current_node : next_bound;
		}
		return _find_right_bound(current_node->left, bound);
	}

	void _delete_head() {
		Node* first = this->head->left;
		Node* second = this->head->right;
		Node::set_parent(first, nullptr);
		Node::set_parent(second, nullptr);

		this->head->right = this->head->left = nullptr;
		delete this->head;

		this->head = _merge(first, second);
	}

	Node* _get_max(Node* current_node) {
		return (current_node->right == nullptr) ? current_node : _get_max(current_node->right);
	}

	Node* _get_min(Node* current_node) {
		return (current_node->left == nullptr) ? current_node : _get_min(current_node->left);
	}

	Node* _at(Node* currnet_node, size_t position) {
		int diff = position - Node::get_tree_size(currnet_node->left);
		if (diff == 1) {
			return currnet_node;
		}
		else if (diff > 1) {
			return _at(currnet_node->right, position - (Node::get_tree_size(currnet_node->left) + 1));
		}
		else {
			return _at(currnet_node->left, position);
		}
	}

	//по индексам
	long long _s_iRange(size_t start_position, size_t end_position) {
		int start_value = _at(this->head, start_position)->value;
		int end_value = _at(this->head, end_position)->value;

		this->head = _splay(_find(this->head, start_value));
		Node* first_part = this->head->left;
		this->head->left = nullptr;
		Node::set_parent(first_part, nullptr);
		update(this->head);

		this->head = _splay(_find(this->head, end_value));
		Node* third_part = this->head->right;
		this->head->right = nullptr;
		Node::set_parent(third_part, nullptr);
		update(this->head);

		long long result = this->head->sum;

		this->head = _merge(first_part, this->head);
		this->head = _merge(this->head, third_part);

		return result;
	}

	Node* _merge(Node* first, Node* second) {
		if (first == nullptr) {
			return second;
		}
		Node* new_head = _splay(_get_max(first));
		new_head->right = second;
		Node::set_parent(new_head->right, new_head);
		update(new_head);
		return new_head;
	}

	Node* _insert(Node* curent_node, int new_value) {
		if (curent_node == nullptr || curent_node->value == new_value) {
			return (curent_node == nullptr) ? new Node(new_value) : nullptr;
		}
		else if ((curent_node->value < new_value && curent_node->right == nullptr)
			|| (curent_node->value > new_value&& curent_node->left == nullptr)) {

			Node* new_node = new Node(new_value);
			(curent_node->value < new_value) ? curent_node->right = new_node : curent_node->left = new_node;
			Node::set_parent(new_node, curent_node);
			return new_node;
		}

		Node* direction = (curent_node->value < new_value) ? curent_node->right : curent_node->left;
		return _insert(direction, new_value);
	}

	Node* _find(Node* current_node, int to_find) {
		if (current_node == nullptr || current_node->value == to_find) {
			return (current_node == nullptr) ? nullptr : current_node;
		}
		Node* direction = (current_node->value < to_find) ? current_node->right : current_node->left;
		return _find(direction, to_find);
	}

	void _in_oder(Node* current_node, std::vector<int>& temp) {
		if (current_node == nullptr) {
			return;
		}

		_in_oder(current_node->left, temp);
		temp.push_back(current_node->value);
		_in_oder(current_node->right, temp);
	}

	Node* _splay(Node* current_node) {
		if (current_node == nullptr) {
			std::invalid_argument new_exeption("splay_tree::splay(nullptr)");
			throw new_exeption;
		}

		if (current_node->parent == nullptr) {
			return current_node;
		}

		Node* father = current_node->parent;
		Node* grandpa = father->parent;

		bool right_gf;
		bool right_fc;

		right_fc = (father->right == current_node) ? true : false;
		if (grandpa != nullptr) {
			right_gf = (grandpa->right == father) ? true : false;
			(right_fc != right_gf) ? zig_zag(grandpa, right_gf) : zig_zig(grandpa, right_gf);
			return _splay(grandpa);
		}
		else {
			zig(father, right_fc);
			return father;
		}
	}

	void zig(Node* current_node, bool right) {
		if (right) {
			std::swap(current_node->value, current_node->right->value);
			Node* left = current_node->left;
			current_node->left = current_node->right;

			current_node->right = current_node->left->right;
			Node::set_parent(current_node->right, current_node);

			current_node->left->right = current_node->left->left;
			Node::set_parent(current_node->left->right, current_node->left);

			current_node->left->left = left;
			Node::set_parent(left, current_node->left);
		}
		else {
			std::swap(current_node->value, current_node->left->value);
			Node* right = current_node->right;
			current_node->right = current_node->left;

			current_node->left = current_node->right->left;
			Node::set_parent(current_node->left, current_node);

			current_node->right->left = current_node->right->right;
			Node::set_parent(current_node->right->left, current_node->right);

			current_node->right->right = right;
			Node::set_parent(right, current_node->right);
		}
		update(current_node->left);
		update(current_node->right);
		update(current_node);
	}

	void zig_zig(Node* current_node, bool right) {
		if (right) {
			std::swap(current_node->value, current_node->right->right->value);
			Node* left = current_node->left;

			current_node->left = current_node->right;
			std::swap(current_node->left->left, current_node->left->right);

			current_node->right = current_node->left->left->right;
			Node::set_parent(current_node->right, current_node);

			current_node->left->left->right = current_node->left->right;
			Node::set_parent(current_node->left->left->right, current_node->left->left);

			current_node->left->right = current_node->left->left->left;
			Node::set_parent(current_node->left->right, current_node->left);

			current_node->left->left->left = left;
			Node::set_parent(current_node->left->left->left, current_node->left->left);

			update(current_node->left->left);
			update(current_node->left);
			update(current_node);
		}
		else {
			std::swap(current_node->value, current_node->left->left->value);
			Node* right = current_node->right;

			current_node->right = current_node->left;
			std::swap(current_node->right->right, current_node->right->left);

			current_node->left = current_node->right->right->left;
			Node::set_parent(current_node->left, current_node);

			current_node->right->right->left = current_node->right->left;
			Node::set_parent(current_node->right->right->left, current_node->right->right);

			current_node->right->left = current_node->right->right->right;
			Node::set_parent(current_node->right->left, current_node->right);

			current_node->right->right->right = right;
			Node::set_parent(current_node->right->right->right, current_node->right->right);

			update(current_node->right->right);
			update(current_node->right);
			update(current_node);
		}


	}

	void zig_zag(Node* current_node, bool right) {
		if (right) {
			std::swap(current_node->value, current_node->right->left->value);
			Node* left = current_node->left;

			current_node->left = current_node->right->left;
			Node::set_parent(current_node->left, current_node);

			current_node->right->left = current_node->left->right;
			Node::set_parent(current_node->right->left, current_node->right);

			current_node->left->right = current_node->left->left;
			Node::set_parent(current_node->left->right, current_node->left);

			current_node->left->right = current_node->left->left;
			Node::set_parent(current_node->left->right, current_node->left);

			current_node->left->left = left;
			Node::set_parent(current_node->left->left, current_node->left);


		}
		else {
			std::swap(current_node->value, current_node->left->right->value);
			Node* right = current_node->right;

			current_node->right = current_node->left->right;
			Node::set_parent(current_node->right, current_node);

			current_node->left->right = current_node->right->left;
			Node::set_parent(current_node->left->right, current_node->left);

			current_node->right->left = current_node->right->right;
			Node::set_parent(current_node->right->left, current_node->right);

			current_node->right->left = current_node->right->right;
			Node::set_parent(current_node->right->left, current_node->right);

			current_node->right->right = right;
			Node::set_parent(current_node->right->right, current_node->right);


		}

		update(current_node->right);
		update(current_node->left);
		update(current_node);
	}

	void update_sum(Node* current_node) {
		if (current_node == nullptr) {
			return;
		}
		long long result_sum = current_node->value;
		result_sum += (current_node->right == nullptr) ? 0 : current_node->right->sum;
		result_sum += (current_node->left == nullptr) ? 0 : current_node->left->sum;

		current_node->sum = result_sum;
	}

	void update_size(Node* current_node) {
		if (current_node == nullptr) {
			return;
		}

		size_t new_size = 1;
		new_size += (current_node->left == nullptr) ? 0 : current_node->left->subtree_size;
		new_size += (current_node->right == nullptr) ? 0 : current_node->right->subtree_size;

		current_node->subtree_size = new_size;
	}

	void update(Node* current_node) {
		update_sum(current_node);
		update_size(current_node);
	}

	size_t size = 0;
	Node* head = nullptr;
};



int main() {
	splay_tree tree;
	return 0;
}
