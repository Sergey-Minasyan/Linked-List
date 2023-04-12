#include <iostream>

template<typename T>
class LinkedList
{
private:
	struct Node
	{
		T value;
		Node* next;
		Node(T v, Node* n);
		Node(T v);
	};
	Node* head;
	int list_size;
public:
	LinkedList();
	int size();
	bool isEmpty();
	Node* getNodeAt(int pos) const;
	void push_front(T value);
	void push_back(T value);
	void print() const;
	void sortedInsert(T value);
	bool isPresent(T data);
	T pop_front();
	bool deleteNode(T delValue);
	void deleteNodes(T delValue);
	void freeList();
	void reverse();
	Node* reverse(Node* head, int k);
	bool loopDetect();
	Node* loopPointDetect();
	void removeLoop();
	friend Node* intersection(Node* head1, Node* head2);
	void removeDuplicate();

};

template<typename T>
typename LinkedList<T>::Node* LinkedList<T>::getNodeAt(int pos) const
{
	Node* curr = head;
	for (int skip = 0; skip < pos; ++skip)
	{
		curr = curr->next;
	}
	return curr;
}

template<typename T>
LinkedList<T>::LinkedList()
	:head{ nullptr }, list_size{ 0 }
{}

template<typename T>
LinkedList<T>::Node::Node(T v)
{
	value = v;
	next = nullptr;
}
template<typename T>
LinkedList<T>::Node::Node(T v, Node* n)
{
	value = v;
	next = n;
}

template<typename T>
int LinkedList<T>::size()
{
	return list_size;
}

template<typename T>
bool LinkedList<T>::isEmpty()
{
	return list_size == 0;
}

template<typename T>
void LinkedList<T>::push_front(T value)
{
	Node* tmp = new Node(value, head);
	head = tmp;
	list_size++;
}

template<typename T>
void LinkedList<T>::push_back(T value)
{
	Node* tmp = new Node(value);
	Node* curr = head;

	if (head == nullptr)
	{
		head = tmp;
		return;
	}
	while (curr->next != nullptr)
	{
		curr = curr->next;
	}
	curr->next = tmp;
	list_size++;
}

template<typename T>
void LinkedList<T>::print() const
{
	Node* curr = head;
	while (curr != nullptr)
	{
		std::cout << curr->value << ' ';
		curr = curr->next;
	}
	std::cout << std::endl;
}

template<typename T>
void LinkedList<T>::sortedInsert(T value)
{
	Node* newNode = new Node(value);
	Node* curr = head;
	if (curr == nullptr || curr->value > value)
	{
		newNode->next = head;
		head = newNode;
		return;
	}

	while (curr != nullptr && curr->next->value < value)
	{
		curr = curr->next;
	}
	newNode->next = curr->next;
	curr->next = newNode;
	list_size++;
}

template<typename T>
bool LinkedList<T>::isPresent(T data)
{
	Node* curr = head;
	while (curr != nullptr)
	{
		if (curr->value == data)
			return true;
		curr = curr->next;
	}
	return false;
}

template<typename T>
T LinkedList<T>::pop_front()
{
	Node* delMe = head;
	T value = head->value;
	head = head->next;
	delete delMe;
	list_size--;
	return value;
}

template<typename T>
bool LinkedList<T>::deleteNode(T delValue)
{
	Node* curr = head;
	Node* delMe;
	if (head->value == delValue)
	{
		delMe = head;
		head = head->next;
		delete delMe;
		list_size--;
		return true;
	}
	while (curr->next != nullptr)
	{
		if (curr->next->value == delValue)
		{
			delMe = curr->next;
			curr->next = curr->next->next;
			delete delMe;
			list_size--;
			return true;
		}
		curr = curr->next;
	}
	return false;
}

template<typename T>
void LinkedList<T>::deleteNodes(T deleteValue)
{
	Node* curr = head;
	Node* nextNode;
	Node* deleteMe;

	while (curr != nullptr && curr->value == deleteValue)
	{
		deleteMe = curr;
		head = curr->next;
		delete deleteMe;
		list_size--;
	}

	while (curr != nullptr)
	{
		nextNode = curr->next;
		if (nextNode != nullptr && nextNode->value == deleteValue)
		{
			deleteMe = curr->next;
			curr->next = nextNode->next;
			delete deleteMe;
			list_size--;
		}
		else
			curr = nextNode;
	}
}

template<typename T>
void LinkedList<T>::reverse()
{
	Node* curr = head;
	Node* next = nullptr;
	Node* prev = nullptr;
	while (curr != nullptr)
	{
		next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;
	}
	head = prev;
}


template<typename T>
typename LinkedList<T>::Node* LinkedList<T>::reverse(LinkedList<T>::Node* head, int k)
{
	Node* curr = head;
	Node* next = nullptr;
	Node* prev = nullptr;
	int count = 0;
	while (count < k && curr != nullptr)
	{
		next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;
		count++;
	}
	if (next != nullptr)
	{
		head->next = reverse(next, k);
	}
	return prev;
}



template<typename T>
bool LinkedList<T>::loopDetect()
{
	Node* fastPtr = head;
	Node* slowPtr = head;
	while (fastPtr->next != nullptr && fastPtr->next->next != nullptr)
	{
		slowPtr = slowPtr->next;
		fastPtr = fastPtr->next->next;
		if (slowPtr == fastPtr)
		{
			std::cout << "Loop found" << std::endl;
			return true;
		}
		std::cout << "Loop NOT found" << std::endl;
		return false;
	}
}

template<typename T>
typename LinkedList<T>::Node* LinkedList<T>::loopPointDetect()
{
	Node* fast = head;
	Node* slow = head;
	while (fast->next != nullptr && fast->next->next != nullptr)
	{
		slow = slow->next;
		fast = fast->next->next;
		if (fast == slow)
		{
			return slow;
		}
	}
	return nullptr;
}


template<typename T>
void LinkedList<T>::removeLoop()
{
	Node* loopPoint = loopPointDetect();
	Node* first = head;

	if (loopPoint == head)
	{
		while (first->next != head)
		{
			first = first->next;
		}
		first->next = nullptr;
		return;
	}
	Node* second = loopPoint;
	while (first->next != second->next)
	{
		first = first->next;
		second = second->next;
	}
	second->next = nullptr;
}


template<typename T>
typename LinkedList<T>::Node* intersection(LinkedList<T>::Node* head1, LinkedList<T>::Node* head2)
{
	Node* tmp1 = head1;
	Node* tmp2 = head2;
	while (tmp1 != nullptr && tmp2 != nullptr)
	{
		if (tmp1 == tmp2)
			return tmp1;
		tmp1 = tmp1->next;
		tmp2 = tmp2->next;
	}
	return nullptr;
}