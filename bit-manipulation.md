# Bit Manipulation Problems - Complete Solutions

```c
#include <stdio.h>
#include <stdbool.h>

// ============================================================================
// PROBLEM 1: Check if Number is Power of 2
// ============================================================================

/*
Problem: Given a positive integer, check if it's a power of 2.

Algorithm/Logic:
1. A power of 2 has only one bit set (e.g., 4 = 100, 8 = 1000)
2. if you subtract 1 from a power of two, all the bits after the single 1-bit flip. Then when you AND these two numbers, you get 0!
    Formula: n & (n - 1) == 0
3. Also handle edge case: n > 0

Examples:
If n = 8 → binary: 1000
Then n - 1 = 7 → binary: 0111
1000 & 0111 = 0000 ✓

If n = 6 → binary: 0110
Then n - 1 = 5 → binary: 0101
0110 & 0101 = 0100 ≠ 0 ✗

- 4 (100) & 3 (011) = 000 ✓
- 8 (1000) & 7 (0111) = 0000 ✓
- 6 (110) & 5 (101) = 100 ✗

Time Complexity: O(1)
Space Complexity: O(1)
*/

bool isPowerOfTwo(int n) {
    return n > 0 && (n & (n - 1)) == 0;
}

void testPowerOfTwo() {
    printf("=== Power of 2 Check ===\n");
    
    int testCases[] = {1, 2, 4, 6, 8, 15, 16, 32};
    int numTests = sizeof(testCases) / sizeof(testCases[0]);
    
    for (int i = 0; i < numTests; i++) {
        bool result = isPowerOfTwo(testCases[i]);
        printf("%2d: %s\n", testCases[i], result ? "✓ Power of 2" : "✗ Not power of 2");
    }
}

output:
=== Power of 2 Check ===
 1: ✓ Power of 2
 2: ✓ Power of 2
 4: ✓ Power of 2
 6: ✗ Not power of 2
 8: ✓ Power of 2
15: ✗ Not power of 2
16: ✓ Power of 2
32: ✓ Power of 2
```
```c
// ============================================================================
// Count Set Bits (Number of 1s in Binary)
// ============================================================================

/*
Key Idea: Use n & (n-1) to remove rightmost set bit one at a time
- Each iteration removes one '1' bit
- Count how many iterations until n becomes 0

Time: O(number of set bits)
Space: O(1)
example:-
528 in binary: 1000010000

Iteration 1: n = 528 (1000010000)
  n & (n-1) = 1000010000 & 1000001111 = 1000000000 → 512
  count = 1

Iteration 2: n = 512 (1000000000)
  n & (n-1) = 1000000000 & 0111111111 = 0 → 0
  count = 2

Loop ends (n = 0)

Result: 2 set bits
*/

int countSetBits(int n) {
    int count = 0;
    while (n) {
        n = n & (n - 1);  // Remove rightmost set bit
        count++;
    }
    return count;
}

void testCountSetBits() {
    printf("=== Count Set Bits ===\n");
    printf("n\tBinary\t\tCount\n");
    printf("---\t--------\t-----\n");
    
    int testCases[] = {7, 15, 255, 1023, 0};
    int numTests = sizeof(testCases) / sizeof(testCases[0]);
    
    for (int i = 0; i < numTests; i++) {
        int n = testCases[i];
        int count = countSetBits(n);
        
        // Print binary (compact)
        printf("%d\t", n);
        if (n == 0) printf("0\t\t");
        else {
            for (int j = 31; j >= 0; j--) {
                if ((n >> j) & 1) printf("1");
                else if (j < 8) printf("0");  // Only show trailing zeros
            }
            printf("\t");
        }
        printf("%d\n", count);
    }
}
// ============================================================================
// PROBLEM 3: Find Single Non-Repeating Element
// ============================================================================

/*
Problem: In array where every element appears twice except one, find that element.

Algorithm/Logic:
1. Use XOR property: a ^ a = 0, a ^ 0 = a
2. XOR all elements - duplicates cancel out, single element remains
3. Works because XOR is commutative and associative

Example: [4, 1, 2, 1, 2] → 4^1^2^1^2 = 4

Time Complexity: O(n)
Space Complexity: O(1)
*/

int findSingleElement(int arr[], int n) {
    printf("Debug: Finding single non-repeating element\n");
    printf("Debug: Array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    
    int result = 0;
    
    for (int i = 0; i < n; i++) {
        printf("Debug: result = %d, arr[%d] = %d, XOR = %d\n", 
               result, i, arr[i], result ^ arr[i]);
        result = result ^ arr[i];
    }
    
    printf("Debug: Single element found = %d\n", result);
    return result;
}

void testFindSingleElement() {
    printf("=== PROBLEM 3: Find Single Non-Repeating Element ===\n");
    
    int test1[] = {4, 1, 2, 1, 2};
    int test2[] = {7, 3, 5, 4, 5, 3, 4};
    int test3[] = {8};
    
    printf("\nTest 1:\n");
    int result1 = findSingleElement(test1, 5);
    printf("Result: %d\n", result1);
    
    printf("\nTest 2:\n");
    int result2 = findSingleElement(test2, 7);
    printf("Result: %d\n", result2);
    
    printf("\nTest 3:\n");
    int result3 = findSingleElement(test3, 1);
    printf("Result: %d\n", result3);
    
    printf("\n");
}

// ============================================================================
// PROBLEM 4: Swap Two Numbers Without Temporary Variable
// ============================================================================

/*
Problem: Swap two numbers using only XOR operations, no temp variable.

Algorithm/Logic:
1. a = a ^ b
2. b = a ^ b  (becomes original a)
3. a = a ^ b  (becomes original b)

Math: If a=5, b=3
- a = 5^3 = 6
- b = 6^3 = 5 (original a)  
- a = 6^5 = 3 (original b)

Time Complexity: O(1)
Space Complexity: O(1)
*/

void swapWithoutTemp(int *a, int *b) {
    printf("Debug: Swapping %d and %d without temp variable\n", *a, *b);
    printf("Debug: Original - a = %d, b = %d\n", *a, *b);
    
    if (*a == *b) {
        printf("Debug: Numbers are equal, no swap needed\n");
        return;
    }
    
    printf("Debug: Step 1 - a = a ^ b = %d ^ %d = %d\n", *a, *b, *a ^ *b);
    *a = *a ^ *b;
    
    printf("Debug: Step 2 - b = a ^ b = %d ^ %d = %d\n", *a, *b, *a ^ *b);
    *b = *a ^ *b;
    
    printf("Debug: Step 3 - a = a ^ b = %d ^ %d = %d\n", *a, *b, *a ^ *b);
    *a = *a ^ *b;
    
    printf("Debug: After swap - a = %d, b = %d\n", *a, *b);
}

void testSwapWithoutTemp() {
    printf("=== PROBLEM 4: Swap Without Temp Variable ===\n");
    
    int test_cases[][2] = {{5, 3}, {10, 20}, {7, 7}, {-5, 15}};
    int numTests = sizeof(test_cases) / sizeof(test_cases[0]);
    
    for (int i = 0; i < numTests; i++) {
        printf("\nTest %d:\n", i+1);
        int a = test_cases[i][0];
        int b = test_cases[i][1];
        swapWithoutTemp(&a, &b);
        printf("Final result: a = %d, b = %d\n", a, b);
    }
    printf("\n");
}

// ============================================================================
// Bit Manipulation: Check, Set, Clear, Toggle
// ============================================================================

/*
Position:  7 6 5 4 3 2 1 0
Example:   0 0 0 0 1 1 0 0  (n = 12)
           └─────────────┘

✓ Check:   (n >> pos) & 1
✓ Set:     n | (1 << pos)
✓ Clear:   n & ~(1 << pos)
✓ Toggle:  n ^ (1 << pos)

Explanation:-
trace through 12, 13, 14, 15 for each operation:
Binary representations:
12 = 1100
13 = 1101
14 = 1110
15 = 1111

CHECK BIT at position 1: (n >> pos) & 1
n=12 (1100): (12 >> 1) & 1 = 0110 & 0001 = 0  ✗ bit is 0
n=13 (1101): (13 >> 1) & 1 = 0110 & 0001 = 0  ✗ bit is 0
n=14 (1110): (14 >> 1) & 1 = 0111 & 0001 = 1  ✓ bit is 1
n=15 (1111): (15 >> 1) & 1 = 0111 & 0001 = 1  ✓ bit is 1

How to explain:
Shift right by pos positions → moves the target bit to position 0
AND with 1 → extracts only that last bit

SET BIT at position 1: n | (1 << pos)
n=12 (1100): 12 | (1 << 1) = 1100 | 0010 = 1110 = 14
n=13 (1101): 13 | (1 << 1) = 1101 | 0010 = 1111 = 15
n=14 (1110): 14 | (1 << 1) = 1110 | 0010 = 1110 = 14 (already set)
n=15 (1111): 15 | (1 << 1) = 1111 | 0010 = 1111 = 15 (already set)

How to explain:
Create a mask: 1 << 1 = position 1 has a 1
OR operation turns bits ON (never turns OFF)
If bit is already 1, it stays 1

CLEAR BIT at position 2: n & ~(1 << pos)
n=12 (1100): 12 & ~(1 << 2) = 1100 & ~0100 = 1100 & 1011 = 1000 = 8
n=13 (1101): 13 & ~(1 << 2) = 1101 & ~0100 = 1101 & 1011 = 1001 = 9
n=14 (1110): 14 & ~(1 << 2) = 1110 & ~0100 = 1110 & 1011 = 1010 = 10
n=15 (1111): 15 & ~(1 << 2) = 1111 & ~0100 = 1111 & 1011 = 1011 = 11

How to explain:

Create mask: 1 << 2 = 0100
Invert it: ~0100 = 1011 (all 1s except position 2)
AND operation turns only that bit OFF

TOGGLE BIT at position 1: n ^ (1 << pos)
n=12 (1100): 12 ^ (1 << 1) = 1100 ^ 0010 = 1110 = 14 (0→1)
n=13 (1101): 13 ^ (1 << 1) = 1101 ^ 0010 = 1111 = 15 (0→1)
n=14 (1110): 14 ^ (1 << 1) = 1110 ^ 0010 = 1100 = 12 (1→0)
n=15 (1111): 15 ^ (1 << 1) = 1111 ^ 0010 = 1101 = 13 (1→0)

How to explain:

XOR with 1 flips the bit: 1^1=0, 0^1=1
If bit is 0, becomes 1. If bit is 1, becomes 0.
*/

#include <stdio.h>
#include <stdbool.h>

bool checkBit(int n, int pos) {
    return (n >> pos) & 1;
}

int setBit(int n, int pos) {
    return n | (1 << pos);
}

int clearBit(int n, int pos) {
    return n & ~(1 << pos);
}

int toggleBit(int n, int pos) {
    return n ^ (1 << pos);
}

void printBinary(int n) {
    for (int i = 7; i >= 0; i--) {
        printf("%d", (n >> i) & 1);
    }
    printf(" (%d)", n);
}

void testBitOperations() {
    printf("=== Bit Manipulation ===\n\n");
    
    int n = 12;  // 00001100
    int pos = 1;
    
    printf("Original:  ");
    printBinary(n);
    printf("\n\n");
    
    printf("Check bit at pos %d:  %s\n", pos, checkBit(n, pos) ? "1" : "0");
    
    printf("Set bit at pos %d:    ");
    printBinary(setBit(n, pos));
    printf("\n");
    
    printf("Clear bit at pos 2:   ");
    printBinary(clearBit(n, 2));
    printf("\n");
    
    printf("Toggle bit at pos %d: ");
    printBinary(toggleBit(n, pos));
    printf("\n");
}
output:-
=== Bit Manipulation ===

Original:  00001100 (12)

Check bit at pos 1:  0
Set bit at pos 1:    00001110 (14)
Clear bit at pos 2:  00001000 (8)
Toggle bit at pos 1: 00001110 (14)

// ============================================================================
// PROBLEM 6: Find Two Non-Repeating Elements
// ============================================================================

/*
Problem: Array where every element appears twice except two elements. Find those two.

Algorithm/Logic:
1. XOR all elements - result is XOR of two unique elements
2. Find rightmost set bit in XOR result
3. Divide elements into two groups based on this bit
4. XOR each group separately to get the two unique elements

Time Complexity: O(n)
Space Complexity: O(1)
*/

void findTwoNonRepeating(int arr[], int n) {
    printf("Debug: Finding two non-repeating elements\n");
    printf("Debug: Array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    
    // Step 1: XOR all elements
    int xorResult = 0;
    for (int i = 0; i < n; i++) {
        xorResult ^= arr[i];
        printf("Debug: XOR so far = %d\n", xorResult);
    }
    
    printf("Debug: Final XOR = %d (XOR of two unique elements)\n", xorResult);
    
    // Step 2: Find rightmost set bit
    int rightmostSetBit = xorResult & (-xorResult);
    printf("Debug: Rightmost set bit = %d\n", rightmostSetBit);
    
    // Step 3: Divide into two groups and XOR each group
    int first = 0, second = 0;
    
    for (int i = 0; i < n; i++) {
        if (arr[i] & rightmostSetBit) {
            first ^= arr[i];
            printf("Debug: Group 1 - adding %d, XOR = %d\n", arr[i], first);
        } else {
            second ^= arr[i];
            printf("Debug: Group 2 - adding %d, XOR = %d\n", arr[i], second);
        }
    }
    
    printf("Debug: Two unique elements are %d and %d\n", first, second);
}

void testFindTwoNonRepeating() {
    printf("=== PROBLEM 6: Find Two Non-Repeating Elements ===\n");
    
    int test1[] = {2, 3, 7, 9, 11, 2, 3, 11};  // Unique: 7, 9
    int test2[] = {1, 2, 3, 2, 1, 4};          // Unique: 3, 4
    
    printf("\nTest 1:\n");
    findTwoNonRepeating(test1, 8);
    
    printf("\nTest 2:\n");
    findTwoNonRepeating(test2, 6);
    
    printf("\n");
}

// ============================================================================
// Reverse Bits of a 32-bit Number
// ============================================================================

/*

After 32 iterations, all bits are reversed."
Idea: Extract bits from right to left, build result by shifting left
- Loop 32 times
- Get rightmost bit of n using n & 1: n & 1
- Shift result left and add that bit to result: result = (result << 1) | bit
- Shift n right for next bit: n >>= 1
*/

unsigned int reverseBits(unsigned int n) {
    unsigned int result = 0;
    
    for (int i = 0; i < 32; i++) {
        int bit = n & 1;           // Extract rightmost bit
        result = (result << 1) | bit;  // Shift result left, add bit
        n >>= 1;                   // Move to next bit
    }
    
    return result;
}

void printBinary32(unsigned int n) {
    for (int i = 31; i >= 0; i--) {
        printf("%d", (n >> i) & 1);
        if (i % 4 == 0 && i > 0) printf(" ");
    }
}

void testReverseBits() {
    printf("=== Reverse Bits ===\n\n");
    
    unsigned int testCases[] = {43261596, 4294967293, 1, 8};
    int numTests = sizeof(testCases) / sizeof(testCases[0]);
    
    for (int i = 0; i < numTests; i++) {
        unsigned int n = testCases[i];
        unsigned int result = reverseBits(n);
        
        printf("Input:  ");
        printBinary32(n);
        printf("\nOutput: ");
        printBinary32(result);
        printf("\n\n");
    }
}

Initial: n = 0101, result = 0000

i=0: bit = 0101 & 1 = 1
     result = (0000 << 1) | 1 = 0001
     n = 0101 >> 1 = 0010

i=1: bit = 0010 & 1 = 0
     result = (0001 << 1) | 0 = 0010
     n = 0010 >> 1 = 0001

i=2: bit = 0001 & 1 = 1
     result = (0010 << 1) | 1 = 0101
     n = 0001 >> 1 = 0000

i=3: bit = 0000 & 1 = 0
     result = (0101 << 1) | 0 = 1010
     n = 0000 >> 1 = 0000

Final: result = 1010 (reversed!)

explanation:-
/*
i=0: bit = 0101 & 1 = 1

    0101  (5 in binary)
  & 0001  (1 in binary)
  ------
    0001  = 1

Why? AND gives 1 only when BOTH bits are 1
Last bit of 0101 is 1, last bit of 0001 is 1 → result is 1 ✓

result = (0000 << 1) | 1 = 0001

Step 1: 0000 << 1  (shift left by 1)
  0000
  ↓ shift left
  0000  (nothing changes, still all zeros)

Step 2: 0000 | 1  (OR with 1)
    0000
  |  0001
  ------
    0001  = 1

Why? OR gives 1 if ANY bit is 1
Position 0: 0 | 1 = 1
Other positions: 0 | 0 = 0
Result: 0001 ✓

n = 0101 >> 1 = 0010  (shift right by 1)

  0101
  ↓ shift right (all bits move right)
  0010

Bits that move right:
- bit 3 → bit 2
- bit 2 → bit 1  
- bit 1 → bit 0
- bit 0 → discarded

Result: 0010 ✓
*/
// ============================================================================
// PROBLEM 8: Check Even/Odd Using Bits
// ============================================================================

/*
Problem: Check if number is even or odd using bitwise operations.

Algorithm/Logic:
1. Check least significant bit (LSB)
2. If LSB = 0, number is even
3. If LSB = 1, number is odd
4. Use bitwise AND with 1: n & 1

Time Complexity: O(1)
Space Complexity: O(1)
*/

bool isEven(int n) {
    printf("Debug: Checking if %d is even using bit operation\n", n);
    
    int lsb = n & 1;
    printf("Debug: LSB of %d = %d & 1 = %d\n", n, n, lsb);
    
    bool even = (lsb == 0);
    printf("Debug: %d is %s\n", n, even ? "EVEN" : "ODD");
    
    return even;
}

void testIsEven() {
    printf("=== PROBLEM 8: Check Even/Odd Using Bits ===\n");
    
    int testCases[] = {4, 7, 0, -3, -8, 15};
    int numTests = sizeof(testCases) / sizeof(testCases[0]);
    
    for (int i = 0; i < numTests; i++) {
        printf("\nTest %d:\n", i+1);
        bool result = isEven(testCases[i]);
        printf("Result: %d is %s\n", testCases[i], result ? "EVEN" : "ODD");
    }
    printf("\n");
}

// ============================================================================
// PROBLEM 9: Position of Rightmost Set Bit
// ============================================================================

/*
Idea: Use n & (-n) to isolate rightmost set bit, then count position

Example: 12 = 1100
  12 & (-12) = 1100 & 0100 = 0100 (isolates rightmost 1)
  0100 = 4 = 2^2 → position 3 (1-indexed not 0 indexed)

Why n & (-n)?
  -12 in two's complement = ~12 + 1 = 0011 + 1 = 0100
  12 & (-12) = 1100 & 0100 = 0100 ✓
*/

int positionOfRightmostSetBit(int n) {
    if (n == 0) return 0;
    
    int rightmostBit = n & (-n);  // Isolate rightmost set bit
    int position = 0;
    
    while (rightmostBit > 1) {
        rightmostBit >>= 1;
        position++;
    }
    
    return position + 1;  // 1-indexed
}

void testPositionOfRightmostSetBit() {
    printf("=== Rightmost Set Bit Position ===\n\n");
    
    int testCases[] = {12, 18, 5, 8, 0};
    int numTests = sizeof(testCases) / sizeof(testCases[0]);
    
    for (int i = 0; i < numTests; i++) {
        int n = testCases[i];
        int result = positionOfRightmostSetBit(n);
        
        printf("n=%2d | Binary: ", n);
        if (n == 0) {
            printf("0000");
        } else {
            for (int j = 7; j >= 0; j--) {
                printf("%d", (n >> j) & 1);
            }
        }
        printf(" | Position: %d\n", result);
    }
}
output:-
=== Rightmost Set Bit Position ===

n=12 | Binary: 00001100 | Position: 3
n=18 | Binary: 00010010 | Position: 2
n= 5 | Binary: 00000101 | Position: 1
n= 8 | Binary: 00001000 | Position: 4
n= 0 | Binary: 0000     | Position: 0

explanation:-
12 in binary: 1100
Rightmost set bit is at position 3 (counting from right, 1-indexed)

Step 1: Isolate rightmost set bit using n & (-n)
  12 = 1100
  -12 in two's complement:
    Flip: ~1100 = 0011
    Add 1: 0011 + 1 = 0100
  
  12 & (-12) = 1100 & 0100 = 0100 = 4

Step 2: Count how many times to shift right to get to position
  0100 >> 1 = 0010 (position++)
  0010 >> 1 = 0001 (position++)
  0001 = 1, stop
  
  position = 2, but we need 1-indexed, so answer = 2 + 1 = 3 ✓

I use n & (-n) to isolate the rightmost set bit.
Why? Because -n flips all bits and adds 1 (two's complement), so when you AND them, only the rightmost 1 survives.
Then I shift that isolated bit right until it becomes 1, counting iterations to find the position.

// ============================================================================
// PROBLEM 10: Add Two Numbers Without Using + Operator
// ============================================================================

/*
Problem: Add two integers without using arithmetic operators.

Algorithm/Logic:
1. Use XOR for sum without carry: a ^ b
2. Use AND and shift for carry: (a & b) << 1
3. Repeat until carry becomes 0
4. Based on how binary addition works

Time Complexity: O(log n) - number of bits
Space Complexity: O(1)
*/

int addWithoutPlus(int a, int b) {
    printf("Debug: Adding %d and %d without using + operator\n", a, b);
    
    while (b != 0) {
        printf("Debug: a = %d, b = %d\n", a, b);
        
        // Calculate carry
        int carry = (a & b) << 1;
        printf("Debug: carry = (a & b) << 1 = (%d & %d) << 1 = %d\n", 
               a, b, carry);
        
        // Calculate sum without carry
        int sum = a ^ b;
        printf("Debug: sum = a ^ b = %d ^ %d = %d\n", a, b, sum);
        
        // Update a and b
        a = sum;
        b = carry;
        
        printf("Debug: Updated - a = %d, b = %d\n", a, b);
        printf("---\n");
    }
    
    printf("Debug: Final result = %d\n", a);
    return a;
}

void testAddWithoutPlus() {
    printf("=== PROBLEM 10: Add Without + Operator ===\n");
    
    int testCases[][2] = {{15, 32}, {7, 3}, {-5, 3}, {0, 42}};
    int numTests = sizeof(testCases) / sizeof(testCases[0]);
    
    for (int i = 0; i < numTests; i++) {
        printf("\nTest %d:\n", i+1);
        int result = addWithoutPlus(testCases[i][0], testCases[i][1]);
        printf("Result: %d + %d = %d\n", testCases[i][0], testCases[i][1], result);
        printf("Verification: %d (correct answer)\n", testCases[i][0] + testCases[i][1]);
    }
    printf("\n");
}

// ============================================================================
// PROBLEM 11: Multiply and Divide by Powers of 2
// ============================================================================

/*
Problem: Multiply/divide by powers of 2 using bit shifts.

Algorithm/Logic:
1. Multiply by 2^k: Left shift by k positions (n << k)
2. Divide by 2^k: Right shift by k positions (n >> k)
3. Much faster than multiplication/division operators

Time Complexity: O(1)
Space Complexity: O(1)
*/

int multiplyByPowerOf2(int n, int power) {
    printf("Debug: Multiplying %d by 2^%d using left shift\n", n, power);
    
    int result = n << power;
    printf("Debug: %d << %d = %d\n", n, power, result);
    printf("Debug: Verification: %d * %d = %d\n", n, 1 << power, n * (1 << power));
    
    return result;
}

int divideByPowerOf2(int n, int power) {
    printf("Debug: Dividing %d by 2^%d using right shift\n", n, power);
    
    int result = n >> power;
    printf("Debug: %d >> %d = %d\n", n, power, result);
    printf("Debug: Verification: %d / %d = %d\n", n, 1 << power, n / (1 << power));
    
    return result;
}

void testMultiplyDividePowerOf2() {
    printf("=== PROBLEM 11: Multiply/Divide by Powers of 2 ===\n");
    
    printf("\n--- Multiplication Tests ---\n");
    int multiplyTests[][2] = {{5, 2}, {7, 3}, {15, 1}};
    int numMultTests = sizeof(multiplyTests) / sizeof(multiplyTests[0]);
    
    for (int i = 0; i < numMultTests; i++) {
        printf("\nMultiply Test %d:\n", i+1);
        int result = multiplyByPowerOf2(multiplyTests[i][0], multiplyTests[i][1]);
        printf("Result: %d\n", result);
    }
    
    printf("\n--- Division Tests ---\n");
    int divideTests[][2] = {{20, 2}, {64, 3}, {100, 1}};
    int numDivTests = sizeof(divideTests) / sizeof(divideTests[0]);
    
    for (int i = 0; i < numDivTests; i++) {
        printf("\nDivide Test %d:\n", i+1);
        int result = divideByPowerOf2(divideTests[i][0], divideTests[i][1]);
        printf("Result: %d\n", result);
    }
    printf("\n");
}

// ============================================================================
// PROBLEM 12: Find Missing Number Using XOR
// ============================================================================

/*
Problem: Array contains numbers 1 to n, but one number is missing. Find it using XOR.

Algorithm/Logic:
1. XOR all numbers from 1 to n
2. XOR all numbers in the array  
3. XOR the two results to get missing number
4. Works because a ^ a = 0, and missing number appears only once

Time Complexity: O(n)
Space Complexity: O(1)
*/

int findMissingNumberXOR(int arr[], int n) {
    printf("Debug: Finding missing number using XOR\n");
    printf("Debug: Array should contain numbers 1 to %d\n", n+1);
    printf("Debug: Given array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    
    // XOR all numbers from 1 to n+1
    int xor1 = 0;
    for (int i = 1; i <= n+1; i++) {
        xor1 ^= i;
        printf("Debug: XOR1 with %d = %d\n", i, xor1);
    }
    printf("Debug: XOR of numbers 1 to %d = %d\n", n+1, xor1);
    
    // XOR all numbers in array
    int xor2 = 0;
    for (int i = 0; i < n; i++) {
        xor2 ^= arr[i];
        printf("Debug: XOR2 with %d = %d\n", arr[i], xor2);
    }
    printf("Debug: XOR of array elements = %d\n", xor2);
    
    // Missing number is XOR of both results
    int missing = xor1 ^ xor2;
    printf("Debug: Missing number = %d ^ %d = %d\n", xor1, xor2, missing);
    
    return missing;
}

void testFindMissingNumberXOR() {
    printf("=== PROBLEM 12: Find Missing Number Using XOR ===\n");
    
    // Test 1: Missing 4 from [1,2,3,5]
    int test1[] = {1, 2, 3, 5};
    printf("\nTest 1:\n");
    int result1 = findMissingNumberXOR(test1, 4);
    printf("Result: Missing number = %d\n", result1);
    
    // Test 2: Missing 2 from [1,3,4,5,6]  
    int test2[] = {1, 3, 4, 5, 6};
    printf("\nTest 2:\n");
    int result2 = findMissingNumberXOR(test2, 5);
    printf("Result: Missing number = %d\n", result2);
    
    printf("\n");
}

// ============================================================================
// MAIN FUNCTION - RUN ALL TESTS
// ============================================================================

int main() {
    printf("CAPGEMINI BIT MANIPULATION PROBLEMS\n");
    printf("===================================\n\n");
    
    testPowerOfTwo();
    testCountSetBits();
    testFindSingleElement();
    testSwapWithoutTemp();
    testBitOperations();
    testFindTwoNonRepeating();
    testReverseBits();
    testIsEven();
    testPositionOfRightmostSetBit();
    testAddWithoutPlus();
    testMultiplyDividePowerOf2();
    testFindMissingNumberXOR();
    
    printf("All bit manipulation problems completed!\n");
    printf("Practice these patterns for your Capgemini interview!\n");
    
    return 0;
}
```

## Compilation Instructions:
```bash
gcc -o bit_manipulation bit_manipulation.c
./bit_manipulation
```

## Quick Reference - Bit Manipulation Tricks:

### **Common Bit Operations:**
- **Check if power of 2:** `(n & (n-1)) == 0`
- **Get rightmost set bit:** `n & (-n)`
- **Turn off rightmost set bit:** `n & (n-1)`
- **Check if bit i is set:** `(n >> i) & 1`
- **Set bit i:** `n | (1 << i)`
- **Clear bit i:** `n & (~(1 << i))`
- **Toggle bit i:** `n ^ (1 << i)`

### **XOR Properties:**
- **a ^ a = 0** (same numbers cancel out)
- **a ^ 0 = a** (XOR with 0 gives original)
- **Commutative:** a ^ b = b ^ a
- **Associative:** (a ^ b) ^ c = a ^ (b ^ c)

### **Shift Operations:**
- **Left shift:** `n << k` = multiply by 2^k
- **Right shift:** `n >> k` = divide by 2^k
- **Arithmetic vs Logical shifts** for negative numbers

### **Two's Complement:**
- **-n = ~n + 1** (flip all bits and add 1)
- **n & (-n)** isolates rightmost set bit

Each problem includes:
✅ **Detailed problem statement**
✅ **Algorithm explanation with examples**  
✅ **Step-by-step debug output**
✅ **Multiple test cases**
✅ **Time/Space complexity analysis**
✅ **Interview tips and variations**

**Master these patterns and you'll ace the bit manipulation section!** 🚀
