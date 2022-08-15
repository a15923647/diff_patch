#include "lcs.h"
#include "operation.h"
LCS::LCS(std::string& s, std::string& t) {
  this->s = std::string(s);
  this->t = std::string(t);
  common_len = std::vector<std::vector<size_t>>(s.length()+1, std::vector<size_t>(t.length()+1, 0));
  construct_arr();
}
size_t LCS::length() {return common_len.back().back();}
std::string LCS::lcs() {
  size_t i = common_len.size()-1, j = common_len[0].size()-1;
  std::string ret;
  op_list.clear();
  while (i > 0 && j > 0) {
    if (s[i-1] == t[j-1]) {
      ret = s[i-1] + ret;
      i--; j--;
    } else if (common_len[i-1][j] < common_len[i][j-1]) {
      op_list.update(edit_operation{EditOperation::Insert, i-1, std::string(1, t[j-1])});
      j--;
    } else {
      op_list.update(edit_operation{EditOperation::Delete, i-1, std::string(1, s[i-1])});
      i--;
    }
  }
  return ret;
}
std::vector<edit_operation> *LCS::diff_list() {return this->op_list.diff_list();}
void LCS::show_arr() {
  for (auto& a : common_len) {
    for (auto b : a) {
      std::cout << b << " ";
    }
    std::cout << std::endl;
  }
}
void LCS::construct_arr() {
  for (size_t i = 1; i < common_len.size(); i++) {
    for (size_t j = 1; j < common_len[0].size(); j++) {
      //                 two end char are identical,+1                    insert s[i] from s[i-1]  insert s[j] from s[j-1]
      common_len[i][j] = (s[i-1] == t[j-1]) ? (common_len[i-1][j-1]+1) : (std::max(common_len[i-1][j], common_len[i][j-1]));
    }
  }
}
