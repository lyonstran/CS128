#include "cord.hpp"

#include <stdexcept>

#include "cord_utilities.hpp"

Cord::Cord(std::string_view sv): left_(nullptr), right_(nullptr) {
  if (sv.empty()) {
    throw std::invalid_argument("why is it empty :(");
  }

  char* ret_data = new char[sv.size() +1];  // done as told through instructions. +1 gives space for
  for (unsigned int i = 0; i < sv.size(); ++i) {
    ret_data[i] = sv[i];
  }
  ret_data[sv.size()] = '\0';  // adding null terminator manually.
  data_ = ret_data;
  length_ = sv.size();
}

Cord::~Cord() {
  delete[] data_;
  data_ = nullptr;
}

SharedPointer<char> Cord::ToString() const {
    if (data_ == nullptr) {
        SharedPointer<char> left_subtree_str = left_->ToString();
        SharedPointer<char> right_subtree_str = right_->ToString();
        unsigned int left_len = left_->Length();
        unsigned int right_len = right_->Length();

        char* return_str = new char[left_len + right_len + 1];
        unsigned int i = 0;

        for (i = 0; i < left_len; ++i) {
            return_str[i] = left_subtree_str.Get()[i];
        }
        for (unsigned int j = 0; j < right_len; ++j, ++i) {
            return_str[i] = right_subtree_str.Get()[j];
        }
        return_str[left_len + right_len] = '\0';
        return SharedPointer<char>(return_str, kSharedPointerType::kArray);
    } else {
        char* return_str = new char[length_ + 1];
        for (unsigned int i = 0; i < length_; ++i) {
            return_str[i] = data_[i];
        }
        return_str[length_] = '\0';
        return SharedPointer<char>(return_str, kSharedPointerType::kArray);
    }
}