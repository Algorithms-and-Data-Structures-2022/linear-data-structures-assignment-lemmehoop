#include "assignment/linked_list.hpp"

namespace assignment {

  LinkedList::~LinkedList() {

    // эквивалентно очистке списка
    LinkedList::Clear();
  }

  void LinkedList::Add(int value) {
    Node* new_node = new Node(value);
    if (front_ == nullptr) {
      front_ = new_node;
      back_ = new_node;
    } else {
      back_->next = new_node;
      back_ = new_node;
    }
    size_ += 1;
  }

  bool LinkedList::Insert(int index, int value) {
    Node* new_node = new Node(value);
    if (index == 0) {
      if (front_ == nullptr) {
        back_ = new_node;
      }
      new_node->next = front_;
      front_ = new_node;
      size_ += 1;
      return true;
    } else if (index == size_) {
      if (back_ == nullptr) {
        back_ = new_node;
      }
      back_->next = new_node;
      back_ = new_node;
      size_ += 1;
      return true;
    } else if (index >= 0 && index < size_) {
      Node *prev_node = FindNode(index - 1);
      new_node->next = prev_node->next;
      prev_node->next = new_node;
      size_ += 1;
      return true;
    }
    return false;
  }

  bool LinkedList::Set(int index, int new_value) {
    if (index >= 0 && index < size_) {
      int index_count = 0;
      for (Node* curr = front_; curr != nullptr;) {
        if (index_count == index) {
          curr->value = new_value;
          return true;
        }
        curr = curr->next;
        index_count += 1;
      }
    }
    return false;
  }

  std::optional<int> LinkedList::Remove(int index) {
    if (index >= 0 && index < size_){
      if (index == 0) {
        Node* curr_node = front_;
        front_ = front_->next;
        size_ -= 1;
        return curr_node->value;
      } else {
        Node* prev_node = FindNode(index - 1);
        Node* curr_node = prev_node->next;
        prev_node->next = prev_node->next->next;
        size_ -= 1;
        return curr_node->value;
      }
    }

    return std::nullopt;
  }

  void LinkedList::Clear() {
    for (Node* curr = front_; curr != nullptr;) {
      Node* node_to_remove = curr;
      curr = curr->next;
      delete node_to_remove;
    }

    front_ = nullptr;
    back_ = nullptr;
    size_ = 0;
  }

  std::optional<int> LinkedList::Get(int index) const {
    if (index >= 0 && index < size_) {
      int index_count = 0;
      for (Node* curr = front_; curr != nullptr;) {
        if (index_count == index) {
          return curr->value;
        }
        curr = curr->next;
        index_count += 1;
      }
    }
    return std::nullopt;
  }

  std::optional<int> LinkedList::IndexOf(int value) const {
    int index = 0;
    for (Node* curr = front_; curr != nullptr;) {
      if (curr->value == value) {
        return index;
      }
      index += 1;
      curr = curr->next;
    }
    return std::nullopt;
  }

  bool LinkedList::Contains(int value) const {
    for (Node* curr = front_; curr != nullptr;) {
      if (curr->value == value) {
        return true;
      }
      curr = curr->next;
    }
    return false;
  }

  bool LinkedList::IsEmpty() const {
    return front_ == nullptr;
  }

  int LinkedList::size() const {
    return size_;
  }

  std::optional<int> LinkedList::front() const {
    if (front_ != nullptr) {
      return front_->value;
    }

    return std::nullopt;
  }

  std::optional<int> LinkedList::back() const {
    if (back_ != nullptr) {
      return back_->value;
    }

    return std::nullopt;
  }

  Node* LinkedList::FindNode(int index) const {
    if (index >= 0 && index < size_) {
      int index_count = 0;
      for (Node* curr = front_; curr != nullptr;) {
        if (index_count == index) {
          return curr;
        }
        index_count += 1;
        curr = curr->next;
      }
    }
    return nullptr;
  }

  // ДЛЯ ТЕСТИРОВАНИЯ
  LinkedList::LinkedList(const std::vector<int>& values) {

    if (values.empty()) {
      return;
    }

    auto* curr_node = new Node(values.front());
    front_ = curr_node;

    for (int index = 1; index < values.size() - 1; ++index) {
      curr_node->next = new Node(values[index]);
      curr_node = curr_node->next;
    }

    if (values.size() == 1) {
      back_ = front_;
    } else {
      curr_node->next = new Node(values.back());
      back_ = curr_node->next;
    }

    size_ = static_cast<int>(values.size());
  }

  std::vector<int> LinkedList::toVector() const {

    if (front_ == nullptr || size_ == 0) {
      return {};
    }

    std::vector<int> array;
    array.reserve(size_);

    for (auto* node = front_; node != nullptr; node = node->next) {
      array.push_back(node->value);
    }

    return array;
  }

}  // namespace assignment