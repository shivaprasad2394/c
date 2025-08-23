# Capgemini Array Problems - Complete Solutions

```c
#define C_CODE1 1
#define CPP_CODE1 0
#define C_CODE2 1
#define CPP_CODE2 0
#define C_CODE3 1
#define CPP_CODE3 0
#define C_CODE4 1
#define CPP_CODE4 0
#define C_CODE5 1
#define CPP_CODE5 0
#define C_CODE6 1
#define CPP_CODE6 0
#define C_CODE7 1
#define CPP_CODE7 0
#define C_CODE8 1
#define CPP_CODE8 0
#define C_CODE9 1
#define CPP_CODE9 0
#define C_CODE10 1
#define CPP_CODE10 0
#define C_CODE11 1
#define CPP_CODE11 0
#define C_CODE12 1
#define CPP_CODE12 0

// ============================================================================
// PROBLEM 1: Find Second Largest Element
// ============================================================================

/*
Algorithm/Logic Steps:
1. Initialize first = -1 and second = -1 (or use INT_MIN)
2. Traverse array once:
   - If current > first: update second = first, first = current
   - Else if current > second && current != first: update second = current
3. Time Complexity: O(n), Space Complexity: O(1)
*/

#if C_CODE1
#include <stdio.h>
#include <limits.h>

int findSecondLargest(int arr[], int n) {
    int first = INT_MIN, second = INT_MIN;
    
    printf("Debug: Finding second largest in array\n");
    
    for (int i = 0; i < n; i++) {
        printf("Debug: Processing arr[%d] = %d\n", i, arr[i]);
        
        if (arr[i] > first) {
            printf("Debug: New largest found! Moving %d to second, %d to first\n", first, arr[i]);
            second = first;  // Move current first to second
            first = arr[i];  // Update first
        }
        else if (arr[i] > second && arr[i] != first) {
            printf("Debug: New second largest found: %d\n", arr[i]);
            second = arr[i]; // Update second
        }
    }
    
    if (second == INT_MIN) {
        printf("Debug: No second largest element found\n");
        return -1;
    }
    
    printf("Debug: First = %d, Second = %d\n", first, second);
    return second;
}

int main() {
    int arr[] = {12, 35, 1, 10, 34, 1};
    int n = sizeof(arr)/sizeof(arr[0]);
    
    int result = findSecondLargest(arr, n);
    if (result != -1)
        printf("Second largest element: %d\n", result);
    else
        printf("No second largest element exists\n");
    
    return 0;
}
#endif

#if CPP_CODE1
#include <iostream>
#include <vector>
#include <climits>
using namespace std;

int findSecondLargest(vector<int>& arr) {
    int first = INT_MIN, second = INT_MIN;
    
    cout << "Debug: Finding second largest in array" << endl;
    
    for (int i = 0; i < arr.size(); i++) {
        cout << "Debug: Processing arr[" << i << "] = " << arr[i] << endl;
        
        if (arr[i] > first) {
            cout << "Debug: New largest found! Moving " << first << " to second, " 
                 << arr[i] << " to first" << endl;
            second = first;
            first = arr[i];
        }
        else if (arr[i] > second && arr[i] != first) {
            cout << "Debug: New second largest found: " << arr[i] << endl;
            second = arr[i];
        }
    }
    
    if (second == INT_MIN) {
        cout << "Debug: No second largest element found" << endl;
        return -1;
    }
    
    cout << "Debug: First = " << first << ", Second = " << second << endl;
    return second;
}

int main() {
    vector<int> arr = {12, 35, 1, 10, 34, 1};
    
    int result = findSecondLargest(arr);
    if (result != -1)
        cout << "Second largest element: " << result << endl;
    else
        cout << "No second largest element exists" << endl;
    
    return 0;
}
#endif

// ============================================================================
// PROBLEM 2: Move All Zeros to End
// ============================================================================

/*
Algorithm/Logic Steps:
1. Use two pointers: writeIndex (for non-zero elements) and readIndex (traverse array)
2. When non-zero element found, move it to writeIndex position
3. Fill remaining positions with zeros
4. Time Complexity: O(n), Space Complexity: O(1)
*/

#if C_CODE2
#include <stdio.h>

void moveZerosToEnd(int arr[], int n) {
    int writeIndex = 0;  // Position to place next non-zero element
    
    printf("Debug: Moving zeros to end\n");
    printf("Original array: ");
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");
    
    // Move all non-zero elements to front
    for (int readIndex = 0; readIndex < n; readIndex++) {
        printf("Debug: Processing arr[%d] = %d\n", readIndex, arr[readIndex]);
        
        if (arr[readIndex] != 0) {
            printf("Debug: Non-zero element found, moving to position %d\n", writeIndex);
            arr[writeIndex] = arr[readIndex];
            writeIndex++;
        } else {
            printf("Debug: Zero found, skipping\n");
        }
    }
    
    // Fill remaining positions with zeros
    printf("Debug: Filling positions %d to %d with zeros\n", writeIndex, n-1);
    while (writeIndex < n) {
        arr[writeIndex] = 0;
        writeIndex++;
    }
    
    printf("Final array: ");
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");
}

int main() {
    int arr[] = {0, 1, 9, 8, 4, 0, 0, 2, 7, 0, 6, 0};
    int n = sizeof(arr)/sizeof(arr[0]);
    
    moveZerosToEnd(arr, n);
    return 0;
}
#endif

#if CPP_CODE2
#include <iostream>
#include <vector>
using namespace std;

void moveZerosToEnd(vector<int>& arr) {
    int writeIndex = 0;
    
    cout << "Debug: Moving zeros to end" << endl;
    cout << "Original array: ";
    for (int x : arr) cout << x << " ";
    cout << endl;
    
    // Move non-zero elements to front
    for (int readIndex = 0; readIndex < arr.size(); readIndex++) {
        cout << "Debug: Processing arr[" << readIndex << "] = " << arr[readIndex] << endl;
        
        if (arr[readIndex] != 0) {
            cout << "Debug: Non-zero element found, moving to position " << writeIndex << endl;
            arr[writeIndex] = arr[readIndex];
            writeIndex++;
        } else {
            cout << "Debug: Zero found, skipping" << endl;
        }
    }
    
    // Fill remaining with zeros
    cout << "Debug: Filling positions " << writeIndex << " to " << arr.size()-1 << " with zeros" << endl;
    while (writeIndex < arr.size()) {
        arr[writeIndex] = 0;
        writeIndex++;
    }
    
    cout << "Final array: ";
    for (int x : arr) cout << x << " ";
    cout << endl;
}

int main() {
    vector<int> arr = {0, 1, 9, 8, 4, 0, 0, 2, 7, 0, 6, 0};
    
    moveZerosToEnd(arr);
    return 0;
}
#endif

// ============================================================================
// PROBLEM 3: Rotate Array Left by D Positions
// ============================================================================

/*
Algorithm/Logic Steps:
1. Method 1 (Reversal): Reverse first d elements, reverse remaining, reverse whole array
2. Method 2 (Temp Array): Store first d elements, shift rest left, place stored elements at end
3. Handle d > n by using d = d % n
4. Time Complexity: O(n), Space Complexity: O(1) for reversal method
Example:

arr = [1, 2, 3, 4, 5, 6, 7]
d = 2
Result = [3, 4, 5, 6, 7, 1, 2]
✅ Handle d > n
Always normalize d:
d = d % n;
This ensures you don't rotate more than necessary.

⚙️ Method 1: Reversal Algorithm
🧠 Logic Steps:

- Reverse the first d elements
- Reverse the remaining n - d elements
- Reverse the entire array
🧪 Example:
arr = [1, 2, 3, 4, 5, 6, 7]
d = 2

🔧 Step-by-Step:
Reverse first d=2 elements: [1, 2] → [2, 1]
→ [2, 1, 3, 4, 5, 6, 7]
Reverse the rest: [3, 4, 5, 6, 7] → [7, 6, 5, 4, 3]
→ [2, 1, 7, 6, 5, 4, 3]
Reverse entire array:
→ [3, 4, 5, 6, 7, 1, 2]
✅ Done!

🗂 Method 2: Temp Array Method
🧠 Logic Steps:

- Store first d elements in a temp array
- Shift remaining elements left by d
- Copy stored d elements to the end

🧪 Example:
arr = [1, 2, 3, 4, 5, 6, 7]
d = 2

🔧 Step-by-Step:
Temp = [1, 2]
Shift elements left:
arr[0] = arr[2] = 3  
arr[1] = arr[3] = 4  
...
arr[4] = arr[6] = 7  
Array becomes: [3, 4, 5, 6, 7, 6, 7]
Copy temp:
arr[5] = temp[0] = 1  
arr[6] = temp[1] = 2  
Final array: [3, 4, 5, 6, 7, 1, 2]
✅ Done!
*/

#if C_CODE3
#include <stdio.h>

void reverse(int arr[], int start, int end) {
    printf("Debug: Reversing from index %d to %d\n", start, end);
    while (start < end) {
        int temp = arr[start];
        arr[start] = arr[end];
        arr[end] = temp;
        start++;
        end--;
    }
}

void rotateLeft(int arr[], int n, int d) {
    // Handle case where d > n
    d = d % n;
    printf("Debug: Rotating array left by %d positions\n", d);
    
    printf("Original array: ");
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");
    
    // Method: Reverse first d elements, reverse rest, reverse whole array
    printf("Debug: Step 1 - Reverse first %d elements\n", d);
    reverse(arr, 0, d - 1);
    
    printf("Debug: Step 2 - Reverse remaining %d elements\n", n - d);
    reverse(arr, d, n - 1);
    
    printf("Debug: Step 3 - Reverse entire array\n");
    reverse(arr, 0, n - 1);
    
    printf("Final array: ");
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7};
    int n = sizeof(arr)/sizeof(arr[0]);
    int d = 2;
    
    rotateLeft(arr, n, d);
    return 0;
}
#endif

#if CPP_CODE3
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void rotateLeft(vector<int>& arr, int d) {
    int n = arr.size();
    d = d % n;  // Handle d > n
    
    cout << "Debug: Rotating array left by " << d << " positions" << endl;
    
    cout << "Original array: ";
    for (int x : arr) cout << x << " ";
    cout << endl;
    
    // Method: Using STL reverse function
    cout << "Debug: Step 1 - Reverse first " << d << " elements" << endl;
    reverse(arr.begin(), arr.begin() + d);
    
    cout << "Debug: Step 2 - Reverse remaining elements" << endl;
    reverse(arr.begin() + d, arr.end());
    
    cout << "Debug: Step 3 - Reverse entire array" << endl;
    reverse(arr.begin(), arr.end());
    
    cout << "Final array: ";
    for (int x : arr) cout << x << " ";
    cout << endl;
}

int main() {
    vector<int> arr = {1, 2, 3, 4, 5, 6, 7};
    int d = 2;
    
    rotateLeft(arr, d);
    return 0;
}
#endif

// ============================================================================
// PROBLEM 4: Kadane's Algorithm - Maximum Subarray Sum
// ============================================================================

/*
Algorithm/Logic Steps:
1. Initialize maxSoFar = arr[0], maxEndingHere = arr[0]
2. For each element from index 1:
   - maxEndingHere = max(arr[i], maxEndingHere + arr[i])
   - maxSoFar = max(maxSoFar, maxEndingHere)
3. Return maxSoFar
4. Time Complexity: O(n), Space Complexity: O(1)

🧠 Kadane’s Algorithm Logic

maxSoFar: Tracks the overall maximum sum found so far.
maxEndingHere: Tracks the maximum sum ending at the current position (can reset if current number is better than extending previous subarray).
ex:-
arr = [−2, 1, −3, 4, −1, 2, 1, −5, 4]
We want the maximum sum of a contiguous subarray.
| i | arr[i] | maxEndingHere = max(arr[i], maxEndingHere + arr[i]) | maxSoFar = max(maxSoFar, maxEndingHere) |
|---|--------|------------------------------------------------------|-------------------------------------------|
| 1 |   1    | max(1, -2 + 1) = 1                                   | max(-2, 1) = 1                            |
| 2 |  -3    | max(-3, 1 + -3) = -2                                 | max(1, -2) = 1                            |
| 3 |   4    | max(4, -2 + 4) = 4                                   | max(1, 4) = 4                             |
| 4 |  -1    | max(-1, 4 + -1) = 3                                  | max(4, 3) = 4                             |
| 5 |   2    | max(2, 3 + 2) = 5                                    | max(4, 5) = 5                             |
| 6 |   1    | max(1, 5 + 1) = 6                                    | max(5, 6) = 6                             |
| 7 |  -5    | max(-5, 6 + -5) = 1                                  | max(6, 1) = 6                             |
| 8 |   4    | max(4, 1 + 4) = 5                                    | max(6, 5) = 6                             |
|---|--------|------------------------------------------------------|-------------------------------------------|
🎯 Final Result:
Maximum subarray sum = 6
The subarray is [4, -1, 2, 1]
*/

#if C_CODE4
#include <stdio.h>
#include <limits.h>

int kadane(int arr[], int n) {
    int maxSoFar = arr[0];
    int maxEndingHere = arr[0];
    
    printf("Debug: Finding maximum subarray sum using Kadane's algorithm\n");
    printf("Array: ");
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");
    
    printf("Debug: Initial - maxSoFar = %d, maxEndingHere = %d\n", maxSoFar, maxEndingHere);
    
    for (int i = 1; i < n; i++) {
        printf("\nDebug: Processing arr[%d] = %d\n", i, arr[i]);
        
        // Either extend existing subarray or start new one
        int extendSubarray = maxEndingHere + arr[i];
        int startNew = arr[i];
        
        printf("Debug: Extend existing subarray: %d + %d = %d\n", maxEndingHere, arr[i], extendSubarray);
        printf("Debug: Start new subarray: %d\n", startNew);
        
        maxEndingHere = (extendSubarray > startNew) ? extendSubarray : startNew;
        printf("Debug: maxEndingHere = %d\n", maxEndingHere);
        
        // Update global maximum
        if (maxEndingHere > maxSoFar) {
            maxSoFar = maxEndingHere;
            printf("Debug: New maximum found: %d\n", maxSoFar);
        }
    }
    
    return maxSoFar;
}

int main() {
    int arr[] = {-2, -3, 4, -1, -2, 1, 5, -3};
    int n = sizeof(arr)/sizeof(arr[0]);
    
    int maxSum = kadane(arr, n);
    printf("\nMaximum subarray sum: %d\n", maxSum);
    return 0;
}
#endif

#if CPP_CODE4
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int kadane(vector<int>& arr) {
    int maxSoFar = arr[0];
    int maxEndingHere = arr[0];
    
    cout << "Debug: Finding maximum subarray sum using Kadane's algorithm" << endl;
    cout << "Array: ";
    for (int x : arr) cout << x << " ";
    cout << endl;
    
    cout << "Debug: Initial - maxSoFar = " << maxSoFar << ", maxEndingHere = " << maxEndingHere << endl;
    
    for (int i = 1; i < arr.size(); i++) {
        cout << "\nDebug: Processing arr[" << i << "] = " << arr[i] << endl;
        
        int extendSubarray = maxEndingHere + arr[i];
        int startNew = arr[i];
        
        cout << "Debug: Extend existing: " << maxEndingHere << " + " << arr[i] << " = " << extendSubarray << endl;
        cout << "Debug: Start new: " << startNew << endl;
        
        maxEndingHere = max(extendSubarray, startNew);
        cout << "Debug: maxEndingHere = " << maxEndingHere << endl;
        
        maxSoFar = max(maxSoFar, maxEndingHere);
        if (maxEndingHere == maxSoFar) {
            cout << "Debug: New maximum found: " << maxSoFar << endl;
        }
    }
    
    return maxSoFar;
}

int main() {
    vector<int> arr = {-2, -3, 4, -1, -2, 1, 5, -3};
    
    int maxSum = kadane(arr);
    cout << "\nMaximum subarray sum: " << maxSum << endl;
    return 0;
}
#endif

// ============================================================================
// PROBLEM 5: Remove Duplicates from Sorted Array
// ============================================================================

/*
Algorithm/Logic Steps:
1. Use two pointers: slow (unique elements) and fast (traverse array)
2. If arr[fast] != arr[slow], move arr[fast] to arr[slow+1] and increment slow
3. Return slow+1 (length of unique elements)
4. Time Complexity: O(n), Space Complexity: O(1)
Algorithm Steps:

Use two pointers:
slow: tracks the position of the last unique element
fast: traverses the array

For each fast from index 1 to n-1:
If arr[fast] != arr[slow], then:
slow++
arr[slow] = arr[fast] → Move the unique element forward
After loop, return slow + 1 → this is the count of unique elements
ex:-arr = [1, 1, 2, 2, 3, 4, 4]
| Index (fast) | arr[fast] | arr[slow] | Action                              | Updated Array          |
|--------------|-----------|-----------|-------------------------------------|------------------------|
| 1            | 1         | 1         | Duplicate → do nothing              | [1, 1, 2, 2, 3, 4, 4]  |
| 2            | 2         | 1         | New value → slow++, arr[slow]=2     | [1, 2, 2, 2, 3, 4, 4]  |
| 3            | 2         | 2         | Duplicate → do nothing              | [1, 2, 2, 2, 3, 4, 4]  |
| 4            | 3         | 2         | New value → slow++, arr[slow]=3     | [1, 2, 3, 2, 3, 4, 4]  |
| 5            | 4         | 3         | New value → slow++, arr[slow]=4     | [1, 2, 3, 4, 3, 4, 4]  |
| 6            | 4         | 4         | Duplicate → do nothing              | [1, 2, 3, 4, 3, 4, 4]  |
|--------------|-----------|-----------|-------------------------------------|------------------------|
🎯 Result:
New length: slow + 1 = 4
Array after removing duplicates: [1, 2, 3, 4]
*/

#if C_CODE5
#include <stdio.h>

int removeDuplicates(int arr[], int n) {
    if (n == 0) return 0;
    
    int slow = 0;  // Points to last unique element
    
    printf("Debug: Removing duplicates from sorted array\n");
    printf("Original array: ");
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");
    
    // Traverse array with fast pointer
    for (int fast = 1; fast < n; fast++) {
        printf("Debug: Comparing arr[%d]=%d with arr[%d]=%d\n", slow, arr[slow], fast, arr[fast]);
        
        if (arr[fast] != arr[slow]) {
            slow++;
            arr[slow] = arr[fast];
            printf("Debug: New unique element found! Moving %d to position %d\n", arr[fast], slow);
        } else {
            printf("Debug: Duplicate found, skipping\n");
        }
    }
    
    printf("Array after removing duplicates: ");
    for (int i = 0; i <= slow; i++) printf("%d ", arr[i]);
    printf("\n");
    
    return slow + 1;  // Length of unique elements
}

int main() {
    int arr[] = {1, 1, 2, 2, 2, 3, 4, 4, 5};
    int n = sizeof(arr)/sizeof(arr[0]);
    
    int newLength = removeDuplicates(arr, n);
    printf("New length after removing duplicates: %d\n", newLength);
    return 0;
}
#endif

#if CPP_CODE5
#include <iostream>
#include <vector>
using namespace std;

int removeDuplicates(vector<int>& arr) {
    if (arr.empty()) return 0;
    
    int slow = 0;
    
    cout << "Debug: Removing duplicates from sorted array" << endl;
    cout << "Original array: ";
    for (int x : arr) cout << x << " ";
    cout << endl;
    
    for (int fast = 1; fast < arr.size(); fast++) {
        cout << "Debug: Comparing arr[" << slow << "]=" << arr[slow] 
             << " with arr[" << fast << "]=" << arr[fast] << endl;
        
        if (arr[fast] != arr[slow]) {
            slow++;
            arr[slow] = arr[fast];
            cout << "Debug: New unique element! Moving " << arr[fast] << " to position " << slow << endl;
        } else {
            cout << "Debug: Duplicate found, skipping" << endl;
        }
    }
    
    cout << "Array after removing duplicates: ";
    for (int i = 0; i <= slow; i++) cout << arr[i] << " ";
    cout << endl;
    
    return slow + 1;
}

int main() {
    vector<int> arr = {1, 1, 2, 2, 2, 3, 4, 4, 5};
    
    int newLength = removeDuplicates(arr);
    cout << "New length after removing duplicates: " << newLength << endl;
    return 0;
}
#endif

// ============================================================================
// PROBLEM 6: Find Majority Element
// ============================================================================

/*
Algorithm/Logic Steps (Boyer-Moore Voting Algorithm):
1. Initialize candidate = 0, count = 0
2. For each element:
   - If count == 0, set candidate = current element
   - If current == candidate, increment count; else decrement count
3. Verify if candidate appears > n/2 times
4. Time Complexity: O(n), Space Complexity: O(1)

Phase 1: Find a Candidate
Initialize:
candidate = 0
count = 0

For each element num in array:
If count == 0:
→ candidate = num

If num == candidate:
→ count++

Else:
→ count--
🔁 This ensures that if a majority element exists, it survives as the candidate.

Phase 2: Verify the Candidate
Count the occurrences of candidate in the array.
If it appears more than n/2 times → return it.
Else → return "no majority element".
ex:-
arr = [2, 2, 1, 1, 2, 2, 2]
n = 7
| i | arr[i] | count | candidate | Action                             |
|---|--------|--------|-----------|------------------------------------|
| 0 |   2    |  0     | -         | count = 0 → candidate = 2, count=1 |
| 1 |   2    |  1     | 2         | 2 == 2 → count = 2                 |
| 2 |   1    |  2     | 2         | 1 != 2 → count = 1                 |
| 3 |   1    |  1     | 2         | 1 != 2 → count = 0                 |
| 4 |   2    |  0     | -         | count = 0 → candidate = 2, count=1 |
| 5 |   2    |  1     | 2         | 2 == 2 → count = 2                 |
| 6 |   2    |  2     | 2         | 2 == 2 → count = 3                 |
|---|--------|--------|-----------|------------------------------------|
✅ Phase 2: Verify
Count how many times 2 appears: 5 times
5 > 7/2 → Yes, it is the majority.
*/

#if C_CODE6
#include <stdio.h>

int findMajorityElement(int arr[], int n) {
    int candidate = 0, count = 0;
    
    printf("Debug: Finding majority element using Boyer-Moore algorithm\n");
    printf("Array: ");
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");
    
    // Phase 1: Find candidate
    for (int i = 0; i < n; i++) {
        printf("Debug: Processing arr[%d] = %d\n", i, arr[i]);
        
        if (count == 0) {
            candidate = arr[i];
            count = 1;
            printf("Debug: New candidate selected: %d (count = %d)\n", candidate, count);
        }
        else if (arr[i] == candidate) {
            count++;
            printf("Debug: Vote for candidate %d (count = %d)\n", candidate, count);
        }
        else {
            count--;
            printf("Debug: Vote against candidate %d (count = %d)\n", candidate, count);
        }
    }
    
    // Phase 2: Verify candidate
    count = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] == candidate) count++;
    }
    
    printf("Debug: Candidate %d appears %d times out of %d\n", candidate, count, n);
    
    if (count > n/2) {
        printf("Debug: Majority element found!\n");
        return candidate;
    }
    
    printf("Debug: No majority element exists\n");
    return -1;  // No majority element
}

int main() {
    int arr[] = {2, 2, 1, 1, 1, 2, 2};
    int n = sizeof(arr)/sizeof(arr[0]);
    
    int majority = findMajorityElement(arr, n);
    if (majority != -1)
        printf("Majority element: %d\n", majority);
    else
        printf("No majority element found\n");
    
    return 0;
}
#endif

#if CPP_CODE6
#include <iostream>
#include <vector>
using namespace std;

int findMajorityElement(vector<int>& arr) {
    int candidate = 0, count = 0;
    
    cout << "Debug: Finding majority element using Boyer-Moore algorithm" << endl;
    cout << "Array: ";
    for (int x : arr) cout << x << " ";
    cout << endl;
    
    // Phase 1: Find candidate
    for (int i = 0; i < arr.size(); i++) {
        cout << "Debug: Processing arr[" << i << "] = " << arr[i] << endl;
        
        if (count == 0) {
            candidate = arr[i];
            count = 1;
            cout << "Debug: New candidate selected: " << candidate << " (count = " << count << ")" << endl;
        }
        else if (arr[i] == candidate) {
            count++;
            cout << "Debug: Vote for candidate " << candidate << " (count = " << count << ")" << endl;
        }
        else {
            count--;
            cout << "Debug: Vote against candidate " << candidate << " (count = " << count << ")" << endl;
        }
    }
    
    // Phase 2: Verify candidate
    count = 0;
    for (int x : arr) {
        if (x == candidate) count++;
    }
    
    cout << "Debug: Candidate " << candidate << " appears " << count << " times out of " << arr.size() << endl;
    
    if (count > arr.size()/2) {
        cout << "Debug: Majority element found!" << endl;
        return candidate;
    }
    
    cout << "Debug: No majority element exists" << endl;
    return -1;
}

int main() {
    vector<int> arr = {2, 2, 1, 1, 1, 2, 2};
    
    int majority = findMajorityElement(arr);
    if (majority != -1)
        cout << "Majority element: " << majority << endl;
    else
        cout << "No majority element found" << endl;
    
    return 0;
}
#endif

// ============================================================================
// PROBLEM 7: Find Missing Number in Sequence 0 to N
// ============================================================================

/*
Algorithm/Logic Steps:
1. Method 1 (Sum): Expected sum = n*(n+1)/2, subtract actual sum
2. Method 2 (XOR): XOR all numbers 0 to n, then XOR with all array elements
3. Method 3 (Index): Place elements at their correct positions
4. Time Complexity: O(n), Space Complexity: O(1)
*/

#if C_CODE7
#include <stdio.h>

int findMissingNumber(int arr[], int n) {
    printf("Debug: Finding missing number in sequence 0 to %d\n", n);
    printf("Array: ");
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");
    
    // Method 1: Using sum formula
    int expectedSum = n * (n + 1) / 2;
    int actualSum = 0;
    
    printf("Debug: Expected sum of 0 to %d = %d\n", n, expectedSum);
    
    for (int i = 0; i < n; i++) {
        actualSum += arr[i];
    }
    
    printf("Debug: Actual sum = %d\n", actualSum);
    int missing = expectedSum - actualSum;
    printf("Debug: Missing number = %d - %d = %d\n", expectedSum, actualSum, missing);
    
    return missing;
}

// Alternative method using XOR
int findMissingNumberXOR(int arr[], int n) {
    printf("Debug: Finding missing number using XOR method\n");
    
    int xorAll = 0;
    int xorArray = 0;
    
    // XOR all numbers from 0 to n
    for (int i = 0; i <= n; i++) {
        xorAll ^= i;
        printf("Debug: XOR with %d, xorAll = %d\n", i, xorAll);
    }
    
    // XOR all array elements
    for (int i = 0; i < n; i++) {
        xorArray ^= arr[i];
        printf("Debug: XOR with arr[%d] = %d, xorArray = %d\n", i, arr[i], xorArray);
    }
    
    int missing = xorAll ^ xorArray;
    printf("Debug: Missing = %d ^ %d = %d\n", xorAll, xorArray, missing);
    
    return missing;
}

int main() {
    int arr[] = {3, 0, 1, 4, 6, 5, 2};  // Missing 7 from 0-7
    int n = sizeof(arr)/sizeof(arr[0]);
    
    printf("Method 1 (Sum): Missing number = %d\n", findMissingNumber(arr, n));
    printf("\nMethod 2 (XOR): Missing number = %d\n", findMissingNumberXOR(arr, n));
    
    return 0;
}
#endif

#if CPP_CODE7
#include <iostream>
#include <vector>
using namespace std;

int findMissingNumber(vector<int>& arr) {
    int n = arr.size();
    
    cout << "Debug: Finding missing number in sequence 0 to " << n << endl;
    cout << "Array: ";
    for (int x : arr) cout << x << " ";
    cout << endl;
    
    // Method: Using sum formula
    int expectedSum = n * (n + 1) / 2;
    int actualSum = 0;
    
    cout << "Debug: Expected sum of 0 to " << n << " = " << expectedSum << endl;
    
    for (int x : arr) {
        actualSum += x;
    }
    
    cout << "Debug: Actual sum = " << actualSum << endl;
    int missing = expectedSum - actualSum;
    cout << "Debug: Missing number = " << expectedSum << " - " << actualSum << " = " << missing << endl;
    
    return missing;
}

// Alternative XOR method
int findMissingNumberXOR(vector<int>& arr) {
    int n = arr.size();
    cout << "Debug: Finding missing number using XOR method" << endl;
    
    int xorAll = 0;
    int xorArray = 0;
    
    for (int i = 0; i <= n; i++) {
        xorAll ^= i;
        cout << "Debug: XOR with " << i << ", xorAll = " << xorAll << endl;
    }
    
    for (int i = 0; i < n; i++) {
        xorArray ^= arr[i];
        cout << "Debug: XOR with arr[" << i << "] = " << arr[i] << ", xorArray = " << xorArray << endl;
    }
    
    int missing = xorAll ^ xorArray;
    cout << "Debug: Missing = " << xorAll << " ^ " << xorArray << " = " << missing << endl;
    
    return missing;
}

int main() {
    vector<int> arr = {3, 0, 1, 4, 6, 5, 2};  // Missing 7
    
    cout << "Method 1 (Sum): Missing number = " << findMissingNumber(arr) << endl;
    cout << "\nMethod 2 (XOR): Missing number = " << findMissingNumberXOR(arr) << endl;
    
    return 0;
}
#endif

// ============================================================================
// PROBLEM 8: Reverse Array in Groups of Size K
// ============================================================================

/*
Algorithm/Logic Steps:
1. Process array in chunks of size k
2. For each chunk, reverse elements within that chunk
3. Handle last group which might have < k elements
4. Time Complexity: O(n), Space Complexity: O(1)
arr = [1, 2, 3, 4, 5, 6, 7, 8, 9]
k = 3

note:-If n % k != 0, the last group may have fewer than k elements — still reverse it.
This works for any k ≥ 1.

| Group Start | Group End | Original Subarray | Reversed Subarray |
|-------------|-----------|-------------------|--------------------|
| 0           | 2         | [1, 2, 3]         | [3, 2, 1]          |
| 3           | 5         | [4, 5, 6]         | [6, 5, 4]          |
| 6           | 8         | [7, 8, 9]         | [9, 8, 7]          |

final result:-[3, 2, 1, 6, 5, 4, 9, 8, 7]
*/

#if C_CODE8
#include <stdio.h>

void reverse(int arr[], int start, int end) {
    printf("Debug: Reversing elements from index %d to %d\n", start, end);
    while (start < end) {
        int temp = arr[start];
        arr[start] = arr[end];
        arr[end] = temp;
        start++;
        end--;
    }
}

void reverseInGroups(int arr[], int n, int k) {
    printf("Debug: Reversing array in groups of size %d\n", k);
    printf("Original array: ");
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");
    
    // Process each group of size k
    for (int i = 0; i < n; i += k) {
        int start = i;
        int end = (i + k - 1 < n) ? i + k - 1 : n - 1;  // Handle last group
        
        printf("Debug: Processing group %d: indices %d to %d\n", i/k + 1, start, end);
        reverse(arr, start, end);
        
        printf("After reversing group: ");
        for (int j = 0; j < n; j++) printf("%d ", arr[j]);
        printf("\n");
    }
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int n = sizeof(arr)/sizeof(arr[0]);
    int k = 3;
    
    reverseInGroups(arr, n, k);
    
    printf("Final result: ");
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");
    
    return 0;
}
#endif

#if CPP_CODE8
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void reverseInGroups(vector<int>& arr, int k) {
    cout << "Debug: Reversing array in groups of size " << k << endl;
    cout << "Original array: ";
    for (int x : arr) cout << x << " ";
    cout << endl;
    
    int n = arr.size();
    
    // Process each group
    for (int i = 0; i < n; i += k) {
        int start = i;
        int end = min(i + k - 1, n - 1);  // Handle last group
        
        cout << "Debug: Processing group " << (i/k + 1) << ": indices " << start << " to " << end << endl;
        
        // Reverse current group using STL
        reverse(arr.begin() + start, arr.begin() + end + 1);
        
        cout << "After reversing group: ";
        for (int x : arr) cout << x << " ";
        cout << endl;
    }
}

int main() {
    vector<int> arr = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int k = 3;
    
    reverseInGroups(arr, k);
    
    cout << "Final result: ";
    for (int x : arr) cout << x << " ";
    cout << endl;
    
    return 0;
}
#endif

// ============================================================================
// PROBLEM 9: Find Minimum in Rotated Sorted Array (Binary Search)
// ============================================================================

/*
Algorithm/Logic Steps:
1. Use binary search with left and right pointers
2. If arr[mid] > arr[right], minimum is in right half
3. Else, minimum is in left half (including mid)
4. Continue until left == right
5. Time Complexity: O(log n), Space Complexity: O(1)

Rotated version: [4, 5, 6, 7, 1, 2, 3]
n = 7
Minimum: 1

🔍 Binary Search Algorithm Steps
Initialize two pointers:
left = 0, right = n - 1

While left < right:
Compute mid = (left + right) / 2
If arr[mid] > arr[right]:
Minimum is to the right of mid → left = mid + 1

Else:
Minimum is at mid or to its left → right = mid
When loop ends, left == right, pointing to the minimum element.
| left | mid | right | arr[mid] | arr[right] | Action                    |
|------|-----|-------|----------|------------|---------------------------|
| 0    | 3   | 6     | 7        | 2          | 7 > 2 → min in right half |
| 4    | 5   | 6     | 1        | 2          | 1 < 2 → min in left half  |
| 4    | 4   | 5     | 0        | 1          | 0 < 1 → min in left half  |
| 4    |     | 4     |          |            | left == right → found `0` |
|------|-----|-------|----------|------------|---------------------------|
*/

#if C_CODE9
#include <stdio.h>

int findMin(int arr[], int n) {
    int left = 0, right = n - 1;
    
    printf("Debug: Finding minimum in rotated sorted array using binary search\n");
    printf("Array: ");
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");
    
    while (left < right) {
        int mid = left + (right - left) / 2;
        
        printf("Debug: left = %d, right = %d, mid = %d\n", left, right, mid);
        printf("Debug: arr[left] = %d, arr[mid] = %d, arr[right] = %d\n", 
               arr[left], arr[mid], arr[right]);
        
        if (arr[mid] > arr[right]) {
            // Minimum is in right half
            printf("Debug: arr[mid] > arr[right], searching right half\n");
            left = mid + 1;
        } else {
            // Minimum is in left half (including mid)
            printf("Debug: arr[mid] <= arr[right], searching left half\n");
            right = mid;
        }
    }
    
    printf("Debug: Search complete, minimum found at index %d\n", left);
    return arr[left];
}

int main() {
    int arr[] = {4, 5, 6, 7, 0, 1, 2};
    int n = sizeof(arr)/sizeof(arr[0]);
    
    int minimum = findMin(arr, n);
    printf("Minimum element: %d\n", minimum);
    
    return 0;
}
#endif

#if CPP_CODE9
#include <iostream>
#include <vector>
using namespace std;

int findMin(vector<int>& arr) {
    int left = 0, right = arr.size() - 1;
    
    cout << "Debug: Finding minimum in rotated sorted array using binary search" << endl;
    cout << "Array: ";
    for (int x : arr) cout << x << " ";
    cout << endl;
    
    while (left < right) {
        int mid = left + (right - left) / 2;
        
        cout << "Debug: left = " << left << ", right = " << right << ", mid = " << mid << endl;
        cout << "Debug: arr[left] = " << arr[left] << ", arr[mid] = " << arr[mid] 
             << ", arr[right] = " << arr[right] << endl;
        
        if (arr[mid] > arr[right]) {
            cout << "Debug: arr[mid] > arr[right], searching right half" << endl;
            left = mid + 1;
        } else {
            cout << "Debug: arr[mid] <= arr[right], searching left half" << endl;
            right = mid;
        }
    }
    
    cout << "Debug: Search complete, minimum found at index " << left << endl;
    return arr[left];
}

int main() {
    vector<int> arr = {4, 5, 6, 7, 0, 1, 2};
    
    int minimum = findMin(arr);
    cout << "Minimum element: " << minimum << endl;
    
    return 0;
}
#endif

// ============================================================================
// PROBLEM 10: Quick Sort and Binary Search Implementation
// ============================================================================

/*
Quick Sort Algorithm:
1. Choose pivot (usually last element)
2. Partition: place smaller elements before pivot, larger after
3. Recursively sort left and right subarrays
4. Time Complexity: O(n log n) average, O(n²) worst case

Binary Search Algorithm:
1. Array must be sorted
2. Compare target with middle element
3. If equal, found; if less, search left half; if greater, search right half
4. Time Complexity: O(log n)
*/

#if C_CODE10
#include <stdio.h>

// Quick Sort Implementation
int partition(int arr[], int low, int high) {
    int pivot = arr[high];  // Choose last element as pivot
    int i = low - 1;        // Index of smaller element
    
    printf("Debug: Partitioning from %d to %d, pivot = %d\n", low, high, pivot);
    
    for (int j = low; j < high; j++) {
        printf("Debug: Comparing arr[%d] = %d with pivot %d\n", j, arr[j], pivot);
        
        if (arr[j] <= pivot) {
            i++;
            // Swap arr[i] and arr[j]
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            printf("Debug: Swapped arr[%d] = %d with arr[%d] = %d\n", i, arr[i], j, arr[j]);
        }
    }
    
    // Place pivot in correct position
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    
    printf("Debug: Pivot %d placed at position %d\n", pivot, i + 1);
    return i + 1;
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pivotIndex = partition(arr, low, high);
        
        printf("Debug: Recursively sorting left subarray [%d to %d]\n", low, pivotIndex - 1);
        quickSort(arr, low, pivotIndex - 1);
        
        printf("Debug: Recursively sorting right subarray [%d to %d]\n", pivotIndex + 1, high);
        quickSort(arr, pivotIndex + 1, high);
    }
}

// Binary Search Implementation
int binarySearch(int arr[], int n, int target) {
    int left = 0, right = n - 1;
    
    printf("Debug: Searching for %d in sorted array\n", target);
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        printf("Debug: left = %d, right = %d, mid = %d, arr[mid] = %d\n", 
               left, right, mid, arr[mid]);
        
        if (arr[mid] == target) {
            printf("Debug: Target found at index %d\n", mid);
            return mid;
        }
        else if (arr[mid] < target) {
            printf("Debug: Target is greater, searching right half\n");
            left = mid + 1;
        }
        else {
            printf("Debug: Target is smaller, searching left half\n");
            right = mid - 1;
        }
    }
    
    printf("Debug: Target not found\n");
    return -1;
}

int main() {
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int n = sizeof(arr)/sizeof(arr[0]);
    
    printf("Original array: ");
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n\n");
    
    // Quick Sort
    printf("=== QUICK SORT ===\n");
    quickSort(arr, 0, n - 1);
    
    printf("\nSorted array: ");
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n\n");
    
    // Binary Search
    printf("=== BINARY SEARCH ===\n");
    int target = 25;
    int result = binarySearch(arr, n, target);
    
    if (result != -1)
        printf("Element %d found at index %d\n", target, result);
    else
        printf("Element %d not found\n", target);
    
    return 0;
}
#endif

#if CPP_CODE10
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Quick Sort Implementation
int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    
    cout << "Debug: Partitioning from " << low << " to " << high << ", pivot = " << pivot << endl;
    
    for (int j = low; j < high; j++) {
        cout << "Debug: Comparing arr[" << j << "] = " << arr[j] << " with pivot " << pivot << endl;
        
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
            cout << "Debug: Swapped arr[" << i << "] = " << arr[i] << " with arr[" << j << "] = " << arr[j] << endl;
        }
    }
    
    swap(arr[i + 1], arr[high]);
    cout << "Debug: Pivot " << pivot << " placed at position " << (i + 1) << endl;
    return i + 1;
}

void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pivotIndex = partition(arr, low, high);
        
        cout << "Debug: Recursively sorting left subarray [" << low << " to " << (pivotIndex - 1) << "]" << endl;
        quickSort(arr, low, pivotIndex - 1);
        
        cout << "Debug: Recursively sorting right subarray [" << (pivotIndex + 1) << " to " << high << "]" << endl;
        quickSort(arr, pivotIndex + 1, high);
    }
}

// Binary Search Implementation
int binarySearch(vector<int>& arr, int target) {
    int left = 0, right = arr.size() - 1;
    
    cout << "Debug: Searching for " << target << " in sorted array" << endl;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        cout << "Debug: left = " << left << ", right = " << right 
             << ", mid = " << mid << ", arr[mid] = " << arr[mid] << endl;
        
        if (arr[mid] == target) {
            cout << "Debug: Target found at index " << mid << endl;
            return mid;
        }
        else if (arr[mid] < target) {
            cout << "Debug: Target is greater, searching right half" << endl;
            left = mid + 1;
        }
        else {
            cout << "Debug: Target is smaller, searching left half" << endl;
            right = mid - 1;
        }
    }
    
    cout << "Debug: Target not found" << endl;
    return -1;
}

int main() {
    vector<int> arr = {64, 34, 25, 12, 22, 11, 90};
    
    cout << "Original array: ";
    for (int x : arr) cout << x << " ";
    cout << endl << endl;
    
    // Quick Sort
    cout << "=== QUICK SORT ===" << endl;
    quickSort(arr, 0, arr.size() - 1);
    
    cout << "\nSorted array: ";
    for (int x : arr) cout << x << " ";
    cout << endl << endl;
    
    // Binary Search
    cout << "=== BINARY SEARCH ===" << endl;
    int target = 25;
    int result = binarySearch(arr, target);
    
    if (result != -1)
        cout << "Element " << target << " found at index " << result << endl;
    else
        cout << "Element " << target << " not found" << endl;
    
    return 0;
}
#endif

// ============================================================================
// PROBLEM 11: Merge Two Sorted Arrays
// ============================================================================

/*
Algorithm/Logic Steps:
1. Use three pointers: i (arr1), j (arr2), k (result)
2. Compare elements at i and j, place smaller in result
3. Advance corresponding pointer and result pointer
4. Copy remaining elements from non-empty array
5. Time Complexity: O(m + n), Space Complexity: O(m + n)
*/

#if C_CODE11
#include <stdio.h>
#include <stdlib.h>

void mergeArrays(int arr1[], int m, int arr2[], int n) {
    int* result = (int*)malloc((m + n) * sizeof(int));
    int i = 0, j = 0, k = 0;
    
    printf("Debug: Merging two sorted arrays\n");
    printf("Array 1: ");
    for (int x = 0; x < m; x++) printf("%d ", arr1[x]);
    printf("\nArray 2: ");
    for (int x = 0; x < n; x++) printf("%d ", arr2[x]);
    printf("\n");
    
    // Merge arrays while both have elements
    while (i < m && j < n) {
        printf("Debug: Comparing arr1[%d] = %d with arr2[%d] = %d\n", i, arr1[i], j, arr2[j]);
        
        if (arr1[i] <= arr2[j]) {
            result[k] = arr1[i];
            printf("Debug: Taking %d from arr1, placing at result[%d]\n", arr1[i], k);
            i++;
        } else {
            result[k] = arr2[j];
            printf("Debug: Taking %d from arr2, placing at result[%d]\n", arr2[j], k);
            j++;
        }
        k++;
    }
    
    // Copy remaining elements from arr1
    while (i < m) {
        printf("Debug: Copying remaining arr1[%d] = %d to result[%d]\n", i, arr1[i], k);
        result[k] = arr1[i];
        i++;
        k++;
    }
    
    // Copy remaining elements from arr2
    while (j < n) {
        printf("Debug: Copying remaining arr2[%d] = %d to result[%d]\n", j, arr2[j], k);
        result[k] = arr2[j];
        j++;
        k++;
    }
    
    printf("Merged array: ");
    for (int x = 0; x < m + n; x++) printf("%d ", result[x]);
    printf("\n");
    
    free(result);
}

int main() {
    int arr1[] = {1, 3, 5, 7, 9};
    int arr2[] = {2, 4, 6, 8, 10, 12};
    int m = sizeof(arr1)/sizeof(arr1[0]);
    int n = sizeof(arr2)/sizeof(arr2[0]);
    
    mergeArrays(arr1, m, arr2, n);
    return 0;
}
#endif

#if CPP_CODE11
#include <iostream>
#include <vector>
using namespace std;

vector<int> mergeArrays(vector<int>& arr1, vector<int>& arr2) {
    vector<int> result;
    int i = 0, j = 0;
    
    cout << "Debug: Merging two sorted arrays" << endl;
    cout << "Array 1: ";
    for (int x : arr1) cout << x << " ";
    cout << "\nArray 2: ";
    for (int x : arr2) cout << x << " ";
    cout << endl;
    
    // Merge while both arrays have elements
    while (i < arr1.size() && j < arr2.size()) {
        cout << "Debug: Comparing arr1[" << i << "] = " << arr1[i] 
             << " with arr2[" << j << "] = " << arr2[j] << endl;
        
        if (arr1[i] <= arr2[j]) {
            result.push_back(arr1[i]);
            cout << "Debug: Taking " << arr1[i] << " from arr1" << endl;
            i++;
        } else {
            result.push_back(arr2[j]);
            cout << "Debug: Taking " << arr2[j] << " from arr2" << endl;
            j++;
        }
    }
    
    // Copy remaining elements
    while (i < arr1.size()) {
        cout << "Debug: Copying remaining arr1[" << i << "] = " << arr1[i] << endl;
        result.push_back(arr1[i]);
        i++;
    }
    
    while (j < arr2.size()) {
        cout << "Debug: Copying remaining arr2[" << j << "] = " << arr2[j] << endl;
        result.push_back(arr2[j]);
        j++;
    }
    
    return result;
}

int main() {
    vector<int> arr1 = {1, 3, 5, 7, 9};
    vector<int> arr2 = {2, 4, 6, 8, 10, 12};
    
    vector<int> merged = mergeArrays(arr1, arr2);
    
    cout << "Merged array: ";
    for (int x : merged) cout << x << " ";
    cout << endl;
    
    return 0;
}
#endif

// ============================================================================
// PROBLEM 12: Heap Sort Implementation
// ============================================================================

/*
Algorithm/Logic Steps:
1. Build max heap from unsorted array
2. Extract maximum (root), place at end
3. Heapify remaining elements
4. Repeat until heap is empty
5. Time Complexity: O(n log n), Space Complexity: O(1)

Heapify Steps:
1. Compare parent with children
2. If parent < largest child, swap
3. Recursively heapify affected subtree
*/

#if C_CODE12
#include <stdio.h>

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(int arr[], int n, int root) {
    int largest = root;
    int left = 2 * root + 1;
    int right = 2 * root + 2;
    
    printf("Debug: Heapifying with root = %d (value = %d)\n", root, arr[root]);
    
    // Check if left child is larger than root
    if (left < n && arr[left] > arr[largest]) {
        printf("Debug: Left child arr[%d] = %d is larger than root\n", left, arr[left]);
        largest = left;
    }
    
    // Check if right child is larger than current largest
    if (right < n && arr[right] > arr[largest]) {
        printf("Debug: Right child arr[%d] = %d is larger\n", right, arr[right]);
        largest = right;
    }
    
    // If largest is not root, swap and continue heapifying
    if (largest != root) {
        printf("Debug: Swapping arr[%d] = %d with arr[%d] = %d\n", 
               root, arr[root], largest, arr[largest]);
        swap(&arr[root], &arr[largest]);
        
        // Recursively heapify the affected subtree
        heapify(arr, n, largest);
    } else {
        printf("Debug: Heap property satisfied at root %d\n", root);
    }
}

void heapSort(int arr[], int n) {
    printf("Debug: Starting Heap Sort\n");
    printf("Original array: ");
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n\n");
    
    // Build max heap (heapify all non-leaf nodes)
    printf("=== BUILDING MAX HEAP ===\n");
    for (int i = n / 2 - 1; i >= 0; i--) {
        printf("Debug: Heapifying node %d\n", i);
        heapify(arr, n, i);
    }
    
    printf("Max heap built: ");
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n\n");
    
    // Extract elements one by one from heap
    printf("=== EXTRACTING ELEMENTS ===\n");
    for (int i = n - 1; i > 0; i--) {
        printf("Debug: Extracting maximum %d, placing at position %d\n", arr[0], i);
        
        // Move current root to end
        swap(&arr[0], &arr[i]);
        
        // Heapify the reduced heap
        printf("Debug: Heapifying reduced heap of size %d\n", i);
        heapify(arr, i, 0);
        
        printf("Array after extraction: ");
        for (int j = 0; j < n; j++) printf("%d ", arr[j]);
        printf("\n");
    }
}

int main() {
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int n = sizeof(arr)/sizeof(arr[0]);
    
    heapSort(arr, n);
    
    printf("\nFinal sorted array: ");
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");
    
    return 0;
}
#endif

#if CPP_CODE12
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void heapify(vector<int>& arr, int n, int root) {
    int largest = root;
    int left = 2 * root + 1;
    int right = 2 * root + 2;
    
    cout << "Debug: Heapifying with root = " << root << " (value = " << arr[root] << ")" << endl;
    
    // Find largest among root, left child and right child
    if (left < n && arr[left] > arr[largest]) {
        cout << "Debug: Left child arr[" << left << "] = " << arr[left] << " is larger than root" << endl;
        largest = left;
    }
    
    if (right < n && arr[right] > arr[largest]) {
        cout << "Debug: Right child arr[" << right << "] = " << arr[right] << " is larger" << endl;
        largest = right;
    }
    
    // If largest is not root, swap and continue heapifying
    if (largest != root) {
        cout << "Debug: Swapping arr[" << root << "] = " << arr[root] 
             << " with arr[" << largest << "] = " << arr[largest] << endl;
        swap(arr[root], arr[largest]);
        
        // Recursively heapify the affected subtree
        heapify(arr, n, largest);
    } else {
        cout << "Debug: Heap property satisfied at root " << root << endl;
    }
}

void heapSort(vector<int>& arr) {
    int n = arr.size();
    
    cout << "Debug: Starting Heap Sort" << endl;
    cout << "Original array: ";
    for (int x : arr) cout << x << " ";
    cout << endl << endl;
    
    // Build max heap
    cout << "=== BUILDING MAX HEAP ===" << endl;
    for (int i = n / 2 - 1; i >= 0; i--) {
        cout << "Debug: Heapifying node " << i << endl;
        heapify(arr, n, i);
    }
    
    cout << "Max heap built: ";
    for (int x : arr) cout << x << " ";
    cout << endl << endl;
    
    // Extract elements one by one
    cout << "=== EXTRACTING ELEMENTS ===" << endl;
    for (int i = n - 1; i > 0; i--) {
        cout << "Debug: Extracting maximum " << arr[0] << ", placing at position " << i << endl;
        
        // Move current root to end
        swap(arr[0], arr[i]);
        
        // Heapify the reduced heap
        cout << "Debug: Heapifying reduced heap of size " << i << endl;
        heapify(arr, i, 0);
        
        cout << "Array after extraction: ";
        for (int x : arr) cout << x << " ";
        cout << endl;
    }
}

int main() {
    vector<int> arr = {64, 34, 25, 12, 22, 22, 11, 90};
    
    heapSort(arr);
    
    cout << "\nFinal sorted array: ";
    for (int x : arr) cout << x << " ";
    cout << endl;
    
    return 0;
}
#endif
```

## Instructions for Use:

1. **To enable C code for problem X**: Set `C_CODEX` to `1`
2. **To enable C++ code for problem X**: Set `CPP_CODEX` to `1` 
3. **You can enable both C and C++ for the same problem**

## Compilation Instructions:

**For C code:**
```bash
gcc -o program program.c
./program
```

**For C++ code:**
```bash
g++ -o program program.cpp
./program
```

## Key Points for Capgemini Interview:

1. **Time Complexity** - Always mention and explain
2. **Space Complexity** - Important for optimization discussions
3. **Edge Cases** - Empty arrays, single elements, duplicates
4. **In-place vs Extra Space** - Many problems have both approaches
5. **Stability** - Important for sorting algorithms
6. **Practice Tracing** - Be able to walk through your code step by step

Each solution includes detailed debug output to help you understand the flow. **Good luck with your Capgemini interview preparation!** 🚀
