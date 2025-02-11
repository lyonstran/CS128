#include <iostream>

#include "db.hpp"
#include "db_table.hpp"

int main() {
  // write informal tests here
  //make a datanbase
  Database db;
  db.CreateTable("meow");
  DbTable& meowTable = db.GetTable("meow");
  meowTable.AddColumn({"meow", DataType::kString});
  meowTable.AddColumn({"age", DataType::kInt});
  meowTable.AddColumn({"weight", DataType::kDouble});

  meowTable.AddRow({"MROW", 1, 5.6});
  meowTable.AddRow({"MEAW", 2, 10.8});
  meowTable.AddRow({"MREOW", 8, 13.2});

  std::cout << "Meow Data Table:\n" << meowTable << std::endl;
  return 0;
}