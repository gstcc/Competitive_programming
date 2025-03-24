#include <iostream>
#include <list>
#include <unordered_map>

using namespace std;

int main() {
    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        int m, r;
        cin >> m >> r;

        list<int> stack;
        unordered_map<int, list<int>::iterator> book_to_iterator;

        for (int j = 1; j <= m; j++) {
            stack.push_back(j);
            book_to_iterator[j] = prev(stack.end());
        }

        while (r--) {
            int movie;
            cin >> movie;
            // Just need to lookup where the book is, distance is number of elements above
            int pos = distance(stack.begin(), book_to_iterator[movie]);
            cout << pos << " ";

            stack.erase(book_to_iterator[movie]);
            stack.push_front(movie);
            book_to_iterator[movie] = stack.begin();
        }
        cout << endl;
    }
}
