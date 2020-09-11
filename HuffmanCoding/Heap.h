//--------------------------------------------------------------------
// HEAP.H
// Declaration and definition of the template Heap class
// Author: Olson (borrowing from a previous edition of Carrano/Henry)
//--------------------------------------------------------------------
// Heap class: 
//	Implements a priority queue with the following methods:
//		insert, deleteMin, findMin, heapify
//  The heap is stored in a vector (see the CSS 502 lecture notes)
//  Assumptions:
//	 Can only store data for which operator< exists
//	 (hence the Comparable type variable)
//--------------------------------------------------------------------

#include <vector>
using namespace std;

template <typename Comparable>
class Heap {
public:
   //------------------------------------------------------------------------
   // The Heap default constructor
   Heap() {
   }

   //------------------------------------------------------------------------
   // The Heap destructor
   ~Heap() {
      items.clear();
      numElements = 0;
   }

   //------------------------------------------------------------------------
   // The copy constructor for Heap
   // @pre items has been allocated space for numElements pointers.
   // @param other The Heap to copy from
   Heap(const Heap& other) {
      for (int i = 0; i < other.numElements; i++) {
         Comparable item = *other.items[i];
         this->items.push_back(&item);
      }

      this->numElements = other.numElements;
   }

   //------------------------------------------------------------------------
   // Overload assignment operator.
   // @pre items has been allocated space for numElements pointers.
   // @param other The Heap object to copy values from
   // @returns The Heap object
   Heap* operator=(const Heap& other) {
      if (&other != this) {
         this->items.clear();

         for (int i = 0; i < other.numElements; i++) {
            Comparable item = *other.items[i];
            this->items.push_back(&item);
         }

         this->numElements = other.numElements;
      }

      return this;
   }

   //------------------------------------------------------------------------
   // Constructor that takes an array of Comparable pointers and constructs a Heap using the (supplied) heapify method
   // @pre items has been allocated space for Comparable array pointers.
   // @param array The array of Comparable pointers
   // @param count The Comparable pointers count
   Heap(Comparable** array, int count) {
      if (count <= 0) return;

      // Add item in position 0 (dummy position) to prevent percolating up from root 
      items.push_back(array[0]);

      for (int i = 0; i < count; i++) {
         items.push_back(array[i]);
         numElements++;
      }

      heapify();
   }

   //------------------------------------------------------------------------
   // insert - adds a single item to the heap
   // Preconditions: the initial heap has sufficient memory allocated
   //					and satisfies the heap order property
   // Postconditions: inserts the item into the queue, such that a new
   //					heap is created containing the union of the elements
   void insert(Comparable* c) {
      if (c == NULL) return;

      // Add item in position 0 (dummy position) to prevent percolating up from root 
      if (items.size() < 1) items.push_back(c);
      else items[0] = c;

      // Ensure we have enough space
      numElements++;
      while ((int)items.size() <= numElements)
         items.push_back(nullptr);

      // Percolate up
      int position = numElements;
      while (*c < *items[position / 2]) {
         items[position] = items[position / 2];
         position = position / 2;
      }
      items[position] = c;
   }


   //------------------------------------------------------------------------
   // findMin - returns a const pointer to the minimum value in the heap
   // Preconditions: items[0] exists if numElements is larger than zero
   // Postconditions: Returns nullptr if the heap is empty, otherwise returns
   //	the item at the root of the heap (presumably the minimum priority).
   const Comparable* findMin() const {
      if (numElements <= 0) return nullptr;
      else return items[1];
   }


   //------------------------------------------------------------------------
   // deleteMin - delete the minimum and return a pointer to it
   // Preconditions: items[0] exists if numElements is larger than zero
   // Postconditions: Returns nullptr if the heap is empty, otherwise returns
   //	the item at the root of the heap (presumably the minimum priority).
   //  That element is deleted from the heap and the heap order property is
   //  restored.
   Comparable* deleteMin() {
      if (numElements == 0) return nullptr;

      // Give memory back to user
      Comparable* toReturn = items[1];
      items[1] = items[numElements];
      numElements--;

      percolateDown(1);
      return toReturn;
   }

   //------------------------------------------------------------------------
   // heapify - modifies any set of data into a heap
   // Preconditions: items has been allocated space for numElements pointers
   // Postconditions: The items stored form a heap
   void heapify() {
      for (int i = numElements / 2; i > 0; i--)
         percolateDown(i);
   }

   //------------------------------------------------------------------------
   // size
   // Preconditions: none
   // Postconditions: returns the size of the heap
   int size() const {
      return numElements;
   }

   //------------------------------------------------------------------------
   // isEmpty
   // Preconditions: none
   // Postconditions: returns whether the heap is empty (zero elements)
   int isEmpty() const {
      return numElements == 0;
   }

private:

   //------------------------------------------------------------------------
   // percolateDown - used to restore the heap order property after deleteMin
   // Preconditions: Both subtrees of the root are heaps
   // Postconditions: Restores the heap order property to shifting the root
   //  down until it reaches an appropriate node
   void percolateDown(int position) {
      int child = position * 2;
      if (child > numElements) return;
      if (child != numElements && *items[child] > * items[child + 1]) child++;
      if (*items[child] < *items[position]) {
         swap(items[child], items[position]);
         percolateDown(child);
      }
   }

   int numElements = 0;			// Number of elements in the heap
   vector <Comparable*> items;	// The elements in the heap
};