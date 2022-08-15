#ifndef OPERATION_INCLUDED
#define OPERATION_INCLUDED

#include <string>
#include <vector>
#include <stack>
#include <iostream>
//EditOperation
enum EditOperation {Insert = 0, Delete = 1};
extern std::string operationstringify[2];
struct edit_operation {
  EditOperation op;
  size_t pos;
  std::string content;
  bool adjacent(size_t o_pos, EditOperation o_op) {
    return (o_op == op) && ((op == EditOperation::Insert && o_pos == pos) || (op == EditOperation::Delete && o_pos == pos-1));
  }
  void show() {
    std::cout << operationstringify[op] << " " << content << " on " << pos << std::endl;
  }
};

class OperationList {
  public:
    OperationList();
    void update(edit_operation new_operation);
    std::vector<edit_operation> *diff_list();
    bool empty();
    size_t size();
    void clear();
  private:
    std::stack<edit_operation> ops;
};

#endif
