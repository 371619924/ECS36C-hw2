#ifndef DEQUE_H_
#define DEQUE_H_

#include <cstddef>     // For size_t.
#include <stdexcept>   // For exception handling (std::out_of_range, std::runtime_error).

/*
Detailed Description:
This header defines a template class "Deque" that implements a double-ended queue using a
dynamically allocated circular array. The Deque supports constant-time insertion and removal
at both the front and back ends, random access to elements, and automatic resizing.
It provides methods for checking capacity, accessing elements, and modifying the queue by
pushing or popping elements at either end. Internal storage automatically expands when full
and shrinks to fit the current number of elements.
*/

template<typename T>
class Deque {
 public:
  // Constructor: Initializes an empty deque with an initial capacity.
  Deque();
  // Destructor: Frees the dynamically allocated memory.
  ~Deque();

  // Capacity functions:
  // Returns true if the deque is empty; false otherwise.
  bool Empty() const noexcept;
  // Returns the number of items in the deque.
  size_t Size() const noexcept;
  // Resizes the internal storage to exactly the number of elements, freeing unused memory.
  void ShrinkToFit();

  // Element access functions:
  // Returns a reference to the item at the specified position.
  T& operator[](size_t pos);
  // Returns a reference to the front element.
  T& Front();
  // Returns a reference to the back element.
  T& Back();

  // Modifier functions:
  // Clears the deque, making it empty.
  void Clear(void) noexcept;
  // Inserts an item at the front of the deque.
  void PushFront(const T &value);
  // Inserts an item at the back of the deque.
  void PushBack(const T &value);
  // Removes the item at the front of the deque.
  void PopFront();
  // Removes the item at the back of the deque.
  void PopBack();

 private:
  T* data_;          // Pointer to the dynamically allocated array that stores elements.
  size_t capacity_;  // Current capacity of the array.
  size_t size_;      // Current number of elements stored.
  size_t head_;      // Index of the front element in the circular array.
  size_t tail_;      // Index of the next available position at the back.

  // Resizes the internal array to a new capacity.
  // Copies all current elements into the new array starting at index 0.
  void resize(size_t new_capacity);
  // Checks whether the array is underutilized (size <= capacity/4) and shrinks it if needed.
  void check_shrink();
};

// ================= Implementation =================

// Constructor: Initializes the deque with a capacity of 8 and sets size, head, and tail to 0.
template<typename T>
Deque<T>::Deque() : capacity_(8), size_(0), head_(0), tail_(0) {
  data_ = new T[capacity_];  // Allocate memory for 8 elements.
}

// Destructor: Releases the allocated memory.
template<typename T>
Deque<T>::~Deque() {
  delete[] data_;  // Free the allocated array.
}

// Returns true if there are no elements in the deque.
template<typename T>
bool Deque<T>::Empty() const noexcept {
  return size_ == 0;
}

// Returns the current number of elements stored in the deque.
template<typename T>
size_t Deque<T>::Size() const noexcept {
  return size_;
}

// Shrinks the internal storage to exactly the number of stored elements,
// freeing any extra memory if the capacity is larger than the current size.
template<typename T>
void Deque<T>::ShrinkToFit() {
  if (size_ == capacity_) return;  // No need to shrink if size equals capacity.
  resize(size_);
}

// Overloaded subscript operator for accessing element at logical index pos.
// Uses modular arithmetic to translate the logical index to the physical array index.
template<typename T>
T& Deque<T>::operator[](size_t pos) {
  if (pos >= size_)
    throw std::out_of_range("Index out of range");  // Throw if pos is invalid.
  return data_[(head_ + pos) % capacity_];  // Compute the correct index.
}

// Returns a reference to the first element in the deque.
// Throws a runtime error if the deque is empty.
template<typename T>
T& Deque<T>::Front() {
  if (Empty())
    throw std::runtime_error("Deque is empty");
  return data_[head_];
}

// Returns a reference to the last element in the deque.
// Uses modular arithmetic to handle the circular structure.
template<typename T>
T& Deque<T>::Back() {
  if (Empty())
    throw std::runtime_error("Deque is empty");
  return data_[(tail_ - 1 + capacity_) % capacity_];
}

// Clears the deque by resetting size, head, and tail indices.
template<typename T>
void Deque<T>::Clear() noexcept {
  size_ = 0;
  head_ = 0;
  tail_ = 0;
}

// Inserts a new element at the front of the deque.
// Resizes the array (doubling its capacity) if the deque is full.
template<typename T>
void Deque<T>::PushFront(const T &value) {
  if (size_ == capacity_)
    resize(capacity_ * 2);
  head_ = (head_ - 1 + capacity_) % capacity_;  // Decrement head index circularly.
  data_[head_] = value;  // Store the new value at the new head position.
  size_++;  // Increase the number of elements.
}

// Inserts a new element at the back of the deque.
// Resizes the array (doubling its capacity) if the deque is full.
template<typename T>
void Deque<T>::PushBack(const T &value) {
  if (size_ == capacity_)
    resize(capacity_ * 2);
  data_[tail_] = value;  // Place the value at the current tail.
  tail_ = (tail_ + 1) % capacity_;  // Increment tail index circularly.
  size_++;  // Increase the element count.
}

// Removes the element at the front of the deque.
// Throws an error if the deque is empty.
template<typename T>
void Deque<T>::PopFront() {
  if (Empty())
    throw std::runtime_error("Deque is empty");
  head_ = (head_ + 1) % capacity_;  // Move head index forward circularly.
  size_--;  // Decrease the number of elements.
  check_shrink();  // Check if internal storage should be shrunk.
}

// Removes the element at the back of the deque.
// Throws an error if the deque is empty.
template<typename T>
void Deque<T>::PopBack() {
  if (Empty())
    throw std::runtime_error("Deque is empty");
  tail_ = (tail_ - 1 + capacity_) % capacity_;  // Move tail index backward circularly.
  size_--;  // Decrease the element count.
  check_shrink();  // Check if resizing down is necessary.
}

// Resizes the internal array to a new capacity.
// Copies all current elements (in proper order) into the new array, then updates internal indices.
template<typename T>
void Deque<T>::resize(size_t new_capacity) {
  T* new_data = new T[new_capacity];  // Allocate a new array.
  for (size_t i = 0; i < size_; i++) {
    // Copy elements starting from head_ and using modular arithmetic.
    new_data[i] = data_[(head_ + i) % capacity_];
  }
  delete[] data_;  // Free old memory.
  data_ = new_data;  // Update pointer.
  capacity_ = new_capacity;  // Set new capacity.
  head_ = 0;         // Reset head index.
  tail_ = size_;     // Tail is now at the end of the stored elements.
}

// Checks if the deque is underutilized (if size is <= one-quarter of capacity) and
// the capacity is above a minimum threshold (8). If so, resizes the array to half the capacity.
template<typename T>
void Deque<T>::check_shrink() {
  if (size_ <= capacity_ / 4 && capacity_ > 8) {
    resize(capacity_ / 2);
  }
}

#endif  // DEQUE_H_
