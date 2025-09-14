#include <algorithm>
#include <cassert>
#include <cmath>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

enum result_t {
  UNEXPECTED,  // correct output is incoherent
  EXCELLENT,   // better than optimal
  SUCCESS,     // exactly optimal
  PARTIAL,     // worse than optimal but coherent
  WRONG,       // correct output format, incorrect logic
  MALFORMED    // incorrect output format
};

const string MSG[] = {
  "Reference output is wrong",
  "Output is extraordinary",
  "translate:success",
  "translate:partial",
  "translate:wrong",
  "Output is malformed"
};

const float VAL[] = {-1, 1.1, 1.0, -1, 0.0, 0.0};

bool reading_corr = true;

void ex(float score, string message) {
  cout << score << endl;
  cerr << message << endl;
  exit(0);
}

void ex(float score) {
  assert(not reading_corr);
  ex(score, MSG[PARTIAL]);
}

void ex(result_t result, string extra = "") {
  assert(result != PARTIAL);
  assert(result != UNEXPECTED);
  if (reading_corr) {
    assert(result != EXCELLENT);
    assert(result != SUCCESS);
    result = UNEXPECTED;
  }
  ex(VAL[result], MSG[result] + (extra == "" ? "" : " (" + extra + ")"));
}

template <typename T> void read(ifstream &s, T &x) {
  if (!(s >> x))
    ex(MALFORMED);
}

template <typename T1, typename T2, typename... Ts>
void read(ifstream &s, T1 &x1, T2 &x2, Ts &...xs) {
  read(s, x1);
  read(s, x2, xs...);
}

template <typename T = int> T read(ifstream &s) {
  T x;
  read(s, x);
  return x;
}

inline void close(ifstream &s) {
  char c;
  while (s.get(c))
    if (!isspace(c))
      ex(MALFORMED);
}

inline void limit(int min, int val, int max) {
  if (val < min)
    ex(MALFORMED);
  if (val > max)
    ex(MALFORMED);
}

// copy-paste the C++ template variables here
int N;
vector<long long> A;
// ------------------------------------------

// Structure to hold output parsing result
struct OutputResult {
  long long claimed_xor;
  bool valid_multiset;
  long long actual_xor;
};

// read output, check and get numeric value for scoring
OutputResult read_output_detailed(ifstream &s) {
  OutputResult result;
  
  read(s, result.claimed_xor);
  
  int size;
  read(s, size);
  
  result.valid_multiset = true;
  result.actual_xor = 0;
  
  // Check size constraint
  if (size > 2 * N || size < 0) {
    result.valid_multiset = false;
  } else {
    vector<int> multiset(size);
    for (int i = 0; i < size; i++) {
      read(s, multiset[i]);
      if (multiset[i] < 1 || multiset[i] > N - 1) {
        result.valid_multiset = false;
      }
    }
    
    if (result.valid_multiset) {
      // Check sum constraint
      long long sum = 0;
      for (int x : multiset) {
        sum += x;
      }
      if (sum % N != 0) {
        result.valid_multiset = false;
      }
      
      // Calculate actual XOR value
      for (int x : multiset) {
        result.actual_xor ^= A[x - 1];  // Convert to 0-based indexing
      }
      
      // Check if claimed XOR matches actual XOR
      if (result.claimed_xor != result.actual_xor) {
        result.valid_multiset = false;
      }
    }
  }
  
  close(s);
  return result;
}

int main(int argc, char const *argv[]) {
  if (argc < 4) {
    cerr << "usage: ./checker <input> <correct> <user>" << endl;
    return 0;
  }
  ifstream in(argv[1]);
  ifstream corr(argv[2]);
  ifstream user(argv[3]);

  // copy-paste the C++ template logic here
  in >> N;
  A.resize(N - 1);
  for (int i = 0; i < N - 1; i++)
    in >> A[i];
  // --------------------------------------

  long long Scorr = read_output_detailed(corr).claimed_xor;
  reading_corr = false;
  
  // Use detailed parsing for user output
  OutputResult user_result = read_output_detailed(user);
  long long Suser = user_result.claimed_xor;

  // if (Suser > Scorr) {
  //   ex(EXCELLENT, string("Suser=") + to_string(Suser) + " Scorr=" + to_string(Scorr));
  // }
  
  if (Suser == Scorr) {
    if (user_result.valid_multiset) {
      ex(SUCCESS);  // 100% - optimal XOR with valid multiset
    } else {
      ex(0.6, "Partial credit: optimal XOR but invalid multiset");  // 60% - optimal XOR but invalid multiset
    }
  } else {
    ex(WRONG, "Incorrect XOR value: " + to_string(Suser) + " != " + to_string(Scorr));  // 0% - wrong XOR
  }
  return 0;
}