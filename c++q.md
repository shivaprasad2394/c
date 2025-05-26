---

These problems represent a strong foundation for string manipulation questions frequently seen in coding interviews.
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

These 10 array problems cover a wide range of logic and are commonly asked in technical interviews. Each includes debug output to help understand the execution step by step.

# 10 Frequently Asked Array Problems in MNC Interviews

## 1. Find the Maximum Subarray (Kadane’s Algorithm)

**Problem:**
Given an integer array, find the contiguous subarray (containing at least one number) which has the largest sum.

**Approach:**
Use Kadane’s algorithm to maintain current and global max sums.

```cpp
#include <iostream>
#include <vector>
using namespace std;

int maxSubArray(vector<int>& nums) {
    int maxSoFar = nums[0], maxEndingHere = nums[0];
    for (int i = 1; i < nums.size(); i++) {
        maxEndingHere = max(nums[i], maxEndingHere + nums[i]);
        maxSoFar = max(maxSoFar, maxEndingHere);
        cout << "Step " << i << ": maxEndingHere=" << maxEndingHere << ", maxSoFar=" << maxSoFar << endl;
    }
    return maxSoFar;
}

int main() {
    vector<int> nums = {-2,1,-3,4,-1,2,1,-5,4};
    cout << "Max Subarray Sum: " << maxSubArray(nums) << endl;
    return 0;
}
```

## 2. Two Sum

**Problem:**
Given an array and a target, return indices of two numbers such that they add up to the target.

**Approach:**
Use a hashmap to store seen numbers.

```cpp
#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

vector<int> twoSum(vector<int>& nums, int target) {
    unordered_map<int, int> map;
    for (int i = 0; i < nums.size(); i++) {
        int complement = target - nums[i];
        if (map.count(complement)) {
            cout << "Found: " << complement << " at index " << map[complement] << endl;
            return {map[complement], i};
        }
        map[nums[i]] = i;
        cout << "Storing: " << nums[i] << " at index " << i << endl;
    }
    return {};
}

int main() {
    vector<int> nums = {2, 7, 11, 15};
    vector<int> result = twoSum(nums, 9);
    cout << "Indices: " << result[0] << ", " << result[1] << endl;
    return 0;
}
```

## 3. Move Zeros

**Problem:**
Move all 0’s to the end of the array without changing the order of non-zero elements.

**Approach:**
Use two pointers to shift non-zero elements forward.

```cpp
#include <iostream>
#include <vector>
using namespace std;

void moveZeroes(vector<int>& nums) {
    int insertPos = 0;
    for (int i = 0; i < nums.size(); i++) {
        if (nums[i] != 0) {
            nums[insertPos++] = nums[i];
            cout << "Moved: " << nums[i] << " to position " << insertPos - 1 << endl;
        }
    }
    while (insertPos < nums.size()) {
        nums[insertPos++] = 0;
        cout << "Inserted 0 at position " << insertPos - 1 << endl;
    }
}

int main() {
    vector<int> nums = {0,1,0,3,12};
    moveZeroes(nums);
    for (int x : nums) cout << x << " ";
    cout << endl;
    return 0;
}
```

## 4. Merge Sorted Arrays

**Problem:**
Merge two sorted arrays into one sorted array.

**Approach:**
Use two pointers and merge like in merge sort.

```cpp
#include <iostream>
#include <vector>
using namespace std;

vector<int> mergeSortedArrays(vector<int>& a, vector<int>& b) {
    vector<int> result;
    int i = 0, j = 0;
    while (i < a.size() && j < b.size()) {
        if (a[i] < b[j]) result.push_back(a[i++]);
        else result.push_back(b[j++]);
        cout << "Merged: " << result.back() << endl;
    }
    while (i < a.size()) result.push_back(a[i++]);
    while (j < b.size()) result.push_back(b[j++]);
    return result;
}

int main() {
    vector<int> a = {1, 3, 5};
    vector<int> b = {2, 4, 6};
    vector<int> result = mergeSortedArrays(a, b);
    for (int x : result) cout << x << " ";
    return 0;
}
```

## 5. Find Missing Number

**Problem:**
Find the missing number in an array of 0 to n.

**Approach:**
Use sum formula: `n*(n+1)/2 - actual sum`

```cpp
#include <iostream>
#include <vector>
using namespace std;

int missingNumber(vector<int>& nums) {
    int n = nums.size();
    int expected = n * (n + 1) / 2;
    int actual = 0;
    for (int x : nums) actual += x;
    cout << "Expected Sum: " << expected << ", Actual Sum: " << actual << endl;
    return expected - actual;
}

int main() {
    vector<int> nums = {3,0,1};
    cout << "Missing Number: " << missingNumber(nums) << endl;
    return 0;
}
```

## 6. Contains Duplicate

**Problem:**
Check if any value appears more than once.

**Approach:**
Use an unordered_set to track elements.

```cpp
#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

bool containsDuplicate(vector<int>& nums) {
    unordered_set<int> seen;
    for (int x : nums) {
        if (seen.count(x)) {
            cout << "Duplicate found: " << x << endl;
            return true;
        }
        seen.insert(x);
        cout << "Inserting: " << x << endl;
    }
    return false;
}

int main() {
    vector<int> nums = {1,2,3,1};
    cout << containsDuplicate(nums) << endl;
    return 0;
}
```

## 7. Rotate Array

**Problem:**
Rotate the array to the right by k steps.

**Approach:**
Reverse the array in 3 parts: full, first k, rest.

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void rotate(vector<int>& nums, int k) {
    int n = nums.size();
    k = k % n;
    reverse(nums.begin(), nums.end());
    reverse(nums.begin(), nums.begin() + k);
    reverse(nums.begin() + k, nums.end());
    cout << "Rotated Array: ";
    for (int x : nums) cout << x << " ";
    cout << endl;
}

int main() {
    vector<int> nums = {1,2,3,4,5,6,7};
    rotate(nums, 3);
    return 0;
}
```

## 8. Intersection of Two Arrays

**Problem:**
Return the intersection of two arrays.

**Approach:**
Use sets to store and compare.

```cpp
#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
    unordered_set<int> set1(nums1.begin(), nums1.end());
    unordered_set<int> result;
    for (int num : nums2) {
        if (set1.count(num)) {
            result.insert(num);
            cout << "Found Intersection: " << num << endl;
        }
    }
    return vector<int>(result.begin(), result.end());
}

int main() {
    vector<int> a = {1,2,2,1};
    vector<int> b = {2,2};
    vector<int> result = intersection(a, b);
    for (int x : result) cout << x << " ";
    return 0;
}
```

## 9. Maximum Product Subarray

**Problem:**
Find the contiguous subarray with the largest product.

**Approach:**
Track max and min product at each step.

```cpp
#include <iostream>
#include <vector>
using namespace std;

int maxProduct(vector<int>& nums) {
    int maxProd = nums[0], minProd = nums[0], result = nums[0];
    for (int i = 1; i < nums.size(); i++) {
        if (nums[i] < 0) swap(maxProd, minProd);
        maxProd = max(nums[i], maxProd * nums[i]);
        minProd = min(nums[i], minProd * nums[i]);
        result = max(result, maxProd);
        cout << "Step " << i << ": maxProd=" << maxProd << ", minProd=" << minProd << ", result=" << result << endl;
    }
    return result;
}

int main() {
    vector<int> nums = {2,3,-2,4};
    cout << "Max Product: " << maxProduct(nums) << endl;
    return 0;
}
```

## 10. Find All Duplicates

**Problem:**
Find all elements that appear twice in an array (1 ≤ a[i] ≤ n).

**Approach:**
Use in-place negation as a marker.

```cpp
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

vector<int> findDuplicates(vector<int>& nums) {
    vector<int> result;
    for (int x : nums) {
        int index = abs(x) - 1;
        if (nums[index] < 0) {
            result.push_back(abs(x));
            cout << "Duplicate: " << abs(x) << endl;
        }
        nums[index] = -nums[index];
    }
    return result;
}

int main() {
    vector<int> nums = {4,3,2,7,8,2,3,1};
    vector<int> result = findDuplicates(nums);
    for (int x : result) cout << x << " ";
    return 0;
}
```


