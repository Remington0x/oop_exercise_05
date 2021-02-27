#ifndef STACK_HPP
#define STACK_HPP

#include <iostream>
#include <memory>

template<class T>
class TStackNode;

template<class T>
class TStack;

template<class T>
void operator ++ (std::shared_ptr< TStackNode<T> > & curStackNode) {
	if (curStackNode) {
		curStackNode = curStackNode->Next;
	} else {
		throw(std::runtime_error("Iterator points to nullptr!"));
	}
}

template<class T>
bool operator != (const TStackNode<T> & lhs, const TStackNode<T> & rhs) {
	return &lhs.Data != &rhs.Data;
}

template<class T>
bool operator == (const TStackNode<T> & lhs, const TStackNode<T> & rhs) {
	return &lhs.Data == &rhs.Data;
}

template<class T>
std::ostream & operator << (std::ostream & out, const TStackNode<T> & curStackNode) {
	out << curStackNode.Data;
	return out;
}

template<class T>
class TStackNode {
public:
	T Data;
	std::shared_ptr< TStackNode<T> > Next;
public:
	TStackNode() noexcept : Data(), Next(nullptr) {};
	explicit TStackNode(const T & elem) noexcept : Data(elem), Next(nullptr) {};
	friend void operator ++ <> (std::shared_ptr< TStackNode<T> > & curStackNode);
	friend bool operator != <> (const TStackNode<T> & lhs, const TStackNode<T> & rhs);
	friend bool operator == <> (const TStackNode<T> & lhs, const TStackNode<T> & rhs);
	friend std::ostream & operator << <> (std::ostream & out, const TStackNode<T> & curStackNode);
	friend class TStack<T>;
};

template<class T>
class TStack {
private:
	std::shared_ptr< TStackNode<T> > TopNode;
public:
	class iterator {
	private:
		std::shared_ptr< TStackNode<T> > ptr;
	public:
		using iterator_category = std::forward_iterator_tag;
		using difference_type = std::ptrdiff_t;
		using value_type = T;
		using pointer = T*;
		using reference = T&;

		iterator() : ptr(nullptr) {}
		iterator(const std::shared_ptr< TStackNode<T> > & anotherPtr) : ptr(anotherPtr) {}

		bool IsNullptr() {
			return ptr == nullptr;
		}

		friend void operator ++ (iterator & it) {
			++it.ptr;
		}

		friend bool operator != (const iterator & lhs, const iterator & rhs) {
			return lhs.ptr != rhs.ptr;
		}

		friend std::ostream & operator << (std::ostream & out, const iterator & it) {
			out << *it.ptr;
			return out;
		}

		TStackNode<T>& operator * () {
			return *ptr;
		}
	};

	iterator begin();
	iterator end();

	TStack() noexcept : TopNode(nullptr) {};
	void Pop();
	void Push(const T & elem);
	T Top();
	void Erase(iterator it);
	void Insert(iterator it, const T & elem);
};

template<class T>
typename TStack<T>::iterator TStack<T>::begin() {
	return TStack<T>::iterator(TopNode);
}

template<class T>
typename TStack<T>::iterator TStack<T>::end() {
	return TStack<T>::iterator(nullptr);
}

template<class T>
void TStack<T>::Pop() {
	if (TopNode) {
		TopNode = TopNode->Next;
	} else {
		throw(std::runtime_error("Stack is empty!"));
	}
}

template<class T>
void TStack<T>::Push(const T & elem) {
	TStackNode<T>* newNode = new TStackNode(elem);
	std::shared_ptr< TStackNode<T> > newNodeShared(newNode);
	newNodeShared->Next = TopNode;
	TopNode = newNodeShared;
}

template<class T>
T TStack<T>::Top() {
	if (TopNode) {
		return TopNode->Data;
	} else {
		throw(std::runtime_error("Stack is empty!"));
	}
}

template<class T>
void TStack<T>::Erase(TStack<T>::iterator it) {
	if (it.IsNullptr()) {
		throw(std::runtime_error("Iterator points to nullptr!"));
	} else {
		if (*it == *TopNode) {
			TopNode = TopNode->Next;
		} else {
			std::shared_ptr< TStackNode<T> > prevNode = TopNode;
			while (*prevNode->Next != *it) {
				++prevNode;
			}
			prevNode->Next = prevNode->Next->Next;
		}
	}
}

template<class T>
void TStack<T>::Insert(TStack<T>::iterator it, const T & elem) {
	TStackNode<T>* newNode = new TStackNode(elem);
	std::shared_ptr< TStackNode<T> > newNodeShared(newNode);
	if (TopNode) {
		if (*it == *TopNode) {
			newNodeShared->Next = TopNode;
			TopNode = newNodeShared;
			return;
		}
		std::shared_ptr< TStackNode<T> > prevNode = TopNode;
		if (it.IsNullptr()) {
			while (prevNode->Next != nullptr) {
				prevNode = prevNode->Next;
			}
			prevNode->Next = newNodeShared;
		} else {
			while (*prevNode != *it) {
				prevNode = prevNode->Next;
			}
			newNodeShared->Next = prevNode->Next;
			prevNode->Next = newNodeShared;
			std::swap(prevNode->Data, prevNode->Next->Data);
		}
	} else {
		TopNode = newNodeShared;
	}

}

#endif
