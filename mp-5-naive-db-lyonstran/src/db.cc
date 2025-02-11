#include "db.hpp"
void Database::CreateTable(const std::string& table_name) {
//Creates a new database table. This is accomplished by creating a new entry in tables_ that maps the table_name to a new dynamically allocated DbTable object (i.e., new DbTable).
    tables_[table_name] = new DbTable();
}
void Database::DropTable(const std::string& table_name) {
//Drops an existing table from the database. This is done by looking up the table_name in the tables_ 
//map and then deallocating the mapped DbTable. Remember that the table key is the table 
//name and the value is the address of the dynamically allocated DbTable object. If table_name does not exist in tables_, throw an exception.
    //tables_[table_name] = new DbTable();
    if (!tables_.contains(table_name)) {
        throw std::invalid_argument("table doesn't exist");
    } 
    delete tables_.at(table_name);
    tables_.erase(table_name); 
}
DbTable& Database::GetTable(const std::string& table_name) {
    //Returns a reference to the DbTable object associated with table_name.
    return *tables_.at(table_name);
}

Database::Database(const Database& rhs) {
    //Copy constructor. Implements a deep copy policy for Database typed objects. This also results in every database row being deep copied into the object as well.
    for (const auto& [k, data_tablep] : rhs.tables_) {
        tables_[k] = new DbTable(*data_tablep);
    }
}
Database::~Database() {
    for (auto& c : tables_) {
        delete c.second;
    }
    tables_.clear();
}
Database& Database::operator=(const Database& rhs) {
    //Copy assignment operator. Implements a deep copy policy for Database typed objects. 
    //This also results in every database row being deep copied into the object as well.
    if (this == &rhs) {
        return *this;
    }
    for (auto& [t_name, d_tablep] : tables_) {
        delete d_tablep;
    }

    tables_.clear();
    
    for (const auto& [t_name, d_tablep] : rhs.tables_) {
        tables_[t_name] = new DbTable(*d_tablep);
    }
    return *this;
}
