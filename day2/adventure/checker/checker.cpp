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
int n, m, q;
vector<tuple<int, int, int, int>> G;
vector<tuple<int, int, int, int>> queries;
vector<tuple<int, int>> e[505];
long long dis[505];
// ------------------------------------------

// Store operations and edge weights for validation
vector<int> operations;
vector<int> edge_weights;

// read output, check and get numeric value for scoring  
long long read_output(ifstream &s) {
  operations.clear();
  edge_weights.clear();
  
  vector<tuple<int, int, int, int>> current_G = G; // Copy initial edges
  
  // Read q operations (0/1 decisions)
  for (int i = 0; i < q; i++) {
    int op;
    read(s, op);
    limit(0, op, 1);
    operations.push_back(op);
    
    if (op == 1) {
      // Add the i-th query edge to the graph
      current_G.push_back(queries[i]);
    }
  }
  
  // Read edge weights for all edges in current_G
  for (auto [u, v, l, r] : current_G) {
    int weight;
    read(s, weight);
    limit(l, weight, r);
    edge_weights.push_back(weight);
  }
  
  close(s);
  return edge_weights.size(); // Return number of edges for scoring
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
  in >> n >> m >> q;
  for (int i = 0; i < m; i++) {
    int u, v, l, r;
    in >> u >> v >> l >> r;
    G.emplace_back(u, v, l, r);
  }
  
  // Store query edges separately
  for (int i = 0; i < q; i++) {
    int u, v, l, r;
    in >> u >> v >> l >> r;
    queries.emplace_back(u, v, l, r);
  }
  // --------------------------------------

  vector<int> corr_operations, user_operations;
  
  // Read correct output
  long long Scorr = read_output(corr);
  corr_operations = operations;
  vector<int> corr_weights = edge_weights;
  
  reading_corr = false;
  
  // Read user output  
  long long Suser = read_output(user);
  user_operations = operations;
  vector<int> user_weights = edge_weights;

  // Compare operations
  for (int i = 0; i < q; i++) {
    if (corr_operations[i] != user_operations[i]) {
      ex(WRONG, "Wrong answer. The value of op[" + to_string(i+1) + "] is wrong");
    }
  }
  
  // Build final graph and validate distances using user weights
  vector<tuple<int, int, int, int>> current_G = G;
  for (int i = 0; i < q; i++) {
    if (corr_operations[i] == 1) {
      current_G.push_back(queries[i]);
    }
  }
  
  // Clear edge lists and distances
  for (int i = 0; i < n; i++) {
    e[i].clear();
    dis[i] = 0;
  }
  
  // Build adjacency list with user weights
  int weight_idx = 0;
  for (auto [u, v, l, r] : current_G) {
    int weight = user_weights[weight_idx++];
    e[u].emplace_back(v, weight);
  }
  
  // Validate distance consistency
  for (int u = 0; u < n; u++) {
    for (auto [v, w] : e[u]) {
      if (dis[v] == 0) {
        dis[v] = dis[u] + w;
      } else if (dis[v] != dis[u] + w) {
        ex(WRONG, "Wrong answer. The distances to vertex " + to_string(v) + " are not same");
      }
    }
  }

  if (Suser > Scorr) {
    ex(EXCELLENT, string("Suser=") + to_string(Suser) + " Scorr=" + to_string(Scorr));
  }
  if (Suser == Scorr)
    ex(SUCCESS);

  // Simple scoring - if everything is valid, give success
  ex(SUCCESS);
  return 0;
}
