#pragma once

class tree {
public:
	tree(int value = 0);
	~tree();
	bool insert_integer(int value);
	void print_tree();
	void terminate_tree();
	bool search(int value);
private:
	int Value = 0;
	tree * left;
	tree * right;
};


