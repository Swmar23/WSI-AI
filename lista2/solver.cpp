#include <random>
#include <iostream>
#include <map>
#include <stdlib.h>  
#include <bits/stdc++.h>
#include <vector>
#include <string>
#include <sstream>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <arpa/inet.h>

using namespace std;

struct GameState {
  uint8_t places[25]; //0 to puste, 1 to O, 2 to X

  GameState(){
    for(int i = 0; i < 25; i++) {
      places[i] = 0;
    }
  };

  GameState(uint8_t places[25]) {
    for (int i = 0; i < 25; i++) {
      this->places[i] = places[i];
    }
  }

  bool isBoardFull() {
    for (int i = 0; i < 25; i++) {
      if (this->places[i] == 0) return false;
    }
    return true;
  }

  bool setMove(int move, uint8_t player) {
    int i,j;
    i = (move/10)-1;
    j = (move%10)-1;
    if( (i<0) || (i>4) || (j<0) || (j>4) ) return false; 
    if( places[i*5 + j] != 0 ) return false;
    places[i*5 + j] = player;
    return true;
  }

  int gameStatus() {
    // 0 - nierozstrzygnięta
    // 1 - wygrana gracza 1
    // 2 - wygrana gracza 2
    // 3 - remis

    //sprawdzanie wygranych
    for (int i = 0; i < 5; i++) {
      //Horizontal
      if (places[5*i + 0] == 1 && places[5*i + 1] == 1 && places[5*i + 2] == 1 && places[5*i + 3] == 1) {
        return 1;
      }
      if (places[5*i + 1] == 1 && places[5*i + 2] == 1 && places[5*i + 3] == 1 && places[5*i + 4] == 1) {
        return 1;
      }
      if (places[5*i + 0] == 2 && places[5*i + 1] == 2 && places[5*i + 2] == 2 && places[5*i + 3] == 2) {
        return 2;
      }
      if (places[5*i + 1] == 2 && places[5*i + 2] == 2 && places[5*i + 3] == 2 && places[5*i + 4] == 2) {
        return 2;
      }

      //Vertical
      if (places[5*0 + i] == 1 && places[5*1 + i] == 1 && places[5*2 + i] == 1 && places[5*3 + i] == 1) {
        return 1;
      }
      if (places[5*1 + i] == 1 && places[5*2 + i] == 1 && places[5*3 + i] == 1 && places[5*4 + i] == 1) {
        return 1;
      }
      if (places[5*0 + i] == 2 && places[5*1 + i] == 2 && places[5*2 + i] == 2 && places[5*3 + i] == 2) {
        return 2;
      }
      if (places[5*1 + i] == 2 && places[5*2 + i] == 2 && places[5*3 + i] == 2 && places[5*4 + i] == 2) {
        return 2;
      }
    }

    //Diagonal One
    if (places[5*1 + 1] == 1 && places[5*2 + 2] == 1 && places[5*3 + 3] == 1 && (places[5*0 + 0] == 1 || places[5*4 + 4] == 1)) {
      return 1;
    }
    if (places[5*1 + 1] == 2 && places[5*2 + 2] == 2 && places[5*3 + 3] == 2 && (places[5*0 + 0] == 2 || places[5*4 + 4] == 2)) {
      return 2;
    }
    if (places[5*1 + 0] == 1 && places[5*2 + 1] == 1 && places[5*3 + 2] == 1 && places[5*4 + 3] == 1) {
      return 1;
    }
    if (places[5*0 + 1] == 1 && places[5*1 + 2] == 1 && places[5*2 + 3] == 1 && places[5*3 + 4] == 1) {
      return 1;
    }
    if (places[5*1 + 0] == 2 && places[5*2 + 1] == 2 && places[5*3 + 2] == 2 && places[5*4 + 3] == 2) {
      return 2;
    }
    if (places[5*0 + 1] == 2 && places[5*1 + 2] == 2 && places[5*2 + 3] == 2 && places[5*3 + 4] == 2) {
      return 2;
    }

    //Diagonal Two
    if (places[5*1 + 3] == 1 && places[5*2 + 2] == 1 && places[5*3 + 1] == 1 && (places[5*4 + 0] == 1 || places[5*0 + 4] == 1)) {
      return 1;
    }
    if (places[5*1 + 3] == 2 && places[5*2 + 2] == 2 && places[5*3 + 1] == 2 && (places[5*4 + 0] == 2 || places[5*0 + 4] == 2)) {
      return 2;
    }
    if (places[5*0 + 3] == 1 && places[5*1 + 2] == 1 && places[5*2 + 1] == 1 && places[5*3 + 0] == 1) {
      return 1;
    }
    if (places[5*1 + 4] == 1 && places[5*2 + 3] == 1 && places[5*3 + 2] == 1 && places[5*4 + 1] == 1) {
      return 1;
    }
    if (places[5*0 + 3] == 2 && places[5*1 + 2] == 2 && places[5*2 + 1] == 2 && places[5*3 + 0] == 2) {
      return 2;
    }
    if (places[5*1 + 4] == 2 && places[5*2 + 3] == 2 && places[5*3 + 2] == 2 && places[5*4 + 1] == 2) {
      return 2;
    }

    //sprawdzanie porażek
    for (int i = 0; i < 5; i++) {
      //Horizontal
      if (places[5*i + 2] == 1 && ((places[5*i + 0] == 1 && places[5*i + 1] == 1) || (places[5*i + 1] == 1 && places[5*i + 3] == 1) || (places[5*i + 3] == 1 && places[5*i + 4] == 1) )) {
        return 2;
      }
      if (places[5*i + 2] == 2 && ((places[5*i + 0] == 2 && places[5*i + 1] == 2) || (places[5*i + 1] == 2 && places[5*i + 3] == 2) || (places[5*i + 3] == 2 && places[5*i + 4] == 2) )) {
        return 1;
      }

      //Vertical
      if (places[5*2 + i] == 1 && ((places[5*0 + i] == 1 && places[5*1 + i] == 1) || (places[5*1 + i] == 1 && places[5*3 + i] == 1) || (places[5*3 + i] == 1 && places[5*4 + i] == 1) )) {
        return 2;
      }
      if (places[5*2 + i] == 2 && ((places[5*0 + i] == 2 && places[5*1 + i] == 2) || (places[5*1 + i] == 2 && places[5*3 + i] == 2) || (places[5*3 + i] == 2 && places[5*4 + i] == 2) )) {
        return 1;
      }
    }

    //Diagonal One
    if (places[5*2 + 2] == 1 && ((places[5*0 + 0] == 1 && places[5*1 + 1] == 1) || (places[5*1 + 1] == 1 && places[5*3 + 3] == 1) || (places[5*3 + 3] == 1 && places[5*4 + 4] == 1) )) {
      return 2;
    }
    if (places[5*2 + 2] == 2 && ((places[5*0 + 0] == 2 && places[5*1 + 1] == 2) || (places[5*1 + 1] == 2 && places[5*3 + 3] == 2) || (places[5*3 + 3] == 2 && places[5*4 + 4] == 2) )) {
      return 1;
    }
    if (places[5*1 + 2] == 1 && places[5*2 + 3] == 1 && (places[5*0 + 1] == 1 || places[5*3 + 4] == 1)) {
      return 2;
    }
    if (places[5*1 + 2] == 2 && places[5*2 + 3] == 2 && (places[5*0 + 1] == 2 || places[5*3 + 4] == 2)) {
      return 1;
    }
    if (places[5*2 + 1] == 1 && places[5*3 + 2] == 1 && (places[5*1 + 0] == 1 || places[5*4 + 3] == 1)) {
      return 2;
    }
    if (places[5*2 + 1] == 2 && places[5*3 + 2] == 2 && (places[5*1 + 0] == 2 || places[5*4 + 3] == 2)) {
      return 1;
    }
    if (places[5*2 + 0] == 1 && places[5*3 + 1] == 1 && places[5*4 + 2] == 1) {
      return 2;
    }
    if (places[5*2 + 0] == 2 && places[5*3 + 1] == 2 && places[5*4 + 2] == 2) {
      return 1;
    }
    if (places[5*0 + 2] == 1 && places[5*1 + 3] == 1 && places[5*2 + 4] == 1) {
      return 2;
    }
    if (places[5*0 + 2] == 2 && places[5*1 + 3] == 2 && places[5*2 + 4] == 2) {
      return 1;
    }

    //Diagonal Two
    if (places[5*2 + 2] == 1 && ((places[5*0 + 4] == 1 && places[5*1 + 3] == 1) || (places[5*1 + 3] == 1 && places[5*3 + 1] == 1) || (places[5*3 + 1] == 1 && places[5*4 + 0] == 1) )) {
      return 2;
    }
    if (places[5*2 + 2] == 2 && ((places[5*0 + 4] == 2 && places[5*1 + 3] == 2) || (places[5*1 + 3] == 2 && places[5*3 + 1] == 2) || (places[5*3 + 1] == 2 && places[5*4 + 0] == 2) )) {
      return 1;
    }
    if (places[5*1 + 2] == 1 && places[5*2 + 1] == 1 && (places[5*0 + 3] == 1 || places[5*3 + 0] == 1)) {
      return 2;
    }
    if (places[5*1 + 2] == 2 && places[5*2 + 1] == 2 && (places[5*0 + 3] == 2 || places[5*3 + 0] == 2)) {
      return 1;
    }
    if (places[5*2 + 3] == 1 && places[5*3 + 2] == 1 && (places[5*1 + 4] == 1 || places[5*4 + 1] == 1)) {
      return 2;
    }
    if (places[5*2 + 3] == 2 && places[5*3 + 2] == 2 && (places[5*1 + 4] == 2 || places[5*4 + 1] == 2)) {
      return 1;
    }
    if (places[5*2 + 4] == 1 && places[5*3 + 3] == 1 && places[5*4 + 2] == 1) {
      return 2;
    }
    if (places[5*2 + 4] == 2 && places[5*3 + 3] == 2 && places[5*4 + 2] == 2) {
      return 1;
    }
    if (places[5*0 + 2] == 1 && places[5*1 + 1] == 1 && places[5*2 + 0] == 1) {
      return 2;
    }
    if (places[5*0 + 2] == 2 && places[5*1 + 1] == 2 && places[5*2 + 0] == 2) {
      return 1;
    }

    //Gdy plansza pełna a nie ma wygranej to remis
    if (isBoardFull()) return 3;
    return 0;
  }

  void printState() {
    cout << "-----------\n";
    cout << "|";
    for (int i = 0; i < 5; i++) {
      printf("%01d|", places[i]);
    }
    cout << "\n-----------\n";
    cout << "|";
    for (int i = 5; i < 10; i++) {
      printf("%01d|", places[i]);
    }
    cout << "\n-----------\n";
    cout << "|";
    for (int i = 10; i < 15; i++) {
      printf("%01d|", places[i]);
    }
    cout << "\n-----------\n";
    cout << "|";
    for (int i = 15; i < 20; i++) {
      printf("%01d|", places[i]);
    }
    cout << "\n-----------\n";
    cout << "|";
    for (int i = 20; i < 25; i++) {
      printf("%01d|", places[i]);
    }
    cout << "\n-----------\n";
  }
};

vector<GameState> getGameStateChildren(GameState gameState, uint8_t whoseMove, int direction) {
  vector<GameState> children;
  if (direction == 1) {
    for (int i = 0; i < 25; i++) {
      if (gameState.places[i] == 0) {
        GameState childOne;
        childOne = gameState;
        childOne.places[i] = whoseMove;

        children.push_back(childOne);
      }
    }
  } else {
    for (int i = 24; i >= 0; i--) {
      if (gameState.places[i] == 0) {
        GameState childOne;
        childOne = gameState;
        childOne.places[i] = whoseMove;

        children.push_back(childOne);
      }
    }
  }
  return children;
}

int getMove(GameState prevState, GameState currentState) {
  for (int i = 0; i < 25; i++) {
    if (prevState.places[i] != currentState.places[i]) {
      return ((i/5) + 1) * 10 + ((i%5) + 1);
    }
  }
  return -1;
}

// na początku alpha = -inf i beta = +inf
pair<double, GameState> minimaxWithAlphaBetaPruning(int depth, GameState gameState, uint8_t playerToMove, uint8_t ai_no, double alpha, double beta, double (*heuristicFunction)(GameState, uint8_t)) {
  pair<double, GameState> toReturn;

  random_device dev;
  mt19937 rng(dev());
  uniform_int_distribution<mt19937::result_type> dist2(1,2);

  if (gameState.gameStatus() != 0 || depth == 0) {
    toReturn.first = heuristicFunction(gameState, ai_no);
    toReturn.second = gameState;
    return toReturn;
  }
  vector<GameState> children = getGameStateChildren(gameState, playerToMove, dist2(rng));
  if (playerToMove == ai_no) {
    double bestValue = -DBL_MAX;
    uint8_t nextPlayer = (playerToMove == 1 ? 2 : 1);
    for (GameState child: children) {
      pair<double, GameState> score = minimaxWithAlphaBetaPruning(depth-1, child, nextPlayer, ai_no, alpha, beta, heuristicFunction);
      if (score.first >= bestValue) {
        bestValue = score.first;
        toReturn.first = bestValue;
        toReturn.second = child;
        if (alpha < bestValue) {
          alpha = bestValue;
        }
        if (bestValue > beta) { 
          break;
        }
      }
     
    }
    return toReturn;
  }
  else {
    double bestValue = DBL_MAX;
    uint8_t nextPlayer = (playerToMove == 1 ? 2 : 1);
    for (GameState child: children) {
      pair<double, GameState> score = minimaxWithAlphaBetaPruning(depth-1, child, nextPlayer, ai_no, alpha, beta, heuristicFunction);
      if (score.first <= bestValue) {
        bestValue = score.first;
        toReturn.first = bestValue;
        toReturn.second = child;
        if (beta > bestValue) {
          beta = bestValue;
        }
        if (alpha > bestValue) {
          // printf("PRUNED - %lf - %lf\n", alpha, beta);
          break;
        }
      }
    }
    // printf("RET FROM MIN: %lf\n", toReturn.first);
    return toReturn;
  }
}

// gameState - aktualny stan planszy, ai_no - numer jaki ma gracz AI
double linesCountHeuristic(GameState gameState, uint8_t ai_no) {
  int maxFourLengthCount = 0;
  int minFourLengthCount = 0;
  int maxThreeLengthCount = 0;
  int minThreeLengthCount = 0;
  int maxSetpieceOneObtainedCount = 0; //XX-X  lub X-XX
  int minSetpieceOneObtainedCount = 0;

  int opponent_no;

  int gameStatus = gameState.gameStatus();
  if (gameStatus == 3) return 0.0;

  (ai_no == 1 ? opponent_no = 2 : opponent_no = 1);

  if (gameStatus != 0) {
    int movesMade = 0;
    for (int i = 0; i < 25; i++) {
      if (gameState.places[i] != 0) movesMade++;
    }
    if (gameStatus == ai_no) return 6666666666.0 - movesMade;
    if (gameStatus == opponent_no) return -6666666666.0 + movesMade;
  }
    // sprawdzenie liczby setpiece ONE
    for (int i = 0; i < 5; i++) {
      //horizontal
      if (gameState.places[5*i + 0] == ai_no && gameState.places[5*i + 3] == ai_no && ((gameState.places[5*i + 1] == ai_no && gameState.places[5*i + 2] != opponent_no) || (gameState.places[5*i + 1] != opponent_no && gameState.places[5*i + 2] == ai_no))) {
        maxSetpieceOneObtainedCount++;
      }
      if (gameState.places[5*i + 1] == ai_no && gameState.places[5*i + 4] == ai_no && ((gameState.places[5*i + 2] == ai_no && gameState.places[5*i + 3] != opponent_no) || (gameState.places[5*i + 2] != opponent_no && gameState.places[5*i + 3] == ai_no))) {
        maxSetpieceOneObtainedCount++;
      }
      if (gameState.places[5*i + 0] == opponent_no && gameState.places[5*i + 3] == opponent_no && ((gameState.places[5*i + 1] == opponent_no && gameState.places[5*i + 2] != ai_no) || (gameState.places[5*i + 1] != ai_no && gameState.places[5*i + 2] == opponent_no))) {
        minSetpieceOneObtainedCount++;
      }
      if (gameState.places[5*i + 1] == opponent_no && gameState.places[5*i + 4] == opponent_no && ((gameState.places[5*i + 2] == opponent_no && gameState.places[5*i + 3] != ai_no) || (gameState.places[5*i + 2] != ai_no && gameState.places[5*i + 3] == opponent_no))) {
        minSetpieceOneObtainedCount++;
      }
      //vertical
      if (gameState.places[5*0 + i] == ai_no && gameState.places[5*3 + i] == ai_no && ((gameState.places[5*1 + i] == ai_no && gameState.places[5*2 + i] != opponent_no) || (gameState.places[5*1 + i] != opponent_no && gameState.places[5*2 + i] == ai_no))) {
        maxSetpieceOneObtainedCount++;
      }
      if (gameState.places[5*1 + i] == ai_no && gameState.places[5*4 + i] == ai_no && ((gameState.places[5*2 + i] == ai_no && gameState.places[5*3 + i] != opponent_no) || (gameState.places[5*2 + i] != opponent_no && gameState.places[5*3 + i] == ai_no))) {
        maxSetpieceOneObtainedCount++;
      }
      if (gameState.places[5*0 + i] == opponent_no && gameState.places[5*3 + i] == opponent_no && ((gameState.places[5*1 + i] == opponent_no && gameState.places[5*2 + i] != ai_no) || (gameState.places[5*1 + i] != ai_no && gameState.places[5*2 + i] == opponent_no))) {
        minSetpieceOneObtainedCount++;
      }
      if (gameState.places[5*1 + i] == opponent_no && gameState.places[5*4 + i] == opponent_no && ((gameState.places[5*2 + i] == opponent_no && gameState.places[5*3 + i] != ai_no) || (gameState.places[5*2 + i] != ai_no && gameState.places[5*3 + i] == opponent_no))) {
        minSetpieceOneObtainedCount++;
      }
    }

    //Diagonal One
    if (gameState.places[5*0 + 0] == ai_no) {
      if (gameState.places[5*3 + 3] == ai_no && ((gameState.places[5*1 + 1] == ai_no && gameState.places[5*2 + 2] != opponent_no) || (gameState.places[5*2 + 2] == ai_no && gameState.places[5*1 + 1] != opponent_no))) {
        maxSetpieceOneObtainedCount++;
      }
    } else if (gameState.places[5*4 + 4] == ai_no) {
      if (gameState.places[5*1 + 1] == ai_no && ((gameState.places[5*2 + 2] == ai_no && gameState.places[5*3 + 3] != opponent_no) || (gameState.places[5*3 + 3] == ai_no && gameState.places[5*2 + 2] != opponent_no))) {
        maxSetpieceOneObtainedCount++;
      }
    }
    if (gameState.places[5*0 + 0] == opponent_no) {
      if (gameState.places[5*3 + 3] == opponent_no && ((gameState.places[5*1 + 1] == opponent_no && gameState.places[5*2 + 2] != ai_no) || (gameState.places[5*2 + 2] == opponent_no && gameState.places[5*1 + 1] != ai_no))) {
        minSetpieceOneObtainedCount++;
      }
    } else if (gameState.places[5*4 + 4] == opponent_no) {
      if (gameState.places[5*1 + 1] == opponent_no && ((gameState.places[5*2 + 2] == opponent_no && gameState.places[5*3 + 3] != ai_no) || (gameState.places[5*3 + 3] == opponent_no && gameState.places[5*2 + 2] != ai_no))) {
        minSetpieceOneObtainedCount++;
      }
    }
    if (gameState.places[5*0 + 1] == ai_no && gameState.places[5*3 + 4] == ai_no && ((gameState.places[5*1 + 2] == ai_no && gameState.places[5*2 + 3] != opponent_no) || (gameState.places[5*2 + 3] == ai_no && gameState.places[5*1 + 2] != opponent_no))) {
      maxSetpieceOneObtainedCount++;
    }
    if (gameState.places[5*0 + 1] == opponent_no && gameState.places[5*3 + 4] == opponent_no && ((gameState.places[5*1 + 2] == opponent_no && gameState.places[5*2 + 3] != ai_no) || (gameState.places[5*2 + 3] == opponent_no && gameState.places[5*1 + 2] != ai_no))) {
      minSetpieceOneObtainedCount++;
    }
    if (gameState.places[5*1 + 0] == ai_no && gameState.places[5*4 + 3] == ai_no && ((gameState.places[5*2 + 1] == ai_no && gameState.places[5*3 + 2] != opponent_no) || (gameState.places[5*3 + 2] == ai_no && gameState.places[5*2 + 1] != opponent_no))) {
      maxSetpieceOneObtainedCount++;
    }
    if (gameState.places[5*1 + 0] == opponent_no && gameState.places[5*4 + 3] == opponent_no && ((gameState.places[5*2 + 1] == opponent_no && gameState.places[5*3 + 2] != ai_no) || (gameState.places[5*3 + 2] == opponent_no && gameState.places[5*2 + 1] != ai_no))) {
      minSetpieceOneObtainedCount++;
    }

    //Diagonal Two
    if (gameState.places[5*0 + 4] == ai_no) {
      if (gameState.places[5*3 + 1] == ai_no && ((gameState.places[5*1 + 3] == ai_no && gameState.places[5*2 + 2] != opponent_no) || (gameState.places[5*2 + 2] == ai_no && gameState.places[5*1 + 3] != opponent_no))) {
        maxSetpieceOneObtainedCount++;
      }
    } else if (gameState.places[5*4 + 0] == ai_no) {
      if (gameState.places[5*1 + 3] == ai_no && ((gameState.places[5*2 + 2] == ai_no && gameState.places[5*3 + 1] != opponent_no) || (gameState.places[5*3 + 1] == ai_no && gameState.places[5*2 + 2] != opponent_no))) {
        maxSetpieceOneObtainedCount++;
      }
    }
    if (gameState.places[5*0 + 4] == opponent_no) {
      if (gameState.places[5*3 + 1] == opponent_no && ((gameState.places[5*1 + 3] == opponent_no && gameState.places[5*2 + 2] != ai_no) || (gameState.places[5*2 + 2] == opponent_no && gameState.places[5*1 + 3] != ai_no))) {
        minSetpieceOneObtainedCount++;
      }
    } else if (gameState.places[5*4 + 0] == opponent_no) {
      if (gameState.places[5*1 + 3] == opponent_no && ((gameState.places[5*2 + 2] == opponent_no && gameState.places[5*3 + 1] != ai_no) || (gameState.places[5*3 + 1] == opponent_no && gameState.places[5*2 + 2] != ai_no))) {
        minSetpieceOneObtainedCount++;
      }
    }
    if (gameState.places[5*0 + 3] == ai_no && gameState.places[5*3 + 0] == ai_no && ((gameState.places[5*1 + 2] == ai_no && gameState.places[5*2 + 1] != opponent_no) || (gameState.places[5*2 + 1] == ai_no && gameState.places[5*1 + 2] != opponent_no))) {
      maxSetpieceOneObtainedCount++;
    }
    if (gameState.places[5*0 + 3] == opponent_no && gameState.places[5*3 + 0] == opponent_no && ((gameState.places[5*1 + 2] == opponent_no && gameState.places[5*2 + 1] != ai_no) || (gameState.places[5*2 + 1] == opponent_no && gameState.places[5*1 + 2] != ai_no))) {
      minSetpieceOneObtainedCount++;
    }
    if (gameState.places[5*1 + 4] == ai_no && gameState.places[5*4 + 1] == ai_no && ((gameState.places[5*2 + 3] == ai_no && gameState.places[5*3 + 2] != opponent_no) || (gameState.places[5*3 + 2] == ai_no && gameState.places[5*2 + 3] != opponent_no))) {
      maxSetpieceOneObtainedCount++;
    }
    if (gameState.places[5*1 + 4] == opponent_no && gameState.places[5*4 + 1] == opponent_no && ((gameState.places[5*2 + 3] == opponent_no && gameState.places[5*3 + 2] != ai_no) || (gameState.places[5*3 + 2] == opponent_no && gameState.places[5*2 + 3] != ai_no))) {
      minSetpieceOneObtainedCount++;
    }


  //sprawdzanie liczby możliwych linii długości 4
    for (int i = 0; i < 5; i++) {
      //Horizontal
      if (gameState.places[5*i + 0] != opponent_no && gameState.places[5*i + 1] != opponent_no && gameState.places[5*i + 2] != opponent_no && gameState.places[5*i + 3] != opponent_no) {
        maxFourLengthCount++;
      }
      if (gameState.places[5*i + 1] != opponent_no && gameState.places[5*i + 2] != opponent_no && gameState.places[5*i + 3] != opponent_no && gameState.places[5*i + 4] != opponent_no) {
        maxFourLengthCount++;
      }
      if (gameState.places[5*i + 0] != ai_no && gameState.places[5*i + 1] != ai_no && gameState.places[5*i + 2] != ai_no && gameState.places[5*i + 3] != ai_no) {
        minFourLengthCount++;
      }
      if (gameState.places[5*i + 1] != ai_no && gameState.places[5*i + 2] != ai_no && gameState.places[5*i + 3] != ai_no && gameState.places[5*i + 4] != ai_no) {
        minFourLengthCount++;
      }

      //Vertical
      if (gameState.places[5*0 + i] != opponent_no && gameState.places[5*1 + i] != opponent_no && gameState.places[5*2 + i] != opponent_no && gameState.places[5*3 + i] != opponent_no) {
        maxFourLengthCount++;
      }
      if (gameState.places[5*1 + i] != opponent_no && gameState.places[5*2 + i] != opponent_no && gameState.places[5*3 + i] != opponent_no && gameState.places[5*4 + i] != opponent_no) {
        maxFourLengthCount++;
      }
      if (gameState.places[5*0 + i] != ai_no && gameState.places[5*1 + i] != ai_no && gameState.places[5*2 + i] != ai_no && gameState.places[5*3 + i] != ai_no) {
        minFourLengthCount++;
      }
      if (gameState.places[5*1 + i] != ai_no && gameState.places[5*2 + i] != ai_no && gameState.places[5*3 + i] != ai_no && gameState.places[5*4 + i] != ai_no) {
        minFourLengthCount++;
      }
    }

    //Diagonal One
    if (gameState.places[5*1 + 1] != opponent_no && gameState.places[5*2 + 2] != opponent_no && gameState.places[5*3 + 3] != opponent_no) {
      if (gameState.places[5*0 + 0] != opponent_no) maxFourLengthCount++;
      if (gameState.places[5*4 + 4] != opponent_no) maxFourLengthCount++;
    }

    if (gameState.places[5*1 + 1] != ai_no && gameState.places[5*2 + 2] != ai_no && gameState.places[5*3 + 3] != ai_no) {
      if (gameState.places[5*0 + 0] != ai_no) minFourLengthCount++;
      if (gameState.places[5*4 + 4] != ai_no) minFourLengthCount++;
    }
    if (gameState.places[5*1 + 0] != opponent_no && gameState.places[5*2 + 1] != opponent_no && gameState.places[5*3 + 2] != opponent_no && gameState.places[5*4 + 3] != opponent_no) {
      maxFourLengthCount++;
    }
    if (gameState.places[5*0 + 1] != opponent_no && gameState.places[5*1 + 2] != opponent_no && gameState.places[5*2 + 3] != opponent_no && gameState.places[5*3 + 4] != opponent_no) {
      maxFourLengthCount++;
    }
    if (gameState.places[5*1 + 0] != ai_no && gameState.places[5*2 + 1] != ai_no && gameState.places[5*3 + 2] != ai_no && gameState.places[5*4 + 3] != ai_no) {
      minFourLengthCount++;
    }
    if (gameState.places[5*0 + 1] != ai_no && gameState.places[5*1 + 2] != ai_no && gameState.places[5*2 + 3] != ai_no && gameState.places[5*3 + 4] != ai_no) {
      minFourLengthCount++;
    }

    //Diagonal Two
    if (gameState.places[5*1 + 3] != opponent_no && gameState.places[5*2 + 2] != opponent_no && gameState.places[5*3 + 1] != opponent_no) {
      if (gameState.places[5*4 + 0] != opponent_no) maxFourLengthCount++;
      if (gameState.places[5*0 + 4] != opponent_no) maxFourLengthCount++;
    }
    if (gameState.places[5*1 + 3] != ai_no && gameState.places[5*2 + 2] != ai_no && gameState.places[5*3 + 1] != ai_no) {
      if (gameState.places[5*4 + 0] != ai_no) minFourLengthCount++;
      if (gameState.places[5*0 + 4] != ai_no) minFourLengthCount++;
    }
    if (gameState.places[5*0 + 3] != opponent_no && gameState.places[5*1 + 2] != opponent_no && gameState.places[5*2 + 1] != opponent_no && gameState.places[5*3 + 0] != opponent_no) {
      maxFourLengthCount++;
    }
    if (gameState.places[5*1 + 4] != opponent_no && gameState.places[5*2 + 3] != opponent_no && gameState.places[5*3 + 2] != opponent_no && gameState.places[5*4 + 1] != opponent_no) {
      maxFourLengthCount++;
    }
    if (gameState.places[5*0 + 3] != ai_no && gameState.places[5*1 + 2] != ai_no && gameState.places[5*2 + 1] != ai_no && gameState.places[5*3 + 0] != ai_no) {
      minFourLengthCount++;
    }
    if (gameState.places[5*1 + 4] != ai_no && gameState.places[5*2 + 3] != ai_no && gameState.places[5*3 + 2] != ai_no && gameState.places[5*4 + 1] != ai_no) {
      minFourLengthCount++;
    }

    //sprawdzanie liczby możliwych linii długości 3
    for (int i = 0; i < 5; i++) {
      //Horizontal
      if (gameState.places[5*i + 2] != opponent_no) {
        if (gameState.places[5*i + 0] != opponent_no && gameState.places[5*i + 1] != opponent_no) maxThreeLengthCount++;
        if (gameState.places[5*i + 1] != opponent_no && gameState.places[5*i + 3] != opponent_no) maxThreeLengthCount++;
        if (gameState.places[5*i + 3] != opponent_no && gameState.places[5*i + 4] != opponent_no) maxThreeLengthCount++;
      }
      if (gameState.places[5*i + 2] != ai_no) {
        if (gameState.places[5*i + 0] != ai_no && gameState.places[5*i + 1] != ai_no) minThreeLengthCount++;
        if (gameState.places[5*i + 1] != ai_no && gameState.places[5*i + 3] != ai_no) minThreeLengthCount++;
        if (gameState.places[5*i + 3] != ai_no && gameState.places[5*i + 4] != ai_no) minThreeLengthCount++;
      }

      //Vertical
      if (gameState.places[5*2 + i] != opponent_no) {
        if (gameState.places[5*0 + i] != opponent_no && gameState.places[5*1 + i] != opponent_no) maxThreeLengthCount++;
        if (gameState.places[5*1 + i] != opponent_no && gameState.places[5*3 + i] != opponent_no) maxThreeLengthCount++;
        if (gameState.places[5*3 + i] != opponent_no && gameState.places[5*4 + i] != opponent_no) maxThreeLengthCount++;
      }
      if (gameState.places[5*2 + i] != ai_no) {
        if (gameState.places[5*0 + i] != ai_no && gameState.places[5*1 + i] != ai_no) minThreeLengthCount++;
        if (gameState.places[5*1 + i] != ai_no && gameState.places[5*3 + i] != ai_no) minThreeLengthCount++;
        if (gameState.places[5*3 + i] != ai_no && gameState.places[5*4 + i] != ai_no) minThreeLengthCount++;
      }
    }

    //Diagonal One
    if (gameState.places[5*2 + 2] != opponent_no) {
      if (gameState.places[5*0 + 0] != opponent_no && gameState.places[5*1 + 1] != opponent_no) maxThreeLengthCount++;
      if (gameState.places[5*1 + 1] != opponent_no && gameState.places[5*3 + 3] != opponent_no) maxThreeLengthCount++;
      if (gameState.places[5*3 + 3] != opponent_no && gameState.places[5*4 + 4] != opponent_no) maxThreeLengthCount++;
    }
    if (gameState.places[5*2 + 2] != ai_no) {
      if (gameState.places[5*0 + 0] != ai_no && gameState.places[5*1 + 1] != ai_no) minThreeLengthCount++;
      if (gameState.places[5*1 + 1] != ai_no && gameState.places[5*3 + 3] != ai_no) minThreeLengthCount++;
      if (gameState.places[5*3 + 3] != ai_no && gameState.places[5*4 + 4] != ai_no) minThreeLengthCount++;
    }
    if (gameState.places[5*1 + 2] != opponent_no && gameState.places[5*2 + 3] != opponent_no) {
      if (gameState.places[5*0 + 1] != opponent_no) maxThreeLengthCount++;
      if (gameState.places[5*3 + 4] != opponent_no) maxThreeLengthCount++;
    }
    if (gameState.places[5*1 + 2] != ai_no && gameState.places[5*2 + 3] != ai_no) {
      if (gameState.places[5*0 + 1] != ai_no) minThreeLengthCount++;
      if (gameState.places[5*3 + 4] != ai_no) minThreeLengthCount++;
    }
    if (gameState.places[5*2 + 1] != opponent_no && gameState.places[5*3 + 2] != opponent_no) {
      if (gameState.places[5*1 + 0] != opponent_no) maxThreeLengthCount++;
      if (gameState.places[5*4 + 3] != opponent_no) maxThreeLengthCount++;
    }
    if (gameState.places[5*2 + 1] != ai_no && gameState.places[5*3 + 2] != ai_no) {
      if (gameState.places[5*1 + 0] != ai_no) minThreeLengthCount++;
      if (gameState.places[5*4 + 3] != ai_no) minThreeLengthCount++;
    }
    if (gameState.places[5*2 + 0] != opponent_no && gameState.places[5*3 + 1] != opponent_no && gameState.places[5*4 + 2] != opponent_no) {
      maxThreeLengthCount++;
    }
    if (gameState.places[5*2 + 0] != ai_no && gameState.places[5*3 + 1] != ai_no && gameState.places[5*4 + 2] != ai_no) {
      minThreeLengthCount++;
    }
    if (gameState.places[5*0 + 2] != opponent_no && gameState.places[5*1 + 3] != opponent_no && gameState.places[5*2 + 4] != opponent_no) {
      maxThreeLengthCount++;
    }
    if (gameState.places[5*0 + 2] != ai_no && gameState.places[5*1 + 3] != ai_no && gameState.places[5*2 + 4] != ai_no) {
      minThreeLengthCount++;
    }

    //Diagonal Two
    if (gameState.places[5*2 + 2] != opponent_no) {
      if (gameState.places[5*0 + 4] != opponent_no && gameState.places[5*1 + 3] != opponent_no) maxThreeLengthCount++;
      if (gameState.places[5*1 + 3] != opponent_no && gameState.places[5*3 + 1] != opponent_no) maxThreeLengthCount++;
      if (gameState.places[5*3 + 1] != opponent_no && gameState.places[5*4 + 0] != opponent_no) maxThreeLengthCount++;
    }
    if (gameState.places[5*2 + 2] != ai_no) {
      if (gameState.places[5*0 + 4] != ai_no && gameState.places[5*1 + 3] != ai_no) minThreeLengthCount++;
      if (gameState.places[5*1 + 3] != ai_no && gameState.places[5*3 + 1] != ai_no) minThreeLengthCount++;
      if (gameState.places[5*3 + 1] != ai_no && gameState.places[5*4 + 0] != ai_no) minThreeLengthCount++;
    }
    if (gameState.places[5*1 + 2] != opponent_no && gameState.places[5*2 + 1] != opponent_no) {
      if (gameState.places[5*0 + 3] != opponent_no) maxThreeLengthCount++;
      if (gameState.places[5*3 + 0] != opponent_no) maxThreeLengthCount++;
    }
    if (gameState.places[5*1 + 2] != ai_no && gameState.places[5*2 + 1] != ai_no) {
      if (gameState.places[5*0 + 3] != ai_no) minThreeLengthCount++;
      if (gameState.places[5*3 + 0] != ai_no) minThreeLengthCount++;
    }
    if (gameState.places[5*2 + 3] != opponent_no && gameState.places[5*3 + 2] != opponent_no) {
      if (gameState.places[5*1 + 4] != opponent_no) maxThreeLengthCount++;
      if (gameState.places[5*4 + 1] != opponent_no) maxThreeLengthCount++;
    }
    if (gameState.places[5*2 + 3] != ai_no && gameState.places[5*3 + 2] != ai_no) {
      if (gameState.places[5*1 + 4] != ai_no) minThreeLengthCount++;
      if (gameState.places[5*4 + 1] != ai_no) minThreeLengthCount++;
    }
    if (gameState.places[5*2 + 4] != opponent_no && gameState.places[5*3 + 3] != opponent_no && gameState.places[5*4 + 2] != opponent_no) {
      maxThreeLengthCount++;
    }
    if (gameState.places[5*2 + 4] != ai_no && gameState.places[5*3 + 3] != ai_no && gameState.places[5*4 + 2] != ai_no) {
      minThreeLengthCount++;
    }
    if (gameState.places[5*0 + 2] != opponent_no && gameState.places[5*1 + 1] != opponent_no && gameState.places[5*2 + 0] != opponent_no) {
      maxThreeLengthCount++;
    }
    if (gameState.places[5*0 + 2] != ai_no && gameState.places[5*1 + 1] != ai_no && gameState.places[5*2 + 0] != ai_no) {
      minThreeLengthCount++;
    }

  return maxFourLengthCount - minFourLengthCount + 0.75 * (minThreeLengthCount - maxThreeLengthCount) + 10 * (maxSetpieceOneObtainedCount - minSetpieceOneObtainedCount);
}



int main(int argc, char *argv[]) {




  int socket_desc;
  struct sockaddr_in server_addr;
  char server_message[16], client_message[16];
  int depth;
  GameState game; 

  bool end_game;
  int player, msg, move;

  if( argc!=5 ) {
    printf("Wrong number of arguments\n");
    return -1;
  }

  depth = atoi(argv[4]);

  // Create socket
  socket_desc = socket(AF_INET, SOCK_STREAM, 0);
  if( socket_desc<0 ) {
    printf("Unable to create socket\n");
    return -1;
  }
  printf("Socket created successfully\n");

  // Set port and IP the same as server-side
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(atoi(argv[2]));
  server_addr.sin_addr.s_addr = inet_addr(argv[1]);

  // Send connection request to server
  if( connect(socket_desc, (struct sockaddr*)&server_addr, sizeof(server_addr))<0 ) {
    printf("Unable to connect\n");
    return -1;
  }
  printf("Connected with server successfully\n");

  // Receive the server message
  memset(server_message, '\0', sizeof(server_message));
  if( recv(socket_desc, server_message, sizeof(server_message), 0)<0 ) {
    printf("Error while receiving server's message\n");
    return -1;
  }
  printf("Server message: %s\n",server_message);

  memset(client_message, '\0', sizeof(client_message));
  strcpy(client_message, argv[3]);
  // Send the message to server
  if( send(socket_desc, client_message, strlen(client_message), 0)<0 ) {
    printf("Unable to send message\n");
    return -1;
  }

  game = GameState();
  end_game = false;
  player = atoi(argv[3]);

  while( !end_game ) {
    memset(server_message, '\0', sizeof(server_message));
    if( recv(socket_desc, server_message, sizeof(server_message), 0)<0 ) {
      printf("Error while receiving server's message\n");
      return -1;
    }
    printf("Server message: %s\n", server_message);
    msg = atoi(server_message);
    move = msg%100;
    msg = msg/100;
    if( move!=0 ) {
      game.setMove(move, 3-player);
      game.printState();
    }
    if( (msg==0) || (msg==6) ) {
      pair<double, GameState> result = minimaxWithAlphaBetaPruning(depth, game, player, player, -DBL_MAX, DBL_MAX, &linesCountHeuristic);
      printf("AI move: \n");
      move = getMove(game, result.second);
      game.setMove(move, player);
      game.printState();
      printf("Value of move: %lf\n", result.first);
      memset(client_message, '\0', sizeof(client_message));
      sprintf(client_message, "%d", move);
      if( send(socket_desc, client_message, strlen(client_message), 0)<0 ) {
        printf("Unable to send message\n");
        return -1;
      }
      printf("AI-Client message: %s\n", client_message);
     }
     else {
       end_game = true;
       switch( msg ) {
         case 1 : printf("AI won.\n"); break;
         case 2 : printf("AI lost.\n"); break;
         case 3 : printf("Draw.\n"); break;
         case 4 : printf("AI won. Opponent error.\n"); break;
         case 5 : printf("AI lost. AI's error.\n"); break;
       }
     }
   }

  // Close socket
  close(socket_desc);

  return 0;
}