#include <bits/stdc++.h>
using namespace std;

int main() {
  int secret = 694;  // Hidden number
  int guess;
  string query;

  while (cin >> query >> guess) {
    if (query != "?") {
      cout << "Protocol error" << endl;
      return 1;
    }

    if (guess < secret)
      cout << ">" << endl;
    else if (guess > secret)
      cout << "<" << endl;
    else {
      cout << "=" << endl;
      return 0;  // Success
    }
    cout.flush();
  }

  return 1;  // Protocol error or failed to guess
}
