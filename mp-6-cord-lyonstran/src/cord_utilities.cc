#include "cord_utilities.hpp"

#include <stdexcept>

SharedPointer<Cord> ConcatCords(SharedPointer<Cord> left_cord,
                                SharedPointer<Cord> right_cord) {
  if (left_cord.Get() == nullptr || right_cord.Get() == nullptr) {
    throw std::invalid_argument("cords can't be null, check again");
  }
  Cord* ret_cord = new Cord();
  ret_cord->left_ = left_cord;
  ret_cord->right_ = right_cord;
  unsigned int tot_len = left_cord->length_ + right_cord->length_;
  ret_cord->length_ = tot_len;
  ret_cord->data_ = nullptr;
  SharedPointer<Cord> returning(ret_cord, kSharedPointerType::kObject);
  return returning;
}

SharedPointer<Cord> SubString(SharedPointer<Cord> curr_cord,
                              unsigned int lower_idx,
                              unsigned int upper_idx) {
    if (curr_cord.Get() == nullptr) {
        throw std::invalid_argument("your cord can't be NULL");
    }

    if (curr_cord->Length() < upper_idx || lower_idx >= upper_idx) {
        throw std::invalid_argument("double check inputs");
    }

    if (lower_idx == 0 && curr_cord->Length() == upper_idx) {
        return curr_cord;
    }

    if (curr_cord->Left().Get() == nullptr && curr_cord->Right().Get() == nullptr) {
        char* substring_word = new char[upper_idx - lower_idx + 1];
        for (unsigned int i = lower_idx; i < upper_idx; ++i) {
            substring_word[i - lower_idx] = curr_cord->Data()[i];
        }
        substring_word[upper_idx - lower_idx] = '\0';
        return SharedPointer<Cord>(new Cord(substring_word));
    }

    const auto kCutoff = curr_cord->Left()->Length();
    if (upper_idx <= kCutoff) {
        return SubString(curr_cord->Left(), lower_idx, upper_idx);
    }
    if (lower_idx >= kCutoff) {
        return SubString(curr_cord->Right(), lower_idx - kCutoff, upper_idx - kCutoff);
    }
    SharedPointer<Cord> lefty = SubString(curr_cord->Left(), lower_idx, kCutoff);
    SharedPointer<Cord> righty = SubString(curr_cord->Right(), 0, upper_idx - kCutoff);
    return ConcatCords(lefty, righty);
}

