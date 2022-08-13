#include <iostream>
#include "Maze.h"
#include <vector>
//Noah Berry - Homework 1
//To run program, navigate to directory, enter 'make' then enter './maze'
//Program will start execution
std::string SquareTypeStringify(SquareType sq){//Returns emoji symbol of whatever SquareType is passed.
  switch (sq) {
    case SquareType::Wall:
    return "🚧";
    break;
    case SquareType::Exit:
    return "🏁";
    break;
    case SquareType::Empty:
    return "⬜";
    break;
    case SquareType::Human:
    return "🐧";
    break;
    case SquareType::Enemy:
    return "🦈";
    break;
    case SquareType::Treasure:
    return "🐟";
    break;
  }
}
//-----------------------------------------------------------
Board::Board(){
  //The initially fill board with SquareType::Empty when Board constructor
  //is called by the Maze constructor.
  for(int i = 0; i < get_rows(); i++){
    for(int j = 0; j < get_cols(); j++){
      arr_[i][j] = SquareType::Empty;
    }
  }
}
//-----------------------------------------------------------
std::vector<Position> Board::GetMoves(Player *p){
    //Presents and returns moves to player.
    std::vector<Position> moves;
    int rowLenO, colLenO;
    //These value are set to be larger than the size of the board
    //So that MovePlayer can test the condition for an invalid choice
    //From the moves vector.
    rowLenO = get_rows()+1;
    colLenO = get_cols()+1;
    Position posToPass, pCurrentPos;
    pCurrentPos = p->get_position();
    std::cout << p->get_name() << " can go: ";
    //Each of the following assignments and if else statements
    //tests to make sure that a move is within the range of the board
    //and not a move into a wall.
    //If move is valid, the position with valid coordinates is pushed into the
    //moves vector, else a position coordinates out of range of the board
    //is pushed into the moves vector.
    posToPass.row = p->get_position().row - 1;
    posToPass.col = p->get_position().col;
    if((pCurrentPos.row - 1 > -1) && (get_square_value(posToPass) != SquareType::Wall)){
            moves.push_back(posToPass);
            std::cout<< "UP ";
        }else{
          posToPass.row = rowLenO;
          posToPass.col = colLenO;
          moves.push_back(posToPass);
        }
    posToPass.row = p->get_position().row + 1;
    posToPass.col = p->get_position().col;
    if((pCurrentPos.row + 1 < get_rows()) && (get_square_value(posToPass) != SquareType::Wall)){
            moves.push_back(posToPass);
            std::cout << "DOWN ";
        }else{
          posToPass.row = rowLenO;
          posToPass.col = colLenO;
          moves.push_back(posToPass);
        }
    posToPass.row = p->get_position().row;
    posToPass.col = p->get_position().col - 1;
    if((pCurrentPos.col - 1 > -1) && (get_square_value(posToPass) != SquareType::Wall)){
            moves.push_back(posToPass);
            std::cout << "LEFT ";
        }else{
          posToPass.row = rowLenO;
          posToPass.col = colLenO;
          moves.push_back(posToPass);
        }
    posToPass.row = p->get_position().row;
    posToPass.col = p->get_position().col + 1;
    if((pCurrentPos.col + 1 < get_cols()) && (get_square_value(posToPass) != SquareType::Wall)){
            moves.push_back(posToPass);
            std::cout << "RIGHT ";
        }else{
          posToPass.row = rowLenO;
          posToPass.col = colLenO;
          moves.push_back(posToPass);
        }
        std::cout<<std::endl;
        return moves;
}
//-----------------------------------------------------------
bool Board::MovePlayer(Player *p, Position pos){
    //If move is out of range of the board, function
    //returns false.
    if((pos.col > get_rows() || (pos.row > get_rows()))){
        return false;
      }else{
          if(!p->is_human()){
              if(get_square_value(pos) == SquareType::Enemy){
                //If a non-human player chooses a move into another
                //non-human player, player does not move position
                //and function returns true according the rules of the game.
                return true;
              }else{
                //If player chooses move not into a non-human player,
                //player's position is changed, and old position
                //is changed to SquareType::Empty.
                arr_[p->get_position().row][p->get_position().col] = SquareType:: Empty;
                //If player moves into position with Treasure player receives 100 points
                if(get_square_value(pos) == SquareType::Treasure){
                  p->ChangePoints(100);
                }
                p->SetPosition(pos);
                SetSquareValue(p->get_position(), SquareType::Enemy);
                return true;
              }

            }else{
              //When a human player moves into a position player's old position
              //is changed to SquareType::Empty.
              arr_[p->get_position().row][p->get_position().col] = SquareType:: Empty;
              //If player moves into position with Treasure player receives 100 points
              if(get_square_value(pos) == SquareType::Treasure){
                p->ChangePoints(100);
              }
              //If human player moves into position with SquareType::Exit player receives 1 point.
              if(get_square_value(pos) == SquareType::Exit){
                p->ChangePoints(1);
              }
              p->SetPosition(pos);
              SetSquareValue(p->get_position(), SquareType::Human);
              return true;
            }

          }
}
//-----------------------------------------------------------
void Board::SetSquareValue(Position pos, SquareType value){
  arr_[pos.row][pos.col] = value; //Simply set a position's Squarevalue to SquareType passed into function.
}
//-----------------------------------------------------------
Maze::Maze(std::string humanPlayer, int opnts){
  turn_count_ = 0;
  turn_limit_ = ((opnts +1) * 9); //Gives each player on the board a limit of 9 moves(improvment).
  std::vector<Player *> tmp;//Empty vector of player instantiated.
  players_ = tmp; //New vector assigned to players_ vector.
  board_ = new Board(); //Board constructor called to start new game.
  Player * homosapien = new Player(humanPlayer, true); //Player object created as human player, assigned given name.
  NewGame(homosapien, opnts);//Human player object and number of enemies passed to NewGame.
}
//-----------------------------------------------------------
void Maze::NewGame(Player *human, const int enemies){

  players_.push_back(human);
  for(int i=0; i < enemies; i++){
    Player * playa = new Player("Amous-"+ std::to_string(i), false);
    players_.push_back(playa);
  }
  //This routine sets players position's and Exit square value
  //after all player objects have been instantiated.
  Position pos;
  pos.row = 0;
  pos.col = 0;
  players_[0]->SetPosition(pos);
  board_->SetSquareValue(players_[0]->get_position(), SquareType::Human);

  for(int i = 1; i < enemies+1; i++){
    pos.row = 0;
    pos.col = board_->get_cols() - i;
    players_[i]->SetPosition(pos);
    board_->SetSquareValue(players_[i]->get_position(), SquareType::Enemy);
  }
  pos.row = 3;
  pos.col = 3;
  board_->SetSquareValue(pos, SquareType::Exit);
  //The following line place Walls and Treasure on board after players
  //and exit square values have been set.
  srand(time(NULL));
  int t1, t2, w1;
  SquareType testPos;
  for(int i = 0; i < 4; i++){
    pos.row = i;
    for(int j = 0; j < 4; j++){
        pos.col = j;
        testPos = board_->get_square_value(pos);
      if((testPos != SquareType::Wall) && (testPos != SquareType::Enemy) && (testPos != SquareType::Human) && (testPos != SquareType::Exit)){
        w1 =(rand() % 5);
        t1 = (rand() % 10);
        t2 = (rand() % 10);
        if(w1==1){
          board_->SetSquareValue(pos, SquareType::Wall);
          }else
        if(t1==0 || t1== 1){
          board_->SetSquareValue(pos, SquareType::Treasure);
          }

        }
      }
    }
  //______________________________________________________________________

  //Prints board to terminal after initial creation.
  PrintBoard();
}
//-----------------------------------------------------------
void Maze::TakeTurn(Player *p){

    std::vector vecOfMoves = board_->GetMoves(GetNextPlayer());

    std::string  move;
    std::cin >> move;
    if(move == "UP" || move == "up" || move == "DOWN" || move == "down" ||move == "LEFT" || move == "left" || move == "RIGHT" || move == "right"){
          if(move == "UP" || move == "up"){
            if(board_->MovePlayer(GetNextPlayer(), vecOfMoves[0])){
              turn_count_ = turn_count_ + 1;
              }else{
                std::cout<< "Move Unsuccessful ☹️. Please choose valid move." << std::endl;
              }
            }
          if(move == "DOWN" || move == "down"){
            if(board_->MovePlayer(GetNextPlayer(), vecOfMoves[1])){
              turn_count_ = turn_count_ + 1;
              }else{
                std::cout<< "Move Unsuccessful ☹️. Please choose valid move." << std::endl;
              }
            }
          if(move == "LEFT" || move == "left"){
            if(board_->MovePlayer(GetNextPlayer(), vecOfMoves[2])){
              turn_count_ = turn_count_ + 1;
              }else{
                std::cout<< "Move Unsuccessful ☹️. Please choose valid move." << std::endl;
              }
            }
          if(move == "RIGHT" || move == "right"){
            if(board_->MovePlayer(GetNextPlayer(), vecOfMoves[3])){
              turn_count_ = turn_count_ + 1;
              }else{
                std::cout<< "Move Unsuccessful ☹️. Please choose valid move." << std::endl;
              }
            }
        }else{
          std::cout<< "Move Unsuccessful ☹️. Please choose valid move." << std::endl;
        }
        //Print board after turn.
        PrintBoard();



}
//-----------------------------------------------------------
Player * Maze::GetNextPlayer(){
  //Mod turn_count_ by number of players to determine turn.
  int calcTurn = (turn_count_ % players_.size());
  return players_[calcTurn];
}
//-----------------------------------------------------------
bool Maze::IsGameOver(){
  Position exitPos;
  exitPos.col = 3;
  exitPos.row = 3;
  // checks if any non-human player shares position with human player
  //If so, function returns true.
  for (int i = 1; i < players_.size(); i++){
    if(players_[i]->get_position() == players_[0]->get_position()){
      std::cout << players_[0]->get_name() << " has been eaten!" << std::endl;
      return true;
    }
  }
  if(turn_count_ > turn_limit_){
    std::cout << "You've run out of turns!" << std::endl;
    return true;
  }
  //Checks to see if human player is in exit square position.
  //If so, function returns true.
  if(exitPos == players_[0]->get_position()){
    return true;
  }else{
    return false;
  }
}
//-----------------------------------------------------------
std::string Maze::GenerateReport(){
  std::string reportString = "";
  //Appends player's name and string representation of player's points onto string.
  for(int i = 0; i < players_.size(); i++){
    reportString = reportString + players_[i]->Stringify();
  }
  return reportString;
}

std::string Maze::GetRemainingTurns(){
  return  "You have " + std::to_string((turn_limit_ - turn_count_)) + " turns remaining.";
}

void Maze::PrintBoard(){
  Position pos;
  for (int i = 0; i < 4; i++){
      std::cout<<std::endl;
      pos.row = i;
    for(int j = 0; j < 4; j++){
          pos.col = j;
          std::cout << SquareTypeStringify(board_->get_square_value(pos));
        }
  }
  std::cout<<std::endl;
}
