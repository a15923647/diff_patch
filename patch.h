#ifndef PATCH_INCLUDED
#define PATCH_INCLUDED
#include <string>
#include <vector>
#include "operation.h"
class Patch {
  public:
    void patch(std::string& x, std::vector<edit_operation>& opv, std::string& res);
  private:
    static void insert(std::string& x, size_t& i, std::string& res, edit_operation& op);
    static void skip(std::string& x, size_t& i, std::string& res, edit_operation& op);
};

#endif
