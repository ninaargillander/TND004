#include "set.h"
#include "node.h"

int Set::Node::count_nodes = 0;  // initialize total number of existing nodes to zero

/*****************************************************
 * Implementation of the member functions             *
 ******************************************************/

 // Used for debug purposes
 // Return number of existing nodes  -- static member function
int Set::get_count_nodes()
{
	return Set::Node::count_nodes;
}

// Default constructor
Set::Set() : head{ new Node() }, tail{ new Node(0, nullptr, head) }, counter{ 0 }
{
	head->next = tail;                      //Point next to tail from head
}

// Conversion constructor
Set::Set(int n)
	: Set{}  // create an empty list
{
	_insert(head, n);                       //Empty Set with one new element -> no need to sort
}

// Constructor to create a Set from a sorted vector v
Set::Set(const std::vector<int>& v)
	: Set{}  // create an empty list
{
	size_t size_v = size(v);

	for (size_t i = 0; i < size_v; ++i) {
		if (!(tail->prev != head && tail->prev->value == v[i])) {
			_insert(tail->prev, v[i]);
		}

	}
}

// Make the set empty
void Set::make_empty() {

	Node* to_be_removed = head->next;   //First Node to remove

	while (to_be_removed != tail) {

		_remove(to_be_removed);         //Removes and relinks first Node
		to_be_removed = head->next;     //Move to new first Node
	}
}

Set::~Set() 
{
	make_empty();                       //Remove all elements

	//Deallocate head/tail and set them to nullptr
	delete head;
	delete tail;
	head = nullptr;
	tail = nullptr;
}

// Copy constructor
Set::Set(const Set& source)
	: Set{}  // create an empty list
{
	Node* to_be_inserted = source.head->next;               //First Node to insert
	Node* to_insert_after = head;                           //Where to insert new Node (after)

	while (to_be_inserted != source.tail) {                 //Step through the entire source Set
		_insert(to_insert_after, to_be_inserted->value);

		to_be_inserted = to_be_inserted->next;              //"increment" position in source
		to_insert_after = to_insert_after->next;            //"increment" position in copy
	}
}

// Copy-and-swap assignment operator
Set& Set::operator=(Set source) 
{
	std::swap(head, source.head);
	std::swap(tail, source.tail);
	std::swap(counter, source.counter);

	return *this;
}

// Test set membership
bool Set::is_member(int val) const 
{
	if (is_empty()) return false;                           //No members in empty Set

	if (tail->prev->value < val                             //Sorted range -> check if val is between
		|| head->next->value > val) return false;           //values of first and last Node.

	Node* temp = head->next;

	while (temp != tail) {                                  //Step through this Set
		if (temp->value == val) return true;                //If found, return true

		temp = temp->next;                                  //If not, move on to next Node in Set.

	}

	return false;                                           //If not found when end of Set has been reached
															//return false
}

// Test whether a set is empty
bool Set::is_empty() const
{
	return (counter == 0);
}


// Return number of elements in the set
size_t Set::cardinality() const
{
	return counter;
}


// Modify *this such that it becomes the union of *this with Set S
// Add to *this all elements in Set S (repeated elements are not allowed)
Set& Set::operator+=(const Set& S)
{
	Node* pos_S = S.head->next;
	Node* pos_this = head;

	while (pos_S != S.tail) {
		if (pos_S->value < pos_this->next->value || pos_this->next == tail) {
			_insert(pos_this, pos_S->value);
			pos_S = pos_S->next;
		}
		else if (pos_S->value == pos_this->next->value) {
			pos_S = pos_S->next;
		}

		pos_this = pos_this->next;
	}

	return *this;
}

// Modify *this such that it becomes the intersection of *this with Set S
Set& Set::operator*=(const Set& S) 
{
	Node* tempA = head;
	Node* tempB = S.head;

	while (tempA->next != tail) {

		if (tempB == S.tail || tempA->next->value < tempB->next->value) {
			_remove(tempA->next);
			continue;
		}
		else if (tempA->next->value == tempB->next->value) {
			tempA = tempA->next;
		}

		tempB = tempB->next;
	}

	return *this;
}

// Modify *this such that it becomes the Set difference between Set *this and Set S
Set& Set::operator-=(const Set& S)
{
	Node* tempA = head;
	Node* tempB = S.head;

	while (tempA->next != tail && tempB->next != S.tail) {

		if (tempA->next->value < tempB->next->value) {
			tempA = tempA->next;
		}
		else if (tempA->next->value == tempB->next->value) {
			_remove(tempA->next);
		}
		else {
			tempB = tempB->next;
		}
	}

	return *this;
}

// Overloaded stream insertion operator<<
std::ostream& operator<<(std::ostream& os, const Set& b) 
{
	if (b.is_empty()) {
		os << "Set is empty!";
	}
	else {
		Set::Node* temp{ b.head->next };

		os << "{ ";
		while (temp != b.tail) {
			os << temp->value << " ";
			temp = temp->next;
		}
		os << "}";
	}
	return os;
}

/* ******************************************** *
 * Private Member Functions -- Implementation   *
 * ******************************************** */

 //If you add any private member functions to class Set then write the implementation here

 // Insert a new Node storing val after the Node pointed by p
void Set::_insert(Node* p, int val) 
{
	if (!p || p == tail) {
		std::cout << "ERROR: Tried to insert after tail or nullptr!\n";
		return;
	}

	p->next = new Node(val, p->next, p);     //create a new Node* with pointers to head                             //Relink Node before new Node
	p->next->next->prev = p->next;                    //Relink Node after new Node

	++counter;
}


// Remove the Node pointed by p
void Set::_remove(Node* p) 
{
	if (p) {
		if (p->next && p->prev) {
			p->prev->next = p->next;
			p->next->prev = p->prev;
			delete p;

			--counter;
		}
		else {
			std::cout << "ERROR: tried to remove head or tail!!\n";
		}
	}
	else {
		std::cout << "ERROR: tried to remove *(nullptr)!\n";
	}
}



//Helper for friend subset operator
bool Set::_is_subset_of(const Set& S) const 
{
	if (counter > S.counter) {
		std::cout << "ERROR in _is_subset_of(const Set& S) : S larger than this!\n";
		return false;
	}

	Node* temp_A = head->next;
	Node* temp_B = S.head->next;

	while (temp_A != tail) {

		if (temp_B == tail) return false;               //End of second Set with not all elements of first Set found.

		if (temp_A->value < temp_B->value) {            //Slot where temp_A->value would be found passed -> not in Set S -> not subset
			return false;
		}
		else if (temp_A->value == temp_B->value) {      //"increment" temp_A
			temp_A = temp_A->next;
		}

		temp_B = temp_B->next;                          //"increment" temp_B
	}

	return true;
}

