// clang-tidy check: cppcoreguidelines-pro-type-member-init
// Clang-C++ warning: none
struct Size {
  Size() {
    width = 0;
    height = 0;
  }

  int width;
  int height;
};

int main() {}
