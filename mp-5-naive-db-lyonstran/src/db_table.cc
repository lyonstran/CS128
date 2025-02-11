#include "db_table.hpp"

const unsigned int kRowGrowthRate = 2;
void DbTable::HelperPutter() {
  unsigned int new_ci = col_descs_.size() - 1;
  for (unsigned int r = 0; r < rows_.size(); ++r) {
    if (col_descs_.at(new_ci).second == DataType::kString) {
      rows_.at(r)[new_ci] = static_cast<void*>(new std::string(""));
    } else if (col_descs_.at(new_ci).second == DataType::kInt) {
      rows_.at(r)[new_ci] = static_cast<void*>(new int(0));
    } else if (col_descs_.at(new_ci).second == DataType::kDouble) {
      rows_.at(r)[new_ci] = static_cast<void*>(new double(0.0));
    }
  }
}
DbTable::DbTable(const DbTable& rhs) {  // Copy constructor that performs a deep
                                        // copy of another DbTable object.
  next_unique_id_ = rhs.next_unique_id_;
  row_col_capacity_ = rhs.row_col_capacity_;
  col_descs_ = rhs.col_descs_;
  for (const auto& [key, v_arr] : rhs.rows_) {
    void** new_r = new void*[rhs.row_col_capacity_];
    for (unsigned int col = 0; col < rhs.col_descs_.size(); col++) {
      if (rhs.col_descs_.at(col).second == DataType::kString) {
        new_r[col] = static_cast<void*>(
            new std::string(*static_cast<std::string*>(v_arr[col])));
      } else if (rhs.col_descs_.at(col).second == DataType::kInt) {
        new_r[col] =
            static_cast<void*>(new int(*static_cast<int*>(v_arr[col])));
      } else if (rhs.col_descs_.at(col).second == DataType::kDouble) {
        new_r[col] =
            static_cast<void*>(new double(*static_cast<double*>(v_arr[col])));
      }
    }
    rows_.insert({key, new_r});
  }
}

DbTable::~DbTable() {
  // Destructor that releases all dynamically allocated memory associated with
  // the table.
  for (auto& [key, v_arr] : rows_) {
    for (unsigned int col_i = 0; col_i < col_descs_.size(); ++col_i) {
      delete static_cast<void**>(v_arr[col_i]);  // point of concern
    }
    delete[] v_arr;
  }
}
void DbTable::HelperDeleteTypes(unsigned int r, unsigned int c) {
  auto& ob = col_descs_.at(c).second;
  switch (ob) {
  case DataType::kString:
    delete static_cast<std::string*>(rows_.at(r)[c]);
    break;
  case DataType::kInt:
    delete static_cast<int*>(rows_.at(r)[c]);
    break;
  case DataType::kDouble:
    delete static_cast<double*>(rows_.at(r)[c]);
    break;
  }
}
void DbTable::AddColumn(const std::pair<std::string, DataType>& col_desc) {
  // meow meow MEOW
  // I got the devil in me. Meow meow (jeff buckley reference)
  // Adds a new column to the table. It updates the column descriptions, resizes
  // existing rows if needed, and initializes the new column in each row with
  // default values.
  if (col_descs_.size() == row_col_capacity_) {
    unsigned int new_row_capacity = row_col_capacity_ * kRowGrowthRate;
    for (unsigned int r = 0; r < rows_.size(); ++r) {
      void** n_row = new void*[new_row_capacity];  // rememebr
      for (unsigned int col = 0; col < col_descs_.size(); ++col) {
        switch (col_descs_.at(col).second) {
        case DataType::kString:
          n_row[col] = static_cast<void*>(
              new std::string(*static_cast<std::string*>(rows_.at(r)[col])));
          break;
        case DataType::kInt:
          n_row[col] =
              static_cast<void*>(new int(*static_cast<int*>(rows_.at(r)[col])));
          break;
        case DataType::kDouble:
          n_row[col] = static_cast<void*>(
              new double(*static_cast<double*>(rows_.at(r)[col])));
          break;
        }
        HelperDeleteTypes(r, col);
      }
      delete[] rows_.at(r);
      rows_.at(r) = n_row;
    }
    row_col_capacity_ = new_row_capacity;
  }
  col_descs_.push_back(col_desc);
  HelperPutter();
}

void DbTable::AddRow(const std::initializer_list<std::string>& col_data) {
  // Adds a new row to the table with the given data. It checks if the number of
  // data elements matches
  //  the number of columns, allocates memory for the new row, and initializes
  //  each cell with the provided data.
  if (col_data.size() != col_descs_.size()) {
    throw std::invalid_argument("bad arg");
  }
  void** insert_r = new void*[row_col_capacity_];
  rows_.insert({next_unique_id_, insert_r});
  next_unique_id_++;
  unsigned int col_i = 0;
  for (const std::string& str : col_data) {
    if (col_descs_.at(col_i).second == DataType::kString) {
      rows_[next_unique_id_ - 1][col_i] =
          //static_cast<void*>(new std::string(str));
          new std::string(str);
    } else if (col_descs_.at(col_i).second == DataType::kInt) {
      rows_[next_unique_id_ - 1][col_i] =
          //static_cast<void*>(new int(std::stoi(str)));
          new int(std::stoi(str));
    } else if (col_descs_.at(col_i).second == DataType::kDouble) {
      rows_[next_unique_id_ - 1][col_i] =
          //static_cast<void*>(new double(std::stod(str)));
          new double(std::stod(str));
    }
    col_i++;
  }
}
void DbTable::DeleteRowById(unsigned int id) {
  // Deletes a row from the table by its ID. It deallocates memory for each cell
  // in the row and then deallocates memory for the row itself.
  if (!rows_.contains(id)) {
    throw std::invalid_argument("id not found in row");
  }
  for (unsigned int ci = 0; ci < col_descs_.size(); ++ci) {
    delete static_cast<void**>(rows_.at(id)[ci]);  // maybe
  }
  delete[] rows_.at(id);
  rows_.erase(id);
}

void DbTable::DeleteColumnByIdx(unsigned int col_i) {
  // Deletes a column from the table by its index.
  // It removes the column description, shifts data in rows to close the gap
  // left by the deleted column, and deallocates memory for the deleted column
  // in each row.
  if (col_i >= col_descs_.size() || col_i < 0) {
    throw std::out_of_range("col_idx not valid");
  }
  if (col_descs_.size() == 1 && !rows_.empty()) {
    throw std::runtime_error(
        "any table gotta table with one row need a column");
  }
  for (auto& [key, v_arr] : rows_) {
    delete static_cast<void**>(v_arr[col_i]);  // maybe bad
    for (unsigned int c = col_i; c < col_descs_.size() - 1; ++c) {
      v_arr[c] = v_arr[c + 1];
    }
  }
  col_descs_.erase(col_descs_.begin() + col_i);
}

std::ostream& operator<<(std::ostream& os, const DbTable& table) {
  // overloads the output stream operator (<<) to allow printing the table's
  // contents to an output stream.
  for (unsigned int cur = 0; cur < table.col_descs_.size(); ++cur) {
    if (table.col_descs_.at(cur).second == DataType::kString) {
      os << table.col_descs_[cur].first << "(std::string)";
    } else if (table.col_descs_.at(cur).second == DataType::kInt) {
      os << table.col_descs_[cur].first << "(int)";
    } else if (table.col_descs_.at(cur).second == DataType::kInt) {
      os << table.col_descs_[cur].first << "(double)";
    }
    if (cur != table.col_descs_.size() - 1) {
      os << ", ";
    }
  } 
  os << std::endl;
  for (unsigned int r = 0; r < table.rows_.size(); ++r) {
    for (unsigned int c = 0; c < table.col_descs_.size(); ++c) {
      if (table.col_descs_.at(c).second == DataType::kString) {
        os << *static_cast<std::string*>(table.rows_.at(r)[c]);
      } else if (table.col_descs_.at(c).second == DataType::kInt) {
        os << *static_cast<int*>(table.rows_.at(r)[c]);
      } else if (table.col_descs_.at(c).second == DataType::kInt) {
        os << *static_cast<double*>(table.rows_.at(r)[c]);
      }
      if (c != table.col_descs_.size() - 1) {
        os << ", ";
      }
    }
    os << std::endl;
  }
  return os;
}

DbTable& DbTable::operator=(const DbTable& table) {
  // Copy assignment operator that performs a deep copy of another DbTable
  // object.
  if (this == &table) {
    return *this;
  }
  for (auto& [k, v_arr] : rows_) {
    for (unsigned int ci = 0; ci < col_descs_.size(); ++ci) {
      delete static_cast<void**>(v_arr[ci]);  //
    }
    delete[] v_arr;
  }
  rows_.clear();
  next_unique_id_ = table.next_unique_id_;
  row_col_capacity_ = table.row_col_capacity_;
  col_descs_ = table.col_descs_;
  for (const auto& [k, v_arr] : table.rows_) {
    void** n_r = new void*[table.row_col_capacity_];
    for (unsigned int c = 0; c < table.col_descs_.size(); ++c) {
      if (table.col_descs_.at(c).second == DataType::kString) {
        n_r[c] = static_cast<void*>(
            new std::string(*static_cast<std::string*>(v_arr[c])));
      } else if (table.col_descs_.at(c).second == DataType::kInt) {
        n_r[c] = static_cast<void*>(new int(*static_cast<int*>(v_arr[c])));
      } else if (table.col_descs_.at(c).second == DataType::kDouble) {
        n_r[c] =
            static_cast<void*>(new double(*static_cast<double*>(v_arr[c])));
      }
    }
    rows_.insert({k, n_r});
  }
  return *this;
}
