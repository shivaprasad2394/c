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
Certainly! Below are **highlighted step-by-step solutions** for each of the 10 graph problems in your document. This will help clarify the logic behind each approach.

---

## ✅ 1. Detect Cycle in Undirected Graph

**Steps:**

1. Perform DFS from every unvisited node.
2. In DFS, for each adjacent node:

   * If it’s not visited, recursively visit it.
   * If it's visited and **not the parent**, a cycle is found.

---

## ✅ 2. Detect Cycle in Directed Graph

**Steps:**

1. Use DFS with a **recursion stack** to track current path.
2. For each adjacent node:

   * If not visited, recurse.
   * If visited and in recursion stack → **cycle exists**.

---

## ✅ 3. Topological Sort (Kahn's Algorithm)

**Steps:**

1. Compute **in-degree** of each node.
2. Add nodes with 0 in-degree to queue.
3. While queue not empty:

   * Remove node, add to result.
   * Decrease in-degree of its neighbors.
   * If neighbor’s in-degree becomes 0, enqueue it.

---

## ✅ 4. Number of Islands (DFS)

**Steps:**

1. Traverse each cell in the grid.
2. On finding `'1'` (land), start DFS.
3. In DFS:

   * Mark current as `'0'` (visited).
   * Recursively visit all 4 neighbors (up/down/left/right).

---

## ✅ 5. Clone Graph

**Steps:**

1. Use DFS and a map to track cloned nodes.
2. For each node:

   * If already cloned → return clone.
   * Else, create new node and recursively clone neighbors.

---

## ✅ 6. Bipartite Graph Check

**Steps:**

1. Initialize all node colors as -1.
2. For every uncolored node:

   * Use BFS to color the graph with 2 colors.
   * If adjacent nodes have **same color**, it’s not bipartite.

---

## ✅ 7. Dijkstra’s Algorithm

**Steps:**

1. Initialize distances to all nodes as ∞, except `src = 0`.
2. Use min-heap (priority queue) for efficient min selection.
3. Pop node with smallest distance.
4. For each neighbor:

   * If shorter path is found → update and push to queue.

---

## ✅ 8. Bellman-Ford Algorithm

**Steps:**

1. Initialize distances to ∞, source = 0.
2. Relax all edges **V-1 times**:

   * For each edge, if shorter path is found → update.
3. (Optional) Run one more time to check for **negative cycle**.

---

## ✅ 9. Floyd-Warshall Algorithm

**Steps:**

1. Initialize `dist[i][j]` matrix with direct edge weights.
2. For each node `k` as intermediate:

   * Update all `dist[i][j]` using `dist[i][k] + dist[k][j]` if shorter.

---

## ✅ 10. Kruskal’s Algorithm (MST)

**Steps:**

1. Sort all edges by weight.
2. Use Union-Find to manage connected components.
3. For each edge:

   * If nodes are in different sets → add edge to MST.
   * Union the sets.
4. Stop after adding `V - 1` edges (for connected graph).

---

# 10 Frequently Asked Graph Problems in MNC Interviews

## 1. Detect Cycle in Undirected Graph

**Problem:**
Given an undirected graph, check if it contains a cycle.

**Approach:**
Use DFS. If a visited node is encountered that is not the parent of the current node, a cycle exists.

```cpp
#include <iostream>
#include <vector>
using namespace std;

bool dfs(int v, int parent, vector<bool>& visited, vector<vector<int>>& adj) {
    visited[v] = true;
    cout << "Visiting node: " << v << endl;
    for (int u : adj[v]) {
        if (!visited[u]) {
            if (dfs(u, v, visited, adj)) return true;
        } else if (u != parent) {
            cout << "Cycle detected via node: " << u << endl;
            return true;
        }
    }
    return false;
}

bool hasCycle(int n, vector<vector<int>>& adj) {
    vector<bool> visited(n, false);
    for (int i = 0; i < n; ++i) {
        if (!visited[i] && dfs(i, -1, visited, adj)) return true;
    }
    return false;
}

int main() {
    int n = 5;
    vector<vector<int>> adj(n);
    adj[0] = {1};
    adj[1] = {0, 2};
    adj[2] = {1, 3};
    adj[3] = {2, 4};
    adj[4] = {3};
    cout << "Cycle exists: " << hasCycle(n, adj) << endl;
    return 0;
}
```

---

## 2. Detect Cycle in Directed Graph

**Problem:**
Check if a directed graph has a cycle.

**Approach:**
Use DFS with recursion stack to detect back edges.

```cpp
#include <iostream>
#include <vector>
using namespace std;

bool dfs(int v, vector<bool>& visited, vector<bool>& recStack, vector<vector<int>>& adj) {
    visited[v] = true;
    recStack[v] = true;
    cout << "DFS at node: " << v << endl;
    for (int u : adj[v]) {
        if (!visited[u] && dfs(u, visited, recStack, adj)) return true;
        if (recStack[u]) {
            cout << "Cycle detected at node: " << u << endl;
            return true;
        }
    }
    recStack[v] = false;
    return false;
}

bool hasCycleDirected(int n, vector<vector<int>>& adj) {
    vector<bool> visited(n, false), recStack(n, false);
    for (int i = 0; i < n; i++) {
        if (!visited[i] && dfs(i, visited, recStack, adj)) return true;
    }
    return false;
}

int main() {
    int n = 4;
    vector<vector<int>> adj = {{1}, {2}, {3}, {1}};
    cout << "Cycle exists: " << hasCycleDirected(n, adj) << endl;
    return 0;
}
```

---

## 3. Topological Sort

**Problem:**
Return a topological order of a DAG.

**Approach:**
Use DFS or Kahn’s algorithm (BFS-based).

```cpp
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

vector<int> topoSort(int n, vector<vector<int>>& adj) {
    vector<int> indegree(n, 0), result;
    for (auto& edges : adj)
        for (int v : edges) indegree[v]++;

    queue<int> q;
    for (int i = 0; i < n; i++) if (indegree[i] == 0) q.push(i);

    while (!q.empty()) {
        int u = q.front(); q.pop();
        result.push_back(u);
        cout << "Visiting: " << u << endl;
        for (int v : adj[u]) {
            if (--indegree[v] == 0) q.push(v);
        }
    }
    return result;
}

int main() {
    vector<vector<int>> adj = {{1, 2}, {3}, {3}, {}};
    vector<int> order = topoSort(4, adj);
    for (int x : order) cout << x << " ";
    return 0;
}
```

---

## 4. Number of Islands (DFS)

**Problem:**
Count islands in a 2D grid of '1' (land) and '0' (water).

**Approach:**
Use DFS to visit and mark each component.

```cpp
#include <iostream>
#include <vector>
using namespace std;

void dfs(vector<vector<char>>& grid, int i, int j) {
    if (i < 0 || i >= grid.size() || j < 0 || j >= grid[0].size() || grid[i][j] == '0') return;
    grid[i][j] = '0';
    cout << "Visiting island cell: (" << i << ", " << j << ")" << endl;
    dfs(grid, i+1, j); dfs(grid, i-1, j); dfs(grid, i, j+1); dfs(grid, i, j-1);
}

int numIslands(vector<vector<char>>& grid) {
    int count = 0;
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[0].size(); j++) {
            if (grid[i][j] == '1') {
                dfs(grid, i, j);
                count++;
                cout << "Island Count: " << count << endl;
            }
        }
    }
    return count;
}

int main() {
    vector<vector<char>> grid = {{'1','1','0','0','0'},
                                 {'1','1','0','0','0'},
                                 {'0','0','1','0','0'},
                                 {'0','0','0','1','1'}};
    cout << "Total Islands: " << numIslands(grid) << endl;
    return 0;
}
```

---

## 5. Clone Graph

**Problem:**
Clone an undirected graph.

**Approach:**
Use DFS with a hashmap to track visited nodes.

```cpp
#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

class Node {
public:
    int val;
    vector<Node*> neighbors;
    Node(int _val) { val = _val; }
};

Node* clone(Node* node, unordered_map<Node*, Node*>& map) {
    if (!node) return nullptr;
    if (map.count(node)) return map[node];

    Node* copy = new Node(node->val);
    map[node] = copy;
    cout << "Cloning node: " << node->val << endl;
    for (Node* n : node->neighbors) copy->neighbors.push_back(clone(n, map));
    return copy;
}

Node* cloneGraph(Node* node) {
    unordered_map<Node*, Node*> map;
    return clone(node, map);
}
```

---

## 6. Bipartite Graph Check

**Problem:**
Check whether a given graph is bipartite.

**Approach:**
Use BFS and color nodes with two colors. If any adjacent nodes have the same color, it's not bipartite.

```cpp
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

bool isBipartite(vector<vector<int>>& graph) {
    int n = graph.size();
    vector<int> color(n, -1);
    for (int i = 0; i < n; i++) {
        if (color[i] == -1) {
            queue<int> q;
            q.push(i);
            color[i] = 0;
            while (!q.empty()) {
                int u = q.front(); q.pop();
                cout << "Coloring node " << u << " with color " << color[u] << endl;
                for (int v : graph[u]) {
                    if (color[v] == -1) {
                        color[v] = 1 - color[u];
                        q.push(v);
                    } else if (color[v] == color[u]) {
                        cout << "Conflict at node: " << v << endl;
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

int main() {
    vector<vector<int>> graph = {{1, 3}, {0, 2}, {1, 3}, {0, 2}};
    cout << "Is Bipartite: " << isBipartite(graph) << endl;
    return 0;
}
```

---

---

### **1. Dijkstra’s Shortest Path Algorithm**

**Algorithm Explanation:**

Dijkstra’s algorithm finds the shortest path from a **single source** to all other vertices in a **graph with non-negative edge weights**. It uses a **priority queue (min-heap)** to always expand the currently known shortest node.

**Steps:**

1. Initialize all distances as infinity, except the source (0).
2. Use a min-heap to greedily select the nearest unvisited node.
3. For each neighbor, update the distance if a shorter path is found.
4. Repeat until all nodes are visited.

---

**MNC Question:**
**Problem:** You are given a city map represented as a graph. Find the shortest path from a starting node to all other cities.

```cpp
#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

typedef pair<int, int> pii;

vector<int> dijkstra(int V, vector<vector<pii>>& adj, int src) {
    vector<int> dist(V, INT_MAX);
    priority_queue<pii, vector<pii>, greater<pii>> pq;

    dist[src] = 0;
    pq.push({0, src});

    while (!pq.empty()) {
        int u = pq.top().second;
        int d = pq.top().first;
        pq.pop();
        cout << "Visiting node " << u << " with distance " << d << endl;

        for (auto [v, weight] : adj[u]) {
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
                cout << "Updated distance of " << v << " to " << dist[v] << endl;
            }
        }
    }
    return dist;
}
```

---

### **2. Bellman-Ford Algorithm**

**Algorithm Explanation:**

Bellman-Ford also finds the shortest path from a **single source** but supports **negative edge weights**.

**Steps:**

1. Initialize all distances to infinity, except source.
2. Relax all edges `V-1` times.
3. If a shorter path is still found, a negative-weight cycle exists.

---

**MNC Question:**
**Problem:** You are given a network with some negative tolls. Can you find the shortest distances from city `0`?

```cpp
#include <iostream>
#include <vector>
using namespace std;

struct Edge {
    int u, v, w;
};

vector<int> bellmanFord(int V, vector<Edge>& edges, int src) {
    vector<int> dist(V, INT_MAX);
    dist[src] = 0;

    for (int i = 1; i < V; ++i) {
        for (auto& e : edges) {
            if (dist[e.u] != INT_MAX && dist[e.u] + e.w < dist[e.v]) {
                dist[e.v] = dist[e.u] + e.w;
                cout << "Relaxing edge " << e.u << "->" << e.v << ", new distance: " << dist[e.v] << endl;
            }
        }
    }
    return dist;
}
```

---

### **3. Floyd-Warshall Algorithm**

**Algorithm Explanation:**

This is an **all-pairs shortest path** algorithm using **dynamic programming**. It works on **both positive and negative weights** (but no negative cycles).

**Steps:**

1. Initialize `dist[i][j]` as edge weight or `∞`.
2. For each intermediate node `k`, update:

   * `dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j])`

---

**MNC Question:**
**Problem:** Given a graph of airline routes with varying costs, find the cheapest cost between all city pairs.

```cpp
#include <iostream>
#include <vector>
using namespace std;

void floydWarshall(vector<vector<int>>& dist) {
    int V = dist.size();
    for (int k = 0; k < V; ++k) {
        for (int i = 0; i < V; ++i) {
            for (int j = 0; j < V; ++j) {
                if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX &&
                    dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    cout << "Updated dist[" << i << "][" << j << "] to " << dist[i][j] << endl;
                }
            }
        }
    }
}
```

---

### **4. Kruskal’s Minimum Spanning Tree Algorithm**

**Algorithm Explanation:**

Kruskal’s algorithm finds the **Minimum Spanning Tree (MST)** for a connected undirected graph.

**Steps:**

1. Sort all edges by weight.
2. Initialize disjoint sets for each vertex.
3. For each edge, if its endpoints belong to different sets, include the edge in MST.
4. Use Union-Find to avoid cycles.

---

**MNC Question:**
**Problem:** Design a network connecting all cities at the minimum cost. Edges represent cable costs.

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Edge {
    int u, v, w;
    bool operator<(const Edge& e) const { return w < e.w; }
};

int find(int u, vector<int>& parent) {
    if (parent[u] != u) parent[u] = find(parent[u], parent);
    return parent[u];
}

bool unionSets(int u, int v, vector<int>& parent, vector<int>& rank) {
    int pu = find(u, parent), pv = find(v, parent);
    if (pu == pv) return false;
    if (rank[pu] < rank[pv]) parent[pu] = pv;
    else if (rank[pu] > rank[pv]) parent[pv] = pu;
    else { parent[pv] = pu; rank[pu]++; }
    return true;
}

int kruskal(int V, vector<Edge>& edges) {
    sort(edges.begin(), edges.end());
    vector<int> parent(V), rank(V, 0);
    for (int i = 0; i < V; i++) parent[i] = i;

    int mst_weight = 0;
    for (auto& e : edges) {
        if (unionSets(e.u, e.v, parent, rank)) {
            mst_weight += e.w;
            cout << "Added edge " << e.u << " - " << e.v << ", weight = " << e.w << endl;
        }
    }
    return mst_weight;
}
```

---

