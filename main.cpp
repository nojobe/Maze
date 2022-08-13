
//Noah Berry, Homework 1.
//To run program, navigate to directory, enter 'make' then enter './maze'
//Program will start execution

#include<iostream>
#include "Player.h"
#include "Maze.h"

int main(){
  int enemies = 0;
  std::string human = "";
  std::cout << "Welcome to Maze" << std::endl;
  std::cout << "Enter your name: " << std::endl;
  std::cin >> human;
  std::cout << "Please enter number of enemies(2-4): "<< std::endl;
  std::cin >> enemies;

  while(enemies <2 || enemies > 4){// While loop will check to make sure that the number of enemies entered is valid
    std::cout<< "Invalid number of enemies." <<std::endl;
    std::cout << "Please enter number of enemies(2-4): "<< std::endl;
    std::cin >> enemies;
  }

  Maze newGame = Maze(human, enemies);

  while(!newGame.IsGameOver()){// Continues to get player according to turn order (even in case of invalid move).
    std::cout << newGame.GetRemainingTurns() << std::endl;
    newGame.TakeTurn(newGame.GetNextPlayer());
}
  std::cout << newGame.GenerateReport() << std::endl; //this line calls Generate Report on game once IsGameOver returns true and while loop exits.
  return 0;
}
