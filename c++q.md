# 10 Frequently Asked String Problems in MNC Interviews

## 1. Reverse a String

**Problem:**
Reverse a given string.

**Approach:**
Use two pointers to swap characters from start and end moving toward the center.

```cpp
#include <iostream>
#include <string>
using namespace std;

string reverseString(string s) {
    int left = 0, right = s.size() - 1;
    while (left < right) {
        cout << "Swapping " << s[left] << " and " << s[right] << endl;
        swap(s[left++], s[right--]);
    }
    return s;
}

int main() {
    string s = "hello";
    cout << "Reversed: " << reverseString(s) << endl;
    return 0;
}
```

## 2. Check for Anagram

**Problem:**
Check if two strings are anagrams of each other.

**Approach:**
Use a character count array of size 26.

```cpp
#include <iostream>
#include <string>
#include <vector>
using namespace std;

bool isAnagram(string s, string t) {
    if (s.size() != t.size()) return false;
    vector<int> count(26, 0);
    for (char c : s) count[c - 'a']++;
    for (char c : t) count[c - 'a']--;
    for (int i = 0; i < 26; ++i) {
        cout << "Character " << char('a' + i) << " count: " << count[i] << endl;
        if (count[i] != 0) return false;
    }
    return true;
}

int main() {
    cout << isAnagram("listen", "silent") << endl;
    return 0;
}
```

## 3. Longest Palindromic Substring

**Problem:**
Find the longest palindromic substring in a given string.

**Approach:**
Expand around each character center.

```cpp
#include <iostream>
#include <string>
using namespace std;

string expandFromCenter(string s, int left, int right) {
    while (left >= 0 && right < s.size() && s[left] == s[right]) {
        cout << "Palindrome: " << s.substr(left, right - left + 1) << endl;
        --left; ++right;
    }
    return s.substr(left + 1, right - left - 1);
}

string longestPalindrome(string s) {
    string longest = "";
    for (int i = 0; i < s.size(); ++i) {
        string odd = expandFromCenter(s, i, i);
        string even = expandFromCenter(s, i, i + 1);
        if (odd.size() > longest.size()) longest = odd;
        if (even.size() > longest.size()) longest = even;
    }
    return longest;
}

int main() {
    cout << longestPalindrome("babad") << endl;
    return 0;
}
```

## 4. Remove All Duplicates

**Problem:**
Remove all duplicate characters from a string.

**Approach:**
Use a boolean array to track seen characters.

```cpp
#include <iostream>
#include <string>
#include <unordered_set>
using namespace std;

string removeDuplicates(string s) {
    unordered_set<char> seen;
    string result = "";
    for (char c : s) {
        if (seen.find(c) == seen.end()) {
            seen.insert(c);
            result += c;
            cout << "Adding: " << c << endl;
        }
    }
    return result;
}

int main() {
    cout << removeDuplicates("programming") << endl;
    return 0;
}
```

## 5. String Compression

**Problem:**
Compress the string using the counts of repeated characters.

**Approach:**
Iterate through and count consecutive characters.

```cpp
#include <iostream>
#include <string>
using namespace std;

string compressString(string s) {
    string result = "";
    for (int i = 0; i < s.length(); ) {
        int count = 1;
        while (i + count < s.length() && s[i] == s[i + count]) count++;
        result += s[i] + to_string(count);
        cout << "Char: " << s[i] << " Count: " << count << endl;
        i += count;
    }
    return result.length() < s.length() ? result : s;
}

int main() {
    cout << compressString("aaabbcc") << endl;
    return 0;
}
```

## 6. Check Rotation

**Problem:**
Check if one string is rotation of another.

**Approach:**
Concatenate original string with itself and check substring.

```cpp
#include <iostream>
#include <string>
using namespace std;

bool isRotation(string s1, string s2) {
    if (s1.size() != s2.size()) return false;
    string temp = s1 + s1;
    cout << "Double string: " << temp << endl;
    return temp.find(s2) != string::npos;
}

int main() {
    cout << isRotation("waterbottle", "erbottlewat") << endl;
    return 0;
}
```

## 7. First Non-Repeating Character

**Problem:**
Find the first non-repeating character in a string.

**Approach:**
Use a frequency array and another pass to find the first with frequency 1.

```cpp
#include <iostream>
#include <string>
#include <vector>
using namespace std;

char firstUniqChar(string s) {
    vector<int> count(26, 0);
    for (char c : s) count[c - 'a']++;
    for (char c : s) {
        cout << "Checking: " << c << " Count: " << count[c - 'a'] << endl;
        if (count[c - 'a'] == 1) return c;
    }
    return '_';
}

int main() {
    cout << firstUniqChar("leetcode") << endl;
    return 0;
}
```

## 8. Valid Palindrome (ignoring non-alphanumeric)

**Problem:**
Check if a string is a palindrome ignoring cases and non-alphanumeric chars.

**Approach:**
Use two pointers with character checks.

```cpp
#include <iostream>
#include <string>
#include <cctype>
using namespace std;

bool isPalindrome(string s) {
    int left = 0, right = s.size() - 1;
    while (left < right) {
        while (left < right && !isalnum(s[left])) left++;
        while (left < right && !isalnum(s[right])) right--;
        if (tolower(s[left]) != tolower(s[right])) return false;
        cout << "Matching: " << s[left] << " and " << s[right] << endl;
        left++; right--;
    }
    return true;
}

int main() {
    cout << isPalindrome("A man, a plan, a canal: Panama") << endl;
    return 0;
}
```

## 9. Count and Say

**Problem:**
Generate the nth term of the count-and-say sequence.

**Approach:**
Iteratively build string by counting digit groups.

```cpp
#include <iostream>
#include <string>
using namespace std;

string countAndSay(int n) {
    string result = "1";
    for (int i = 1; i < n; ++i) {
        string current = "";
        for (int j = 0; j < result.size(); ) {
            int count = 1;
            while (j + count < result.size() && result[j] == result[j + count]) count++;
            current += to_string(count) + result[j];
            cout << "Appending: " << count << result[j] << endl;
            j += count;
        }
        result = current;
    }
    return result;
}

int main() {
    cout << countAndSay(5) << endl;
    return 0;
}
```

## 10. Check Subsequence

**Problem:**
Check if one string is a subsequence of another.

**Approach:**
Use two pointers to traverse both strings.

```cpp
#include <iostream>
#include <string>
using namespace std;

bool isSubsequence(string s, string t) {
    int i = 0, j = 0;
    while (i < s.size() && j < t.size()) {
        cout << "Comparing: " << s[i] << " with " << t[j] << endl;
        if (s[i] == t[j]) ++i;
        ++j;
    }
    return i == s.size();
}

int main() {
    cout << isSubsequence("abc", "ahbgdc") << endl;
    return 0;
}
```

---

These problems represent a strong foundation for string manipulation questions frequently seen in coding interviews.
