#include <iostream>
#include <fstream> 
using namespace std;

int main() {
  int p1_ships[5][5] = {{1,1,1,1,1}, {1,1,1,1,1},{1,1,1,1,1},{1,1,1,1,1},{1,1,1,1,1}};
  int (*p_ships)[5];
  p_ships = p1_ships;
  cout << p_ships[0][0] << endl;
  p_ships[0][0] = 2;
  cout << p1_ships[0][0] << endl;
  cout << p_ships[0][0] << endl;
}