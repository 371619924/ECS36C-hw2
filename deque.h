#ifndef DEQUE_H_
#define DEQUE_H_

#include <cstddef>

template<typename T>
class Deque {
 public:
  //
  // @@@ The class's public API below should NOT be modified @@@
  //

  // Constructor
  Deque();
  // Destructor
  ~Deque();


  //
  // Capacity
  //

  // Return true if empty, false otherwise
  // Complexity: O(1)
  bool Empty() const noexcept;
  // Return number of items in deque
  // Complexity: O(1)
  size_t Size() const noexcept;
  // Resize internal data structure to fit precisely the number of items and
  // free unused memory
  // Complexity: O(N)
  void ShrinkToFit();


  //
  // Element access
  //

  // Return item at pos @pos
  // Complexity: O(1)
  T& operator[](size_t pos);
  // Return item at front of deque
  // Complexity: O(1)
  T& Front();
  // Return item at back of deque
  // Complexity: O(1)
  T& Back();


  //
  // Modifiers
  //

  // Clear contents of deque (make it empty)
  // Complexity: O(1)
  void Clear(void) noexcept;
  // Push item @value at front of deque
  // Complexity: O(1) amortized
  void PushFront(const T &value);
  // Push item @value at back of deque
  // Complexity: O(1) amortized
  void PushBack(const T &value);
  // Remove item at front of deque
  // Complexity: O(1) amortized
  void PopFront();
  // Remove item at back of deque
  void PopBack();
  // Complexity: O(1) amortized

 private:
  //
  // @@@ The class's internal members below can be modified @@@
  //

  // Private member variables
  // ...To be completed...

  // Private constants
  // ...To be completed (if any)...

  // Private methods
  // ...To be completed (if any)...
};

//
// Your implementation of the class should be located below
//

// ...To be completed...

#endif  // DEQUE_H_
