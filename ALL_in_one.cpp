/*Math based 
1.Digit Extraction
2.Reverse Number
3.Palindrome Number
4.Armstrong Number
5.printDivisors
6.Prime Number Check
7.Euclidean Algorithm for GCD
8. Big Integer Addition

string based 
1. Reverse a String
2. Check for Anagram
3. Longest Palindromic Substring and unique sub string
4. Remove All Duplicates
5. String Compression
6. Check string is a rotation of another string
7.First & second Non-Repeating Character
8.Valid Palindrome
9.Count and Say
10.Check Subsequence
11.reverseWords

Array based
1.Find second largest
2. Move all zeros to the end
3. Rotate array left by d positions
4. Kadane's Algorithm - Maximum subarray sum
5. Remove duplicates from sorted array
6. Find majority element 
7. Find missing number in sequence 0 to n
8. Reverse array in groups of size k
9. Find minimum in rotated sorted array using binary search
10.implement quick sort and binary search
11.Merge two sorted arrays
12.Heap Sort

Trees and list based
1.Binary Search Tree 
2.linked list
3.queue
*/
/*
shivaprasad@anonymous:~/chandu/husband/interview_coding_practice$ gcc -o all_in_one ALL_in_one.cpp
or
shivaprasad@anonymous:~/chandu/husband/interview_coding_practice$ gcc -DC_CODE1=1 -o program ALL_in_one.cpp
shivaprasad@anonymous:~/chandu/husband/interview_coding_practice$ ./program
*/
/*======================string solutions================================*/
#define C_CODE1 1
#define CPP_CODE1 0
#define C_CODE2 0
#define CPP_CODE2 0
#define C_CODE3 0
#define CPP_CODE3 0
#define C_CODE4 0
#define CPP_CODE4 0
#define C_CODE5 0
#define CPP_CODE5 0
#define C_CODE6 0
#define CPP_CODE6 0
#define C_CODE7 0
#define CPP_CODE7 0
#define C_CODE8 0
#define CPP_CODE8 0
#define C_CODE9 0
#define CPP_CODE9 0
#define C_CODE10 0
#define CPP_CODE10 0
#define C_CODE11 0
#define CPP_CODE11 0

/*
1. Reverse a String
Algorithm Steps:
1.Use two pointers: left (start) and right (end)
2.Swap characters at these positions
3.Move pointers towards center until they meet

String: "hello"
Indexes: 0 1 2 3 4

Step 1: swap 'h' and 'o' → "oellh"
left = 1, right = 3

Step 2: swap 'e' and 'l' → "olleh"
left = 2, right = 2

Pointers meet, stop.
Result: "olleh"

*/
#if C_CODE1
#include <stdio.h>
#include <string.h>

void reverseString(char* str) {
    int left = 0;                    // Start pointer at beginning
    int right = strlen(str) - 1;     // End pointer at last character
    
    printf("Original string: %s\n", str);
    printf("Starting reversal process...\n");
    
    // Continue until pointers meet in middle
    while (left < right) {
        printf("Debug: Swapping str[%d]='%c' with str[%d]='%c'\n", 
               left, str[left], right, str[right]);
        
        // Swap characters
        char temp = str[left];
        str[left] = str[right];
        str[right] = temp;
        
        // Move pointers towards center
        left++;
        right--;
    }
    
    printf("Reversal complete!\n");
}

int main() {
    char str[] = "capgemini";
    reverseString(str);
    printf("Final result: %s\n", str);
    return 0;
}
#endif
#if CPP_CODE1
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

void reverseString(string &str) {
    int left = 0;                    // Start pointer
    int right = str.length() - 1;    // End pointer
    
    cout << "Original string: " << str << endl;
    cout << "Starting reversal process..." << endl;
    
    // Loop until pointers meet
    while (left < right) {
        cout << "Debug: Swapping str[" << left << "]='" << str[left] 
             << "' with str[" << right << "]='" << str[right] << "'" << endl;
        
        // Using STL swap function
        swap(str[left], str[right]);
        
        // Move pointers inward
        left++;
        right--;
    }
    
    cout << "Reversal complete!" << endl;
}

int main() {
    string str = "capgemini";
    reverseString(str);
    cout << "Final result: " << str << endl;
    return 0;
} 
#endif
/*================anagram======================*/
#if C_CODE2
/*2. Check for Anagram
Algorithm Steps:
Check if lengths are equal (if not, can't be anagrams)
Count frequency of each character in both strings
Compare frequency arrays .

str1 = "listen"
str2 = "silent"
Lengths are equal (6).
Count frequency:
| Character | str1 Count | str2 Count |
| --------- | ---------- | ---------- |
| l         | 1          | 1          |
| i         | 1          | 1          |
| s         | 1          | 1          |
| t         | 1          | 1          |
| e         | 1          | 1          |
| n         | 1          | 1          |
| --------- | ---------- | ---------- |
*/
#include <stdio.h>
#include <string.h>
#define CHAR_SIZE 256

int isAnagram(char* str1, char* str2) {
    int freq[CHAR_SIZE] = {0};  // Frequency array for all ASCII characters
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    
    printf("Debug: Checking strings '%s' and '%s'\n", str1, str2);
    
    // Check if lengths are different
    if (len1 != len2) {
        printf("Debug: Different lengths (%d vs %d) - Not anagrams\n", len1, len2);
        return 0;
    }
    
    // Count frequencies
    for (int i = 0; i < len1; i++) {
        printf("Debug: Processing char '%c' from str1 and '%c' from str2\n", 
               str1[i], str2[i]);
        
        freq[(unsigned char)str1[i]]++;  // Increment for str1 character
        freq[(unsigned char)str2[i]]--;  // Decrement for str2 character
    }
    
    // Check if all frequencies are zero
    for (int i = 0; i < CHAR_SIZE; i++) {
        if (freq[i] != 0) {
            printf("Debug: Frequency mismatch found for character '%c'\n", (char)i);
            return 0;
        }
    }
    
    printf("Debug: All frequencies match - Strings are anagrams!\n");
    return 1;
}

int main() {
    char str1[] = "listen";
    char str2[] = "silent";
    
    if (isAnagram(str1, str2)) {
        printf("Result: '%s' and '%s' are anagrams\n", str1, str2);
    } else {
        printf("Result: '%s' and '%s' are not anagrams\n", str1, str2);
    }
    
    return 0;
}
#endif
#if CPP_CODE2
#include <iostream>
#include <string>
#include <vector>
using namespace std;

bool isAnagram(string str1, string str2) {
    vector<int> freq(256, 0);  // Frequency vector for ASCII characters
    
    cout << "Debug: Checking strings '" << str1 << "' and '" << str2 << "'" << endl;
    
    // Check lengths first
    if (str1.length() != str2.length()) {
        cout << "Debug: Different lengths - Not anagrams" << endl;
        return false;
    }
    
    // Count character frequencies
    for (int i = 0; i < str1.length(); i++) {
        cout << "Debug: Processing char '" << str1[i] << "' from str1 and '" 
             << str2[i] << "' from str2" << endl;
        
        freq[str1[i]]++;  // Increment for str1
        freq[str2[i]]--;  // Decrement for str2
    }
    
    // Verify all frequencies are zero
    for (int i = 0; i < 256; i++) {
        if (freq[i] != 0) {
            cout << "Debug: Frequency mismatch found" << endl;
            return false;
        }
    }
    
    cout << "Debug: All frequencies match - Anagrams confirmed!" << endl;
    return true;
}

int main() {
    string str1 = "listen";
    string str2 = "silent";
    
    if (isAnagram(str1, str2)) {
        cout << "Result: '" << str1 << "' and '" << str2 << "' are anagrams" << endl;
    } else {
        cout << "Result: '" << str1 << "' and '" << str2 << "' are not anagrams" << endl;
    }
    
    return 0;
} 
#endif
/*========================LPS==================
3. Longest Palindromic Substring
Algorithm Steps:
For each character, expand around it as center
Check for both odd-length (center = i) and even-length (center = i, i+1) palindromes
Keep track of longest palindrome found

String: "babad"

Center at i = 0 (char 'b'):
Odd length palindrome: "b"
Even length palindrome: "" (no match)

Center at i = 1 (char 'a'):
Odd length palindrome: "bab"
Even length palindrome: ""

Center at i = 2 (char 'b'):
Odd length palindrome: "aba"
Even length palindrome: ""

Longest palindrome is "bab" or "aba" (length 3).
*/
#if C_CODE3
#include <stdio.h>
#include <string.h>

void findLongestPalindrome(char* str) {
    int n = strlen(str);
    int maxLen = 1;      // Length of longest palindrome
    int start = 0;       // Starting index of longest palindrome
    
    printf("Debug: Finding longest palindrome in '%s'\n", str);
    
    // Check for palindromes centered at each position
    for (int i = 0; i < n; i++) {
        printf("\nDebug: Checking center at position %d (char '%c')\n", i, str[i]);
        
        // Check for odd-length palindromes (center = i)
        int left = i, right = i;
        while (left >= 0 && right < n && str[left] == str[right]) {
            int currentLen = right - left + 1;
            printf("Debug: Found odd-length palindrome: '%.*s' (length %d)\n", 
                   currentLen, &str[left], currentLen);
            
            if (currentLen > maxLen) {
                start = left;
                maxLen = currentLen;
                printf("Debug: New longest palindrome found!\n");
            }
            left--;   // Expand left
            right++;  // Expand right
        }
        
        // Check for even-length palindromes (center between i and i+1)
        left = i;
        right = i + 1;
        while (left >= 0 && right < n && str[left] == str[right]) {
            int currentLen = right - left + 1;
            printf("Debug: Found even-length palindrome: '%.*s' (length %d)\n", 
                   currentLen, &str[left], currentLen);
            
            if (currentLen > maxLen) {
                start = left;
                maxLen = currentLen;
                printf("Debug: New longest palindrome found!\n");
            }
            left--;   // Expand left
            right++;  // Expand right
        }
    }
    
    printf("\nResult: Longest palindromic substring: '%.*s' (length %d)\n", 
           maxLen, &str[start], maxLen);
}

int main() {
    char str[] = "babad";
    findLongestPalindrome(str);
    return 0;
}
#endif
#if CPP_CODE3
#include <iostream>
#include <string>
using namespace std;

string longestPalindrome(string s) {
    int n = s.length();
    int maxLen = 1;
    int start = 0;
    
    cout << "Debug: Finding longest palindrome in '" << s << "'" << endl;
    
    // Check all possible centers
    for (int i = 0; i < n; i++) {
        cout << "\nDebug: Checking center at position " << i << " (char '" << s[i] << "')" << endl;
        
        // Odd-length palindromes
        int left = i, right = i;
        while (left >= 0 && right < n && s[left] == s[right]) {
            int currentLen = right - left + 1;
            cout << "Debug: Found odd-length palindrome: '" 
                 << s.substr(left, currentLen) << "' (length " << currentLen << ")" << endl;
            
            if (currentLen > maxLen) {
                start = left;
                maxLen = currentLen;
                cout << "Debug: New longest found!" << endl;
            }
            left--;   // Expand outward
            right++;
        }
        
        // Even-length palindromes
        left = i;
        right = i + 1;
        while (left >= 0 && right < n && s[left] == s[right]) {
            int currentLen = right - left + 1;
            cout << "Debug: Found even-length palindrome: '" 
                 << s.substr(left, currentLen) << "' (length " << currentLen << ")" << endl;
            
            if (currentLen > maxLen) {
                start = left;
                maxLen = currentLen;
                cout << "Debug: New longest found!" << endl;
            }
            left--;
            right++;
        }
    }
    
    string result = s.substr(start, maxLen);
    cout << "\nResult: Longest palindromic substring: '" << result << "'" << endl;
    return result;
}

int main() {
    string s = "babad";
    longestPalindrome(s);
    return 0;
}
#endif
/*
============4. Remove All Duplicates===============
Algorithm Steps:
Use a boolean array to track seen characters
Iterate through string, only keep first occurrence of each character

Input: "banana"
Seen: {}

Iterate:
'b': not seen, keep → "b"
'a': not seen, keep → "ba"
'n': not seen, keep → "ban"
'a': seen, skip
'n': seen, skip
'a': seen, skip

Output: "ban"
*/
#if C_CODE4
#include <stdio.h>
#include <string.h>
#define CHAR_SIZE 256

void removeDuplicates(char* str) {
    int seen[CHAR_SIZE] = {0};  // Track seen characters
    int writeIndex = 0;         // Position to write next unique character
    int len = strlen(str);
    
    printf("Debug: Removing duplicates from '%s'\n", str);
    
    // Process each character
    for (int i = 0; i < len; i++) {
        unsigned char ch = (unsigned char)str[i];
        
        printf("Debug: Processing character '%c' at position %d\n", str[i], i);
        
        // If character not seen before
        if (!seen[ch]) {
            printf("Debug: First occurrence of '%c', keeping it at position %d\n", 
                   str[i], writeIndex);
            
            str[writeIndex] = str[i];  // Keep the character
            writeIndex++;
            seen[ch] = 1;              // Mark as seen
        } else {
            printf("Debug: '%c' already seen, skipping\n", str[i]);
        }
    }
    
    str[writeIndex] = '\0';  // Null terminate the result
    printf("Debug: Final string after removing duplicates: '%s'\n", str);
}

int main() {
    char str[] = "programming";
    printf("Original string: %s\n", str);
    removeDuplicates(str);
    printf("Result: %s\n", str);
    return 0;
}
#endif
#if CPP_CODE4
#include <iostream>
#include <string>
#include <vector>
using namespace std;

string removeDuplicates(string str) {
    vector<bool> seen(256, false);  // Track seen characters
    string result = "";
    
    cout << "Debug: Removing duplicates from '" << str << "'" << endl;
    
    // Process each character
    for (int i = 0; i < str.length(); i++) {
        char ch = str[i];
        
        cout << "Debug: Processing character '" << ch << "' at position " << i << endl;
        
        // If not seen before, add to result
        if (!seen[(unsigned char)ch]) {
            cout << "Debug: First occurrence of '" << ch << "', adding to result" << endl;
            result += ch;
            seen[(unsigned char)ch] = true;
        } else {
            cout << "Debug: '" << ch << "' already seen, skipping" << endl;
        }
    }
    
    cout << "Debug: Final result: '" << result << "'" << endl;
    return result;
}

int main() {
    string str = "programming";
    cout << "Original string: " << str << endl;
    string result = removeDuplicates(str);
    cout << "Result: " << result << endl;
    return 0;
}
#endif
/*
==============5. String Compression===================
Algorithm Steps:
Count consecutive occurrences of each character

Append character followed by its count
🧠 Algorithm Steps:
Initialize a count = 1 for the first character.
Iterate through the string from the second character onward:
If current character == previous character, increment count.

Else:
Append previous character and count to output.
Reset count = 1 for current character.
After the loop, append the last character and its count.

🔧 Example:

Input: "aaabbc"
'a' repeated 3 times → "a3"
'b' repeated 2 times → "b2"
'c' repeated 1 time → "c1"

Output: "a3b2c1"
*/
#if C_CODE5
#include <stdio.h>
#include <string.h>

void compressString(char* str) {
    int len = strlen(str);
    char result[1000] = "";  // Result string
    int resIndex = 0;
    
    printf("Debug: Compressing string '%s'\n", str);
    
    // Process each character
    for (int i = 0; i < len; ) {
        char currentChar = str[i];
        int count = 1;
        
        printf("Debug: Starting count for character '%c' at position %d\n", currentChar, i);
        
        // Count consecutive occurrences
        while (i + count < len && str[i + count] == currentChar) {
            count++;
            printf("Debug: Found another '%c', count is now %d\n", currentChar, count);
        }
        
        // Add character to result
        result[resIndex++] = currentChar;
        
        // Add count to result
        if (count > 1) {
            // Convert count to string and append
            char countStr[10];
            sprintf(countStr, "%d", count);
            for (int j = 0; countStr[j]; j++) {
                result[resIndex++] = countStr[j];
            }
            printf("Debug: Added '%c%d' to result\n", currentChar, count);
        } else {
            printf("Debug: Added '%c' to result (count = 1, not showing count)\n", currentChar);
        }
        
        // Move to next different character
        i += count;
    }
    
    result[resIndex] = '\0';
    printf("Debug: Compression complete\n");
    printf("Result: %s\n", result);
}

int main() {
    char str[] = "aabcccccaaa";
    printf("Original: %s\n", str);
    compressString(str);
    return 0;
}
#endif
#if CPP_CODE5
#include <iostream>
#include <string>
using namespace std;

string compressString(string str) {
    string result = "";
    int len = str.length();
    
    cout << "Debug: Compressing string '" << str << "'" << endl;
    
    // Process each character group
    for (int i = 0; i < len; ) {
        char currentChar = str[i];
        int count = 1;
        
        cout << "Debug: Starting count for character '" << currentChar << "' at position " << i << endl;
        
        // Count consecutive characters
        while (i + count < len && str[i + count] == currentChar) {
            count++;
            cout << "Debug: Found another '" << currentChar << "', count is now " << count << endl;
        }
        
        // Append character and count to result
        result += currentChar;
        result += to_string(count);
        
        cout << "Debug: Added '" << currentChar << count << "' to result" << endl;
        
        // Move to next group
        i += count;
    }
    
    cout << "Debug: Compression complete" << endl;
    return result;
}

int main() {
    string str = "aabcccccaaa";
    cout << "Original: " << str << endl;
    string compressed = compressString(str);
    cout << "Result: " << compressed << endl;
    return 0;
}
#endif
/*
============6. Check String Rotation=========================
Algorithm Steps:
Check if lengths are equal
Concatenate second string with itself
Check if first string is substring of concatenated string

str1 = "erbottlewat"
str2 = "waterbottle"

Concat str2 with itself:
"waterbottlewaterbottle"

Check if "erbottlewat" is substring:
Yes → str1 is rotation of str2.
*/
#if C_CODE6
#include <stdio.h>
#include <string.h>

int isRotation(char* str1, char* str2) {
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    
    printf("Debug: Checking if '%s' is rotation of '%s'\n", str2, str1);
    
    // Check if lengths are equal
    if (len1 != len2) {
        printf("Debug: Different lengths (%d vs %d) - cannot be rotation\n", len1, len2);
        return 0;
    }
    
    // Create concatenated string: str2 + str2
    char concatenated[500];
    strcpy(concatenated, str2);
    strcat(concatenated, str2);
    
    printf("Debug: Concatenated string: '%s'\n", concatenated);
    printf("Debug: Looking for '%s' in concatenated string\n", str1);
    
    // Check if str1 is substring of concatenated string
    char* found = strstr(concatenated, str1);
    if (found != NULL) {
        printf("Debug: Found '%s' at position %ld in concatenated string\n", 
               str1, found - concatenated);
        return 1;
    } else {
        printf("Debug: '%s' not found in concatenated string\n", str1);
        return 0;
    }
}

int main() {
    char str1[] = "waterbottle";
    char str2[] = "erbottlewat";
    
    if (isRotation(str1, str2)) {
        printf("Result: '%s' is a rotation of '%s'\n", str2, str1);
    } else {
        printf("Result: '%s' is NOT a rotation of '%s'\n", str2, str1);
    }
    
    return 0;
}
#endif
#if CPP_CODE6
#include <iostream>
#include <string>
using namespace std;

bool isRotation(string str1, string str2) {
    cout << "Debug: Checking if '" << str2 << "' is rotation of '" << str1 << "'" << endl;
    
    // Check lengths first
    if (str1.length() != str2.length()) {
        cout << "Debug: Different lengths - cannot be rotation" << endl;
        return false;
    }
    
    // Create concatenated string
    string concatenated = str2 + str2;
    cout << "Debug: Concatenated string: '" << concatenated << "'" << endl;
    cout << "Debug: Looking for '" << str1 << "' in concatenated string" << endl;
    
    // Check if str1 is substring of concatenated
    size_t pos = concatenated.find(str1);
    if (pos != string::npos) {
        cout << "Debug: Found '" << str1 << "' at position " << pos << endl;
        return true;
    } else {
        cout << "Debug: '" << str1 << "' not found in concatenated string" << endl;
        return false;
    }
}

int main() {
    string str1 = "waterbottle";
    string str2 = "erbottlewat";
    
    if (isRotation(str1, str2)) {
        cout << "Result: '" << str2 << "' is a rotation of '" << str1 << "'" << endl;
    } else {
        cout << "Result: '" << str2 << "' is NOT a rotation of '" << str1 << "'" << endl;
    }
    
    return 0;
}
#endif
/*
===============7. First & Second Non-Repeating Character===============
Algorithm Steps:
Count frequency of all characters

Find first two characters with frequency = 1
*/

#if C_CODE7
#include <stdio.h>
#include <string.h>
#define CHAR_SIZE 256

void findNonRepeatingChars(char* str) {
    int freq[CHAR_SIZE] = {0};
    int len = strlen(str);
    
    printf("Debug: Finding non-repeating characters in '%s'\n", str);
    
    // Count frequency of each character
    for (int i = 0; i < len; i++) {
        unsigned char ch = (unsigned char)str[i];
        freq[ch]++;
        printf("Debug: Character '%c' frequency is now %d\n", str[i], freq[ch]);
    }
    
    // Find first and second non-repeating characters
    int found = 0;
    for (int i = 0; i < len && found < 2; i++) {
        unsigned char ch = (unsigned char)str[i];
        
        printf("Debug: Checking character '%c' at position %d, frequency = %d\n", 
               str[i], i, freq[ch]);
        
        if (freq[ch] == 1) {
            found++;
            printf("Debug: Found %s non-repeating character: '%c'\n", 
                   (found == 1) ? "first" : "second", str[i]);
            
            if (found == 1) {
                printf("First non-repeating character: %c\n", str[i]);
            } else {
                printf("Second non-repeating character: %c\n", str[i]);
            }
        }
    }
    
    if (found < 2) {
        printf("Debug: Only found %d non-repeating character(s)\n", found);
    }
}

int main() {
    char str[] = "abccba";
    findNonRepeatingChars(str);
    return 0;
}
#endif
#if CPP_CODE7
#include <iostream>
#include <string>
#include <vector>
using namespace std;

void findNonRepeatingChars(string str) {
    vector<int> freq(256, 0);
    
    cout << "Debug: Finding non-repeating characters in '" << str << "'" << endl;
    
    // Count frequencies
    for (char ch : str) {
        freq[(unsigned char)ch]++;
        cout << "Debug: Character '" << ch << "' frequency is now " << freq[(unsigned char)ch] << endl;
    }
    
    // Find first two non-repeating characters
    int found = 0;
    for (int i = 0; i < str.length() && found < 2; i++) {
        char ch = str[i];
        
        cout << "Debug: Checking character '" << ch << "' at position " << i 
             << ", frequency = " << freq[(unsigned char)ch] << endl;
        
        if (freq[(unsigned char)ch] == 1) {
            found++;
            cout << "Debug: Found " << (found == 1 ? "first" : "second") 
                 << " non-repeating character: '" << ch << "'" << endl;
            
            if (found == 1) {
                cout << "First non-repeating character: " << ch << endl;
            } else {
                cout << "Second non-repeating character: " << ch << endl;
            }
        }
    }
    
    if (found < 2) {
        cout << "Debug: Only found " << found << " non-repeating character(s)" << endl;
    }
}

int main() {
    string str = "abccba";
    findNonRepeatingChars(str);
    return 0;
}
#endif

/*
8. Valid Palindrome
Algorithm Steps:
Use two pointers from both ends

Skip non-alphanumeric characters

Compare characters (case-insensitive)
*/
#if C_CODE8
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int isPalindrome(char* str) {
    int left = 0;
    int right = strlen(str) - 1;
    
    printf("Debug: Checking if '%s' is a valid palindrome\n", str);
    
    // Use two pointers approach
    while (left < right) {
        printf("Debug: Comparing positions %d and %d\n", left, right);
        
        // Skip non-alphanumeric from left
        while (left < right && !isalnum(str[left])) {
            printf("Debug: Skipping non-alphanumeric '%c' at position %d\n", str[left], left);
            left++;
        }
        
        // Skip non-alphanumeric from right
        while (left < right && !isalnum(str[right])) {
            printf("Debug: Skipping non-alphanumeric '%c' at position %d\n", str[right], right);
            right--;
        }
        
        // Compare characters (case insensitive)
        char leftChar = tolower(str[left]);
        char rightChar = tolower(str[right]);
        
        printf("Debug: Comparing '%c' (from pos %d) with '%c' (from pos %d)\n", 
               leftChar, left, rightChar, right);
        
        if (leftChar != rightChar) {
            printf("Debug: Mismatch found - not a palindrome\n");
            return 0;
        }
        
        printf("Debug: Characters match, moving inward\n");
        left++;
        right--;
    }
    
    printf("Debug: All characters matched - valid palindrome!\n");
    return 1;
}

int main() {
    char str[] = "A man, a plan, a canal: Panama";
    
    if (isPalindrome(str)) {
        printf("Result: '%s' is a valid palindrome\n", str);
    } else {
        printf("Result: '%s' is not a valid palindrome\n", str);
    }
    
    return 0;
}
#endif
#if CPP_CODE8
#include <iostream>
#include <string>
#include <cctype>
using namespace std;

bool isPalindrome(string str) {
    int left = 0;
    int right = str.length() - 1;
    
    cout << "Debug: Checking if '" << str << "' is a valid palindrome" << endl;
    
    // Two pointers approach
    while (left < right) {
        cout << "Debug: Comparing positions " << left << " and " << right << endl;
        
        // Skip non-alphanumeric from left
        while (left < right && !isalnum(str[left])) {
            cout << "Debug: Skipping non-alphanumeric '" << str[left] << "' at position " << left << endl;
            left++;
        }
        
        // Skip non-alphanumeric from right
        while (left < right && !isalnum(str[right])) {
            cout << "Debug: Skipping non-alphanumeric '" << str[right] << "' at position " << right << endl;
            right--;
        }
        
        // Compare characters (case insensitive)
        char leftChar = tolower(str[left]);
        char rightChar = tolower(str[right]);
        
        cout << "Debug: Comparing '" << leftChar << "' (from pos " << left 
             << ") with '" << rightChar << "' (from pos " << right << ")" << endl;
        
        if (leftChar != rightChar) {
            cout << "Debug: Mismatch found - not a palindrome" << endl;
            return false;
        }
        
        cout << "Debug: Characters match, moving inward" << endl;
        left++;
        right--;
    }
    
    cout << "Debug: All characters matched - valid palindrome!" << endl;
    return true;
}

int main() {
    string str = "A man, a plan, a canal: Panama";
    
    if (isPalindrome(str)) {
        cout << "Result: '" << str << "' is a valid palindrome" << endl;
    } else {
        cout << "Result: '" << str << "' is not a valid palindrome" << endl;
    }
    
    return 0;
}
#endif

/*
9. Count and Say
Algorithm Steps:
Start with "1"
For each iteration, read the previous term and describe it
Count consecutive digits and say the count followed by the digit

🧠 Algorithm Logic:
Start with the string "1" (this is the 1st term).
For each iteration from 2 to n:
Read the previous term digit by digit.
Count consecutive identical digits.
Construct the new string by saying the count followed by the digit.
Repeat until the n-th term is built.

🔧 Example (First 5 terms):
| Term | Sequence   | Explanation          |
| ---- | ---------- | -------------------- |
| 1    | `"1"`      | starting point       |
| 2    | `"11"`     | one 1                |
| 3    | `"21"`     | two 1s               |
| 4    | `"1211"`   | one 2, one 1         |
| 5    | `"111221"` | one 1, one 2, two 1s |
| ---- | ---------- | -------------------- |
🧾 Detailed Breakdown: From "21" → "1211"
Start with "21"
Read left to right:
One 2 → "12"
One 1 → "11"

Result: "1211"
*/
#if C_CODE9
#include <stdio.h>
#include <string.h>

void countAndSay(int n) {
    char current[1000] = "1";  // Start with "1"
    char next;
    
    printf("Debug: Generating Count and Say sequence for n = %d\n", n);
    printf("Term 1: %s\n", current);
    
    // Generate n terms
    for (int term = 2; term <= n; term++) {
        int nextIndex = 0;
        int len = strlen(current);
        
        printf("Debug: Processing term %d: '%s'\n", term - 1, current);
        
        // Process each group of consecutive characters
        for (int i = 0; i < len; ) {
            char digit = current[i];
            int count = 1;
            
            printf("Debug: Starting count for digit '%c' at position %d\n", digit, i);
            
            // Count consecutive occurrences
            while (i + count < len && current[i + count] == digit) {
                count++;
                printf("Debug: Found another '%c', count is now %d\n", digit, count);
            }
            
            // Add count and digit to next string
            next[nextIndex++] = '0' + count;  // Convert count to character
            next[nextIndex++] = digit;
            
            printf("Debug: Added '%d%c' to next term\n", count, digit);
            
            // Move to next different digit
            i += count;
        }
        
        next[nextIndex] = '\0';  // Null terminate
        strcpy(current, next);   // Update current for next iteration
        
        printf("Term %d: %s\n", term, current);
    }
}

int main() {
    int n = 5;
    countAndSay(n);
    return 0;
}
#endif
#if CPP_CODE9
#include <iostream>
#include <string>
using namespace std;

string countAndSay(int n) {
    string current = "1";  // Start with "1"
    
    cout << "Debug: Generating Count and Say sequence for n = " << n << endl;
    cout << "Term 1: " << current << endl;
    
    // Generate terms from 2 to n
    for (int term = 2; term <= n; term++) {
        string next = "";
        int len = current.length();
        
        cout << "Debug: Processing term " << (term - 1) << ": '" << current << "'" << endl;
        
        // Process each group of consecutive characters
        for (int i = 0; i < len; ) {
            char digit = current[i];
            int count = 1;
            
            cout << "Debug: Starting count for digit '" << digit << "' at position " << i << endl;
            
            // Count consecutive digits
            while (i + count < len && current[i + count] == digit) {
                count++;
                cout << "Debug: Found another '" << digit << "', count is now " << count << endl;
            }
            
            // Append count and digit to result
            next += to_string(count);
            next += digit;
            
            cout << "Debug: Added '" << count << digit << "' to next term" << endl;
            
            // Move to next group
            i += count;
        }
        
        current = next;  // Update for next iteration
        cout << "Term " << term << ": " << current << endl;
    }
    
    return current;
}

int main() {
    int n = 5;
    string result = countAndSay(n);
    cout << "Final result: " << result << endl;
    return 0;
}
#endif
/*
10. Check Subsequence
Algorithm Steps:
Use two pointers - one for each string

If characters match, advance both pointers

If not, advance only the main string pointer
*/
#if C_CODE10
#include <stdio.h>
#include <string.h>

int isSubsequence(char* s, char* t) {
    int i = 0;  // Pointer for main string s
    int j = 0;  // Pointer for subsequence t
    int sLen = strlen(s);
    int tLen = strlen(t);
    
    printf("Debug: Checking if '%s' is subsequence of '%s'\n", t, s);
    
    // Traverse both strings
    while (i < sLen && j < tLen) {
        printf("Debug: Comparing s[%d]='%c' with t[%d]='%c'\n", i, s[i], j, t[j]);
        
        if (s[i] == t[j]) {
            printf("Debug: Characters match! Moving both pointers\n");
            j++;  // Move subsequence pointer
        } else {
            printf("Debug: Characters don't match, moving main string pointer only\n");
        }
        
        i++;  // Always move main string pointer
    }
    
    // Check if we've matched all characters of subsequence
    if (j == tLen) {
        printf("Debug: All characters of subsequence matched!\n");
        return 1;
    } else {
        printf("Debug: Only matched %d out of %d characters\n", j, tLen);
        return 0;
    }
}

int main() {
    char s[] = "capgemini";
    char t[] = "cgm";
    
    if (isSubsequence(s, t)) {
        printf("Result: '%s' is a subsequence of '%s'\n", t, s);
    } else {
        printf("Result: '%s' is NOT a subsequence of '%s'\n", t, s);
    }
    
    return 0;
}
#endif
#if CPP_CODE10
#include <iostream>
#include <string>
using namespace std;

bool isSubsequence(string s, string t) {
    int i = 0;  // Pointer for main string s
    int j = 0;  // Pointer for subsequence t
    
    cout << "Debug: Checking if '" << t << "' is subsequence of '" << s << "'" << endl;
    
    // Traverse both strings
    while (i < s.length() && j < t.length()) {
        cout << "Debug: Comparing s[" << i << "]='" << s[i] 
             << "' with t[" << j << "]='" << t[j] << "'" << endl;
        
        if (s[i] == t[j]) {
            cout << "Debug: Characters match! Moving both pointers" << endl;
            j++;  // Move subsequence pointer
        } else {
            cout << "Debug: Characters don't match, moving main string pointer only" << endl;
        }
        
        i++;  // Always move main string pointer
    }
    
    // Check if all characters of subsequence were found
    if (j == t.length()) {
        cout << "Debug: All characters of subsequence matched!" << endl;
        return true;
    } else {
        cout << "Debug: Only matched " << j << " out of " << t.length() << " characters" << endl;
        return false;
    }
}

int main() {
    string s = "capgemini";
    string t = "cgm";
    
    if (isSubsequence(s, t)) {
        cout << "Result: '" << t << "' is a subsequence of '" << s << "'" << endl;
    } else {
        cout << "Result: '" << t << "' is NOT a subsequence of '" << s << "'" << endl;
    }
    
    return 0;
}
#endif
/*
11. Reverse Words in a String
Algorithm Steps:
Split string into words (by spaces)
Store words in array/vector
Print/concatenate words in reverse order

🧠 Algorithm Steps:
Split the string into individual words:
Use space ' ' as the delimiter.
Store the words in an array or vector.
Reverse the array/vector of words.
Concatenate the reversed words into a new string:
Add a space between words (but not after the last one).

🔧 Example:
Input:
"the sky is blue"

Step-by-step:
Split → ["the", "sky", "is", "blue"]
Reverse → ["blue", "is", "sky", "the"]
Join → "blue is sky the"

Output:
"blue is sky the"
*/
#if C_CODE11
#include <stdio.h>
#include <string.h>

void reverseWords(char* str) {
    char words[100][100];  // Array to store words
    int wordCount = 0;
    char* token;
    
    printf("Debug: Reversing words in '%s'\n", str);
    
    // Split string into words using strtok
    token = strtok(str, " ");
    while (token != NULL) {
        strcpy(words[wordCount], token);
        printf("Debug: Found word %d: '%s'\n", wordCount + 1, words[wordCount]);
        wordCount++;
        token = strtok(NULL, " ");
    }
    
    printf("Debug: Total words found: %d\n", wordCount);
    printf("Debug: Printing words in reverse order:\n");
    
    // Print words in reverse order
    printf("Result: ");
    for (int i = wordCount - 1; i >= 0; i--) {
        printf("%s", words[i]);
        if (i > 0) {
            printf(" ");  // Add space between words
        }
        printf(" (word %d)", wordCount - i);
        if (i > 0) printf("\n        ");
    }
    printf("\n");
}

int main() {
    char str[] = "I love Capgemini coding";  // Note: strtok modifies original string
    printf("Original: %s\n", str);
    reverseWords(str);
    return 0;
}
#endif
#if CPP_CODE11
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

string reverseWords(string str) {
    vector<string> words;
    stringstream ss(str);
    string word;
    
    cout << "Debug: Reversing words in '" << str << "'" << endl;
    
    // Extract words using stringstream
    while (ss >> word) {
        words.push_back(word);
        cout << "Debug: Found word " << words.size() << ": '" << word << "'" << endl;
    }
    
    cout << "Debug: Total words found: " << words.size() << endl;
    cout << "Debug: Building reversed string:" << endl;
    
    // Build result string with words in reverse order
    string result = "";
    for (int i = words.size() - 1; i >= 0; i--) {
        cout << "Debug: Adding word '" << words[i] << "' to result" << endl;
        result += words[i];
        
        // Add space between words (except after last word)
        if (i > 0) {
            result += " ";
        }
    }
    
    return result;
}

int main() {
    string str = "I love Capgemini coding";
    cout << "Original: " << str << endl;
    string reversed = reverseWords(str);
    cout << "Result: " << reversed << endl;
    return 0;
}
#endif
/*==============c main function=====================*/
/*==============c++ main function===================*/

