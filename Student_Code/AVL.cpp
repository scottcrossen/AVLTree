#include "AVL.h"
//cout << "flag ## value: " << current->value << " height: " << current->height << " height_left: " << get_height(current->left_child) << " height_right: " << get_height(current->right_child); cin.get();

/*
* Deconstructor
*/
AVL::~AVL(void){
	AVL::clear();
}
/*
* Returns the root node for this tree
*
* @return the root node for this tree.
*/
NodeInterface* AVL::getRootNode(){
	return root;
}

/*
* Attempts to add the given int to the AVL tree
*
* @return true if added
* @return false if unsuccessful (i.e. the int is already in tree)
*/
bool AVL::add(int data){
	if (root != nullptr)
		return AVL::add_this(root, data);
	else{
		root = new Node(data);
		return true;
	}
}
bool AVL::add_this(Node* &current, int value){
	bool output = false;
	if (current->value == value) return false;
	else if (value < current->value && current->left_child == nullptr){
		Node* new_node=new Node(value);
		current->left_child=new_node;
		if (current->height == 1) current->height = 2;
		output=true;
	}
	else if (value > current->value && current->right_child == nullptr){
		Node* new_node=new Node(value);
		current->right_child = new_node;
		if (current->height == 1) current->height = 2;
		output=true;
	}
	else if (value < current->value && current->left_child != nullptr){
		output=add_this(current->left_child, value);
		if (output && AVL::get_height(current->left_child) >= current->height) current->height = current->left_child->height + 1;
	}
	else if (value > current->value && current->right_child != nullptr){
		output = add_this(current->right_child, value);
		if (output && AVL::get_height(current->right_child) >= current->height) current->height = current->right_child->height + 1;
	}
	if (output) balance(current);
	return output;
}

/*
* Attempts to remove the given int from the AVL tree
*
* @return true if successfully removed
* @return false if remove is unsuccessful(i.e. the int is not in the tree)
*/
bool AVL::remove(int data){
	return AVL::remove_this(root, data);
}
bool AVL::remove_this(Node* &current, int value){
	bool output = false;
	if (current == nullptr) return false;
	else if (value < current->value) output = remove_this(current->left_child, value);
	else if (value > current->value) output = remove_this(current->right_child, value);
	else if (current->left_child == nullptr){
		Node* temp = current;
		current = current->right_child;
		delete temp;
		output = true;
	}
	else if (current->right_child == nullptr){
		Node* temp = current;
		current = current->left_child;
		delete temp;
		output = true;
	}
	else {
		current->value = AVL::find_max(current->left_child);
		output = AVL::remove_this(current->left_child, current->value);
	}
	if (current != nullptr){
		//if (current->height <= AVL::get_height(current->right_child)) current->height = current->right_child->height + 1;
		//if (current->height <= AVL::get_height(current->left_child)) current->height = current->left_child->height + 1;
		if (current->height > AVL::get_height(current->right_child) + 1 && AVL::get_height(current->right_child) >= AVL::get_height(current->left_child))
			current->height = get_height(current->right_child) + 1;
		if (current->height > AVL::get_height(current->left_child) + 1 && AVL::get_height(current->left_child) >= AVL::get_height(current->right_child))
			current->height = get_height(current->left_child) + 1;
		balance(current);
	}
	return output;
}
int AVL::find_max(Node* current){
	if (current->right_child==nullptr) return current->value;
	else return AVL::find_max(current->right_child);
}
/*
* Removes all nodes from the tree, resulting in an empty tree.
*/
void AVL::clear(){
	if (root != nullptr) AVL::clear_this(root);
	root=nullptr;
	return;
}
void AVL::clear_this(Node* &current){
	if(current->left_child != nullptr)
		AVL::clear_this(current->left_child);
	if(current->right_child != nullptr)
		AVL::clear_this(current->right_child);
	delete current;
	return;
}
/*
* Returns the height of a given node. 0 if empty.
*
* @return height of node if successfull.
*/
int AVL::get_height(Node* current){
	if (current == nullptr) return 0;
	else return current -> height;
}
/*
* Determines if a node needs to be balanced and then calls the appropriate balancing function.
*/
void AVL::balance(Node* &current){
	if (get_height(current->left_child) - get_height(current->right_child) > 1){
		if (get_height(current->left_child->right_child) > get_height(current->left_child->left_child))
			rotate_left(current->left_child);	// double right rotation.
		rotate_right(current);
	}
	else if (get_height(current->right_child) - get_height(current->left_child) > 1){
		if (get_height(current->right_child->left_child) > get_height(current->right_child->right_child))
			rotate_right(current->right_child);	// double left rotation.
		rotate_left(current);
	}
}
/*
* does a single right rotation.
*/
void AVL::rotate_right(Node* &current){
	Node* temporary = current->left_child;
	current->left_child = temporary->right_child;
	temporary->right_child = current;
	current = temporary;
	if (get_height(current->right_child) > 0){
		if (get_height(current->right_child->right_child) > get_height(current->right_child->left_child))
			current->right_child->height = get_height(current->right_child->right_child) + 1;
		else current->right_child->height = get_height(current->right_child->left_child) + 1;
	}
	else current->right_child->height = 1;
	if (get_height(current->right_child) > get_height(current->left_child))
		current->height = get_height(current->right_child) + 1;
	else current->height = get_height(current->left_child) + 1;
	return;
}
/*
* does a single left rotation.
*/
void AVL::rotate_left(Node* &current){
	Node* temporary = current->right_child;
	current->right_child = temporary->left_child;
	temporary->left_child = current;
	current = temporary;
	if (get_height(current->left_child) > 0){
		if (get_height(current->left_child->left_child) > get_height(current->left_child->right_child))
			current->left_child->height = get_height(current->left_child->left_child) + 1;
		else current->left_child->height = get_height(current->left_child->right_child) + 1;
	}
	else current->left_child->height = 1;
	if (get_height(current->right_child) > get_height(current->left_child))
		current->height = get_height(current->right_child) + 1;
	else current->height = get_height(current->left_child) + 1;
	return;
}