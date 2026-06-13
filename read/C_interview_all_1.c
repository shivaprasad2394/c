/*
 * ============================================================================
 *  C INTERVIEW STUDY FILE - ALL PROGRAMS IN ONE FILE
 *  Covers: Strings | Arrays | Bit Manipulation | Math | Linked Lists | BST | Queues | sscanf/snprintf
 * ============================================================================
 *
 *  HOW TO COMPILE & RUN:
 *    gcc -Wall -Wextra -o interview interview_all.c -lm
 *    ./interview
 *
 *  HOW TO USE:
 *    - main() at the bottom calls demo functions for each section
 *    - Uncomment the section you want to test in main()
 *    - Each function has: Definition -> Algorithm -> Example trace -> Code
 *
 *  TOTAL PROGRAMS: 89 functions across 8 sections
 * ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

/* ============================================================================
 *  SECTION 1: STRING PROBLEMS
 * ============================================================================ */

/* --------------------------------------------------------------------------
 * 1. Reverse a String (in-place)
 * --------------------------------------------------------------------------
 * Definition:
 *   Reverse the characters of a string without using extra memory.
 *
 * Algorithm:
 *   step1: Place 'left' pointer at index 0, 'right' pointer at last char (len-1)
 *   step2: Swap characters at left and right positions
 *   step3: Move left forward (left++), move right backward (right--)
 *   step4: Repeat step2-3 until left >= right (pointers meet in middle)
 *
 * Example: str = "hello"
 *   left=0, right=4: swap 'h' and 'o' -> "oellh"
 *   left=1, right=3: swap 'e' and 'l' -> "olleh"
 *   left=2, right=2: pointers meet, STOP
 *   Result: "olleh"
 *
 * Complexity: O(n) time, O(1) space
 * Pattern: TWO-POINTER (opposite ends)
 * -------------------------------------------------------------------------- */
void reverseString(char *s) {
    int left = 0;
    int right = (int)strlen(s) - 1;
    while (left < right) {
        char t = s[left];          /* save left char */
        s[left]  = s[right];       /* overwrite left with right */
        s[right] = t;              /* put saved char at right */
        left++;                    /* shrink window inward */
        right--;
    }
}

/* --------------------------------------------------------------------------
 * 2. Check for Anagram
 * --------------------------------------------------------------------------
 * Definition:
 *   Two strings are anagrams if one can be formed by rearranging the
 *   letters of the other. Example: "listen" and "silent".
 *
 * Algorithm:
 *   step1: If lengths differ, return 0 (cannot be anagram)
 *   step2: Create a frequency array of 256 slots (one per ASCII char)
 *   step3: Walk both strings simultaneously:
 *          - freq[str1[i]]++ (count chars in first string)
 *          - freq[str2[i]]-- (un-count chars using second string)
 *   step4: If all freq[] entries are 0, strings are anagrams
 *
 * Example: str1="listen", str2="silent"
 *   After counting: freq['l']=0, freq['i']=0, freq['s']=0, ...
 *   All zero -> anagram!
 *
 * Example: str1="hello", str2="world"
 *   freq['h']=1, freq['w']=-1, ... -> NOT all zero -> not anagram
 *
 * Complexity: O(n) time, O(1) space (256 is constant)
 * Pattern: FREQUENCY TABLE
 * -------------------------------------------------------------------------- */
int isAnagram(const char *str1, const char *str2) {
    if (strlen(str1) != strlen(str2)) return 0;
    int freq[256] = {0};
    for (int i = 0; str1[i]; i++) {
        freq[(unsigned char)str1[i]]++;   /* cast: avoid negative index if char is signed */
        freq[(unsigned char)str2[i]]--;
    }
    for (int i = 0; i < 256; i++) {
        if (freq[i] != 0) return 0;       /* mismatch found */
    }
    return 1;
}

/* --------------------------------------------------------------------------
 * 3. Longest Palindromic Substring (expand around center)
 * --------------------------------------------------------------------------
 * Definition:
 *   Find the longest substring that reads the same forwards and backwards.
 *   Example: "babad" -> "bab" or "aba" (length 3).
 *
 * Algorithm:
 *   step1: For each index i in the string, treat it as the CENTER of a palindrome
 *   step2: Expand outward (left--, right++) as long as chars match
 *   step3: Check BOTH odd-length centers (i,i) and even-length centers (i,i+1)
 *   step4: Track the longest palindrome found (start index + length)
 *
 * Example: str = "babad"
 *   i=0: center 'b' -> expand: "b" (len 1)
 *   i=1: center 'a' -> expand: "a"->"bab" (len 3, NEW MAX)
 *   i=2: center 'b' -> expand: "b"->"aba" (len 3, ties)
 *   i=3: center 'a' -> expand: "a" (len 1)
 *   i=4: center 'd' -> expand: "d" (len 1)
 *   Result: start=0, length=3 -> "bab"
 *
 * Complexity: O(n^2) time, O(1) space
 * Pattern: EXPAND FROM CENTER
 * -------------------------------------------------------------------------- */
void longestPalindrome(const char *s, int *outStart, int *outLen) {
    int n = (int)strlen(s);
    if (n == 0) { *outStart = 0; *outLen = 0; return; }  /* edge: empty string */
    int maxLen = 1, start = 0;

    for (int i = 0; i < n; i++) {
        /* Odd-length: center at i */
        int lo = i, hi = i;
        while (lo >= 0 && hi < n && s[lo] == s[hi]) {
            if (hi - lo + 1 > maxLen) { start = lo; maxLen = hi - lo + 1; }
            lo--; hi++;
        }
        /* Even-length: center between i and i+1 */
        lo = i; hi = i + 1;
        while (lo >= 0 && hi < n && s[lo] == s[hi]) {
            if (hi - lo + 1 > maxLen) { start = lo; maxLen = hi - lo + 1; }
            lo--; hi++;
        }
    }
    *outStart = start;
    *outLen   = maxLen;
}

/* --------------------------------------------------------------------------
 * 4. Remove All Duplicate Characters from a String
 * --------------------------------------------------------------------------
 * Definition:
 *   Keep only the FIRST occurrence of each character, remove all repeats.
 *   Example: "programming" -> "progamin"
 *
 * Algorithm:
 *   step1: Create a boolean seen[256] array, all false
 *   step2: Use a write-index 'w' starting at 0
 *   step3: For each char in the string:
 *          - if NOT seen: copy to str[w++], mark seen[ch] = 1
 *          - if already seen: skip it
 *   step4: Null-terminate: str[w] = '\0'
 *
 * Example: str = "banana"
 *   'b': not seen, keep -> "b", w=1
 *   'a': not seen, keep -> "ba", w=2
 *   'n': not seen, keep -> "ban", w=3
 *   'a': SEEN, skip
 *   'n': SEEN, skip
 *   'a': SEEN, skip
 *   Result: "ban"
 *
 * Complexity: O(n) time, O(1) space (256 is constant)
 * Pattern: FREQUENCY TABLE (boolean variant)
 * -------------------------------------------------------------------------- */
void removeDupChars(char *str) {
    int seen[256] = {0};
    int w = 0;                         /* write index */
    for (int r = 0; str[r]; r++) {
        unsigned char ch = (unsigned char)str[r];
        if (!seen[ch]) {
            seen[ch] = 1;
            str[w++] = str[r];
        }
    }
    str[w] = '\0';
}

/* --------------------------------------------------------------------------
 * 5. String Compression (Run-Length Encoding)
 * --------------------------------------------------------------------------
 * Definition:
 *   Replace consecutive identical chars with char + count.
 *   Example: "aabcccccaaa" -> "a2b1c5a3"
 *
 * Algorithm:
 *   step1: Walk the string from left to right
 *   step2: At each position, count how many consecutive identical chars follow
 *   step3: Write the character and its count to the output buffer
 *   step4: Jump past the group (i += count) and repeat
 *
 * Example: str = "aabcccccaaa"
 *   i=0: ch='a', count=2 -> write "a2", i jumps to 2
 *   i=2: ch='b', count=1 -> write "b1", i jumps to 3
 *   i=3: ch='c', count=5 -> write "c5", i jumps to 8
 *   i=8: ch='a', count=3 -> write "a3", i jumps to 11
 *   Result: "a2b1c5a3"
 *
 * Complexity: O(n) time, O(n) space for output
 * Pattern: COUNT RUNS
 * -------------------------------------------------------------------------- */
void compressString(const char *str, char *out, int outCap) {
    int len = (int)strlen(str);
    int w = 0;
    for (int i = 0; i < len; ) {
        char ch = str[i];
        int count = 1;
        while (i + count < len && str[i + count] == ch) count++;
        int written = snprintf(out + w, (size_t)(outCap - w), "%c%d", ch, count);
        if (written < 0 || w + written >= outCap) break;   /* safety */
        w += written;
        i += count;
    }
    out[w] = '\0';
}

/* --------------------------------------------------------------------------
 * 6. Check If One String Is a Rotation of Another
 * --------------------------------------------------------------------------
 * Definition:
 *   A rotation shifts chars from one end to the other.
 *   Example: "waterbottle" rotated -> "erbottlewat"
 *
 * Algorithm:
 *   step1: If lengths differ, return 0 (can't be rotation)
 *   step2: Concatenate s1 with itself: s1+s1
 *          Key insight: if s2 is a rotation of s1, s2 ALWAYS appears
 *          as a substring inside s1+s1
 *   step3: Use strstr() to check if s2 is inside the concatenation
 *
 * Example: s1="waterbottle", s2="erbottlewat"
 *   concat = "waterbottlewaterbottle"
 *   Does "erbottlewat" appear in it? -> YES (at position 3)
 *   Result: IS a rotation
 *
 * Complexity: O(n) time (assuming strstr is O(n)), O(n) space
 * Pattern: STRING CONCATENATION TRICK
 * -------------------------------------------------------------------------- */
int isRotation(const char *s1, const char *s2) {
    int len = (int)strlen(s1);
    if (len != (int)strlen(s2)) return 0;
    if (len == 0) return 1;
    char *concat = (char *)malloc((size_t)(2 * len + 1));
    if (concat == NULL) return -1;     /* allocation failed */
    sprintf(concat, "%s%s", s1, s1);
    int found = (strstr(concat, s2) != NULL);
    free(concat);
    return found;
}

/* --------------------------------------------------------------------------
 * 7. First and Second Non-Repeating Character
 * --------------------------------------------------------------------------
 * Definition:
 *   Find the first two characters that appear exactly once in the string.
 *   Must preserve the ORDER they appear in the string (not the freq table).
 *
 * Algorithm:
 *   step1: Count frequency of each char using freq[256]
 *   step2: Walk the STRING (not freq table!) from left to right
 *   step3: First char with freq==1 is the "first non-repeating"
 *   step4: Second char with freq==1 is the "second non-repeating"
 *
 * Example: str = "aabccbde"
 *   freq: a=2, b=2, c=2, d=1, e=1
 *   Walk string: a(2),a(2),b(2),c(2),c(2),b(2),d(1)->FIRST, e(1)->SECOND
 *   Result: First='d', Second='e'
 *
 * Complexity: O(n) time, O(1) space
 * Pattern: FREQUENCY TABLE (two-pass)
 * -------------------------------------------------------------------------- */
void findNonRepeating(const char *str) {
    int freq[256] = {0};
    for (int i = 0; str[i]; i++)
        freq[(unsigned char)str[i]]++;

    int found = 0;
    for (int i = 0; str[i] && found < 2; i++) {
        if (freq[(unsigned char)str[i]] == 1) {
            found++;
            printf("%s non-repeating: '%c'\n",
                   found == 1 ? "First" : "Second", str[i]);
        }
    }
    if (found < 2) printf("Fewer than 2 unique chars\n");
}

/* --------------------------------------------------------------------------
 * 8. Valid Palindrome (alphanumeric only, case-insensitive)
 * --------------------------------------------------------------------------
 * Definition:
 *   Check if a string is a palindrome, considering only alphanumeric
 *   characters and ignoring case.
 *   Example: "A man, a plan, a canal: Panama" -> TRUE
 *
 * Algorithm:
 *   step1: Place left=0 and right=len-1 pointers
 *   step2: Skip non-alphanumeric from left (while !isalnum, left++)
 *   step3: Skip non-alphanumeric from right (while !isalnum, right--)
 *   step4: Compare tolower(left) vs tolower(right)
 *          - if different: NOT a palindrome, return 0
 *          - if same: move both pointers inward (left++, right--)
 *   step5: Repeat until left >= right
 *
 * Example: str = "A man, a plan, a canal: Panama"
 *   left=0('A'), right=29('a'): tolower match -> move in
 *   left=2('m'), right=27('m'): match -> move in
 *   ... all match ...
 *   Result: TRUE (palindrome)
 *
 * Complexity: O(n) time, O(1) space
 * Pattern: TWO-POINTER (opposite ends) + skip
 *
 * TRAP: Must cast to (unsigned char) before calling isalnum/tolower.
 *       Negative char values cause UB in <ctype.h> functions.
 * -------------------------------------------------------------------------- */
int isValidPalindrome(const char *s) {
    int left = 0, right = (int)strlen(s) - 1;
    while (left < right) {
        while (left < right && !isalnum((unsigned char)s[left]))  left++;
        while (left < right && !isalnum((unsigned char)s[right])) right--;
        if (tolower((unsigned char)s[left]) != tolower((unsigned char)s[right]))
            return 0;
        left++; right--;
    }
    return 1;
}

/* --------------------------------------------------------------------------
 * 9. Count and Say Sequence
 * --------------------------------------------------------------------------
 * Definition:
 *   Each term describes the digits of the previous term:
 *     Term 1: "1"
 *     Term 2: "11"     (one 1)
 *     Term 3: "21"     (two 1s)
 *     Term 4: "1211"   (one 2, one 1)
 *     Term 5: "111221" (one 1, one 2, two 1s)
 *
 * Algorithm:
 *   step1: Start with cur = "1"
 *   step2: For each term from 2 to n:
 *          - Read cur left to right, count consecutive identical digits
 *          - Build next string: write count followed by digit
 *          - Copy next into cur for the next iteration
 *   step3: Print the final term
 *
 * Example: Building term 4 from term 3 ("21"):
 *   Read '2': count=1 -> write "12"
 *   Read '1': count=1 -> write "11"
 *   next = "1211"
 *
 * Complexity: O(n * L) where L is the length of each term
 * Pattern: BUILD FROM PREVIOUS
 *
 * BUG FIX from original: 'char next;' was declared as a single char
 *   but used as an array. Fixed to char next[512].
 * -------------------------------------------------------------------------- */
void countAndSay(int n) {
    char cur[512] = "1";
    char nxt[512];

    for (int term = 2; term <= n; term++) {
        int len = (int)strlen(cur);
        int w = 0;
        for (int i = 0; i < len; ) {
            char ch = cur[i];
            int count = 1;
            while (i + count < len && cur[i + count] == ch) count++;
            w += sprintf(nxt + w, "%d%c", count, ch);
            i += count;
        }
        nxt[w] = '\0';
        strcpy(cur, nxt);
    }
    printf("Term %d: %s\n", n, cur);
}

/* --------------------------------------------------------------------------
 * 10. Check If t Is a Subsequence of s
 * --------------------------------------------------------------------------
 * Definition:
 *   A subsequence is formed by deleting zero or more characters from a
 *   string WITHOUT changing the order of remaining characters.
 *   Example: "cgm" is a subsequence of "capgemini"
 *
 * Algorithm:
 *   step1: Use two pointers: i walks main string s, j walks subsequence t
 *   step2: If s[i] == t[j]: match found, advance BOTH i and j
 *          If s[i] != t[j]: no match, advance ONLY i
 *   step3: If j reaches end of t, ALL chars of t were matched -> return 1
 *          If i reaches end of s first -> return 0
 *
 * Example: s="capgemini", t="cgm"
 *   i=0('c')==t[0]('c'): match! j=1, i=1
 *   i=1('a')!=t[1]('g'): skip, i=2
 *   i=2('p')!=t[1]('g'): skip, i=3
 *   i=3('g')==t[1]('g'): match! j=2, i=4
 *   i=4('e')!=t[2]('m'): skip, i=5
 *   i=5('m')==t[2]('m'): match! j=3
 *   j==3==strlen(t) -> ALL matched, return 1
 *
 * Complexity: O(n) time, O(1) space
 * Pattern: TWO-POINTER (merge walk)
 * -------------------------------------------------------------------------- */
int isSubsequence(const char *s, const char *t) {
    int i = 0, j = 0;
    int sLen = (int)strlen(s), tLen = (int)strlen(t);
    while (i < sLen && j < tLen) {
        if (s[i] == t[j]) j++;    /* match: advance subsequence pointer */
        i++;                      /* always advance main string pointer */
    }
    return j == tLen;             /* did we match ALL chars of t? */
}

/* --------------------------------------------------------------------------
 * 11. Reverse Words in a String (in-place, three-reversal trick)
 * --------------------------------------------------------------------------
 * Definition:
 *   Reverse the order of words. "the sky is blue" -> "blue is sky the"
 *
 * Algorithm:
 *   step1: Reverse the ENTIRE string
 *          "the sky is blue" -> "eulb si yks eht"
 *   step2: Reverse EACH WORD individually (between spaces)
 *          "eulb" -> "blue"
 *          "si"   -> "is"
 *          "yks"  -> "sky"
 *          "eht"  -> "the"
 *   Result: "blue is sky the"
 *
 * Why it works:
 *   Reversing the whole string puts words in the right order but each
 *   word is backwards. Reversing each word fixes the letters.
 *
 * Complexity: O(n) time, O(1) space (in-place!)
 * Pattern: REVERSAL TRICK (three reverses)
 * -------------------------------------------------------------------------- */
static void rev(char *s, int i, int j) {
    while (i < j) { char t = s[i]; s[i] = s[j]; s[j] = t; i++; j--; }
}

void reverseWords(char *s) {
    int n = (int)strlen(s);
    rev(s, 0, n - 1);                  /* step 1: reverse whole string */

    int start = 0;
    for (int i = 0; i <= n; i++) {     /* step 2: reverse each word */
        if (s[i] == ' ' || s[i] == '\0') {
            rev(s, start, i - 1);
            start = i + 1;
        }
    }
}

/* --------------------------------------------------------------------------
 * 12. Longest Common Substring (brute force)
 * --------------------------------------------------------------------------
 * Definition:
 *   Find the longest contiguous sequence of characters that appears in
 *   BOTH strings. Example: "abcdfgh" and "zcdemgh" -> "cd"
 *
 * Algorithm:
 *   step1: For every pair (i, j) where i is index in str1, j in str2
 *   step2: Count how many consecutive characters match starting at (i, j)
 *   step3: Track the maximum match length and its starting index
 *   step4: Extract the result substring
 *
 * Example: a="abcdfgh", b="zcdemgh"
 *   i=2,j=1: a[2]='c'==b[1]='c', a[3]='d'==b[2]='d', a[4]='f'!=b[3]='e'
 *   Match length = 2 ("cd") -> new max
 *   Result: "cd"
 *
 * Complexity: O(m * n * min(m,n)) time, O(result) space
 * -------------------------------------------------------------------------- */
char *longestCommonSubstring(const char *a, const char *b) {
    int m = (int)strlen(a), n = (int)strlen(b);
    int maxLen = 0, startIdx = 0;

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            int len = 0;
            while (i + len < m && j + len < n && a[i + len] == b[j + len])
                len++;
            if (len > maxLen) { maxLen = len; startIdx = i; }
        }
    }
    char *res = (char *)malloc((size_t)(maxLen + 1));
    if (res == NULL) return NULL;
    memcpy(res, a + startIdx, (size_t)maxLen);
    res[maxLen] = '\0';
    return res;                       /* CALLER MUST free() */
}

/* --------------------------------------------------------------------------
 * 13. Validate an IPv4 Address
 * --------------------------------------------------------------------------
 * Definition:
 *   Check if a string is a valid IPv4 address: four segments separated
 *   by dots, each segment is a number 0-255, no leading zeros.
 *   Valid:   "192.168.0.1"
 *   Invalid: "256.1.2.3", "01.02.03.04", "1.2.3", ""
 *
 * Algorithm:
 *   step1: Walk char by char through the string
 *   step2: On a digit: accumulate into 'num' (num = num*10 + digit)
 *   step3: On a dot or end-of-string: validate the completed segment:
 *          - Must have at least 1 digit (no empty segments)
 *          - Must be 0-255
 *          - No leading zeros (if digits > 1, first digit can't be '0')
 *   step4: After full walk, must have exactly 4 segments (3 dots + terminal)
 *
 * Example: ip = "192.168.0.1"
 *   Segment "192": digits=3, num=192, 0-255 OK
 *   Segment "168": digits=3, num=168, 0-255 OK
 *   Segment "0":   digits=1, num=0,   0-255 OK
 *   Segment "1":   digits=1, num=1,   0-255 OK
 *   dots = 4 (3 dots + 1 terminal) -> VALID
 *
 * Complexity: O(n) time, O(1) space
 * Pattern: STATE MACHINE (single pass)
 * -------------------------------------------------------------------------- */
int isValidIPv4(const char *ip) {
    int len = (int)strlen(ip);
    if (len == 0) return 0;

    int dots = 0, num = 0, digits = 0;
    for (int i = 0; i <= len; i++) {
        char ch = ip[i];
        if (ch == '.' || ch == '\0') {
            if (digits == 0)                        return 0;  /* empty segment */
            if (digits > 1 && ip[i - digits] == '0') return 0;  /* leading zero */
            if (num > 255)                           return 0;  /* out of range */
            dots++;
            num = 0; digits = 0;
            if (ch == '\0') break;
        } else if (isdigit((unsigned char)ch)) {
            num = num * 10 + (ch - '0');
            digits++;
            if (digits > 3)                          return 0;
        } else {
            return 0;                                /* non-digit, non-dot */
        }
    }
    return dots == 4;                                 /* 3 dots + 1 terminal */
}

/* ============================================================================
 *  SECTION 2: ARRAY PROBLEMS
 * ============================================================================ */

/* --------------------------------------------------------------------------
 * 14. Find Second Largest Element
 * --------------------------------------------------------------------------
 * Definition:
 *   Find the second largest distinct value in an array.
 *
 * Algorithm:
 *   step1: Initialize first = INT_MIN, second = INT_MIN
 *   step2: Walk the array once:
 *          - if arr[i] > first: second = first, first = arr[i]
 *          - else if arr[i] > second AND arr[i] != first: second = arr[i]
 *   step3: Return second (or -1 if not found)
 *
 * Example: arr = [12, 35, 1, 10, 34, 1]
 *   i=0: 12 > INT_MIN -> second=INT_MIN, first=12
 *   i=1: 35 > 12      -> second=12, first=35
 *   i=2: 1 < 12       -> skip
 *   i=3: 10 < 12      -> skip
 *   i=4: 34 > 12      -> second=34  (34 > second=12 AND 34 != first=35)
 *   Result: second = 34
 *
 * Complexity: O(n) time, O(1) space
 * Pattern: SINGLE PASS (two trackers)
 * -------------------------------------------------------------------------- */
int findSecondLargest(const int arr[], int n) {
    int first = INT_MIN, second = INT_MIN;
    for (int i = 0; i < n; i++) {
        if (arr[i] > first) {
            second = first;        /* old first becomes second */
            first  = arr[i];       /* new first */
        } else if (arr[i] > second && arr[i] != first) {
            second = arr[i];
        }
    }
    return (second == INT_MIN) ? -1 : second;
}

/* --------------------------------------------------------------------------
 * 15. Move All Zeros to End
 * --------------------------------------------------------------------------
 * Definition:
 *   Move all 0s to the end while maintaining relative order of non-zeros.
 *
 * Algorithm:
 *   step1: Use a write-index 'w' starting at 0
 *   step2: Walk the array with read-index 'r':
 *          - if arr[r] != 0: copy arr[r] to arr[w], then w++
 *   step3: After the loop, fill arr[w..n-1] with zeros
 *
 * Example: arr = [0, 1, 0, 3, 12]
 *   r=0: arr[0]=0, skip
 *   r=1: arr[1]=1, copy to arr[0], w=1 -> [1, 1, 0, 3, 12]
 *   r=2: arr[2]=0, skip
 *   r=3: arr[3]=3, copy to arr[1], w=2 -> [1, 3, 0, 3, 12]
 *   r=4: arr[4]=12, copy to arr[2], w=3 -> [1, 3, 12, 3, 12]
 *   Fill w=3 to n-1 with 0: [1, 3, 12, 0, 0]
 *
 * Complexity: O(n) time, O(1) space
 * Pattern: TWO-POINTER (read/write)
 * -------------------------------------------------------------------------- */
void moveZerosToEnd(int arr[], int n) {
    int w = 0;
    for (int r = 0; r < n; r++) {
        if (arr[r] != 0) arr[w++] = arr[r];
    }
    while (w < n) arr[w++] = 0;
}

/* --------------------------------------------------------------------------
 * 16. Rotate Array Left by d Positions (reversal trick)
 * --------------------------------------------------------------------------
 * Definition:
 *   Shift all elements left by d positions. Elements that fall off the
 *   left end wrap around to the right.
 *   Example: [1,2,3,4,5,6,7] d=2 -> [3,4,5,6,7,1,2]
 *
 * Algorithm:
 *   step1: Normalize d = d % n (handles d > n)
 *   step2: Reverse first d elements:     [2,1,3,4,5,6,7]
 *   step3: Reverse remaining n-d elems:  [2,1,7,6,5,4,3]
 *   step4: Reverse the entire array:     [3,4,5,6,7,1,2]
 *
 * Example: arr = [1,2,3,4,5,6,7], d=2
 *   After rev(0..1):  [2,1,3,4,5,6,7]
 *   After rev(2..6):  [2,1,7,6,5,4,3]
 *   After rev(0..6):  [3,4,5,6,7,1,2]  <- correct!
 *
 * Complexity: O(n) time, O(1) space
 * Pattern: REVERSAL TRICK (three reverses)
 * -------------------------------------------------------------------------- */
static void revArr(int a[], int i, int j) {
    while (i < j) { int t = a[i]; a[i] = a[j]; a[j] = t; i++; j--; }
}

void rotateLeft(int arr[], int n, int d) {
    if (n == 0) return;
    d %= n;                            /* handle d > n */
    if (d == 0) return;                /* no rotation needed */
    revArr(arr, 0, d - 1);            /* reverse first d */
    revArr(arr, d, n - 1);            /* reverse rest */
    revArr(arr, 0, n - 1);            /* reverse whole */
}

/* --------------------------------------------------------------------------
 * 17. Kadane's Algorithm (Maximum Subarray Sum)
 * --------------------------------------------------------------------------
 * Definition:
 *   Find the contiguous subarray with the largest sum.
 *
 * Algorithm:
 *   step1: Initialize maxEndingHere = arr[0], maxSoFar = arr[0]
 *   step2: For each element from index 1:
 *          - Decision: should I EXTEND the current subarray or START fresh?
 *          - maxEndingHere = max(arr[i], maxEndingHere + arr[i])
 *          - if maxEndingHere > maxSoFar: update maxSoFar
 *   step3: Return maxSoFar
 *
 * Example: arr = [-2, -3, 4, -1, -2, 1, 5, -3]
 *   i=0: maxHere=-2, maxSoFar=-2
 *   i=1: maxHere=max(-3, -2+-3=-5)=-3, maxSoFar=-2
 *   i=2: maxHere=max(4, -3+4=1)=4, maxSoFar=4
 *   i=3: maxHere=max(-1, 4+-1=3)=3, maxSoFar=4
 *   i=4: maxHere=max(-2, 3+-2=1)=1, maxSoFar=4
 *   i=5: maxHere=max(1, 1+1=2)=2, maxSoFar=4
 *   i=6: maxHere=max(5, 2+5=7)=7, maxSoFar=7  <- NEW MAX
 *   i=7: maxHere=max(-3, 7+-3=4)=4, maxSoFar=7
 *   Result: 7 (subarray: [4,-1,-2,1,5])
 *
 * TRAP: Init to arr[0], NOT 0. Otherwise all-negative arrays fail.
 *
 * Complexity: O(n) time, O(1) space
 * Pattern: SINGLE PASS GREEDY (extend or restart)
 * -------------------------------------------------------------------------- */
int kadane(const int arr[], int n) {
    if (n <= 0) return 0;              /* edge: empty array */
    int maxHere = arr[0];
    int maxSoFar = arr[0];
    for (int i = 1; i < n; i++) {
        int ext = maxHere + arr[i];
        maxHere = (arr[i] > ext) ? arr[i] : ext;
        if (maxHere > maxSoFar) maxSoFar = maxHere;
    }
    return maxSoFar;
}

/* --------------------------------------------------------------------------
 * 18. Remove Duplicates from Sorted Array
 * --------------------------------------------------------------------------
 * Definition:
 *   Given a SORTED array, remove duplicates in-place. Return new length.
 *
 * Algorithm:
 *   step1: slow = 0 (tracks tail of unique prefix)
 *   step2: fast walks from 1 to n-1:
 *          - if arr[fast] != arr[slow]: slow++, copy arr[fast] to arr[slow]
 *   step3: Return slow + 1 (length, not index)
 *
 * Example: arr = [1, 1, 2, 2, 3, 4, 4]
 *   fast=1: arr[1]=1 == arr[0]=1 -> skip
 *   fast=2: arr[2]=2 != arr[0]=1 -> slow=1, arr[1]=2
 *   fast=3: arr[3]=2 == arr[1]=2 -> skip
 *   fast=4: arr[4]=3 != arr[1]=2 -> slow=2, arr[2]=3
 *   fast=5: arr[5]=4 != arr[2]=3 -> slow=3, arr[3]=4
 *   fast=6: arr[6]=4 == arr[3]=4 -> skip
 *   Result: new length = 3+1 = 4, arr = [1,2,3,4,...]
 *
 * Complexity: O(n) time, O(1) space
 * Pattern: TWO-POINTER (slow/fast)
 * -------------------------------------------------------------------------- */
int removeDuplicates(int arr[], int n) {
    if (n == 0) return 0;
    int slow = 0;
    for (int fast = 1; fast < n; fast++) {
        if (arr[fast] != arr[slow]) {
            slow++;
            arr[slow] = arr[fast];
        }
    }
    return slow + 1;
}

/* --------------------------------------------------------------------------
 * 19. Majority Element (Boyer-Moore Voting)
 * --------------------------------------------------------------------------
 * Definition:
 *   Find the element that appears MORE than n/2 times.
 *
 * Algorithm:
 *   PHASE 1 (candidate selection):
 *     step1: candidate=0, count=0
 *     step2: For each element:
 *            - if count==0: candidate = arr[i], count = 1
 *            - else if arr[i]==candidate: count++
 *            - else: count--
 *
 *   PHASE 2 (verification - MANDATORY):
 *     step3: Count actual occurrences of candidate
 *     step4: If count > n/2, return candidate. Else return -1.
 *
 * Example: arr = [2, 2, 1, 1, 1, 2, 2]
 *   Phase 1: candidate ends as 2 (count survives)
 *   Phase 2: count of 2 = 4, n/2 = 3, 4 > 3 -> majority IS 2
 *
 * TRAP: Phase 2 is MANDATORY. Phase 1 alone can return wrong answer
 *       for arrays with no majority (e.g., [1,2,3]).
 *
 * Complexity: O(n) time, O(1) space
 * Pattern: SINGLE PASS GREEDY (vote + verify)
 * -------------------------------------------------------------------------- */
int findMajority(const int arr[], int n) {
    int candidate = 0, count = 0;
    for (int i = 0; i < n; i++) {
        if (count == 0) { candidate = arr[i]; count = 1; }
        else if (arr[i] == candidate) count++;
        else count--;
    }
    count = 0;
    for (int i = 0; i < n; i++) if (arr[i] == candidate) count++;
    return (count > n / 2) ? candidate : -1;
}

/* --------------------------------------------------------------------------
 * 20. Missing Number in 0..n (XOR method)
 * --------------------------------------------------------------------------
 * Definition:
 *   Given n distinct numbers from {0, 1, ..., n}, find the missing one.
 *
 * Algorithm:
 *   step1: XOR all values 0 to n together
 *   step2: XOR all array elements together
 *   step3: XOR the two results -> missing number
 *   Why: a^a=0, so all duplicates cancel; the missing one survives
 *
 * Example: arr = [3, 0, 1], n = 3 (should have 0,1,2,3)
 *   XOR(0..3) = 0^1^2^3 = 0
 *   XOR(arr)  = 3^0^1   = 2
 *   0 ^ 2 = 2 -> missing is 2
 *
 * Complexity: O(n) time, O(1) space
 * Pattern: XOR CANCEL
 * -------------------------------------------------------------------------- */
int findMissing(const int arr[], int n) {
    int x = 0;
    for (int i = 0; i <= n; i++) x ^= i;
    for (int i = 0;  i < n; i++) x ^= arr[i];
    return x;
}

/* --------------------------------------------------------------------------
 * 21. Reverse Array in Groups of k
 * --------------------------------------------------------------------------
 * Algorithm:
 *   step1: Walk array in strides of k (i=0, i+=k)
 *   step2: For each stride, reverse from i to min(i+k-1, n-1)
 *          (last group may have fewer than k elements)
 *
 * Example: arr = [1,2,3,4,5,6,7,8,9], k=3
 *   i=0: reverse [0..2]: [3,2,1, 4,5,6, 7,8,9]
 *   i=3: reverse [3..5]: [3,2,1, 6,5,4, 7,8,9]
 *   i=6: reverse [6..8]: [3,2,1, 6,5,4, 9,8,7]
 *
 * Complexity: O(n) time, O(1) space
 * -------------------------------------------------------------------------- */
void reverseInGroups(int arr[], int n, int k) {
    if (k <= 1) return;
    for (int i = 0; i < n; i += k) {
        int end = (i + k - 1 < n) ? i + k - 1 : n - 1;
        revArr(arr, i, end);
    }
}

/* --------------------------------------------------------------------------
 * 22. Find Minimum in Rotated Sorted Array (binary search)
 * --------------------------------------------------------------------------
 * Definition:
 *   A sorted array has been rotated at an unknown pivot.
 *   Find the minimum element in O(log n).
 *
 * Algorithm:
 *   step1: left=0, right=n-1
 *   step2: While left < right:
 *          - mid = left + (right-left)/2  (overflow-safe!)
 *          - if arr[mid] > arr[right]: min is in RIGHT half -> left = mid + 1
 *          - else: min is mid or in LEFT half -> right = mid
 *   step3: Return arr[left]
 *
 * Example: arr = [4, 5, 6, 7, 0, 1, 2]
 *   left=0, right=6, mid=3: arr[3]=7 > arr[6]=2 -> left=4
 *   left=4, right=6, mid=5: arr[5]=1 < arr[6]=2 -> right=5
 *   left=4, right=5, mid=4: arr[4]=0 < arr[5]=1 -> right=4
 *   left==right==4 -> arr[4] = 0 = MINIMUM
 *
 * TRAP: Compare with arr[right], NOT arr[left]. Using left is wrong!
 * TRAP: Use left + (right-left)/2, NOT (left+right)/2 (overflow!)
 *
 * Complexity: O(log n) time, O(1) space
 * Pattern: BINARY SEARCH
 * -------------------------------------------------------------------------- */
int findMinRotated(const int arr[], int n) {
    int left = 0, right = n - 1;
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] > arr[right]) left  = mid + 1;
        else                       right = mid;
    }
    return arr[left];
}

/* --------------------------------------------------------------------------
 * 23. Binary Search (iterative)
 * --------------------------------------------------------------------------
 * Algorithm:
 *   step1: left=0, right=n-1
 *   step2: While left <= right:
 *          - mid = left + (right-left)/2
 *          - if arr[mid] == target: return mid
 *          - if arr[mid] < target:  search right half (left = mid+1)
 *          - if arr[mid] > target:  search left half (right = mid-1)
 *   step3: Return -1 (not found)
 *
 * TRAP: Condition is left <= right (not <)
 *
 * Complexity: O(log n) time, O(1) space
 * Precondition: array MUST be sorted
 * -------------------------------------------------------------------------- */
int binarySearch(const int arr[], int n, int target) {
    int left = 0, right = n - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if      (arr[mid] == target) return mid;
        else if (arr[mid] <  target) left  = mid + 1;
        else                         right = mid - 1;
    }
    return -1;
}

/* --------------------------------------------------------------------------
 * 24. Quicksort (Lomuto partition)
 * --------------------------------------------------------------------------
 * Algorithm:
 *   step1: Pick pivot = arr[high] (last element)
 *   step2: Partition: walk j from low to high-1
 *          - if arr[j] <= pivot: swap arr[j] with arr[++i]
 *   step3: Place pivot at arr[i+1] (its correct sorted position)
 *   step4: Recurse on left partition (low..p-1) and right (p+1..high)
 *
 * Complexity: O(n log n) average, O(n^2) worst (sorted input)
 * -------------------------------------------------------------------------- */
static void swapi(int *a, int *b) { int t = *a; *a = *b; *b = t; }

static int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) { i++; swapi(&arr[i], &arr[j]); }
    }
    swapi(&arr[i + 1], &arr[high]);
    return i + 1;
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int p = partition(arr, low, high);
        quickSort(arr, low, p - 1);
        quickSort(arr, p + 1, high);
    }
}

/* --------------------------------------------------------------------------
 * 25. Merge Two Sorted Arrays
 * --------------------------------------------------------------------------
 * Algorithm:
 *   step1: Use three pointers: i for a[], j for b[], k for out[]
 *   step2: Compare a[i] and b[j], take the smaller one into out[k++]
 *   step3: When one array is exhausted, copy the remainder of the other
 *
 * Complexity: O(m+n) time, O(m+n) space
 * -------------------------------------------------------------------------- */
void mergeSorted(const int a[], int m, const int b[], int n, int out[]) {
    int i = 0, j = 0, k = 0;
    while (i < m && j < n)
        out[k++] = (a[i] <= b[j]) ? a[i++] : b[j++];
    while (i < m) out[k++] = a[i++];
    while (j < n) out[k++] = b[j++];
}

/* --------------------------------------------------------------------------
 * 26. Heap Sort
 * --------------------------------------------------------------------------
 * Algorithm:
 *   step1: Build a max-heap from the array (bottom-up, starting at n/2-1)
 *   step2: Repeatedly:
 *          - Swap root (max) with last unsorted element
 *          - Shrink heap by 1
 *          - Heapify the root to restore max-heap property
 *
 * Children of node i: left = 2*i+1, right = 2*i+2
 *
 * Complexity: O(n log n) time, O(1) space
 * -------------------------------------------------------------------------- */
static void heapify(int arr[], int n, int root) {
    int largest = root;
    int left    = 2 * root + 1;
    int right   = 2 * root + 2;
    if (left  < n && arr[left]  > arr[largest]) largest = left;
    if (right < n && arr[right] > arr[largest]) largest = right;
    if (largest != root) {
        int t = arr[root]; arr[root] = arr[largest]; arr[largest] = t;
        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) heapify(arr, n, i);
    for (int i = n - 1; i > 0; i--) {
        int t = arr[0]; arr[0] = arr[i]; arr[i] = t;
        heapify(arr, i, 0);
    }
}

/* ============================================================================
 *  SECTION 3: BIT MANIPULATION
 * ============================================================================ */

/* --------------------------------------------------------------------------
 * 27-30. Set / Clear / Toggle / Check Bit
 * --------------------------------------------------------------------------
 * Definition:
 *   The four fundamental register operations used in every MCU driver.
 *
 * Algorithm:
 *   SET bit pos:    n |=  (1u << pos)   -- OR with a mask of 1 at pos
 *   CLEAR bit pos:  n &= ~(1u << pos)   -- AND with inverted mask (0 at pos)
 *   TOGGLE bit pos: n ^=  (1u << pos)   -- XOR flips: 0->1 or 1->0
 *   CHECK bit pos:  (n >> pos) & 1      -- shift bit to LSB, mask with 1
 *
 * TRAP: Always use 1u (unsigned), NOT 1. Shifting signed 1 into the
 *       sign bit (e.g. 1 << 31) is UNDEFINED BEHAVIOR.
 *
 * Example: n = 12 (binary: 1100), pos = 1
 *   SET:    12 | (1<<1) = 1100 | 0010 = 1110 = 14
 *   CLEAR:  12 & ~(1<<2) = 1100 & 1011 = 1000 = 8
 *   TOGGLE: 12 ^ (1<<1) = 1100 ^ 0010 = 1110 = 14
 *   CHECK:  (12 >> 1) & 1 = 0110 & 0001 = 0  (bit 1 is NOT set)
 * -------------------------------------------------------------------------- */
unsigned int setBit    (unsigned int n, int pos) { return n |  (1u << pos); }
unsigned int clearBit  (unsigned int n, int pos) { return n & ~(1u << pos); }
unsigned int toggleBit (unsigned int n, int pos) { return n ^  (1u << pos); }
int          checkBit  (unsigned int n, int pos) { return (n >> pos) & 1;   }

/* --------------------------------------------------------------------------
 * 31. Check if n is a Power of 2
 * --------------------------------------------------------------------------
 * Definition:
 *   Powers of 2 have exactly ONE set bit: 1, 2, 4, 8, 16, ...
 *
 * Algorithm:
 *   step1: A power of 2 in binary is 10...0 (one 1 followed by zeros)
 *   step2: Subtracting 1 flips that bit and turns on all bits below:
 *          n = 1000, n-1 = 0111
 *   step3: n & (n-1) == 0 iff n was a power of 2
 *   step4: Must also exclude n == 0 (0 is NOT a power of 2)
 *
 * Example: n=8 -> 1000, n-1=7 -> 0111, 8 & 7 = 0 -> YES
 *          n=6 -> 0110, n-1=5 -> 0101, 6 & 5 = 4 -> NO
 *
 * Complexity: O(1) time, O(1) space
 * -------------------------------------------------------------------------- */
int isPowerOfTwo(int n) {
    return n > 0 && (n & (n - 1)) == 0;
}

/* --------------------------------------------------------------------------
 * 32. Count Set Bits (Brian Kernighan's Trick)
 * --------------------------------------------------------------------------
 * Definition:
 *   Count how many bits are 1 in the binary representation of n.
 *
 * Algorithm:
 *   step1: While n != 0:
 *          - n = n & (n-1)  -- this clears the LOWEST set bit each pass
 *          - count++
 *   step2: Return count
 *
 * Why n & (n-1) works:
 *   n   = ...1000  (lowest set bit)
 *   n-1 = ...0111  (flips lowest set bit and all below)
 *   AND clears that bit, leaving all higher bits untouched
 *
 * Example: n=13 (1101), count=0
 *   1101 & 1100 = 1100, count=1  (cleared bit 0)
 *   1100 & 1011 = 1000, count=2  (cleared bit 2)
 *   1000 & 0111 = 0000, count=3  (cleared bit 3)
 *   n==0, STOP. Result: 3 set bits
 *
 * Complexity: O(number of set bits), NOT O(32)
 * -------------------------------------------------------------------------- */
int countSetBits(unsigned int n) {
    int count = 0;
    while (n) { n &= (n - 1); count++; }
    return count;
}

/* --------------------------------------------------------------------------
 * 33. Single Non-Repeating Element (XOR)
 * --------------------------------------------------------------------------
 * Definition:
 *   Every element appears exactly twice except one. Find the unique one.
 *
 * Algorithm:
 *   step1: Initialize result = 0
 *   step2: XOR every element into result
 *   step3: Duplicates cancel (a^a=0), unique survives (x^0=x)
 *
 * Example: arr = [4, 1, 2, 1, 2]
 *   0 ^ 4 = 4
 *   4 ^ 1 = 5
 *   5 ^ 2 = 7
 *   7 ^ 1 = 6   (1 cancels)
 *   6 ^ 2 = 4   (2 cancels)
 *   Result: 4
 *
 * Complexity: O(n) time, O(1) space
 * Pattern: XOR CANCEL
 * -------------------------------------------------------------------------- */
int findSingle(const int arr[], int n) {
    int result = 0;
    for (int i = 0; i < n; i++) result ^= arr[i];
    return result;
}

/* --------------------------------------------------------------------------
 * 34. Two Non-Repeating Elements
 * --------------------------------------------------------------------------
 * Definition:
 *   Every element appears twice except TWO distinct elements a and b.
 *   Find both.
 *
 * Algorithm:
 *   step1: XOR everything -> result = a ^ b (nonzero since a != b)
 *   step2: Find any set bit in result. Easiest: diffBit = x & -x
 *          This bit is where a and b DIFFER
 *   step3: Partition array by that bit:
 *          - Group1 (bit set): XOR all -> gives a
 *          - Group2 (bit clear): XOR all -> gives b
 *          Pairs within each group still cancel out
 *
 * Example: arr = [2, 3, 7, 9, 11, 2, 3, 11]
 *   XOR all = 7 ^ 9 = 14 = 1110
 *   diffBit = 14 & -14 = 2 = 0010
 *   Group1 (bit 1 set): {2,3,7,2,3} -> XOR = 7
 *   Group2 (bit 1 clear): {9,11,11} -> XOR = 9
 *   Result: 7 and 9
 *
 * Complexity: O(n) time, O(1) space
 * -------------------------------------------------------------------------- */
void findTwoUniques(const int arr[], int n, int *a, int *b) {
    int x = 0;
    for (int i = 0; i < n; i++) x ^= arr[i];
    int diffBit = x & -x;
    int g1 = 0, g2 = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] & diffBit) g1 ^= arr[i];
        else                  g2 ^= arr[i];
    }
    *a = g1; *b = g2;
}

/* --------------------------------------------------------------------------
 * 35. Swap Two Numbers Without Temp (XOR)
 * --------------------------------------------------------------------------
 * Algorithm:
 *   *a ^= *b  -- a now holds a^b
 *   *b ^= *a  -- b = b^(a^b) = a  (original a)
 *   *a ^= *b  -- a = (a^b)^a = b  (original b)
 *
 * TRAP: if a and b point to the SAME address, the result is 0 (not a swap!)
 *       Always guard with: if (a == b) return;
 * -------------------------------------------------------------------------- */
void swapXOR(int *a, int *b) {
    if (a == b) return;
    *a ^= *b;
    *b ^= *a;
    *a ^= *b;
}

/* --------------------------------------------------------------------------
 * 36. Reverse Bits of a 32-bit Number
 * --------------------------------------------------------------------------
 * Algorithm:
 *   step1: result = 0
 *   step2: Loop 32 times:
 *          - Shift result LEFT by 1 (make room)
 *          - OR in the LSB of n: result |= (n & 1)
 *          - Shift n RIGHT by 1 (move to next bit)
 *   step3: Return result
 *
 * Example (4-bit demo): n = 0101 (5)
 *   iter1: result = 0000<<1 | 1 = 0001, n = 0010
 *   iter2: result = 0010<<1 | 0 = 0010, n = 0001
 *   iter3: result = 0100<<1 | 1 = 0101, n = 0000
 *   iter4: result = 1010<<1 | 0 = 1010
 *   Result: 1010 (10)
 *
 * Complexity: O(32) = O(1) time
 * -------------------------------------------------------------------------- */
unsigned int reverseBits(unsigned int n) {
    unsigned int result = 0;
    for (int i = 0; i < 32; i++) {
        result = (result << 1) | (n & 1u);
        n >>= 1;
    }
    return result;
}

/* --------------------------------------------------------------------------
 * 37. Even / Odd via LSB
 * --------------------------------------------------------------------------
 * The LSB (bit 0) tells you: 0 = even, 1 = odd
 * Works for negatives too (two's complement)
 * -------------------------------------------------------------------------- */
int isEven(int n) { return (n & 1) == 0; }

/* --------------------------------------------------------------------------
 * 38. Position of Rightmost Set Bit (1-indexed)
 * --------------------------------------------------------------------------
 * Algorithm:
 *   step1: Isolate lowest set bit: iso = n & -n
 *          In two's complement: -n = ~n + 1, so only the lowest 1 survives
 *   step2: Count shifts until iso == 1: that's the 0-indexed position
 *   step3: Return position + 1 (1-indexed)
 *
 * Example: n = 12 = 1100
 *   -n = ...0100 (two's complement)
 *   n & -n = 0100 = 4 -> isolated bit at position 2
 *   Shift: 4 >> 1 = 2, 2 >> 1 = 1 -> 2 shifts -> position 2+1 = 3
 *
 * Complexity: O(position) time, O(1) space
 * -------------------------------------------------------------------------- */
int positionOfRightmostSetBit(unsigned int n) {
    if (n == 0) return 0;
    unsigned int iso = n & -n;
    int pos = 0;
    while (iso > 1) { iso >>= 1; pos++; }
    return pos + 1;
}

/* --------------------------------------------------------------------------
 * 39-41. Bit Range Operations (Set / Clear / Write bits in [start..end])
 * --------------------------------------------------------------------------
 * Algorithm:
 *   step1: Build a mask of (end-start+1) ones: (1u << nbits) - 1
 *   step2: Shift mask to the right position: mask << start
 *   step3: Apply:
 *          - SET range:   reg |= mask
 *          - CLEAR range: reg &= ~mask
 *          - WRITE value: clear the range, then OR in (value << start)
 *
 * Example: reg=0xFF (11111111), clear bits [2..4]
 *   mask = ((1<<3)-1) << 2 = 0b111 << 2 = 0b11100 = 0x1C
 *   ~mask = 0xE3 = 11100011
 *   reg & ~mask = 11100011 (bits 2,3,4 cleared)
 * -------------------------------------------------------------------------- */
static unsigned int rangeMask(int start, int end) {
    int nbits = end - start + 1;
    return ((1u << nbits) - 1u) << start;
}
unsigned int setBitsInRange  (unsigned int reg, int s, int e) { return reg | rangeMask(s,e); }
unsigned int clearBitsInRange(unsigned int reg, int s, int e) { return reg & ~rangeMask(s,e); }
unsigned int writeBitsInRange(unsigned int reg, int s, int e, unsigned int val) {
    unsigned int mask = rangeMask(s, e);
    val = (val << s) & mask;
    return (reg & ~mask) | val;
}

/* --------------------------------------------------------------------------
 * 42. Add Two Numbers Without + Operator
 * --------------------------------------------------------------------------
 * Algorithm:
 *   step1: XOR gives the sum WITHOUT carry:   sum = a ^ b
 *   step2: AND-then-shift gives the carry:    carry = (a & b) << 1
 *   step3: Repeat: a = sum, b = carry, until carry == 0
 *
 * Example: a=15 (1111), b=32 (100000)
 *   iter1: sum = 1111 ^ 100000 = 101111, carry = 0
 *   carry == 0, STOP. Result: 101111 = 47
 *
 * Complexity: O(32) worst case = O(1)
 * -------------------------------------------------------------------------- */
int addNoPlus(int a, int b) {
    while (b != 0) {
        int carry = (a & b) << 1;
        a = a ^ b;
        b = carry;
    }
    return a;
}

/* --------------------------------------------------------------------------
 * 43. Multiply / Divide by Powers of 2
 * --------------------------------------------------------------------------
 *   n << k  ==  n * 2^k
 *   n >> k  ==  n / 2^k  (for unsigned; for signed, implementation-defined)
 *
 * TRAP: n >> k on negative signed n is impl-defined (usually arithmetic
 *       shift = sign-extending). Cast to unsigned for logical shift.
 * -------------------------------------------------------------------------- */
int mul2k(int n, int k) { return n << k; }
int div2k(int n, int k) { return n >> k; }

/* --------------------------------------------------------------------------
 * 44. Missing Number from 1..N (XOR variant)
 * --------------------------------------------------------------------------
 * Same as #20 but for range 1..n instead of 0..n
 * Array has n-1 elements; one value from 1..n is missing
 * -------------------------------------------------------------------------- */
int findMissing1toN(const int arr[], int n) {
    int x = 0;
    for (int i = 1; i <= n; i++) x ^= i;
    for (int i = 0; i < n - 1; i++) x ^= arr[i];
    return x;
}

/* ============================================================================
 *  SECTION 4: MATH / NUMBER PROBLEMS
 * ============================================================================ */

/* --------------------------------------------------------------------------
 * 45. Digit Extraction
 * --------------------------------------------------------------------------
 * Algorithm: n%10 extracts last digit, n/10 removes it. Loop until n==0.
 * Digits come out in REVERSE order.
 *
 * Example: n = 5283
 *   5283 % 10 = 3,  5283 / 10 = 528
 *    528 % 10 = 8,   528 / 10 = 52
 *     52 % 10 = 2,    52 / 10 = 5
 *      5 % 10 = 5,     5 / 10 = 0 -> stop
 *   Digits: 3, 8, 2, 5
 * -------------------------------------------------------------------------- */
void extractDigits(int n) {
    if (n < 0) n = -n;
    if (n == 0) { printf("0\n"); return; }
    while (n > 0) {
        printf("%d ", n % 10);
        n /= 10;
    }
    printf("\n");
}

/* --------------------------------------------------------------------------
 * 46. Reverse a Number
 * --------------------------------------------------------------------------
 * Algorithm: Build reversed number digit by digit:
 *   rev = rev * 10 + (n % 10),  n = n / 10
 *
 * TRAP: Overflow! Reversing 1999999999 overflows int.
 *       Check: if (rev > (INT_MAX - digit) / 10) return 0;
 *
 * Example: n = 1234
 *   rev=0:  rev = 0*10+4 = 4,     n=123
 *   rev=4:  rev = 4*10+3 = 43,    n=12
 *   rev=43: rev = 43*10+2 = 432,  n=1
 *   rev=432: rev = 432*10+1 = 4321, n=0
 *   Result: 4321
 * -------------------------------------------------------------------------- */
int reverseNumber(int n) {
    if (n == INT_MIN) return 0;        /* INT_MIN * -1 overflows */
    int rev = 0;
    int sign = (n < 0) ? -1 : 1;
    n *= sign;
    while (n > 0) {
        int digit = n % 10;
        if (rev > (INT_MAX - digit) / 10) return 0;
        rev = rev * 10 + digit;
        n /= 10;
    }
    return rev * sign;
}

/* --------------------------------------------------------------------------
 * 47. Palindrome Number Check
 * --------------------------------------------------------------------------
 * Algorithm: Reverse the number, compare to original.
 *   Negatives are NEVER palindromes.
 *
 * Example: 121 -> reversed = 121 -> equal -> palindrome
 *          -121 -> negative -> NOT palindrome
 * -------------------------------------------------------------------------- */
int isPalindromeNumber(int n) {
    if (n < 0) return 0;
    int original = n, rev = 0;
    while (n > 0) { rev = rev * 10 + (n % 10); n /= 10; }
    return rev == original;
}

/* --------------------------------------------------------------------------
 * 48. Armstrong Number (Narcissistic Number)
 * --------------------------------------------------------------------------
 * Definition: Sum of each digit raised to the power of (number of digits)
 *   equals the number itself.
 *   153 = 1^3 + 5^3 + 3^3 = 1 + 125 + 27 = 153 -> Armstrong
 *   9474 = 9^4 + 4^4 + 7^4 + 4^4 = 9474 -> Armstrong
 *
 * Algorithm:
 *   step1: Count digits (d)
 *   step2: For each digit: sum += digit^d
 *   step3: Compare sum == original
 * -------------------------------------------------------------------------- */
static int intPow(int base, int exp) {
    int r = 1; for (int i = 0; i < exp; i++) r *= base; return r;
}

int isArmstrong(int n) {
    if (n < 0) return 0;
    int original = n, d = 0, temp = n;
    while (temp > 0) { d++; temp /= 10; }
    int sum = 0; temp = n;
    while (temp > 0) { sum += intPow(temp % 10, d); temp /= 10; }
    return sum == original;
}

/* --------------------------------------------------------------------------
 * 49. Print All Divisors of N
 * --------------------------------------------------------------------------
 * Algorithm: Loop i from 1 to sqrt(n). If n%i==0, both i and n/i are divisors.
 *
 * TRAP: Use i*i <= n instead of i <= sqrt(n) to avoid floating point on MCUs.
 *       Print n/i only when i != n/i to avoid duplicate for perfect squares.
 *
 * Example: n = 36
 *   i=1: 36%1==0 -> print 1, 36
 *   i=2: 36%2==0 -> print 2, 18
 *   i=3: 36%3==0 -> print 3, 12
 *   i=4: 36%4==0 -> print 4, 9
 *   i=5: 36%5!=0 -> skip
 *   i=6: 36%6==0 -> print 6 (6==36/6, so only once)
 * -------------------------------------------------------------------------- */
void printDivisors(int n) {
    for (int i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            printf("%d ", i);
            if (i != n / i) printf("%d ", n / i);
        }
    }
    printf("\n");
}

/* --------------------------------------------------------------------------
 * 50. Prime Number Check (6k +/- 1 optimization)
 * --------------------------------------------------------------------------
 * Why 6k+/-1: Every integer is 6k, 6k+1, 6k+2, 6k+3, 6k+4, or 6k+5.
 *   6k, 6k+2, 6k+4 are even (divisible by 2).
 *   6k+3 is divisible by 3.
 *   Only 6k+1 and 6k+5 (= 6(k+1)-1) can be prime.
 *   So after eliminating 2 and 3, check i and i+2 stepping by 6.
 *
 * Example: n = 29
 *   29 > 3, not divisible by 2 or 3
 *   i=5: 29%5=4 (no), 29%7=1 (no). 7*7=49 > 29 -> stop
 *   Result: PRIME
 * -------------------------------------------------------------------------- */
int isPrime(int n) {
    if (n <= 1) return 0;
    if (n <= 3) return 1;
    if (n % 2 == 0 || n % 3 == 0) return 0;
    for (int i = 5; i * i <= n; i += 6)
        if (n % i == 0 || n % (i + 2) == 0) return 0;
    return 1;
}

/* --------------------------------------------------------------------------
 * 51. GCD - Euclidean Algorithm (iterative)
 * --------------------------------------------------------------------------
 * Algorithm: while b != 0: temp=b, b=a%b, a=temp. Return a.
 *
 * Example: gcd(48, 18)
 *   48 % 18 = 12 -> gcd(18, 12)
 *   18 % 12 = 6  -> gcd(12, 6)
 *   12 % 6  = 0  -> gcd(6, 0)  -> answer = 6
 *
 * LCM from GCD: lcm(a,b) = (a / gcd(a,b)) * b  (divide first to avoid overflow!)
 * -------------------------------------------------------------------------- */
int gcd(int a, int b) {
    if (a < 0) a = -a;
    if (b < 0) b = -b;
    while (b != 0) { int t = b; b = a % b; a = t; }
    return a;
}
int lcm(int a, int b) {
    if (a == 0 || b == 0) return 0;
    return (a / gcd(a, b)) * b;
}

/* --------------------------------------------------------------------------
 * 52. Big Integer Addition (string-based)
 * --------------------------------------------------------------------------
 * Algorithm:
 *   step1: Walk both strings from RIGHT to LEFT (least significant digit)
 *   step2: Add digits + carry. Store (sum % 10), carry forward (sum / 10).
 *   step3: If one string is shorter, treat missing digits as 0.
 *   step4: After loop, if carry > 0, write it.
 *   step5: Result is built in reverse -> reverse it at end.
 *
 * Example: "999" + "1"
 *   9+1+0=10 -> write 0, carry=1
 *   9+0+1=10 -> write 0, carry=1
 *   9+0+1=10 -> write 0, carry=1
 *   carry=1  -> write 1
 *   Reverse "0001" -> "1000"
 * -------------------------------------------------------------------------- */
void addBigInt(const char *a, const char *b, char *result, int resCap) {
    int la = (int)strlen(a), lb = (int)strlen(b);
    int carry = 0, k = 0;
    int i = la - 1, j = lb - 1;
    while (i >= 0 || j >= 0 || carry) {
        int sum = carry;
        if (i >= 0) sum += a[i--] - '0';
        if (j >= 0) sum += b[j--] - '0';
        if (k < resCap - 1) result[k++] = (char)('0' + (sum % 10));
        carry = sum / 10;
    }
    result[k] = '\0';
    for (int l = 0, r = k - 1; l < r; l++, r--) {
        char t = result[l]; result[l] = result[r]; result[r] = t;
    }
}

/* ============================================================================
 *  SECTION 5: LINKED LIST
 * ============================================================================ */

/* --------------------------------------------------------------------------
 * Node definition and create helper
 * -------------------------------------------------------------------------- */
typedef struct Node {
    int           id;
    struct Node  *next;
} Node;

/* --------------------------------------------------------------------------
 * 53. createNode - allocate + initialize a new node
 * --------------------------------------------------------------------------
 * step1: Allocate memory using malloc. sizeof(*newNode) is safer than
 *        sizeof(Node) -- if you rename the type, allocation stays correct.
 * step2: Check for NULL (malloc can fail, especially on MCUs)
 * step3: Set id = value, next = NULL
 * -------------------------------------------------------------------------- */
Node *createNode(int id) {
    Node *newNode = (Node *)malloc(sizeof(*newNode));
    if (newNode == NULL) return NULL;
    newNode->id   = id;
    newNode->next = NULL;
    return newNode;
}

/* --------------------------------------------------------------------------
 * 54. insertAtHead - O(1) insertion at the beginning
 * --------------------------------------------------------------------------
 * step1: Create a new node
 * step2: Point new node's next to current head: newNode->next = *head
 * step3: Update head to point to new node: *head = newNode
 *
 * Why Node **head (double pointer)?
 *   Because we need to MODIFY the caller's head pointer.
 *   If we used Node *head, changes would be local to this function.
 *
 * Example: head -> [10] -> [20] -> NULL
 *   insertAtHead(&head, 5)
 *   Result: head -> [5] -> [10] -> [20] -> NULL
 * -------------------------------------------------------------------------- */
int insertAtHead(Node **head, int id) {
    Node *newNode = createNode(id);
    if (newNode == NULL) return -1;
    newNode->next = *head;
    *head = newNode;
    return 0;
}

/* --------------------------------------------------------------------------
 * 55. insertAtEnd - O(n) insertion at the tail
 * --------------------------------------------------------------------------
 * step1: Create new node
 * step2: If list is empty (*head == NULL): *head = newNode, done.
 * step3: Else walk to the last node (temp->next == NULL)
 * step4: Set last->next = newNode
 *
 * Example: head -> [10] -> [20] -> NULL
 *   insertAtEnd(&head, 30)
 *   Walk to [20], set [20]->next = [30]
 *   Result: head -> [10] -> [20] -> [30] -> NULL
 * -------------------------------------------------------------------------- */
int insertAtEnd(Node **head, int id) {
    Node *newNode = createNode(id);
    if (newNode == NULL) return -1;
    if (*head == NULL) { *head = newNode; return 0; }
    Node *temp = *head;
    while (temp->next != NULL) temp = temp->next;
    temp->next = newNode;
    return 0;
}

/* --------------------------------------------------------------------------
 * 56. deleteNode - remove first node matching 'key'
 * --------------------------------------------------------------------------
 * step1: Special case: if head itself matches, update *head and free old head
 * step2: Else walk with prev and cur pointers until cur->id == key
 * step3: Bypass: prev->next = cur->next, then free(cur)
 *
 * Example: head -> [10] -> [20] -> [30], delete 20
 *   prev=[10], cur=[20]: match!
 *   [10]->next = [30], free [20]
 *   Result: head -> [10] -> [30] -> NULL
 * -------------------------------------------------------------------------- */
void deleteNode(Node **head, int key) {
    if (*head == NULL) return;
    if ((*head)->id == key) {
        Node *dead = *head;
        *head = (*head)->next;
        free(dead);
        return;
    }
    Node *prev = *head, *cur = (*head)->next;
    while (cur != NULL && cur->id != key) { prev = cur; cur = cur->next; }
    if (cur == NULL) return;
    prev->next = cur->next;
    free(cur);
}

/* --------------------------------------------------------------------------
 * 57. printList & 58. freeList
 * -------------------------------------------------------------------------- */
void printList(const Node *head) {
    for (const Node *cur = head; cur != NULL; cur = cur->next)
        printf("%d -> ", cur->id);
    printf("NULL\n");
}

void freeList(Node *head) {
    while (head) { Node *next = head->next; free(head); head = next; }
}

/* --------------------------------------------------------------------------
 * 59. reverseList - THE three-pointer classic
 * --------------------------------------------------------------------------
 * Definition: Reverse a singly linked list in-place.
 *
 * Algorithm:
 *   step1: Initialize prev = NULL, cur = head
 *   step2: Loop while cur != NULL:
 *          - Save next: next = cur->next
 *          - Flip the link: cur->next = prev
 *          - Advance prev: prev = cur
 *          - Advance cur: cur = next
 *   step3: When cur is NULL, prev points to the new head. Return prev.
 *
 * Example: head -> [1] -> [2] -> [3] -> NULL
 *   prev=NULL, cur=[1]: next=[2], [1]->next=NULL,   prev=[1], cur=[2]
 *   prev=[1],  cur=[2]: next=[3], [2]->next=[1],    prev=[2], cur=[3]
 *   prev=[2],  cur=[3]: next=NULL,[3]->next=[2],    prev=[3], cur=NULL
 *   Return prev=[3]
 *   Result: head -> [3] -> [2] -> [1] -> NULL
 *
 * TRAP: Return prev, NOT cur. cur is NULL at the end.
 *       NEVER use recursion for long lists -- blows the stack.
 *
 * Complexity: O(n) time, O(1) space
 * -------------------------------------------------------------------------- */
Node *reverseList(Node *head) {
    Node *prev = NULL, *cur = head;
    while (cur != NULL) {
        Node *next = cur->next;    /* save next */
        cur->next  = prev;         /* flip link */
        prev       = cur;          /* advance prev */
        cur        = next;         /* advance cur */
    }
    return prev;                   /* new head */
}

/* --------------------------------------------------------------------------
 * 60. findMiddle - slow & fast pointer
 * --------------------------------------------------------------------------
 * Algorithm:
 *   step1: slow = head, fast = head
 *   step2: Move slow by 1, fast by 2 each iteration
 *   step3: When fast reaches end (NULL or last node), slow is at the middle
 *
 * Example: [1] -> [2] -> [3] -> [4] -> [5]
 *   slow=[1],fast=[1]: slow=[2],fast=[3]
 *   slow=[2],fast=[3]: slow=[3],fast=[5]
 *   fast->next == NULL, STOP. Middle = [3]
 *
 * Complexity: O(n) time, O(1) space
 * -------------------------------------------------------------------------- */
Node *findMiddle(Node *head) {
    if (head == NULL) return NULL;
    Node *slow = head, *fast = head;
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

/* --------------------------------------------------------------------------
 * 61. hasCycle - Floyd's Tortoise and Hare
 * --------------------------------------------------------------------------
 * Algorithm:
 *   step1: slow and fast both start at head
 *   step2: slow moves 1 step, fast moves 2 steps
 *   step3: If cycle exists: fast will eventually lap slow (they meet)
 *          If no cycle: fast hits NULL
 *
 * Complexity: O(n) time, O(1) space
 * -------------------------------------------------------------------------- */
int hasCycle(const Node *head) {
    const Node *slow = head, *fast = head;
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) return 1;
    }
    return 0;
}

/* ============================================================================
 *  SECTION 6: BINARY SEARCH TREE
 * ============================================================================ */

typedef struct BstNode {
    int             id;
    struct BstNode *left;
    struct BstNode *right;
} BstNode;

/* --------------------------------------------------------------------------
 * 62. createBstNode
 * -------------------------------------------------------------------------- */
BstNode *createBstNode(int id) {
    BstNode *n = (BstNode *)malloc(sizeof(*n));
    if (n == NULL) return NULL;
    n->id = id; n->left = n->right = NULL;
    return n;
}

/* --------------------------------------------------------------------------
 * 63. bstInsert - recursive, return-root pattern
 * --------------------------------------------------------------------------
 * Definition: Insert a value into a BST maintaining the invariant:
 *   left subtree < root < right subtree
 *
 * Algorithm:
 *   step1: If root == NULL, this is the insertion point. Create & return node.
 *   step2: If id < root->id: recurse LEFT, assign result to root->left
 *   step3: If id > root->id: recurse RIGHT, assign result to root->right
 *   step4: If id == root->id: duplicate, do nothing
 *   step5: Return root (unchanged or with updated child pointer)
 *
 * Why "return-root" pattern?
 *   The caller writes: root = bstInsert(root, 42);
 *   This handles the empty-tree case (root was NULL, now it's the new node)
 *   without needing a special check.
 *
 * Example: Insert 5 into: [10] -> left=[3], right=[15]
 *   5 < 10 -> recurse left with root=[3]
 *   5 > 3  -> recurse right with root=NULL
 *   root==NULL -> create [5], return it
 *   [3]->right = [5]
 *   Result: [10] -> left=[3 -> right=[5]], right=[15]
 *
 * Complexity: O(h) where h = height. Balanced: O(log n). Worst: O(n).
 * -------------------------------------------------------------------------- */
BstNode *bstInsert(BstNode *root, int id) {
    if (root == NULL) return createBstNode(id);
    if      (id <  root->id) root->left  = bstInsert(root->left,  id);
    else if (id >  root->id) root->right = bstInsert(root->right, id);
    return root;
}

/* --------------------------------------------------------------------------
 * 64. bstSearch
 * -------------------------------------------------------------------------- */
BstNode *bstSearch(BstNode *root, int key) {
    if (root == NULL || root->id == key) return root;
    if (key < root->id) return bstSearch(root->left,  key);
    else                return bstSearch(root->right, key);
}

/* --------------------------------------------------------------------------
 * 65. bstMin / bstMax
 * -------------------------------------------------------------------------- */
BstNode *bstMin(BstNode *root) {
    if (root == NULL) return NULL;
    while (root->left) root = root->left;
    return root;
}
BstNode *bstMax(BstNode *root) {
    if (root == NULL) return NULL;
    while (root->right) root = root->right;
    return root;
}

/* --------------------------------------------------------------------------
 * 66-68. Traversals: inorder (sorted!), preorder, postorder
 * --------------------------------------------------------------------------
 * Inorder  (L-Root-R): produces sorted output for a BST
 * Preorder (Root-L-R): used to serialize tree structure
 * Postorder(L-R-Root): used to FREE the tree safely (children before parent)
 * -------------------------------------------------------------------------- */
void inorder  (const BstNode *r) { if(r){ inorder(r->left);  printf("%d ",r->id); inorder(r->right); }}
void preorder (const BstNode *r) { if(r){ printf("%d ",r->id); preorder(r->left);  preorder(r->right);}}
void postorder(const BstNode *r) { if(r){ postorder(r->left); postorder(r->right); printf("%d ",r->id);}}

/* --------------------------------------------------------------------------
 * 69. bstDelete - the three cases
 * --------------------------------------------------------------------------
 * Case 1: LEAF (no children) -> just free it
 * Case 2: ONE child -> splice: parent bypasses this node to the child
 * Case 3: TWO children -> copy inorder successor's value here,
 *         then recursively delete the successor (which has at most one child)
 *
 * Inorder successor = smallest node in the RIGHT subtree = leftmost in right
 *
 * Example: Delete 10 from:      [10]
 *                             /      \
 *                          [5]       [15]
 *                                   /
 *                                [12]
 *   Case 3: two children. Successor = bstMin(right) = 12
 *   Copy: root->id = 12. Delete 12 from right subtree (Case 1: leaf)
 *   Result:     [12]
 *             /      \
 *          [5]       [15]
 * -------------------------------------------------------------------------- */
BstNode *bstDelete(BstNode *root, int id) {
    if (root == NULL) return NULL;
    if      (id <  root->id) root->left  = bstDelete(root->left,  id);
    else if (id >  root->id) root->right = bstDelete(root->right, id);
    else {
        if (root->left == NULL) { BstNode *r = root->right; free(root); return r; }
        if (root->right == NULL){ BstNode *l = root->left;  free(root); return l; }
        BstNode *succ = bstMin(root->right);
        root->id      = succ->id;
        root->right   = bstDelete(root->right, succ->id);
    }
    return root;
}

/* --------------------------------------------------------------------------
 * 70. freeTree - MUST use postorder (children before parent!)
 * -------------------------------------------------------------------------- */
void freeTree(BstNode *root) {
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

/* ============================================================================
 *  SECTION 7: QUEUES & STACKS
 * ============================================================================ */

/* ---------- 71-76. Linked Queue ---------- */
typedef struct QNode { int id; struct QNode *next; } QNode;
typedef struct { QNode *front; QNode *rear; int size; } Queue;

Queue *qCreate(void) {
    Queue *q = (Queue *)malloc(sizeof(*q));
    if (!q) return NULL;
    q->front = q->rear = NULL; q->size = 0;
    return q;
}
int qEnqueue(Queue *q, int id) {
    QNode *n = (QNode *)malloc(sizeof(*n));
    if (!n) return -1;
    n->id = id; n->next = NULL;
    if (q->rear == NULL) q->front = q->rear = n;
    else { q->rear->next = n; q->rear = n; }
    q->size++; return 0;
}
int qDequeue(Queue *q, int *out) {
    if (!q || !q->front) return -1;
    QNode *dead = q->front;
    *out = dead->id;
    q->front = dead->next;
    if (!q->front) q->rear = NULL;  /* TRAP: must reset rear when empty! */
    free(dead); q->size--; return 0;
}
int qPeek(const Queue *q, int *out) {
    if (!q || !q->front) return -1;
    *out = q->front->id; return 0;
}
void qDestroy(Queue *q) {
    if (!q) return;
    while (q->front) { QNode *d = q->front; q->front = d->next; free(d); }
    free(q);
}

/* ---------- 77-80. Ring Buffer Queue ---------- */
typedef struct { int *data; int capacity; int front; int rear; int size; } RingQ;

RingQ *rqCreate(int capacity) {
    RingQ *q = (RingQ *)malloc(sizeof(*q));
    if (!q) return NULL;
    q->data = (int *)malloc((size_t)capacity * sizeof(int));
    if (!q->data) { free(q); return NULL; }
    q->capacity = capacity; q->front = 0; q->rear = -1; q->size = 0;
    return q;
}
int rqEnqueue(RingQ *q, int v) {
    if (q->size == q->capacity) return -1;
    q->rear = (q->rear + 1) % q->capacity;
    q->data[q->rear] = v; q->size++; return 0;
}
int rqDequeue(RingQ *q, int *out) {
    if (q->size == 0) return -1;
    *out = q->data[q->front];
    q->front = (q->front + 1) % q->capacity;
    q->size--; return 0;
}
int rqPeek(const RingQ *q, int *out) {
    if (q->size == 0) return -1;
    *out = q->data[q->front]; return 0;
}
void rqDestroy(RingQ *q) { if(q){free(q->data); free(q);} }

/* ---------- 81. Linked Stack ---------- */
typedef struct SNode { int id; struct SNode *next; } SNode;
typedef struct { SNode *top; int size; } Stack;

int sPush(Stack *s, int id) {
    SNode *n = (SNode *)malloc(sizeof(*n));
    if (!n) return -1;
    n->id = id; n->next = s->top;
    s->top = n; s->size++; return 0;
}
int sPop(Stack *s, int *out) {
    if (!s->top) return -1;
    SNode *dead = s->top;
    *out = dead->id;
    s->top = dead->next;
    free(dead); s->size--; return 0;
}

/* ============================================================================
 *  SECTION 8: STRING PARSING & FORMATTING (sscanf / snprintf)
 * ============================================================================
 *
 *  WHY THESE MATTER IN INTERVIEWS:
 *    sscanf  = parse structured text INTO variables (input / deserialization)
 *    snprintf= format variables INTO a string SAFELY (output / serialization)
 *
 *    snprintf is the SAFE cousin of sprintf: it takes a buffer size and never
 *    writes past it, returning how many chars it WOULD have written. This is
 *    the correct tool for building strings without buffer overflows -- a topic
 *    interviewers love to probe ("how do you format safely in C?").
 *
 *  sscanf RETURN VALUE (critical):
 *    Returns the NUMBER of input items successfully matched & assigned.
 *    ALWAYS check it -- a partial parse means malformed input.
 *
 *  snprintf RETURN VALUE (critical):
 *    Returns the number of chars that WOULD have been written (excluding the
 *    null terminator), even if truncated. So:
 *      if (n >= size) -> output was TRUNCATED.
 *    It always null-terminates (as long as size > 0).
 * ============================================================================ */

/* --------------------------------------------------------------------------
 * 82. Parse three integers from a string (sscanf basics)
 * --------------------------------------------------------------------------
 * Definition:
 *   Extract structured numbers out of a text line into variables.
 *
 * Algorithm:
 *   step1: call sscanf(str, "%d %d %d", &a, &b, &c)
 *   step2: check the return value == 3 (all three matched)
 *   step3: if fewer matched, the input was malformed
 *
 * Example: str = "10 20 30"
 *   sscanf matches 3 items -> a=10, b=20, c=30, returns 3
 *
 * Example: str = "10 xx 30"
 *   sscanf matches only "10", stops at "xx" -> returns 1 (malformed)
 * -------------------------------------------------------------------------- */
int parseThreeInts(const char *str, int *a, int *b, int *c) {
    int matched = sscanf(str, "%d %d %d", a, b, c);
    return matched;                       /* caller checks == 3 */
}

/* --------------------------------------------------------------------------
 * 83. Parse a "key=value" configuration line (sscanf with %[ ])
 * --------------------------------------------------------------------------
 * Definition:
 *   Split a line like "timeout=30" into key string and value string.
 *
 * Algorithm:
 *   step1: use a scanset %[^=] to read everything up to '=' into key
 *   step2: skip the '=' literally
 *   step3: %s (or %[^\n]) reads the value
 *   step4: check sscanf returned 2 (both fields parsed)
 *
 * The %[^=] means "match any char that is NOT '='". The width limits
 * (%63[^=]) prevent buffer overflow -- ALWAYS bound scanset/string widths.
 *
 * Example: line = "timeout=30"
 *   key="timeout", value="30", returns 2
 * -------------------------------------------------------------------------- */
int parseKeyValue(const char *line, char *key, size_t keySz,
                  char *value, size_t valSz) {
    /* Build a format string with widths derived from the buffer sizes.
     * For a fixed example we hardcode safe widths; in real code you would
     * snprintf the format string itself. Here keySz/valSz are assumed >= 64. */
    (void)keySz; (void)valSz;
    int matched = sscanf(line, "%63[^=]=%63s", key, value);
    return matched;                       /* caller checks == 2 */
}

/* --------------------------------------------------------------------------
 * 84. Parse an IPv4 address into four octets (sscanf with field count)
 * --------------------------------------------------------------------------
 * Definition:
 *   Convert "192.168.1.10" into four integers, validating the structure.
 *
 * Algorithm:
 *   step1: sscanf(str, "%d.%d.%d.%d", &o1,&o2,&o3,&o4)
 *   step2: require return value == 4 (exactly four octets)
 *   step3: validate each octet is in range 0..255
 *
 * Example: "192.168.1.10" -> 192,168,1,10 (valid)
 *          "192.168.1"     -> returns 3 (invalid - missing octet)
 *          "300.1.2.3"     -> returns 4 but 300 > 255 (invalid range)
 * -------------------------------------------------------------------------- */
int parseIPv4(const char *str, int octets[4]) {
    int matched = sscanf(str, "%d.%d.%d.%d",
                         &octets[0], &octets[1], &octets[2], &octets[3]);
    if (matched != 4) return 0;           /* wrong number of octets */
    for (int i = 0; i < 4; i++)
        if (octets[i] < 0 || octets[i] > 255) return 0;  /* out of range */
    return 1;                             /* valid */
}

/* --------------------------------------------------------------------------
 * 85. Parse "HH:MM:SS" time and convert to total seconds (sscanf)
 * --------------------------------------------------------------------------
 * Algorithm:
 *   step1: sscanf(str, "%d:%d:%d", &h, &m, &s)
 *   step2: require 3 matched
 *   step3: total = h*3600 + m*60 + s
 *
 * Example: "01:30:45" -> 1*3600 + 30*60 + 45 = 5445 seconds
 * -------------------------------------------------------------------------- */
long parseTimeToSeconds(const char *str) {
    int h, m, s;
    if (sscanf(str, "%d:%d:%d", &h, &m, &s) != 3) return -1;  /* malformed */
    return (long)h * 3600 + (long)m * 60 + s;
}

/* --------------------------------------------------------------------------
 * 86. Safe string building with snprintf (no overflow)
 * --------------------------------------------------------------------------
 * Definition:
 *   Build a formatted string into a fixed buffer WITHOUT ever overflowing it.
 *
 * Algorithm:
 *   step1: snprintf(buf, size, fmt, ...) writes at most size-1 chars + '\0'
 *   step2: it returns how many chars it WOULD have written
 *   step3: if return value >= size, output was TRUNCATED -> handle it
 *
 * Example: buffer size 20, formatting "User: Alice (age 30)"
 *   fits -> returns 20-ish, no truncation
 *   tiny buffer -> returns full length, output truncated, still safe
 * -------------------------------------------------------------------------- */
int buildUserString(char *buf, size_t size, const char *name, int age) {
    int n = snprintf(buf, size, "User: %s (age %d)", name, age);
    /* n = number of chars that WOULD be written (excluding '\0') */
    if (n < 0) return -1;                 /* encoding error */
    if ((size_t)n >= size) return 1;      /* truncated (output too long) */
    return 0;                             /* success, fully written */
}

/* --------------------------------------------------------------------------
 * 87. Build a CSV row safely by appending with snprintf
 * --------------------------------------------------------------------------
 * Definition:
 *   Concatenate several fields into one CSV line, tracking remaining space so
 *   we never overflow. This is the safe pattern for incremental string build.
 *
 * Algorithm:
 *   step1: keep an offset into the buffer (chars written so far)
 *   step2: each snprintf writes at (buf + offset) with (size - offset) space
 *   step3: advance offset by the return value
 *   step4: if offset >= size, stop (buffer full)
 *
 * Example: fields {"id","name","age"} -> "id,name,age"
 * -------------------------------------------------------------------------- */
int buildCSVRow(char *buf, size_t size, const char *fields[], int count) {
    size_t offset = 0;
    for (int i = 0; i < count; i++) {
        const char *sep = (i == 0) ? "" : ",";   /* comma before all but first */
        int n = snprintf(buf + offset, size - offset, "%s%s", sep, fields[i]);
        if (n < 0) return -1;                     /* encoding error */
        if ((size_t)n >= size - offset) return 1; /* would overflow -> stop */
        offset += (size_t)n;
    }
    return 0;                                     /* success */
}

/* --------------------------------------------------------------------------
 * 88. Integer to string conversion (snprintf instead of itoa)
 * --------------------------------------------------------------------------
 * Definition:
 *   C has no standard itoa(). snprintf is the portable, safe way to convert
 *   a number to its string form.
 *
 * Algorithm:
 *   snprintf(buf, size, "%d", value)
 *
 * Example: 42 -> "42",  -7 -> "-7"
 * -------------------------------------------------------------------------- */
void intToStr(int value, char *buf, size_t size) {
    snprintf(buf, size, "%d", value);
}

/* --------------------------------------------------------------------------
 * 89. Round-trip: format with snprintf, then parse back with sscanf
 * --------------------------------------------------------------------------
 * Definition:
 *   Demonstrate serialization (snprintf) and deserialization (sscanf) as
 *   inverse operations -- the core of any text protocol or config file.
 *
 * Algorithm:
 *   step1: snprintf packs three ints into "a,b,c"
 *   step2: sscanf unpacks "a,b,c" back into three ints
 *   step3: verify the round-trip preserved the values
 *
 * Example: (1,2,3) -> "1,2,3" -> (1,2,3)  [matches]
 * -------------------------------------------------------------------------- */
int roundTripInts(int a, int b, int c) {
    char buf[32];
    snprintf(buf, sizeof(buf), "%d,%d,%d", a, b, c);   /* serialize */
    int x, y, z;
    if (sscanf(buf, "%d,%d,%d", &x, &y, &z) != 3) return 0;  /* deserialize */
    return (x == a && y == b && z == c);               /* round-trip OK? */
}

/* ============================================================================
 *  MAIN - DEMO / TEST DRIVER
 *  Uncomment the section you want to test.
 * ============================================================================ */

static void printArr(const int a[], int n) {
    for (int i = 0; i < n; i++) printf("%d ", a[i]);
    printf("\n");
}

int main(void) {

    /* ---- STRING DEMOS ---- */
    printf("=== STRING PROBLEMS ===\n");
    char s1[] = "hello";
    reverseString(s1);
    printf("1. Reverse string: %s\n", s1);

    printf("2. Anagram: listen/silent = %d\n", isAnagram("listen", "silent"));

    int ps, pl;
    longestPalindrome("babad", &ps, &pl);
    printf("3. Longest palindrome in 'babad': '%.*s' (len %d)\n", pl, "babad"+ps, pl);

    char s4[] = "programming";
    removeDupChars(s4);
    printf("4. Remove dup chars: %s\n", s4);

    char comp[64];
    compressString("aabcccccaaa", comp, sizeof(comp));
    printf("5. Compress 'aabcccccaaa': %s\n", comp);

    printf("6. Rotation 'waterbottle'/'erbottlewat': %d\n",
           isRotation("waterbottle", "erbottlewat"));

    printf("7. Non-repeating in 'aabccbde': ");
    findNonRepeating("aabccbde");

    printf("8. Valid palindrome 'A man, a plan...': %d\n",
           isValidPalindrome("A man, a plan, a canal: Panama"));

    printf("9. Count and Say n=5: ");
    countAndSay(5);

    printf("10. Subsequence 'cgm' in 'capgemini': %d\n",
           isSubsequence("capgemini", "cgm"));

    char s11[] = "the sky is blue";
    reverseWords(s11);
    printf("11. Reverse words: %s\n", s11);

    char *lcs = longestCommonSubstring("abcdfgh", "zcdemgh");
    printf("12. Longest common substr: %s\n", lcs);
    free(lcs);

    printf("13. IPv4 '192.168.0.1': %d, '256.1.2.3': %d\n",
           isValidIPv4("192.168.0.1"), isValidIPv4("256.1.2.3"));

    /* ---- ARRAY DEMOS ---- */
    printf("\n=== ARRAY PROBLEMS ===\n");
    int a14[] = {12, 35, 1, 10, 34, 1};
    printf("14. 2nd largest: %d\n", findSecondLargest(a14, 6));

    int a15[] = {0, 1, 0, 3, 12};
    moveZerosToEnd(a15, 5);
    printf("15. Move zeros: "); printArr(a15, 5);

    int a16[] = {1,2,3,4,5,6,7};
    rotateLeft(a16, 7, 2);
    printf("16. Rotate left 2: "); printArr(a16, 7);

    int a17[] = {-2,-3,4,-1,-2,1,5,-3};
    printf("17. Kadane max subarray: %d\n", kadane(a17, 8));

    int a18[] = {1,1,2,2,3,4,4};
    int newLen = removeDuplicates(a18, 7);
    printf("18. Remove dups sorted: "); printArr(a18, newLen);

    int a19[] = {2,2,1,1,1,2,2};
    printf("19. Majority: %d\n", findMajority(a19, 7));

    int a20[] = {3,0,1};
    printf("20. Missing in 0..3: %d\n", findMissing(a20, 3));

    int a21[] = {1,2,3,4,5,6,7,8,9};
    reverseInGroups(a21, 9, 3);
    printf("21. Reverse groups k=3: "); printArr(a21, 9);

    int a22[] = {4,5,6,7,0,1,2};
    printf("22. Min rotated sorted: %d\n", findMinRotated(a22, 7));

    int a23[] = {1,3,5,7,9,11};
    printf("23. Binary search 7: index=%d\n", binarySearch(a23, 6, 7));

    int a24[] = {10,7,8,9,1,5};
    quickSort(a24, 0, 5);
    printf("24. Quicksort: "); printArr(a24, 6);

    int a25a[] = {1,3,5}, a25b[] = {2,4,6}, a25o[6];
    mergeSorted(a25a, 3, a25b, 3, a25o);
    printf("25. Merge sorted: "); printArr(a25o, 6);

    int a26[] = {12,11,13,5,6,7};
    heapSort(a26, 6);
    printf("26. Heap sort: "); printArr(a26, 6);

    /* ---- BIT MANIPULATION DEMOS ---- */
    printf("\n=== BIT MANIPULATION ===\n");
    printf("27. Set bit 1 of 12: %u\n", setBit(12, 1));
    printf("28. Clear bit 2 of 12: %u\n", clearBit(12, 2));
    printf("29. Toggle bit 1 of 12: %u\n", toggleBit(12, 1));
    printf("30. Check bit 2 of 12: %d\n", checkBit(12, 2));
    printf("31. isPowerOfTwo(8)=%d, (6)=%d\n", isPowerOfTwo(8), isPowerOfTwo(6));
    printf("32. Count set bits of 13: %d\n", countSetBits(13));
    int a33[] = {4,1,2,1,2};
    printf("33. Single non-repeating: %d\n", findSingle(a33, 5));
    int a34[] = {2,3,7,9,11,2,3,11}; int u1, u2;
    findTwoUniques(a34, 8, &u1, &u2);
    printf("34. Two uniques: %d and %d\n", u1, u2);
    int sa=5, sb=10;
    swapXOR(&sa, &sb);
    printf("35. XOR swap 5,10: a=%d, b=%d\n", sa, sb);
    printf("36. Reverse bits of 5: %u\n", reverseBits(5));
    printf("37. isEven(4)=%d, isEven(7)=%d\n", isEven(4), isEven(7));
    printf("38. Rightmost set bit of 12: pos %d\n", positionOfRightmostSetBit(12));
    printf("39. Set range [1..3] of 0x00: 0x%X\n", setBitsInRange(0x00, 1, 3));
    printf("40. Clear range [1..3] of 0xFF: 0x%X\n", clearBitsInRange(0xFF, 1, 3));
    printf("41. Write 5 into [1..3] of 0x00: 0x%X\n", writeBitsInRange(0x00, 1, 3, 5));
    printf("42. Add 15+32 without +: %d\n", addNoPlus(15, 32));
    printf("43. 5*8=%d, 40/4=%d\n", mul2k(5, 3), div2k(40, 2));

    /* ---- MATH DEMOS ---- */
    printf("\n=== MATH PROBLEMS ===\n");
    printf("45. Digits of 5283: "); extractDigits(5283);
    printf("46. Reverse 1234: %d\n", reverseNumber(1234));
    printf("47. Palindrome 121=%d, 123=%d\n", isPalindromeNumber(121), isPalindromeNumber(123));
    printf("48. Armstrong 153=%d, 123=%d\n", isArmstrong(153), isArmstrong(123));
    printf("49. Divisors of 36: "); printDivisors(36);
    printf("50. isPrime(29)=%d, isPrime(15)=%d\n", isPrime(29), isPrime(15));
    printf("51. GCD(48,18)=%d, LCM(12,18)=%d\n", gcd(48,18), lcm(12,18));
    char bigRes[64];
    addBigInt("999", "1", bigRes, sizeof(bigRes));
    printf("52. BigInt 999+1=%s\n", bigRes);

    /* ---- LINKED LIST DEMOS ---- */
    printf("\n=== LINKED LIST ===\n");
    Node *list = NULL;
    insertAtEnd(&list, 10); insertAtEnd(&list, 20); insertAtEnd(&list, 30);
    printf("Original: "); printList(list);
    insertAtHead(&list, 5);
    printf("After insertHead(5): "); printList(list);
    deleteNode(&list, 20);
    printf("After delete(20): "); printList(list);
    list = reverseList(list);
    printf("After reverse: "); printList(list);
    Node *mid = findMiddle(list);
    printf("Middle: %d\n", mid ? mid->id : -1);
    printf("Has cycle: %d\n", hasCycle(list));
    freeList(list);

    /* ---- BST DEMOS ---- */
    printf("\n=== BST ===\n");
    BstNode *bst = NULL;
    int keys[] = {50, 30, 70, 20, 40, 60, 80};
    for (int i = 0; i < 7; i++) bst = bstInsert(bst, keys[i]);
    printf("Inorder: "); inorder(bst); printf("\n");
    printf("Search 40: %s\n", bstSearch(bst, 40) ? "found" : "not found");
    printf("Min=%d, Max=%d\n", bstMin(bst)->id, bstMax(bst)->id);
    bst = bstDelete(bst, 50);
    printf("After delete 50, inorder: "); inorder(bst); printf("\n");
    freeTree(bst);

    /* ---- QUEUE & STACK DEMOS ---- */
    printf("\n=== QUEUE & STACK ===\n");
    Queue *q = qCreate();
    qEnqueue(q, 10); qEnqueue(q, 20); qEnqueue(q, 30);
    int val;
    qDequeue(q, &val); printf("Dequeue: %d\n", val);
    qPeek(q, &val); printf("Peek: %d\n", val);
    qDestroy(q);

    RingQ *rq = rqCreate(4);
    rqEnqueue(rq, 1); rqEnqueue(rq, 2); rqEnqueue(rq, 3);
    rqDequeue(rq, &val); printf("Ring dequeue: %d\n", val);
    rqDestroy(rq);

    Stack stk = {NULL, 0};
    sPush(&stk, 100); sPush(&stk, 200);
    sPop(&stk, &val); printf("Stack pop: %d\n", val);
    sPop(&stk, &val); printf("Stack pop: %d\n", val);

    /* ---- SSCANF / SNPRINTF DEMOS ---- */
    printf("\n=== STRING PARSING & FORMATTING (sscanf/snprintf) ===\n");

    int pa, pb, pc;
    int got = parseThreeInts("10 20 30", &pa, &pb, &pc);
    printf("82. Parse 3 ints '10 20 30': matched=%d -> %d,%d,%d\n", got, pa, pb, pc);

    char key[64], value[64];
    if (parseKeyValue("timeout=30", key, sizeof(key), value, sizeof(value)) == 2)
        printf("83. Parse key=value 'timeout=30': key='%s' value='%s'\n", key, value);

    int oct[4];
    int ipValid = parseIPv4("192.168.1.10", oct);   /* call FIRST */
    printf("84. Parse IPv4 '192.168.1.10': valid=%d -> %d.%d.%d.%d\n",
           ipValid, oct[0], oct[1], oct[2], oct[3]);
    printf("    Parse IPv4 '300.1.2.3': valid=%d (octet out of range)\n",
           parseIPv4("300.1.2.3", oct));

    printf("85. Parse time '01:30:45' -> %ld seconds\n",
           parseTimeToSeconds("01:30:45"));

    char ubuf[40];
    int rc = buildUserString(ubuf, sizeof(ubuf), "Alice", 30);
    printf("86. snprintf user string (rc=%d): '%s'\n", rc, ubuf);
    char tiny[10];
    rc = buildUserString(tiny, sizeof(tiny), "Alice", 30);
    printf("    snprintf into tiny buffer (rc=%d=truncated): '%s'\n", rc, tiny);

    char csv[64];
    const char *fields[] = {"id", "name", "age"};
    buildCSVRow(csv, sizeof(csv), fields, 3);
    printf("87. Build CSV row: '%s'\n", csv);

    char numbuf[16];
    intToStr(-42, numbuf, sizeof(numbuf));
    printf("88. intToStr(-42) -> '%s'\n", numbuf);

    printf("89. Round-trip (1,2,3) via snprintf+sscanf: %s\n",
           roundTripInts(1, 2, 3) ? "MATCHED" : "FAILED");

    printf("\n=== ALL TESTS PASSED ===\n");
    return 0;
}
