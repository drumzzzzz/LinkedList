#include <iostream>
#include <cstring>
#include <string>
using namespace std;

class ListItem {

private:

	const char* item;
	ListItem* next = nullptr;

public:

	ListItem(const char* newItem) {
		item = newItem;
		next = nullptr;
	}

	ListItem* nextItem() {
		return next;
	}

	void setNextItem(ListItem* new_next) {
		next = new_next;
	}

	void setItem(const char* newItem)
	{
		item = newItem;
	}

	const char* view() {
		return item;
	}

};

class LinkedList {

private:
	int list_length;

	void deleteItem(ListItem* parent, ListItem* item) {
		parent->setNextItem(item->nextItem());
		delete item;
	}

public:
	ListItem* first_item;
	LinkedList(const char* newItem) {
		first_item = new ListItem(newItem);
		list_length = 1;
	}

	void addListItem(const char* newItem) {
		ListItem* new_item = new ListItem(newItem);
		ListItem* current_item = first_item;
		ListItem* next_item = first_item->nextItem();
		while (next_item != nullptr) {
			current_item = next_item;
			next_item = current_item->nextItem();
		}
		current_item->setNextItem(new_item);
		list_length += 1;
	}

	int length() {
		return list_length;
	}

	void outputLength() {
		std::cout << length() << std::endl;
	}

	void outputList() {
		std::cout << first_item->view() << std::endl;
		ListItem* next_item = first_item->nextItem();
		while (next_item != nullptr) {
			std::cout << next_item->view() << std::endl;
			next_item = next_item->nextItem();
		}
	}
};

class ListUtils : public LinkedList
{
public:
	ListUtils(const char* newItem) : LinkedList(newItem)
	{}

	// Views at item at supplied index position
	void viewItemAtIndex(int position)
	{
		// Return if invalid
		if (position > length() - 1 || position < 0)
		{
			cout << "Invalid item position (" << position << ")" << endl;
			return;
		}
		
		int index = 0;
		ListItem* next_item = first_item;

		// Iterate list
		while (next_item != nullptr)
		{
			// Display item on index
			if (index == position)
			{
				cout << "The item at index " << position << " is " << next_item->view() << endl;
				return;
			}
			next_item = next_item->nextItem();
			index++;
		}
		// Failure
		cout << "Item was not found at (" << position << ")" << endl;
	}

	// Swaps two linked list items at two supplied index positions 
	void swapItemsAtIndex(int position1, int position2)
	{
		// Return if invalid
		if (position1 > length() - 1 || position2 > length() - 1 || position1 < 0 || position2 < 0)
		{
			cout << "Swap failed: invalid position value (" << position1 << ", " << position2 << ")" << endl;
			return;
		}

		// Vars
		ListItem* next_item = first_item;
		int index = 0;
		const char* firstItem = nullptr;
		const char* secondItem = nullptr;

		// Iterate list
		while (next_item != nullptr) 
		{
			// Store item on index position
			if (index == position1)
			{
				firstItem = next_item->view();
			}
			else if (index == position2)
			{
				secondItem = next_item->view();
			}

			// Exit loop if both items have been stored
			if (firstItem != nullptr && secondItem != nullptr)
				break;

			next_item = next_item->nextItem();
			index++;
		}

		// Return if either item not stored
		if (firstItem == nullptr || secondItem == nullptr)
		{
			cout << "An item was not found, swap failed!" << endl;
			return;
		}

		next_item = first_item;
		int count = 0;
		index = 0;

		// Iterate list
		while (next_item != nullptr) 
		{
			// Swap items on position index
			if (index == position1)
			{
				next_item->setItem(secondItem);
				count++;
			}
			else if (index == position2)
			{
				next_item->setItem(firstItem);
				count++;
			}

			// Exit loop when done
			if (count == 2)
				break;

			next_item = next_item->nextItem();
			index++;
		}

		// Display message if an item was not swapped
		if (count != 2)
		{
			cout << "An item swap failed!" << endl;
		}
	}
};

int main(){
	// Generate list
	ListUtils lu("item 0");
	string str;
	
	for (int i = 1; i < 11; i++)
	{
		str = ("item " + to_string(i));
		char* cstr = new char(str.length());
		cstr = strdup(str.c_str());
		lu.addListItem(cstr);
	}

	// Display length and list contents 
	lu.outputLength();
	lu.outputList();
	cout << endl;
	
	// Try some invalid operations
	lu.viewItemAtIndex(-1);
	lu.viewItemAtIndex(lu.length() + 10);
	lu.swapItemsAtIndex(-1, lu.length() + 10);
	lu.swapItemsAtIndex(lu.length() + 10, -1);
	cout << endl;
	
	// view items
	lu.viewItemAtIndex(0);
	lu.viewItemAtIndex(7);
	lu.viewItemAtIndex(9);
	lu.viewItemAtIndex(2);
	cout << endl;

	// Swap items
	lu.swapItemsAtIndex(0, 7);
	lu.swapItemsAtIndex(9, 2);

	// View items
	lu.viewItemAtIndex(0);
	lu.viewItemAtIndex(7);
	lu.viewItemAtIndex(9);
	lu.viewItemAtIndex(2);
	cout << endl;

	// Display length and list contents 
	lu.outputLength();
	lu.outputList();
}