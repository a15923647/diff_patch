#include "patch.h"
void Patch::patch(std::string& x, std::vector<edit_operation>& opv, std::string& res) {
  size_t idx = 0;
  for (size_t i = 0; i < x.length(); i++) {
    if (idx < opv.size() && i == opv[idx].pos && opv[idx].op == EditOperation::Delete) 
      Patch::skip(x, i, res, opv[idx++]);
    if (i < x.length()) res += x[i];
    if (idx < opv.size() && i == opv[idx].pos && opv[idx].op == EditOperation::Insert)
      Patch::insert(x, i, res, opv[idx++]);
  }
}
void Patch::insert(std::string& x, size_t& i, std::string& res, edit_operation& op) {
  res += op.content;
}
void Patch::skip(std::string& x, size_t& i, std::string& res, edit_operation& op) {
  i += op.content.length();
}
