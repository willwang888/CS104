// GameCommands.hpp
// 11/5/16
// David Silverstone
// an interface to play the game

#ifndef GAME_INTERFACE_SO_PLAYERS_CAN_PLAY_FFS_H
#define GAME_INTERFACE_SO_PLAYERS_CAN_PLAY_FFS_H

#include "Game.h"
#include "Exceptions.h"

void init(Game& game, int&); // second parameter is the number of players - tells caller how many players there are
void play(Game& game);
std::string strtoupper(std::string);
void endDialog(Game& game);


#endif /* GAME_INTERFACE_SO_PLAYERS_CAN_PLAY_FFS_H */