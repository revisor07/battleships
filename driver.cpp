#include <iostream>
#include <fstream> 
using namespace std;

const int field_size = 10;
bool game_over = false;
bool p1_turn = true;
string winner = "0";
string p1_ships[field_size][field_size];
string p1_attacks[field_size][field_size];
string p2_ships[field_size][field_size];
string p2_attacks[field_size][field_size];

void print_field(string field[field_size][field_size]){ 
  int rows = 0;
  cout << "     ";
  for(int columns = 0; columns < field_size; columns++){
    cout << columns << "  ";
  }
  cout << "\n\n";
  for(int i = 0; i < field_size; i++){
    cout << rows << "    ";
    rows++;
    for(int j = 0; j < field_size; j++){
      cout << field[i][j] << "  ";
    }
    cout << "\n";
  }
}

void read_field(string field[field_size][field_size], string file){
  ifstream f(file);
  for (int i = 0; i < field_size; i++)
    for (int j = 0; j < field_size; j++)
      f >> field[i][j];
}

void execute_player_turn(){
  string (*ships)[field_size];
  string (*attacks)[field_size];
  string (*ships_other)[field_size];
  string player_num;
  if(p1_turn){
    ships = p1_ships;
    ships_other = p2_ships;
    attacks = p1_attacks;
    player_num = "1";
    p1_turn = false;
  }
  else{
    ships = p2_ships;
    ships_other = p1_ships;
    attacks = p2_attacks;
    player_num = "2";   
    p1_turn = true;
  }

  //print board before attack
  system("clear");
  cout << "     --- PLAYER "<<player_num<<" TURN ---" << endl;
  cout << "\n";
  cout << "     YOUR SHIPS" << endl;
  print_field(ships);
  cout << "\n";
  cout << "     ENEMY FIELD" << endl;
  print_field(attacks);

  cout << "\n";
  int x;
  int y;
  cout << "What coordinate would you like to strike at? (format as 'x y')" << endl;
  cin >> x >> y;
  bool enemy_hit = false;
  bool ship_survived = false;
  string target_type = ships_other[x][y];
  ships_other[x][y] = "*";
  if(target_type != "." && target_type != "*")
    enemy_hit = true;
    for (int i = 0; i < field_size; i++)
      for (int j = 0; j < field_size; j++)
        if(ships_other[i][j] == target_type){
          ship_survived = true;
        }
  if (enemy_hit){
    attacks[x][y] = target_type;
    ships_other[x][y] = "*";
  }
  else
    attacks[x][y] = "*";
  cout << "\n";

  //print board after attack
  system("clear");
  cout << "     --- PLAYER "<<player_num<<" TURN ---" << endl;
  cout << "\n";
  cout << "     YOUR SHIPS" << endl;
  print_field(ships);
  cout << "\n";
  cout << "     ENEMY FIELD" << endl;
  print_field(attacks);

  //feedback
  cout << "\n";
  cout << "You shot at coordinates [" << x << " " << y <<"] " << endl;
  if(!ship_survived)
    cout << "Enemy ship destroyed" << endl;
  else if(enemy_hit)
    cout << "You hit an enemy ship!" << endl;
  else
    cout << "You missed!" << endl;
  cout << "\n";
}

void privacy_turn_transition(){
  string end_turn1 = "" ;
  do
  {
    cout << "Type 'x' followed by 'enter' when you are ready to end the turn and pass the device to the opponent" << endl;
    cin >> end_turn1;
  }
  while(end_turn1 != "x");
  system("clear");
  string end_turn2 = "" ;
  do
  {
    cout << "Type 'x' to start next player's turn" << endl;
    cin >> end_turn2;
  }
  while(end_turn2 != "x");
}

void game_over_check(){
  bool p1_ship_survived = false;
  bool p2_ship_survived = false;
  for (int i = 0; i < field_size; i++)
    for (int j = 0; j < field_size; j++){
      if(p1_ships[i][j] != "." && p1_ships[i][j] != "*"){
        p1_ship_survived = true;
      }
      if(p2_ships[i][j] != "." && p2_ships[i][j] != "*"){
        p2_ship_survived = true;
      }
    }
  
  if(!p1_ship_survived){
    winner = "2";
    game_over = true;
  }
  if(!p2_ship_survived){
    winner = "1";
    game_over = true;
  }
}

int main() {
  //setup
  read_field(p1_ships, "p1_ships.txt");
  read_field(p2_ships, "p2_ships.txt");
  for(int i = 0; i < field_size; i++)
    for(int j = 0; j < field_size; j++){
      p1_attacks[i][j] = ".";
      p2_attacks[i][j] = ".";
    }


  cout << "\n";
  while(!game_over){
    execute_player_turn();
    game_over_check();
    if(!game_over)
      privacy_turn_transition();
  }
  cout << "\n";
  cout << "GAME OVER" << endl;
  cout << "\n";
  cout << "Winner: Player " << winner << endl; 
  return 0;
}








