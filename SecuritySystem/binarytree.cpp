#include "stdafx.h"
#include "binarytree.h"

using namespace std;


tree::tree(int value)
{
	this->Value = value;
	left = NULL;
	right = NULL;
}

tree::~tree()
{
	if (left != NULL) {
		left->terminate_tree();
	}
	if (right != NULL) {
		right->terminate_tree();
	}

}
bool tree::insert_integer(int value)
{
	if (this == NULL) return false;
	if (this->Value == value) return false;
	if (this->Value > value) {
		if (left == NULL)
		{
			tree* n = new tree(value);
			left = n;
		}
		else {
			if (left->insert_integer(value) == false)
				return false;
		}
	}
	else if (this->Value < value)
	{
		if (right == NULL)
		{
			tree* n = new tree(value);
			right = n;
		}
		else {
			if (right->insert_integer(value) == false)
				return false;
		}
	}
	return true;
}

void tree::print_tree()
{
	if (left != NULL) {
		left->print_tree();
	}
	cout << Value << "\n";
	if (right != NULL) {
		right->print_tree();
	}
}

void tree::terminate_tree()
{
	delete this;
}

bool tree::search(int value)
{
	if (this->Value == value)
		return true;

	if (left != NULL) {
		if (left->search(value))
			return true;
	}
	if (right != NULL) {
		if (right->search(value))
			return true;
	}

	return false;
}
