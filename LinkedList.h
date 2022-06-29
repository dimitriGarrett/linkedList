#pragma once

#include <memory>

//Node is what is used inside the linkedList, it holds data.
template<typename T>
class Node
{
public:
	Node(T value)
	{
		m_Data = value;
		m_NextAddress = nullptr;
		m_LastAddress = nullptr;
	}

	Node()
	{
		m_Data = nullptr;
		m_NextAddress = nullptr;
		m_LastAddress = nullptr;
	}

	T& getValue()
	{
		return m_Data;
	}

	void setValue(T value)
	{
		m_Data = value;
	}

	T m_Data;
	std::shared_ptr<Node<T>> m_NextAddress;
	std::shared_ptr<Node<T>> m_LastAddress;
};

template<typename T>
class linkedList
{
public:
	linkedList() {}

	//Get the value of the node at the given index
	T& valueAt(const int index)
	{
		checkBounds(index);

		std::shared_ptr<Node<T>> temporary = head;

		int indexTemp = 0;

		while (temporary != nullptr)
		{
			if (index == indexTemp)
			{
				return temporary->getValue();
			}

			temporary = temporary->m_NextAddress;

			indexTemp++;
		}
	}

	//Get the node at the given index
	std::shared_ptr<Node<T>> nodeAt(const int index)
	{
		checkBounds(index);

		std::shared_ptr<Node<T>> temporary = head;

		int indexTemp = 0;

		while (temporary != nullptr)
		{
			if (index == indexTemp)
			{
				return temporary;
			}

			temporary = temporary->m_NextAddress;

			indexTemp++;
		}
	}

	//Add node with value to end
	const void insert_back(T value)
	{
		std::shared_ptr<Node<T>> node = std::make_shared<Node<T>>(value);

		if (head != nullptr)
		{
			node->m_NextAddress = head;
			head->m_LastAddress = node;
		}

		else
		{
			node->m_NextAddress = node;
			head = node;
		}

		if (tail != nullptr)
		{
			node->m_LastAddress = tail;
			tail->m_NextAddress = node;
		}

		else
		{
			node->m_LastAddress = node;
			tail = node;
		}

		tail = node;

		m_Size++;
	}

	//Add node with value to front
	const void insert_front(T value) noexcept
	{
		std::shared_ptr<Node<T>> newNode = std::make_shared<Node<T>>(value);

		head->m_LastAddress = newNode;

		if (tail == nullptr)
		{
			newNode->m_LastAddress = newNode;
			tail = newNode;
		}

		else
		{
			newNode->m_LastAddress = tail;
		}

		if (head == nullptr)
		{
			newNode->m_NextAddress = newNode;
		}

		else
		{
			newNode->m_NextAddress = head;
		}

		head = newNode;

		m_Size++;
	}

	//Add node with value at arbitrary position
	const void insert(T value, const int index)
	{
		if (index == 0)
		{
			if (m_Size == 0)
			{
				insert_back(value);

				return;
			}

			insert_front(value);

			return;
		}

		else if (index == m_Size)
		{
			insert_back(value);

			return;
		}

		else
		{
			int tempIndex = m_Size;

			std::shared_ptr<Node<T>> temp = tail;
			std::shared_ptr<Node<T>> nod = std::make_shared<Node<T>>(value);

			while (temp != head)
			{
				tempIndex--;

				if (tempIndex == index)
				{
					//temp == the index after the one you want
					auto last = temp->m_LastAddress;

					last->m_NextAddress = nod;
					temp->m_LastAddress = nod;

					nod->m_NextAddress = temp;
					nod->m_LastAddress = last;

					m_Size++;

					return;
				}

				temp = temp->m_LastAddress;
			}
		}
	}

	//Remove first node
	const inline void remove_front()
	{
		tail->m_NextAddress = head->m_NextAddress;
		head = head->m_NextAddress;
		head->m_LastAddress = tail;

		m_Size--;
	}

	//Remove last node
	const inline void remove_back()
	{
		head->m_LastAddress = tail->m_LastAddress;
		tail = tail->m_LastAddress;
		tail->m_NextAddress = head;

		m_Size--;
	}

	//Remove node at given index
	const void remove(const int index)
	{
		int tempIndex = m_Size;

		std::shared_ptr<Node<T>> temp = tail;

		while (temp != head)
		{
			tempIndex--;

			if (tempIndex == index + 1)
			{
				//temp == the index after the one you want
				std::shared_ptr<Node<T>> toDelete = temp->m_LastAddress;

				toDelete->m_LastAddress->m_NextAddress = temp;
				temp->m_LastAddress = toDelete->m_LastAddress;

				toDelete.reset();

				m_Size--;

				return;
			}

			temp = temp->m_LastAddress;
		}
	}

	//Get how big the list is
	const inline int size()
	{
		return m_Size;
	}

	//Check if size is 0
	bool inline is_empty()
	{
		return m_Size == 0;
	}

private:
	void checkBounds(int index)
	{
		if (index < 0 || index >= m_Size)
		{
			//CHANGE THIS if you want to handle errors differently
			throw new std::exception("Invalid Index");

			abort();
		}
	}

	std::shared_ptr<Node<T>> head = nullptr;
	std::shared_ptr<Node<T>> tail = nullptr;

	int m_Size = 0;
};