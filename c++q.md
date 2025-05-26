## 10 Frequently Asked String Problems in MNC Interviews (HackerRank Style)

---

**1. Check if Two Strings are Anagrams**

**Problem Statement:**  
Given two strings, determine if they are anagrams (case-insensitive). An anagram is a rearrangement of the letters of one string to form another.

**Approach:**  
- Convert both strings to lowercase.
- Sort both strings.
- If sorted strings are equal, they are anagrams.

**C++ Solution:**
```cpp
#include 
#include 
using namespace std;

int main() {
    string s1, s2;
    cin >> s1 >> s2;
    cout 
#include 
#include 
using namespace std;

int main() {
    string a, b;
    cin >> a >> b;
    vector freq(26, 0);
    for (char c : a) freq[c - 'a']++;
    for (char c : b) freq[c - 'a']--;
    int deletions = 0;
    for (int i = 0; i 
---
**10. Count Number of Occurrences of Each Query String**

**Problem Statement:**
Given a list of input strings and a list of query strings, for each query, count how many times it occurs in the input.

**Approach:**  

Use a map to count frequencies, then answer queries.

**C++ Solution:**
```cpp
#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

int main() {
    int n, q;
    cin >> n;
    unordered_map<string, int> freq;
    string s;
    for (int i = 0; i < n; ++i) {
        cin >> s;
        freq[s]++;
        cout << "Input: " << s << ", Count: " << freq[s] << endl;
    }
    cin >> q;
    vector<string> queries(q);
    for (int i = 0; i < q; ++i) cin >> queries[i];
    for (auto &query : queries)
        cout << query << ": " << freq[query] << endl;
    return 0;
}
