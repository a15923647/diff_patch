#include <bits/stdc++.h>
#include "operation.h"
#include "lcs.h"
#include "patch.h"

using namespace std;

class Test {
  public:
    bool testOperation();
    bool testLCS(string x_path, string y_path);
    bool testPatch();
  private:
    LCS *lcs;
    string x_path;
    string y_path;
};

bool Test::testOperation() {
  edit_operation example{EditOperation::Insert, 1, "insert"};
  example.show();
  if (!example.adjacent(1, EditOperation::Insert)) {
    return false;
  }
  return true;
}

bool Test::testLCS(string x_path, string y_path) {
  this->x_path = string(x_path);
  this->y_path = string(y_path);
  ifstream x_fd(x_path);
  ifstream y_fd(y_path);
  string x((istreambuf_iterator<char>(x_fd)), istreambuf_iterator<char>());
  string y((istreambuf_iterator<char>(y_fd)), istreambuf_iterator<char>());
  x_fd.close(); y_fd.close();
  lcs = new LCS(x, y);
  lcs->lcs();
  return true;
}

bool Test::testPatch() {
  if (!this->lcs) return false;
  auto *diff_list = lcs->diff_list();
  auto patch = Patch();
  ifstream x_fd(x_path);
  ifstream y_fd(y_path);
  string x((istreambuf_iterator<char>(x_fd)), istreambuf_iterator<char>());
  string y((istreambuf_iterator<char>(y_fd)), istreambuf_iterator<char>());
  x_fd.close(); y_fd.close();
  string patch_res;
  patch.patch(x, *diff_list, patch_res);
  return (patch_res == y);
}

int main(int argc, char* argv[]) {
  if (argc < 3) {
    cout << "Usage: " << argv[0] << " x_path y_path\n";
    return 1;
  }
  Test test;
  cout << "test operation " << (test.testOperation() ? "SUCCESS" : "FAIL") << endl;
  cout << "test LCS " << (test.testLCS(argv[1], argv[2]) ? "SUCCESS" : "FAIL") << endl;
  cout << "test patch " << (test.testPatch() ? "SUCCESS" : "FAIL") << endl;
  return 0;
}
