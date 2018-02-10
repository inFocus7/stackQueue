//Fabian Gonzalez
//////////////////////////////////////////////////////
// Topics: circular arrays, templated classes, dynamic arrays
//
// Implement a stackQueue using a
// circular array implementation as discussed in class.
// Your data structure must increase its array size dynamically
// if the array runs out of room.
//
// Abstractly, your stackQueue represents a list of items
// with a front and back from which items may be added
// or removed.  If you choose to add and remove from just
// one end, you effectively have a stack.  If you choose
// to add to the back and remove from the front, (or vice versa)
// you effectively have a queue, thus the name "stackQueue".
//
//
///////////////////////////////////////////////////////
//I'm assuming this isn't supposed to be a doubly linked list.
#include <iostream>
#include <string>
using namespace std;

template <class T>
class stackQueue
{
private:
	//declare your array variable and
	//any additional variables you need
	//to solve the problem
	int numItems, capacity, front, back, oldCapacity;
	T * items;

public:
	stackQueue()
	{
		numItems = 0;
		capacity = 5;
		items = new T[capacity]; //Initialize array with a capacity of 5
		//Used to initialize front and back to certain values to check if empty.
		front = -183927402;
		back = -183927402;
	}

	//Insert x to the "back" of the list of items.
	void addBack(T x)
	{
		//If empty, initialize
		if (empty() == true)
		{
			front = 0;
			back = 0;
			items[0] = x;
			numItems++;
		}
		//else if full resize
		else if (numItems == capacity)
		{
				//resize 
			resize();
				//re-sort in correct order if needed
			if(front > back) //only re-sorts if "back" is before "front", meaning it did its loop
				sort();

			addBack(x);
		}
		//else
		else
		{
			back = (back + 1) % capacity; //moves back, while being aware of the next if it's within bounds (does so by mod.)
			items[back] = x;
			numItems++;
		}
	}

	//Add x to the "front" of the list of items.
	void addFront(T x)
	{
		//If empty initialize
		if (empty() == true)
		{
			front = 0;
			back = 0;
			items[0] = x;
			numItems++;
		}
		//else if full resize
		else if (numItems == capacity)
		{
			//resize
			resize();
			//re-sort in correct order if needed
			if (front > back) //only re-sorts if "back" is before "front", meaning it did its loop
				sort();

			addFront(x);
		}
		//else
		else
		{
			//Shift all one to right && make sure there's enough space
			int index = back;
			for (int i = 0; i < numItems; i++)
			{
				items[index+1] = items[index];
				index = (index - 1) % capacity;
			}
			//set new front if needed
			items[front] = x;
			numItems++;
			back = (back + 1) % capacity; //since back had to be moved back to make the shift and add a new "front"
		}
	}

	//Remove and return the item currently at the "back" of the list
	T removeBack()
	{
		T output = items[back];
		back = (back - 1) % capacity;
		numItems--;
		return output;
	}

	//Remove and return the item currently at the "front" of the list
	T removeFront()
	{
		T output = items[front];
		front = (front + 1) % capacity;
		numItems--;
		return output;
	}

	//Is the stackQueue empty?
	bool empty()
	{
		if (front == -183927402 && back == -183927402)
			return true;
		else
			return false;
	}

	//Resize the array
	void resize() //problem here(?)
	{
		oldCapacity = capacity;
		capacity = capacity * 2; //sets new capacity
		T * temp = new T[capacity]; //creates a temp array.
		for (int i = 0; i < oldCapacity; i++) //moves items from the "items" array to "temp"
			temp[i] = items[i];

		delete [] items; //erases previous items array "[]" signifies it's an array //hereliesproblemithink
		items = temp; //sets temp to items
	}

	//Sorts them from front to back normally
	void sort()
	{
		int newInsertIndex = oldCapacity; //making the index to where I'd want to insert the ones that were after the old capacity
		for (int i = 0; i < front; i++) //start one before the "front" so it can arrange
			items[newInsertIndex + i] = items[i];

		//shift stuff if needed
		for (int i = 0; i < numItems; i++)
			items[i] = items[front + i]; //moves everything in relation to front to the start of the array.

		front = 0; //resets front
		back = (oldCapacity - 1); // 1 before the older capacity, since index is one value smaller than full capacity.
	}

	//Shows the stackQueue 
	void waitlist()
	{
		cout << "----- WAITLIST -----" << endl;
		cout << "Capacity: " << capacity << endl;
		cout << "In Queue: " << numItems << endl;
		for (int i = 0; i < numItems; i++)
		{
			//PRINTS IT ALL OUT IN ORDER FROM "FRONT" TO "BACK"
			//cout << items[(front + i)%capacity] << endl;
			
			//PRINTS IT BASED ON HOW THE REPRESENTATION/DRAWING ON PAPER WOULD LOOK LIKE 
			if (i == front)
				cout << items[i] << " |||FRONT" << endl;
			else if (i == back)
				cout << items[i] << " |||BACK" << endl;
			else
				cout << items[i] << endl;
			
		}
		cout << "----- WAITLIST -----" << endl;
	}
};

int main()
{
	cout << "testing..." << endl;
	stackQueue<int> nums;
	nums.addFront(1);
	nums.addFront(0);
	nums.addBack(2);
	nums.addBack(3);
	nums.addBack(4);
	cout << "Popped: " << nums.removeFront() << endl;
	cout << "Popped: " << nums.removeFront() << endl;
	nums.addBack(5);
	nums.addBack(6);
	nums.addBack(7);
	nums.addBack(8);
	nums.addBack(9);
	nums.addBack(10);
	nums.addFront(1);
	cout << "Popped: " << nums.removeBack() << endl;
	nums.addFront(-1);
	cout << "Popped: " << nums.removeFront() << endl;
	nums.addBack(11);
	cout << "Popped: " << nums.removeFront() << endl;
	nums.addBack(12);
	//Adding the next lines would trigger the newarray to form, which also then sorts everything now that there's enough space.
	nums.addBack(13);
	nums.addBack(14);
	nums.addFront(-1);
	nums.addBack(14);
	nums.addBack(15);
	nums.addBack(16);
	nums.addFront(-2);
	nums.addBack(17);
	nums.addBack(18);
	nums.addFront(-4);

	nums.waitlist();
	
	/*
	*ADDED A SORT AFTER RESIZING SINCE NOW THAT THE ARRAY IS BIGGER, IN ORDER TO ADD THINGS SEQUENTUALLY THEY HAVE TO BE IN ORDER ONCE MORE.
	*Whole code and structure works, just that I'm bad at thinking of how to show it correctly on the screen, since for example:
			[1 | 2 | 3 | 4 | 5] 
			 F				 B
			If I were to delete front twice and add a back:
			[6 | X | 3 | 4 | 5] --where "X" is the "removed"
			 B       F
			To print that out in order as the array, I'd have to find a way to skip over the "X", but didn't know how.
			I almost made (and left commented out) the array to print from Front to Back in order, but I wanted to try and show how the array normally is from.
			An idea I had was to set the removed array as some random int or NULL string using the typeid() to see which to use, but didn't want to risk having errors if someone happened to input said int.
	*/


	return 0;
}