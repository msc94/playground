#pragma once

#include <memory>
#include <optional>
#include <stdexcept>
#include <algorithm>

template <class T>
class BinaryTreeNode
{
private:
	T _element;
	std::unique_ptr<BinaryTreeNode<T>> left = nullptr, right = nullptr;
public:
	BinaryTreeNode(T element) {
		_element = element;
	}

	void add(T element) {
		if (_element == element) {
			return;
		}
		else if (element > _element) {
			if (right) {
				right->add(element);
			}
			else {
				right = std::make_unique<BinaryTreeNode<T>>(element);
			}
		}
		else if (element < _element) {
			if (left) {
				left->add(element);
			}
			else {
				left = std::make_unique<BinaryTreeNode<T>>(element);
			}
		}
		else {
			throw new std::runtime_error("what?");
		}
	}

	bool has(T element) {
		if (_element == element) {
			return true;
		}
		if (element < _element && left && left->has(element)) {
			return true;
		}
		if (element > _element && right && right->has(element)) {
			return true;
		}
		return false;
	}

	int height() {
		auto left_height = left ? left->height() : 0;
		auto right_height = right ? right->height() : 0;
		return std::max(left_height, right_height) + 1;
	}
};

template <class T>
class BinaryTree
{
private:
	std::unique_ptr<BinaryTreeNode<T>> _root = nullptr;
public:
	BinaryTree() = default;

	// Add element
	void add(T element)	{
		if (!_root) {
			_root = std::make_unique<BinaryTreeNode<T>>(element);
			return;
		}
		_root->add(element);
	}

	int height() {
		return _root->height();
	}

	bool has(T element) {
		return _root->has(element);
	}
};