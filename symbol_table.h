#ifndef TURBOPASCAL_SYMBOLTABLE_H
#define TURBOPASCAL_SYMBOLTABLE_H

#include <string>
#include <sstream>
#include <map>
#include "language.h"
#include "common.h"

class SymbolTable {
 public:

  enum class EntryType {
    sVariable, sFunction, sProcedure
  };

  struct Entry {
    EntryType entry_type;
    std::string signature;
    Language::DataType data_type;

    const std::string str() {
        const std::map<EntryType, const char*> enum_to_text {
            { EntryType::sVariable, "sVariable" },
            { EntryType::sFunction, "sFunction" },
            { EntryType::sProcedure, "sProcedure" }
        };
        auto it = enum_to_text.find(entry_type);
        std::string s = it->second;
        std::stringstream ss;
        ss << s << ' ' << signature << ' ' << data_type.str();
        return ss.str();
    }
  };

  static std::string key(const std::string &scope, const std::string &name) {
    return scope + ":" + name;
  }

  bool in(const std::string &key) const {
    return table_.find(Common::to_lower(key)) != table_.end();
  }

  Entry *lookup(const std::string &key) {
    auto it = table_.find(Common::to_lower(key));
    if (it != table_.end()) {
      return &(it->second);
    }
    return nullptr;
  }

  Entry *lookup(const std::string &scope, const std::string &name) {
    return lookup(key(scope, name));
  }

  void add(const std::string &scope,
           const std::string &name,
           EntryType etype,
           const std::string &signature,
           Language::DataType dtype) {
    std::string k = key(scope, name);
    table_[Common::to_lower(k)] = {etype, signature, dtype};
  }

  void add_var(const std::string &scope, const std::string &name, Language::DataType dtype = LNG::DataType()) {
    add(scope, name, EntryType::sVariable, "", dtype);
  }

  void add_procedure(const std::string &name, const std::string &signature) {
    add("", name, EntryType::sProcedure, signature, LNG::DataType());
  }

  void add_function(const std::string &name, const std::string &signature, Language::DataType dtype) {
    add("", name, EntryType::sFunction, signature, LNG::DataType());
  }

  void clear() {
    table_.clear();
  }

  std::map<std::string, Entry> get() { return table_; }

 private:
  std::map<std::string, Entry> table_;
};
#endif //TURBOPASCAL_SYMBOLTABLE_H
