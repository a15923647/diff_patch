#include "operation.h"
std::string operationstringify[2] = {"insert", "delete"};
std::vector<edit_operation> *OperationList::diff_list() {
  std::stack<edit_operation> dup(ops);
  const size_t n = this->size();
  std::vector<edit_operation> *ret = new std::vector<edit_operation>(n);
  for (size_t i = 0; i < n; i++) {
    (*ret)[i] = dup.top(); dup.pop();
  }
  return ret;
}

void OperationList::update(edit_operation new_operation) {
  if (!ops.empty() && ops.top().adjacent(new_operation.pos, new_operation.op)) {
    ops.top().content = new_operation.content + ops.top().content;
    ops.top().pos = new_operation.pos;
  } else {
    ops.push(new_operation);
  }
}

OperationList::OperationList() {this->ops = std::stack<edit_operation>();}
bool OperationList::empty() {return this->ops.empty();}
size_t OperationList::size() {return this->ops.size();}
void OperationList::clear() {while (!this->ops.empty()) this->ops.pop();}
