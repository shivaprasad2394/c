# Capgemini Bit Manipulation Problems - Complete Solutions

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
2. If n is power of 2, then (n & (n-1)) == 0
3. Also handle edge case: n > 0

Examples:
- 4 (100) & 3 (011) = 000 ✓
- 8 (1000) & 7 (0111) = 0000 ✓
- 6 (110) & 5 (101) = 100 ✗

Time Complexity: O(1)
Space Complexity: O(1)
*/

bool isPowerOfTwo(int n) {
    printf("Debug: Checking if %d is power of 2\n", n);
    printf("Debug: Binary of %d = ", n);
    
    // Print binary representation
    for (int i = 31; i >= 0; i--) {
        printf("%d", (n >> i) & 1);
        if (i % 4 == 0 && i > 0) printf(" ");
    }
    printf("\n");
    
    if (n <= 0) {
        printf("Debug: %d is not positive, so not power of 2\n", n);
        return false;
    }
    
    int result = n & (n - 1);
    printf("Debug: %d & %d = %d\n", n, n-1, result);
    
    bool isPower = (result == 0);
    printf("Debug: %d is %s power of 2\n", n, isPower ? "a" : "not a");
    
    return isPower;
}

void testPowerOfTwo() {
    printf("=== PROBLEM 1: Check Power of 2 ===\n");
    
    int testCases[] = {1, 2, 4, 6, 8, 15, 16, 32};
    int numTests = sizeof(testCases) / sizeof(testCases[0]);
    
    for (int i = 0; i < numTests; i++) {
        printf("\nTest %d: %d\n", i+1, testCases[i]);
        bool result = isPowerOfTwo(testCases[i]);
        printf("Result: %s\n", result ? "True" : "False");
    }
    printf("\n");
}

// ============================================================================
// PROBLEM 2: Count Set Bits (Number of 1s)
// ============================================================================

/*
Problem: Count the number of 1 bits in binary representation of a number.

Algorithm/Logic Methods:
1. Brian Kernighan's Algorithm: n & (n-1) removes rightmost set bit
2. Built-in function: __builtin_popcount()
3. Lookup table method
4. Simple method: Check each bit position

Time Complexity: O(log n) or O(number of set bits)
Space Complexity: O(1)
*/

int countSetBits(int n) {
    printf("Debug: Counting set bits in %d\n", n);
    printf("Debug: Binary representation: ");
    
    // Print binary
    for (int i = 31; i >= 0; i--) {
        int bit = (n >> i) & 1;
        printf("%d", bit);
        if (i % 4 == 0 && i > 0) printf(" ");
    }
    printf("\n");
    
    // Method 1: Brian Kernighan's Algorithm
    int count = 0;
    int temp = n;
    
    while (temp) {
        printf("Debug: temp = %d, temp & (temp-1) = %d\n", temp, temp & (temp-1));
        temp = temp & (temp - 1);  // Remove rightmost set bit
        count++;
    }
    
    printf("Debug: Total set bits = %d\n", count);
    return count;
}

int countSetBitsSimple(int n) {
    printf("Debug: Counting set bits using simple method for %d\n", n);
    
    int count = 0;
    for (int i = 0; i < 32; i++) {
        if (n & (1 << i)) {
            printf("Debug: Bit at position %d is set\n", i);
            count++;
        }
    }
    
    return count;
}

void testCountSetBits() {
    printf("=== PROBLEM 2: Count Set Bits ===\n");
    
    int testCases[] = {7, 15, 255, 1023, 0};
    int numTests = sizeof(testCases) / sizeof(testCases[0]);
    
    for (int i = 0; i < numTests; i++) {
        printf("\nTest %d: %d\n", i+1, testCases[i]);
        
        printf("Method 1 (Kernighan's):\n");
        int result1 = countSetBits(testCases[i]);
        
        printf("Method 2 (Simple):\n");
        int result2 = countSetBitsSimple(testCases[i]);
        
        printf("Results: %d (both methods should match)\n", result1);
    }
    printf("\n");
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
// PROBLEM 5: Check, Set, Clear, Toggle Bit Operations
// ============================================================================

/*
Problem: Implement basic bit manipulation operations at specific positions.

Algorithms:
1. Check bit at position i: (n >> i) & 1
2. Set bit at position i: n | (1 << i)
3. Clear bit at position i: n & (~(1 << i))
4. Toggle bit at position i: n ^ (1 << i)

Time Complexity: O(1) for each operation
Space Complexity: O(1)
*/

bool checkBit(int n, int pos) {
    printf("Debug: Checking bit at position %d in number %d\n", pos, n);
    
    int mask = 1 << pos;
    printf("Debug: Mask = 1 << %d = %d\n", pos, mask);
    
    int result = n & mask;
    printf("Debug: %d & %d = %d\n", n, mask, result);
    
    bool isSet = (result != 0);
    printf("Debug: Bit at position %d is %s\n", pos, isSet ? "SET" : "NOT SET");
    
    return isSet;
}

int setBit(int n, int pos) {
    printf("Debug: Setting bit at position %d in number %d\n", pos, n);
    
    int mask = 1 << pos;
    printf("Debug: Mask = 1 << %d = %d\n", pos, mask);
    
    int result = n | mask;
    printf("Debug: %d | %d = %d\n", n, mask, result);
    
    return result;
}

int clearBit(int n, int pos) {
    printf("Debug: Clearing bit at position %d in number %d\n", pos, n);
    
    int mask = 1 << pos;
    printf("Debug: Mask = 1 << %d = %d\n", pos, mask);
    
    int invMask = ~mask;
    printf("Debug: ~mask = ~%d = %d\n", mask, invMask);
    
    int result = n & invMask;
    printf("Debug: %d & %d = %d\n", n, invMask, result);
    
    return result;
}

int toggleBit(int n, int pos) {
    printf("Debug: Toggling bit at position %d in number %d\n", pos, n);
    
    int mask = 1 << pos;
    printf("Debug: Mask = 1 << %d = %d\n", pos, mask);
    
    int result = n ^ mask;
    printf("Debug: %d ^ %d = %d\n", n, mask, result);
    
    return result;
}

void printBinary(int n, char* label) {
    printf("%s: ", label);
    for (int i = 7; i >= 0; i--) {
        printf("%d", (n >> i) & 1);
    }
    printf(" (%d)\n", n);
}

void testBitOperations() {
    printf("=== PROBLEM 5: Bit Operations ===\n");
    
    int n = 12;  // Binary: 00001100
    int pos = 1;
    
    printBinary(n, "Original");
    
    printf("\n--- Check Bit ---\n");
    bool isSet = checkBit(n, pos);
    printf("Bit at position %d: %s\n", pos, isSet ? "SET" : "NOT SET");
    
    printf("\n--- Set Bit ---\n");
    int afterSet = setBit(n, pos);
    printBinary(afterSet, "After SET");
    
    printf("\n--- Clear Bit ---\n");
    int afterClear = clearBit(n, 2);  // Clear bit at position 2
    printBinary(afterClear, "After CLEAR");
    
    printf("\n--- Toggle Bit ---\n");
    int afterToggle = toggleBit(n, pos);
    printBinary(afterToggle, "After TOGGLE");
    
    printf("\n");
}

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
// PROBLEM 7: Reverse Bits of a Number
// ============================================================================

/*
Problem: Reverse the binary representation of a 32-bit unsigned integer.

Algorithm/Logic:
1. Process each bit from right to left
2. For each bit, add it to result and shift result left
3. Alternative: Use lookup table for faster execution

Time Complexity: O(log n) or O(32) = O(1)
Space Complexity: O(1)
*/

unsigned int reverseBits(unsigned int n) {
    printf("Debug: Reversing bits of %u\n", n);
    
    // Print original binary
    printf("Debug: Original binary: ");
    for (int i = 31; i >= 0; i--) {
        printf("%d", (n >> i) & 1);
    }
    printf("\n");
    
    unsigned int result = 0;
    
    for (int i = 0; i < 32; i++) {
        // Get the rightmost bit of n
        int bit = n & 1;
        
        // Shift result left and add the bit
        result = (result << 1) | bit;
        
        printf("Debug: Bit %d = %d, result = %u\n", i, bit, result);
        
        // Shift n right for next bit
        n >>= 1;
    }
    
    // Print reversed binary
    printf("Debug: Reversed binary: ");
    for (int i = 31; i >= 0; i--) {
        printf("%d", (result >> i) & 1);
    }
    printf("\n");
    
    printf("Debug: Reversed number = %u\n", result);
    return result;
}

void testReverseBits() {
    printf("=== PROBLEM 7: Reverse Bits ===\n");
    
    unsigned int testCases[] = {43261596, 4294967293};
    int numTests = sizeof(testCases) / sizeof(testCases[0]);
    
    for (int i = 0; i < numTests; i++) {
        printf("\nTest %d: Input = %u\n", i+1, testCases[i]);
        unsigned int result = reverseBits(testCases[i]);
        printf("Output = %u\n", result);
    }
    printf("\n");
}

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
Problem: Find position of rightmost set bit (1-indexed).

Algorithm/Logic:
1. Use n & (-n) to isolate rightmost set bit
2. Count position using log2 or bit counting
3. Alternative: Use lookup table

Example: 12 (1100) → rightmost set bit at position 3

Time Complexity: O(log n)
Space Complexity: O(1)
*/

int positionOfRightmostSetBit(int n) {
    printf("Debug: Finding position of rightmost set bit in %d\n", n);
    
    if (n == 0) {
        printf("Debug: Number is 0, no set bits\n");
        return 0;
    }
    
    // Print binary
    printf("Debug: Binary: ");
    for (int i = 31; i >= 0; i--) {
        printf("%d", (n >> i) & 1);
        if (i % 4 == 0 && i > 0) printf(" ");
    }
    printf("\n");
    
    // Method 1: Using n & (-n)
    int rightmostBit = n & (-n);
    printf("Debug: n & (-n) = %d & (%d) = %d\n", n, -n, rightmostBit);
    
    // Count position
    int position = 0;
    while (rightmostBit > 0) {
        rightmostBit >>= 1;
        position++;
    }
    
    printf("Debug: Position of rightmost set bit = %d\n", position);
    return position;
}

void testPositionOfRightmostSetBit() {
    printf("=== PROBLEM 9: Position of Rightmost Set Bit ===\n");
    
    int testCases[] = {12, 18, 5, 8, 0};
    int numTests = sizeof(testCases) / sizeof(testCases[0]);
    
    for (int i = 0; i < numTests; i++) {
        printf("\nTest %d:\n", i+1);
        int result = positionOfRightmostSetBit(testCases[i]);
        printf("Result: Position = %d\n", result);
    }
    printf("\n");
}

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