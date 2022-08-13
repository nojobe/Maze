#include<iostream>
#include "Player.h"


Player::Player(const std::string name, const bool is_human){
  is_human_ = is_human;
  name_ = name;
  points_ = 0;
  pos_.row = 0;
  pos_.col = 0;

}

void Player::ChangePoints(const int x){
  points_ = points_ + x;
}

void Player::SetPosition(Position pos){
  pos_ = pos;
}

std::string Player::Stringify(){
  return (name_ + " has " + std::to_string(points_) + " ");
}
