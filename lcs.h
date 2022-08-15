#ifndef LCS_INCLUDED
#define LCS_INCLUDED

#include <string>
#include <vector>
#include "operation.h"
class LCS {
  public:
    LCS(std::string& s, std::string& t);
    size_t length();
    std::string lcs();
    std::vector<edit_operation> *diff_list();
    void show_arr();
  private:
    void construct_arr();
    std::vector<std::vector<size_t>> common_len;
    OperationList op_list;
    std::string s;
    std::string t;
};

#endif
