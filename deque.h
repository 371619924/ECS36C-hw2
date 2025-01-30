#ifndef DEQUE_H_
#define DEQUE_H_

#include <cstddef>
#include <stdexcept>

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
  bool Empty() const noexcept;
  // Return number of items in deque
  size_t Size() const noexcept;
  // Resize internal data structure to fit precisely the number of items and
  // free unused memory
  void ShrinkToFit();

  //
  // Element access
  //

  // Return item at pos @pos
  T& operator[](size_t pos);
  // Return item at front of deque
  T& Front();
  // Return item at back of deque
  T& Back();

  //
  // Modifiers
  //

  // Clear contents of deque (make it empty)
  void Clear(void) noexcept;
  // Push item @value at front of deque
  void PushFront(const T &value);
  // Push item @value at back of deque
  void PushBack(const T &value);
  // Remove item at front of deque
  void PopFront();
  // Remove item at back of deque
  void PopBack();

 private:
  //
  // @@@ The class's internal members below can be modified @@@
  //

  T* data_;          // Internal array storage
  size_t capacity_;  // Capacity of the array
  size_t size_;      // Number of elements in deque
  size_t head_;      // Index of the front element
  size_t tail_;      // Index of the next position of the back element

  // Resize the internal array to a new capacity
  void resize(size_t new_capacity);
  // Check if deque needs shrinking and resize if necessary
  void check_shrink();
};

// ================= Implementation =================

// Constructor
template<typename T>
Deque<T>::Deque() : capacity_(8), size_(0), head_(0), tail_(0) {
  data_ = new T[capacity_];
}

// Destructor
template<typename T>
Deque<T>::~Deque() {
  delete[] data_;
}

// Return true if empty
template<typename T>
bool Deque<T>::Empty() const noexcept {
  return size_ == 0;
}

// Return number of items
template<typename T>
size_t Deque<T>::Size() const noexcept {
  return size_;
}

// Resize to fit the number of items
template<typename T>
void Deque<T>::ShrinkToFit() {
  if (size_ == capacity_) return;
  resize(size_);
}

// Access item at position
template<typename T>
T& Deque<T>::operator[](size_t pos) {
  if (pos >= size_) throw std::out_of_range("Index out of range");
  return data_[(head_ + pos) % capacity_];
}

// Access front item
template<typename T>
T& Deque<T>::Front() {
  if (Empty()) throw std::runtime_error("Deque is empty");
  return data_[head_];
}

// Access back item
template<typename T>
T& Deque<T>::Back() {
  if (Empty()) throw std::runtime_error("Deque is empty");
  return data_[(tail_ - 1 + capacity_) % capacity_];
}

// Clear deque
template<typename T>
void Deque<T>::Clear() noexcept {
  size_ = 0;
  head_ = 0;
  tail_ = 0;
}

// Push item to front
template<typename T>
void Deque<T>::PushFront(const T &value) {
  if (size_ == capacity_) resize(capacity_ * 2);
  head_ = (head_ - 1 + capacity_) % capacity_;
  data_[head_] = value;
  size_++;
}

// Push item to back
template<typename T>
void Deque<T>::PushBack(const T &value) {
  if (size_ == capacity_) resize(capacity_ * 2);
  data_[tail_] = value;
  tail_ = (tail_ + 1) % capacity_;
  size_++;
}

// Pop item from front
template<typename T>
void Deque<T>::PopFront() {
  if (Empty()) throw std::runtime_error("Deque is empty");
  head_ = (head_ + 1) % capacity_;
  size_--;
  check_shrink();
}

// Pop item from back
template<typename T>
void Deque<T>::PopBack() {
  if (Empty()) throw std::runtime_error("Deque is empty");
  tail_ = (tail_ - 1 + capacity_) % capacity_;
  size_--;
  check_shrink();
}

// Resize internal array
template<typename T>
void Deque<T>::resize(size_t new_capacity) {
  T* new_data = new T[new_capacity];
  for (size_t i = 0; i < size_; i++) {
    new_data[i] = data_[(head_ + i) % capacity_];
  }
  delete[] data_;
  data_ = new_data;
  capacity_ = new_capacity;
  head_ = 0;
  tail_ = size_;
}

// Check if deque should shrink
template<typename T>
void Deque<T>::check_shrink() {
  if (size_ <= capacity_ / 4 && capacity_ > 8) {
    resize(capacity_ / 2);
  }
}

#endif  // DEQUE_H_
