#include <iostream>
#include <vector>
#include <string>
#include <cassert>

struct Variable {
  bool global;
  size_t identifier;
};

struct Value {
  size_t integer_value;
};

struct VariableType {
  size_t bit_width;
  bool is_signed;
  uint8_t pointer_depth;
  size_t array_size;
};

std::string substring(const std::string& input, std::string::size_type from, std::string::size_type to) {
  assert(to - from > 0);
  return input.substr(from, to - from);
}

std::vector<std::string> split(const std::string& input, const std::vector<std::string>& deliminators) {
  if (deliminators.empty())
    return {input};
  std::vector<std::string> result;
  using SPos = std::string::size_type;
  auto end_pos = std::string::npos;
  SPos curr_del_pos = 0;
  SPos next_del_pos = input.find(deliminators[0]);
  for (size_t curr_index = 0; next_del_pos != end_pos;) {
    result.push_back(substring(input, curr_del_pos, next_del_pos));
    curr_del_pos = next_del_pos + deliminators[curr_index].size();
    next_del_pos = input.find(deliminators[++curr_index]);
  }
  return result;
}

using VarVal = std::variant<Variable, Value>;

struct Instruction {
  virtual void read_from_line(const std::string& line);
};

struct LoadInstruction : Instruction {
  Variable lhs_variable;
  Variable rhs_variable;

  VariableType lhs_type;
  VariableType rhs_type;

  size_t alignment;

  void read_from_line(const std::string& line) {
  }
};

struct AllocaInstruction : Instruction {
  Variable variable;
  VariableType type;

  size_t alignment;

  void read_from_line(const std::string& line) {
  }
};

struct StoreInstruction : Instruction {
  Variable lhs_variable;
  VarVal rhs;

  VariableType lhs_type;
  VariableType rhs_type;

  size_t alignment;

  void read_from_line(const std::string& line) {
  }
};

struct SextInstruction : Instruction {
  Variable lhs_variable;
  VarVal rhs;

  VariableType lhs_type;
  VariableType rhs_type;

  size_t alignment;

  void read_from_line(const std::string& line) {
  }
};

struct AddInstruction : Instruction {
  Variable variable;
  VarVal left_argument;
  VarVal right_argument;

  VariableType type;

  bool nsw;

  void read_from_line(const std::string& line) {
  }
};

using Attributes = std::set<std::string>;
using Instructions = std::vector<Instruction>;

struct llvm_function {
  std::string name;
  VariableType return_type;
  Attributes attributes;
  Instructions instructions;
};
