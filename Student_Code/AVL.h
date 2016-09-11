#pragma once
#include "AVLInterface.h"
#include "NodeInterface.h"
class AVL : public AVLInterface
{
private:
	class Node : public NodeInterface {
		public:
			int value = 0;
			int height = 1;
			Node* left_child = nullptr;
			Node* right_child = nullptr;
			Node(void){}
			Node(int value){
				this->value=value;
			}
			~Node(void){}
			int getData(){return value;}
			NodeInterface* getLeftChild(){return left_child;}
			NodeInterface* getRightChild(){return right_child;}
			int getHeight(){ return height; }
	};
	Node* root = nullptr;
	bool add_this(Node* &current, int value);
	bool remove_this(Node* &current, int value);
	int find_max(Node* current);
	void clear_this(Node* &current);
	int get_height(Node* current);
	void balance(Node* &current);
	void rotate_left(Node* &current);
	void rotate_right(Node* &current);
public:
	AVL(void){}
	~AVL(void);
	NodeInterface * getRootNode();
	bool add(int data);
	bool remove(int data);
	void clear();
};

