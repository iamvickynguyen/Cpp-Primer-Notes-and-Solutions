#include <iostream>
#include <string>
using namespace std;

class Screen {
public:
  using pos = std::string::size_type;

  Screen() = default;
  Screen(pos ht, pos wd, char c): height(ht), width(wd), contents(ht * wd, c) {}
  
  Screen &move(pos r, pos c); 

  Screen &set(char c);
  Screen &set(pos ht, pos wd, char c);

  Screen &display(std::ostream &os) {
    do_display(os);
    return *this;
  }

  const Screen &display(std::ostream &os) const {
    do_display(os);
    return *this;
  }

private:
  pos cursor = 0;
  pos height = 0, width = 0;
  std::string contents;

  void do_display(std::ostream &os) const {
    os << contents;
  }
};

inline Screen &Screen::set(char c) {
  contents[cursor] = c;
  return *this; // return this object as an lvalue
}

inline Screen &Screen::set(pos row, pos col, char c) {
  contents[row * width + col] = c;
  return *this;
}

inline Screen &Screen::move(pos r, pos c) {
  pos row = r * width;
  cursor = row + c;
  return *this;
}

int main() {
  Screen myScreen(5, 5, 'X');
  myScreen.move(4,0).set('#').display(cout);
  cout << "\n";
  myScreen.display(cout);
  cout << "\n";
}
