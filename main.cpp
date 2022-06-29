#include <iostream>

#include "LinkedList.h"

int main()
{
	//Create the linked list using ints (any type can be used)
	linkedList<int> list = linkedList<int>();

	//insert values into the list
	list.insert(1521, 0);
	list.insert(12442, 1);
	list.insert(5893, 2);
	list.insert(125815, 1);
	list.insert(125, 2);

	//get the values at the given index
	std::cout << list.valueAt(0) << std::endl;
	std::cout << list.valueAt(1) << std::endl;
	std::cout << list.valueAt(2) << std::endl;
	std::cout << list.valueAt(3) << std::endl;
	std::cout << list.valueAt(4) << std::endl << std::endl;

	//remove the 1st element
	list.remove(1);

	//get the values again
	std::cout << list.valueAt(0) << std::endl;
	std::cout << list.valueAt(1) << std::endl;
	std::cout << list.valueAt(2) << std::endl;
	std::cout << list.valueAt(3) << std::endl;
}