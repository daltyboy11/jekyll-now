#include <assert.h>
#include "instant-runoff-votes.h"
#include <iostream>

// Test a very simple election with 1 winner
void test1() {
  std::vector<std::string> candidates = {"Donald Trump", "Hillary Clinton"};
  std::vector<std::vector<int>> ballots;
  ballots.push_back({1, 2});
  ballots.push_back({1, 2});

  std::vector<std::string> winner = election(candidates, ballots);
  assert(winner.size() == 1);
  assert(winner[0].compare("Donald Trump") == 0);
}

// Test a very simple election that ends in a tie
void test2() {
  std::vector<std::string> candidates = {"Donald Trump", "Hillary Clinton"};
  std::vector<std::vector<int>> ballots;
  ballots.push_back({1, 2});
  ballots.push_back({2, 1});

  std::vector<std::string> winners = election(candidates, ballots);
  assert(winners.size() == 2);
  assert(winners[0].compare("Donald Trump") == 0);
  assert(winners[1].compare("Hillary Clinton") == 0);
}

// Test a more elaborate election that declares a winner on the second round of voting
void test3() {
  std::vector<std::string> candidates = {"Justin Trudeau", "Andrew Scheer", "Jagmeet Singh", "Elizabeth May"};
  std::vector<std::vector<int>> ballots;
  ballots.push_back({1, 2, 3, 4});
  ballots.push_back({3, 2, 4, 1});
  ballots.push_back({1, 3, 2, 4});
  ballots.push_back({3, 2, 1, 4});
  ballots.push_back({2, 3, 4, 1});
  ballots.push_back({2, 1, 4, 3});
  ballots.push_back({3, 1, 2, 4});
  // In the first round of voting Trudeau, Scheer, and Singh receive two votes each. May receives 1 vote so she is eliminated.
  // In the second round of voting Trudeau and Scheer receive two votes each. Singh receives three votes (because the voter
  // who has May as their highest preference in the first round had Singh as their second highest preference) so we wins.
  
  std::vector<std::string> winner = election(candidates, ballots);
  assert(winner.size() == 1);
  assert(winner[0].compare("Jagmeet Singh") == 0);
}

// Test an election that eliminates candidates down to the last two and then declares a winner.
void test4() {
  std::vector<std::string> candidates = {"Justin Trudeau", "Andrew Scheer", "Jagmeet Singh", "Elizabeth May"};
  std::vector<std::vector<int>> ballots;
  ballots.push_back({1, 2, 3, 4});
  ballots.push_back({2, 3, 4, 1});
  ballots.push_back({2, 4, 1, 3});
  ballots.push_back({2, 1, 4, 3});
  ballots.push_back({2, 1, 3, 4});
  ballots.push_back({1, 2, 3, 4});
  ballots.push_back({4, 2, 1, 3});
  ballots.push_back({4, 3, 2, 1});
  ballots.push_back({1, 3, 4, 2});
  ballots.push_back({4, 1, 3, 2});
  ballots.push_back({3, 2, 1, 4});
  // Round 1: Trudeau, Scheer, and Singh receive three votes each. May receives two votes and is eliminated.
  // Round 2: Trudeau and Singh receive four votes each. Scheer receives three votes and is eliminated.
  // Round 3: Trudeau receives six votes. Singh receives four votes and is eliminated.

  std::vector<std::string> winner = election(candidates, ballots);
  assert(winner.size() == 1);
  assert(winner[0].compare("Justin Trudeau") == 0);
}

int main(int argc, const char* arg[]) {
  test1();
  test2();
  test3();
  std::cout << "here" << std::endl;
  test4();
  std::cout << "there" << std::endl;
  return 1;
}
