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
  cout << "Testing operation\n";
  edit_operation example{EditOperation::Insert, 1, "insert content"};
  example.show();
  ofstream f("eop_dump.txt");
  f << example;
  f.close();
  if (!example.adjacent(1, EditOperation::Insert)) {
    return false;
  }
  OperationList op_list;
  ifstream fin("op_list_dump.txt");
  fin >> op_list;
  fin.close();
  cout << op_list;
  return true;
}

bool Test::testLCS(string x_path, string y_path) {
  cout << "testing LCS\n";
  this->x_path = string(x_path);
  this->y_path = string(y_path);
  ifstream x_fd(x_path);
  ifstream y_fd(y_path);
  string x((istreambuf_iterator<char>(x_fd)), istreambuf_iterator<char>());
  string y((istreambuf_iterator<char>(y_fd)), istreambuf_iterator<char>());
  x_fd.close(); y_fd.close();
  cout << x << y;
  lcs = new LCS(x, y);
  string lcs_res;
  lcs->lcs(lcs_res);
  ofstream f("op_list_dump.txt");
  f << lcs->op_list;
  f.close();
  cout << lcs->op_list << endl;
  return true;
}

bool Test::testPatch() {
  cout << "testing Patch\n";
  if (!this->lcs) return false;
  auto *diff_list = lcs->diff_list();
  auto patch = Patch();
  ifstream x_fd(x_path);
  ifstream y_fd(y_path);
  string x((istreambuf_iterator<char>(x_fd)), istreambuf_iterator<char>());
  string y((istreambuf_iterator<char>(y_fd)), istreambuf_iterator<char>());
  std::cout <<  "x length: " << x.length() << ", y length: " << y.length() << std::endl;
  x_fd.close(); y_fd.close();
  string patch_res;
  patch.patch(x, *diff_list, patch_res);
  if (patch_res != y) {
    cout << "patch fail!\n";
    cout << patch_res << endl;
    cout << y << endl;
  }
  string patch_back_res;
  patch.patchBack(y, *diff_list, patch_back_res);
  if (patch_back_res != x) {
    cout << "patchBack fail\n";
    cout << patch_back_res << endl;
    cout << x << endl;
  }
  return (patch_res == y) && (patch_back_res == x);
}

int main(int argc, char* argv[]) {
  if (argc < 3) {
    cout << "Usage: " << argv[0] << " x_path y_path\n";
    return 1;
  }
  cout << "x_path: " << argv[1] << endl;
  cout << "y_path: " << argv[2] << endl;
  Test test;
  const string op_res = (test.testOperation() ? "SUCCESS" : "FAIL");
  const string lcs_res = (test.testLCS(argv[1], argv[2]) ? "SUCCESS" : "FAIL");
  const string patch_res = (test.testPatch() ? "SUCCESS" : "FAIL");
  cout << "test operation " << op_res << endl;
  cout << "test LCS " << lcs_res << endl;
  cout << "test patch " << patch_res << endl;
  return 0;
}
