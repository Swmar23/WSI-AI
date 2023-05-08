#include <random>
#include <iostream>
#include <map>
#include <stdlib.h>  
#include <bits/stdc++.h>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>

using namespace std;

struct PuzzleState 
{
  uint8_t pieces[16];
  uint8_t combinedDistance;
  uint8_t heuristicDistance;
  uint8_t realDistance;

  PuzzleState(){};

  PuzzleState(uint8_t pieces[16]) {
    for (int i = 0; i < 16; i++) {
      this->pieces[i] = pieces[i];
    }
    this->realDistance = UINT8_MAX;
    this->heuristicDistance = UINT8_MAX;
    this->combinedDistance = UINT8_MAX;
  }

  PuzzleState(uint8_t pieces[16], uint8_t c, uint8_t h, uint8_t r) {
    for (int i = 0; i < 16; i++) {
      this->pieces[i] = pieces[i];
    }
    this->realDistance = r;
    this->heuristicDistance = h;
    this->combinedDistance = c;
  }

  bool operator==(const PuzzleState& rhs) const{
    for (int i = 0; i < 16; i++) {
      if (pieces[i] != rhs.pieces[i]) {
        return false;
      }
    }
    return true;
  }

  bool operator<(const PuzzleState& rhs) const { //operator używany do mapy
    for(int i = 0; i < 16; i++) {
      if (pieces[i] != rhs.pieces[i]) {
        return (pieces[i] < rhs.pieces[i]);
      }
    }
    return false;
  }

  bool operator>(const PuzzleState& rhs) const { //operator używany do priority queue
    if (combinedDistance > rhs.combinedDistance) {
      return true;
    } else if (combinedDistance == rhs.combinedDistance) {
      return (heuristicDistance > rhs.heuristicDistance);
    } else {
      return false;
    }
  }

  void displayPuzzle() {
    cout << "-------------\n";
    cout << "|";
    for(int i = 0; i < 4; i++) {
      printf("%02d|", pieces[i]);
    }
    cout << "\n-------------\n";
    cout << "|";
    for(int i = 4; i < 8; i++) {
      printf("%02d|", pieces[i]);
    }
    cout << "\n-------------\n";
    cout << "|";
    for(int i = 8; i < 12; i++) {
      printf("%02d|", pieces[i]);
    }
    cout << "\n-------------\n";
    cout << "|";
    for(int i = 12; i < 16; i++) {
      printf("%02d|", pieces[i]);
    }
    cout << "\n-------------\n";
  }

  bool isSolvable() {
    uint8_t toFind = 0;
    bool found = false;
    while (toFind < 16) {
      found = false;
      for (int i = 0; i < 16; i++) {
        if (pieces[i] == toFind) {
          toFind++;
          found = true;
          break;
        }
      }
      if (!found) return false;
    }

    int parity = 0;
    int currentRow = 0;
    int blankRow = 0; //row with the blank tile

    for (int i = 0; i < 16; i++) {
      if (i % 4 == 0) {
        currentRow++;
      }
      if (pieces[i] == 0) {
        blankRow = currentRow;
        continue;
      }
      for (int j = i+1; j < 16; j++) {
        if (pieces[i] > pieces[j] && pieces[j] != 0) parity++;
      }
    }

    if (blankRow % 2 == 0) return (parity % 2 == 0);
    return (parity % 2 == 1);
  }

  unsigned long long toID() {  // LSB -> MSB is the order of saving pieces (piece[0] is on LSB's)
    unsigned long long id = 0;
    for (int i = 0; i < 16; i++) {
      id += ( (unsigned long long) pieces[i] << (4*i));
      // printf("%llx\n", id);
    }
    return id;
  }
};

uint8_t solvedPieces[16] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0};

PuzzleState solvedPuzzle = PuzzleState(solvedPieces);

PuzzleState generateRandomPuzzleState() {

  uint8_t pieces[16];
  std::random_device dev;
  std::mt19937 rng(dev());
  vector<uint8_t> v;
  for (int i=0;i<16;i++)
    v.push_back((uint8_t)i);

  for (int i = 15; i >= 0; i--) {
    std::uniform_int_distribution<std::mt19937::result_type> dist(0,i);
    int index = dist(rng);
    uint8_t piece = v.at(index);
    v.erase(v.begin() + index);
    pieces[i] = piece;
  }

  PuzzleState puzzleState = PuzzleState(pieces);
  return puzzleState;
}

vector<PuzzleState> getPuzzleStateNeighbors(PuzzleState puzzleState) {
  vector<PuzzleState> neighbors;
  int indexOfZero;
  for (int i = 0; i < 16; i++) {
    if (puzzleState.pieces[i] == 0) {
      indexOfZero = i;
      break;
    }
  }

  if (indexOfZero - 4 >= 0) {
    uint8_t neighbor[16];
    for(int i = 0; i < 16; i++) {
      if (i == indexOfZero - 4) {
        neighbor[i] = 0;
      } else if (i == indexOfZero) {
        neighbor[i] = puzzleState.pieces[indexOfZero - 4];
      } else {
        neighbor[i] = puzzleState.pieces[i];
      }
    }
    neighbors.push_back(PuzzleState(neighbor));
  }

  if (indexOfZero - 1 >= 0 && ((indexOfZero - 1) / 4 == (indexOfZero / 4))) {
    uint8_t neighbor[16];
    for(int i = 0; i < 16; i++) {
      if (i == indexOfZero - 1) {
        neighbor[i] = 0;
      } else if (i == indexOfZero) {
        neighbor[i] = puzzleState.pieces[indexOfZero - 1];
      } else {
        neighbor[i] = puzzleState.pieces[i];
      }
    }
    neighbors.push_back(PuzzleState(neighbor));
  }

  if (indexOfZero + 1 < 16 && ((indexOfZero + 1) / 4 == (indexOfZero / 4))) {
    uint8_t neighbor[16];
    for(int i = 0; i < 16; i++) {
      if (i == indexOfZero + 1) {
        neighbor[i] = 0;
      } else if (i == indexOfZero) {
        neighbor[i] = puzzleState.pieces[indexOfZero + 1];
      } else {
        neighbor[i] = puzzleState.pieces[i];
      }
    }
    neighbors.push_back(PuzzleState(neighbor));
  }

  if (indexOfZero + 4 < 16) {
    uint8_t neighbor[16];
    for(int i = 0; i < 16; i++) {
      if (i == indexOfZero + 4) {
        neighbor[i] = 0;
      } else if (i == indexOfZero) {
        neighbor[i] = puzzleState.pieces[indexOfZero + 4];
      } else {
        neighbor[i] = puzzleState.pieces[i];
      }
    }
    neighbors.push_back(PuzzleState(neighbor));
  }

  return neighbors;
}

int manhattanHeuristic(PuzzleState puzzleState) {
  int totalDistance = 0;
  for (int i = 0; i < 16; i++) {
    if (puzzleState.pieces[i] != 0) {
      totalDistance += abs((puzzleState.pieces[i]-1) % 4 - i % 4);
      totalDistance += abs((puzzleState.pieces[i]-1) / 4 - i / 4);
    }
  }
  return totalDistance;
}

int manhattanPlusLinearConflictHeuristic(PuzzleState puzzleState) {
  int totalDistance = 0;
  for (int i = 0; i < 16; i++) {
    if (puzzleState.pieces[i] != 0) {
      totalDistance += abs((puzzleState.pieces[i]-1) % 4 - i % 4);
      totalDistance += abs((puzzleState.pieces[i]-1) / 4 - i / 4);
    }
  }
  int rowConflicts = 0;
  int columnConflicts = 0;

  for (int i = 0; i < 16; i++) {
    for (int j = i+1; j < 16; j++) {
      if (i % 4 == j % 4 && puzzleState.pieces[i] != 0 && puzzleState.pieces[j] != 0 && (puzzleState.pieces[i]-1) % 4 == i % 4 && (puzzleState.pieces[j]-1) % 4 == j % 4) {
        if (puzzleState.pieces[j] < puzzleState.pieces[i]) { rowConflicts += 2; continue; }
      }
    }
  }

  for (int i = 0; i < 16; i++) {
    for (int j = i+1; j < 16; j++) {
      if (i / 4 == j / 4 && puzzleState.pieces[i] != 0 && puzzleState.pieces[j] != 0 && (puzzleState.pieces[i]-1) / 4 == i / 4 && (puzzleState.pieces[j]-1) / 4 == j / 4) {
        if (puzzleState.pieces[j] < puzzleState.pieces[i]) { rowConflicts += 2; continue; }
      }
    }
  }
  totalDistance = totalDistance + rowConflicts + columnConflicts;
  return totalDistance;
}

int inversionDistanceHeuristic(PuzzleState puzzleState) {
  vector<uint8_t> horizontalSolved{1,5,9,13,2,6,10,14,3,7,11,15,4,8,12,0};

  int lowerBound = 0;
  int invCount = 0;
  for (int i = 0; i < 16; i++) {
    for (int j = i+1; j < 16; j++) {
      if (puzzleState.pieces[i] != 0 && puzzleState.pieces[j] != 0 && puzzleState.pieces[j] < puzzleState.pieces[i]) invCount++;
    }
  }
  lowerBound += invCount / 3 + invCount % 3;
  invCount = 0;

  int i = 0;
  while (i < 16) {
    int j = i + 4;
    if (j > 15 && j < 19) j = j%4 + 1;
    while (j < 16) {
      if (puzzleState.pieces[i] != 0 && puzzleState.pieces[j] != 0 && find(horizontalSolved.begin(), horizontalSolved.end(), puzzleState.pieces[j]) < find(horizontalSolved.begin(), horizontalSolved.end(), puzzleState.pieces[i])) invCount++;
      j += 4;
      if (j > 15 && j < 19) j = j%4 + 1;
    }
    i += 4;
    if (i > 15 && i < 19) i = i%4 + 1;
  }
  lowerBound += invCount / 3 + invCount % 3;
  return lowerBound;
}

int maxMDID(PuzzleState puzzleState) {
  int md = manhattanHeuristic(puzzleState);
  int id = inversionDistanceHeuristic(puzzleState);
  return max(md, id);
}

tuple<map<unsigned long long, unsigned long long>, int> AStar(PuzzleState start, PuzzleState goal, int (*heuristicFunction)(PuzzleState)) {
  map<unsigned long long, bool> statesAnalyzed;
  priority_queue<PuzzleState, vector<PuzzleState>, greater<PuzzleState>> pq;

  map<unsigned long long, unsigned long long> cameFrom;
  map<unsigned long long, uint8_t> bestDistance; // here we keep best real distances from start to specific stateID

  start.realDistance = 0;
  start.heuristicDistance = heuristicFunction(start);
  start.combinedDistance = start.realDistance + start.combinedDistance;

  bestDistance[start.toID()] = 0;

  pq.emplace(start);

  while (!pq.empty()) {
    PuzzleState currentState = pq.top();
    unsigned long long currentStateID = currentState.toID();
    pq.pop();
    if (currentState == goal) {
      return {cameFrom, statesAnalyzed.size()};
    }
    if (statesAnalyzed.find(currentStateID) == statesAnalyzed.end()) {
      vector<PuzzleState> neighbors = getPuzzleStateNeighbors(currentState);
      for (PuzzleState neighbor: neighbors) {
        unsigned long long neighborID = neighbor.toID();
        int currentNeighborDistance = bestDistance[currentState.toID()] + 1;
        if (bestDistance.find(neighborID) != bestDistance.end()) {
          if (bestDistance[neighborID] > currentNeighborDistance) {
            cameFrom[neighborID] = currentStateID;
            bestDistance[neighborID] = currentNeighborDistance;
            neighbor.combinedDistance = currentNeighborDistance + heuristicFunction(neighbor);
            neighbor.heuristicDistance = neighbor.combinedDistance - currentNeighborDistance;
            neighbor.realDistance = currentNeighborDistance;
            if (statesAnalyzed.find(neighborID) == statesAnalyzed.end()) {
              pq.emplace(neighbor);
            }
          }
        } else {
          cameFrom[neighborID] = currentStateID;
          bestDistance[neighborID] = currentNeighborDistance;
          neighbor.combinedDistance = currentNeighborDistance + heuristicFunction(neighbor);
          neighbor.heuristicDistance = neighbor.combinedDistance - currentNeighborDistance;
          neighbor.realDistance = currentNeighborDistance;
          pq.emplace(neighbor);
        }
      }
      statesAnalyzed[currentStateID] = true;
    }
  }
  cout <<"Problemy!!!\n";
  return {cameFrom, statesAnalyzed.size()};
}

// we assume that there is only one move differentiating startState and movedState NOT USED!
int getMovedPiece (PuzzleState startState, PuzzleState movedState) {
  for(int i = 0; i < 16; i++) {
    if(startState.pieces[i] == 0)
      return movedState.pieces[i];
  }
  return -1; //error 
}

// we assume that there is only one move differentiating startState and movedState
int getMovedPieceFromID (unsigned long long startStateID, unsigned long long movedStateID) {
  for(int i = 0; i < 16; i++) {
    if((startStateID >> (4*i) ) % 16 == 0)
      return (movedStateID >> (4*i) ) % 16;
  }
  return -1; //error 
}

vector<uint8_t> postProcessSolution (map<unsigned long long, unsigned long long> m, PuzzleState start, PuzzleState goal) {
  vector<uint8_t> moves;
  unsigned long long currentStateID = goal.toID();
  while (!(currentStateID == start.toID())) {
    unsigned long long nextStateID = m[currentStateID];
    moves.insert(moves.begin(), getMovedPieceFromID(nextStateID, currentStateID));
    currentStateID = nextStateID;
  }
  return moves;
}

int main(int argc, char *argv[]) {

  if (argc > 1 && strcmp(argv[1], "--generate") == 0) {
    for (int i = 0; i < 100; i++) {
      PuzzleState puzzleState = generateRandomPuzzleState();
      while (!puzzleState.isSolvable()) {
        puzzleState = generateRandomPuzzleState();
      }
      for (int j = 0; j < 16; j++) {
        cout << unsigned(puzzleState.pieces[j]) << ";";
      }
      cout << "\n";
    }
  }

  else if (argc > 1 && strcmp(argv[1], "--testMDLC") == 0) {
    tuple<map<unsigned long long, unsigned long long>, int> result;
    vector<uint8_t> moves;

    uint8_t pieces[16];

    string s;

    cin >> s;

    stringstream ss(s);

    int n = 0;
    int x;
    for (int i; ss >> i;) {
      pieces[n] = unsigned(i); 
      n++;
      if (ss.peek() == ';')
        ss.ignore();
    }
    PuzzleState puzzleState = PuzzleState(pieces);

    result = AStar(puzzleState, solvedPuzzle, &manhattanPlusLinearConflictHeuristic);
    moves = postProcessSolution(get<0>(result), puzzleState, solvedPuzzle);
    cout << moves.size() << ";" << get<1>(result) << "\n";

  }

  else if (argc > 1 && strcmp(argv[1], "--testMAXMDID") == 0) {
    tuple<map<unsigned long long, unsigned long long>, int> result;
    vector<uint8_t> moves;

    uint8_t pieces[16];

    string s;

    cin >> s;

    stringstream ss(s);

    int n = 0;
    int x;
    for (int i; ss >> i;) {
      pieces[n] = unsigned(i); 
      n++;
      if (ss.peek() == ';')
        ss.ignore();
    }
    PuzzleState puzzleState = PuzzleState(pieces);

    result = AStar(puzzleState, solvedPuzzle, &maxMDID);
    moves = postProcessSolution(get<0>(result), puzzleState, solvedPuzzle);
    cout << moves.size() << ";" << get<1>(result) << "\n";

  }

  else if (argc > 1 && strcmp(argv[1], "--testID") == 0) {
    tuple<map<unsigned long long, unsigned long long>, int> result;
    vector<uint8_t> moves;

    uint8_t pieces[16];

    string s;

    cin >> s;

    stringstream ss(s);

    int n = 0;
    int x;
    for (int i; ss >> i;) {
      pieces[n] = unsigned(i); 
      n++;
      if (ss.peek() == ';')
        ss.ignore();
    }
    PuzzleState puzzleState = PuzzleState(pieces);

    result = AStar(puzzleState, solvedPuzzle, &inversionDistanceHeuristic);
    moves = postProcessSolution(get<0>(result), puzzleState, solvedPuzzle);
    cout << moves.size() << ";" << get<1>(result) << "\n";

  }

  else if (argc > 1 && strcmp(argv[1], "--testMD") == 0) {
    tuple<map<unsigned long long, unsigned long long>, int> result;
    vector<uint8_t> moves;

    uint8_t pieces[16];

    string s;

    cin >> s;

    stringstream ss(s);

    int n = 0;
    int x;
    for (int i; ss >> i;) {
      pieces[n] = unsigned(i); 
      n++;
      if (ss.peek() == ';')
        ss.ignore();
    }
    PuzzleState puzzleState = PuzzleState(pieces);

    result = AStar(puzzleState, solvedPuzzle, &manhattanHeuristic);
    moves = postProcessSolution(get<0>(result), puzzleState, solvedPuzzle);
    cout << moves.size() << ";" << get<1>(result) << "\n";

  }


  else if (argc > 1 && strcmp(argv[1], "--test") == 0) {
    tuple<map<unsigned long long, unsigned long long>, int> result;
    vector<uint8_t> moves;

    PuzzleState puzzleState = generateRandomPuzzleState();
    while (!puzzleState.isSolvable()) {
      puzzleState = generateRandomPuzzleState();
    }
    cout << "--------------\n";

    result = AStar(puzzleState, solvedPuzzle, &manhattanPlusLinearConflictHeuristic);
    moves = postProcessSolution(get<0>(result), puzzleState, solvedPuzzle);
    cout << moves.size() << ";" << get<1>(result) << "\n";

    result = AStar(puzzleState, solvedPuzzle, &inversionDistanceHeuristic);
    moves = postProcessSolution(get<0>(result), puzzleState, solvedPuzzle);
    cout << moves.size() << ";" << get<1>(result) << "\n";

    result = AStar(puzzleState, solvedPuzzle, &maxMDID);
    moves = postProcessSolution(get<0>(result), puzzleState, solvedPuzzle);
    cout << moves.size() << ";" << get<1>(result) << "\n";

    cout << "--------------\n";

  }

  else {
    tuple<map<unsigned long long, unsigned long long>, int> result;
    vector<uint8_t> moves;
    PuzzleState puzzleState;

    if (argc > 2 && strcmp(argv[2], "--random") == 0) {
      puzzleState = generateRandomPuzzleState();
      while (!puzzleState.isSolvable()) {
        puzzleState = generateRandomPuzzleState();
      }
      cout << "Generated permutation: \n";
      puzzleState.displayPuzzle();
    } 
    else if (argc > 1 && argc < 4) {

      uint8_t pieces[16];

      string s;

      cin >> s;

      stringstream ss(s);

      int n = 0;
      int x;
      for (int i; ss >> i;) {
        pieces[n] = unsigned(i); 
        n++;
        if (ss.peek() == ';')
          ss.ignore();
      } 
      if (n < 16) {
        cout << "Wrong input!\n";
        return 0;
      }
      else {
        puzzleState = PuzzleState(pieces);
        if (puzzleState.isSolvable()) {
          cout << "Read instance (solvable): \n";
          puzzleState.displayPuzzle();
        } else {
          cout << "Read instance (not solvable!): \n";
          puzzleState.displayPuzzle();
          return 0;
        }
      }
    }

    if (argc > 1 && strcmp(argv[1], "MDLC") == 0) {
      result = AStar(puzzleState, solvedPuzzle, &manhattanPlusLinearConflictHeuristic);
      moves = postProcessSolution(get<0>(result), puzzleState, solvedPuzzle);
      cout << "Moves MD+SimplifiedLC (" << moves.size() << " total):\n";
      for (auto & move : moves) {
        cout << unsigned(move) << "->";
      }
      cout << "SOLVED!\n";
      cout << "Solution found with " << get<1>(result) << " explored game states.\n";
    }

    else if (argc > 1 && strcmp(argv[1], "MAXMDID") == 0) {
      result = AStar(puzzleState, solvedPuzzle, &maxMDID);
      moves = postProcessSolution(get<0>(result), puzzleState, solvedPuzzle);
      cout << "Moves max(MD,ID) (" << moves.size() << " total):\n";
      for (auto & move : moves) {
        cout << unsigned(move) << "->";
      }
      cout << "SOLVED!\n";
      cout << "Solution found with " << get<1>(result) << " explored game states.\n";
    }

    else if (argc > 1 && strcmp(argv[1], "MD") == 0) {
      result = AStar(puzzleState, solvedPuzzle, &manhattanHeuristic);
      moves = postProcessSolution(get<0>(result), puzzleState, solvedPuzzle);
      cout << "Moves MD (" << moves.size() << " total):\n";
      for (auto & move : moves) {
        cout << unsigned(move) << "->";
      }
      cout << "SOLVED!\n";
      cout << "Solution found with " << get<1>(result) << " explored game states.\n";
    }

    else if (argc > 1 && strcmp(argv[1], "ID") == 0) {
      result = AStar(puzzleState, solvedPuzzle, &inversionDistanceHeuristic);
      moves = postProcessSolution(get<0>(result), puzzleState, solvedPuzzle);
      cout << "Moves ID (" << moves.size() << " total):\n";
      for (auto & move : moves) {
        cout << unsigned(move) << "->";
      }
      cout << "SOLVED!\n";
      cout << "Solution found with " << get<1>(result) << " explored game states.\n";
    }

    else {
      cout << "Unknown command (take a look at README)\n";
    }
  }

  return 0;
}