/*******************************************************************************
 * Name        : waterjugpuzzle.cpp
 * Author      : Alex Johnson and Andrew Johnson
 * Date        : 10/15/19
 * Description : Solves the great water jug puzzle.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <queue>
#include <string>
#include <stdexcept>

using namespace std;

struct State {
    int a, b, c;
    State *parent;

    vector<string> directions;
    
    State(int  a_, int  b_, int  c_, State *p_) : a(a_), b(b_), c(c_), parent(p_) { }

    int getA() const{
        return a;
    }
    int getB() const{
        return b;
    }
    int getC() const{
        return c;
    }
    
    string to_string() {
        ostringstream oss;
        oss << "(" << a << ", " << b << ", " << c << ")";
        return oss.str();
    }

    State* getParent(){
        return parent;
    }

    bool operator == (State &jug){
        return(a == jug.getA() and  b == jug.getB() and c == jug.getC());
    }

    //Ensures proper formating of outputs
    void fixOutput(State &jug){
        int diff_a = a - jug.getA();
        int diff_b = b - jug.getB();
        int diff_c = c - jug.getC();
        int tot = max(diff_a, diff_b);
        tot = max(tot, diff_c);

        string first;
        string second;

        if (diff_a < 0) {
            first = 'A';
        }
        if (diff_b < 0) {
            first = 'B';
        }
        if (diff_c < 0) {
            first = 'C';
        }
        if (diff_a > 0) {
            second = 'A';
        }
        if (diff_b > 0) {
            second = 'B';
        }
        if (diff_c > 0) {
            second = 'C';
        }

        if (tot == 1) {
            cout << "Pour " << tot <<  " gallon from " << second << " to " << first << ". ";
            cout << "(" << jug.getA() << ", " << jug.getB() << ", " << jug.getC()  << ")" << endl;
        }
        else {
            cout << "Pour " << tot << " gallons from " << second << " to " << first << ". ";
            cout << "(" << jug.getA() << ", " << jug.getB() << ", " << jug.getC()  << ")" << endl;
        }

    }

    void outputBest(vector<State> &path){
        for (unsigned int i = 0; i < path.size(); i++)
        {
            cout << "(" << path[i].getA() << ", " << path[i].getB() << ", " << path[i].getC()  << ")" << endl;
            cout << endl;
        }
    }
};

vector<State> findBest(State &child, State &initial){
  vector<State> bestPath;
  State* currententState = &child;
  while (!(*currententState == initial))
  {
    bestPath.push_back(*currententState);
        if (currententState->getParent() == NULL)
        {
          break;
        }
        currententState = currententState->getParent();
  }
  bestPath.push_back(initial);
  reverse(bestPath.begin(), bestPath.end());
  return bestPath;
}

//Print the best path.
void bestPath(vector<State> vect){
  int length = vect.size();

  for(int i = 0; i < length - 1; i++)
  {
    vect.at(i).fixOutput(vect.at(i+1));
  }
}

//Breadth first search algorithm.
void bfs(State* current, State &capacity, queue<State> &q, bool** visited){

  int a = current->getA();
  int b = current->getB();
  int c = current->getC();
  // C -> A
  if (c != 0 && a < capacity.getA()) {
    int amnt = min(c, (capacity.getA() - a));
    if (!visited[a + amnt][b]) {
      q.push(State(a + amnt, b, c - amnt, current));
      visited[a + amnt][b] = true;
    }
  }
  // B -> A
  if (b != 0 && a != capacity.getA()) {
    int amnt = min(b, (capacity.getA() - a));
    if (!visited[a + amnt][b - amnt]) {
      q.push(State(a + amnt, b - amnt, c, current));
      visited[a + amnt][b - amnt] = true;
    }
  }
  // C -> B
  if (c != 0 && b != capacity.getB()) {
    int amnt = min(c, (capacity.getB() - b));
    if (!visited[a][b + amnt]) {
      q.push(State(a, b + amnt, c - amnt, current));
      visited[a][b + amnt] = true;
    }
  }
  // A -> B
  if (a != 0 && b != capacity.getB()) {
    int amnt = min(a, (capacity.getB() - b));
    if (!visited[a - amnt][b + amnt]) {
      q.push(State(a - amnt, b + amnt, c, current));
      visited[a - amnt][b + amnt] = true;
    }
  }
  // B -> C
  if (b != 0 && c != capacity.getC()) {
    int amnt = min(b, (capacity.getC() - c));
    if (!visited[a][b - amnt]) {
      q.push(State(a, b - amnt, c + amnt, current));
      visited[a][b - amnt] = true;
    }
  }
  // A -> C
  if (a != 0 && c != capacity.getC()) {
    int amnt = min(a, (capacity.getC() - c));
    if (!visited[a - amnt][b]) {
      q.push(State(a - amnt, b, c + amnt, current));
      visited[a - amnt][b] = true;
    }
  }
}

int main(int argc, char * const argv[]) {
    istringstream iss;
    int ca, cb, cc, ga, gb, gc;

    //Error checking.
    if (argc != 7) {
      cerr << "Usage: " << argv[0] << " <cap A> <cap B> <cap C> <goal A> <goal B> <goal C>" << endl;
      return 1;
    }

    iss.str(argv[1]);
    if (!(iss >> ca) || ca < 0) {
      cerr << "Error: Invalid capacity '" << argv[1] << "' for jug A." << endl;
      return 1;
    }
    iss.clear();

    iss.str(argv[2]);
    if (!(iss >> cb) || cb < 0) {
      cerr << "Error: Invalid capacity '" << argv[2] << "' for jug B." << endl;
      return 1;
    }
    iss.clear();

    iss.str(argv[3]);
    if (!(iss >> cc) || cc <= 0) {
      cerr << "Error: Invalid capacity '" << argv[3] << "' for jug C."<< endl;
      return 1;
    }
    iss.clear();

    iss.str(argv[4]);
    if (!(iss >> ga) || ga < 0) {
      cerr << "Error: Invalid goal '" << argv[4] << "' for jug A."<< endl;
      return 1;
    }
    iss.clear();

    iss.str(argv[5]);
    if (!(iss >> gb) || gb < 0) {
      cerr << "Error: Invalid goal '" << argv[5] << "' for jug B." << endl;
      return 1;
    }
    iss.clear();

    iss.str(argv[6]);
    if (!(iss >> gc) || gc < 0) {
      cerr << "Error: Invalid goal '" << argv[6] << "' for jug C."<< endl;
      return 1;
    }
    iss.clear();

    if (ga > ca) {
      cerr << "Error: Goal cannot exceed capacity of jug A." << endl;
      return 1;
    }

    if (gb > cb) {
      cerr << "Error: Goal cannot exceed capacity of jug B." << endl;
      return 1;
    }

    if (gc > cc) {
      cerr << "Error: Goal cannot exceed capacity of jug C." << endl;
      return 1;
    }

    if (cc != ga + gb + gc) {
      cerr << "Error: Total gallons in goal state must be equal to the capacity of jug C." << endl;
      return 1;
    }

    //If no errors, the rest of the process executes.
    State goalState(ga, gb, gc, NULL);
    State capacityState(ca, cb, cc, NULL);
    State initialState(0, 0, capacityState.getC(), NULL);
    queue<State> q;

    bool foundGoal = false;
    bool** seen = new bool*[capacityState.getA() + 1];
    for (int i = 0; i <= capacityState.getA(); i++) {
      seen[i] = new bool[capacityState.getB() + 1];
    }
    fill(&seen[0][0], &seen[capacityState.getA()][0], false);
    seen[0][0] = true;
    q.push(initialState);

    while (!q.empty()) {
      if (q.front() == goalState) {
        foundGoal = true;
        break;
      }
      bfs(&q.front(), capacityState, q, seen);
      q.pop();
    }

    if (foundGoal == false) {
      cout << "No solution." << endl;
    }

    if (foundGoal == true) {
      cout << "Initial state. " << "(" << initialState.getA() << ", " << initialState.getB() << ", " << initialState.getC()  << ")" << endl;
      vector<State> choose = findBest(q.front(), initialState);
      bestPath(choose);
    }

    delete[] seen;
    return 0;
}
