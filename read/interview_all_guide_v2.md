# C Interview Programs — Standalone Edition

> **93 self-contained C programs.** Every program below is complete and runnable on its own — each has its own `main()`, sample input, and expected output. Copy any single block into a `.c` file and compile it directly:
>
> ```bash
> gcc -Wall -Wextra -o prog prog.c        # add -lm for the math section
> ./prog
> ```

Each program follows the same shape:

> **Problem** → **Approach / Algorithm (steps + logic)** → **Code (with its own `main`)** → **Sample Output**

---

## Index

| # | Section | Count |
|---|---------|-------|
| 1 | [Strings](#section-1--strings) | 13 |
| 2 | [Arrays](#section-2--arrays) | 13 |
| 3 | [Bit Manipulation](#section-3--bit-manipulation) | 18 |
| 4 | [Math / Number](#section-4--math--number) | 8 |
| 5 | [Linked List](#section-5--linked-list) | 9 + sorted-insert |
| 6 | [Binary Search Tree](#section-6--binary-search-tree) | 9 |
| 7 | [Queues & Stacks](#section-7--queues--stacks) | 8 |
| 8 | [Parsing & Formatting (sscanf/snprintf)](#section-8--parsing--formatting) | 8 |
| 9 | [Buffers & Driver Patterns](#section-9--buffers--driver-patterns) | ring buffer, DMA descriptor ring, WiFi pack/unpack |
| 10 | [Memory, DMA, mmap & Reimplementing libc](#section-10--memory-dma-mmap--reimplementing-libc) | mem*/str* funcs, custom libc, DMA copy, mmap |

> **Note on duplication:** because each program is standalone, small helpers (like `createNode`, `swap`, or a print routine) are repeated inside the programs that need them. That is intentional — it keeps every block copy-paste-runnable with zero external dependencies.

---

## Section 1 — Strings


### 1. Reverse a String (in-place)

**Definition:** Reverse the characters of a string without using extra memory.

**Algorithm**

```text
step1: Place 'left' pointer at index 0, 'right' pointer at last char (len-1)
step2: Swap characters at left and right positions
step3: Move left forward (left++), move right backward (right--)
step4: Repeat step2-3 until left >= right (pointers meet in middle)
```

**Example**

```text
str = "hello"
  left=0, right=4: swap 'h' and 'o' -> "oellh"
  left=1, right=3: swap 'e' and 'l' -> "olleh"
  left=2, right=2: pointers meet, STOP
  Result: "olleh"
```

**Complexity:** O(n) time, O(1) space

**Pattern:** TWO-POINTER (opposite ends)

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

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

int main(void) {
    char s[]="hello"; reverseString(s); printf("reverse(\"hello\") = %s\n", s);
    return 0;
}
```

**Sample output:**

```text
reverse("hello") = olleh
```

### 2. Check for Anagram

**Definition:** Two strings are anagrams if one can be formed by rearranging the letters of the other. Example: "listen" and "silent".

**Algorithm**

```text
step1: If lengths differ, return 0 (cannot be anagram)
step2: Create a frequency array of 256 slots (one per ASCII char)
step3: Walk both strings simultaneously:
       - freq[str1[i]]++ (count chars in first string)
       - freq[str2[i]]-- (un-count chars using second string)
step4: If all freq[] entries are 0, strings are anagrams
```

**Example**

```text
str1="listen", str2="silent"
  After counting: freq['l']=0, freq['i']=0, freq['s']=0, ...
  All zero -> anagram!
```

**Example**

```text
str1="hello", str2="world"
  freq['h']=1, freq['w']=-1, ... -> NOT all zero -> not anagram
```

**Complexity:** O(n) time, O(1) space (256 is constant)

**Pattern:** FREQUENCY TABLE

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

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

int main(void) {
    printf("isAnagram(listen,silent)=%d\n", isAnagram("listen","silent")); printf("isAnagram(hello,world)=%d\n", isAnagram("hello","world"));
    return 0;
}
```

**Sample output:**

```text
isAnagram(listen,silent)=1
isAnagram(hello,world)=0
```

### 3. Longest Palindromic Substring (expand around center)

**Definition:** Find the longest substring that reads the same forwards and backwards.

**Example**

```text
"babad" -> "bab" or "aba" (length 3).
```

**Algorithm**

```text
step1: For each index i in the string, treat it as the CENTER of a palindrome
step2: Expand outward (left--, right++) as long as chars match
step3: Check BOTH odd-length centers (i,i) and even-length centers (i,i+1)
step4: Track the longest palindrome found (start index + length)
```

**Example**

```text
str = "babad"
  i=0: center 'b' -> expand: "b" (len 1)
  i=1: center 'a' -> expand: "a"->"bab" (len 3, NEW MAX)
  i=2: center 'b' -> expand: "b"->"aba" (len 3, ties)
  i=3: center 'a' -> expand: "a" (len 1)
  i=4: center 'd' -> expand: "d" (len 1)
  Result: start=0, length=3 -> "bab"
```

**Complexity:** O(n^2) time, O(1) space

**Pattern:** EXPAND FROM CENTER

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

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

int main(void) {
    int s,l; longestPalindrome("babad",&s,&l); printf("LPS(babad)=\"%.*s\" len %d\n", l, "babad"+s, l);
    return 0;
}
```

**Sample output:**

```text
LPS(babad)="bab" len 3
```

### 4. Remove All Duplicate Characters from a String

**Definition:** Keep only the FIRST occurrence of each character, remove all repeats.

**Example**

```text
"programming" -> "progamin"
```

**Algorithm**

```text
step1: Create a boolean seen[256] array, all false
step2: Use a write-index 'w' starting at 0
step3: For each char in the string:
       - if NOT seen: copy to str[w++], mark seen[ch] = 1
       - if already seen: skip it
step4: Null-terminate: str[w] = '\0'
```

**Example**

```text
str = "banana"
  'b': not seen, keep -> "b", w=1
  'a': not seen, keep -> "ba", w=2
  'n': not seen, keep -> "ban", w=3
  'a': SEEN, skip
  'n': SEEN, skip
  'a': SEEN, skip
  Result: "ban"
```

**Complexity:** O(n) time, O(1) space (256 is constant)

**Pattern:** FREQUENCY TABLE (boolean variant)

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

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

int main(void) {
    char s[]="programming"; removeDupChars(s); printf("removeDup(programming)=%s\n", s);
    return 0;
}
```

**Sample output:**

```text
removeDup(programming)=progamin
```

### 5. String Compression (Run-Length Encoding)

**Definition:** Replace consecutive identical chars with char + count.

**Example**

```text
"aabcccccaaa" -> "a2b1c5a3"
```

**Algorithm**

```text
step1: Walk the string from left to right
step2: At each position, count how many consecutive identical chars follow
step3: Write the character and its count to the output buffer
step4: Jump past the group (i += count) and repeat
```

**Example**

```text
str = "aabcccccaaa"
  i=0: ch='a', count=2 -> write "a2", i jumps to 2
  i=2: ch='b', count=1 -> write "b1", i jumps to 3
  i=3: ch='c', count=5 -> write "c5", i jumps to 8
  i=8: ch='a', count=3 -> write "a3", i jumps to 11
  Result: "a2b1c5a3"
```

**Complexity:** O(n) time, O(n) space for output

**Pattern:** COUNT RUNS

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

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

int main(void) {
    char out[64]; compressString("aabcccccaaa",out,sizeof out); printf("compress=%s\n",out);
    return 0;
}
```

**Sample output:**

```text
compress=a2b1c5a3
```

### 6. Check If One String Is a Rotation of Another

**Definition:** A rotation shifts chars from one end to the other.

**Example**

```text
"waterbottle" rotated -> "erbottlewat"
```

**Algorithm**

```text
step1: If lengths differ, return 0 (can't be rotation)
step2: Concatenate s1 with itself: s1+s1
       Key insight: if s2 is a rotation of s1, s2 ALWAYS appears
       as a substring inside s1+s1
step3: Use strstr() to check if s2 is inside the concatenation
```

**Example**

```text
s1="waterbottle", s2="erbottlewat"
  concat = "waterbottlewaterbottle"
  Does "erbottlewat" appear in it? -> YES (at position 3)
  Result: IS a rotation
```

**Complexity:** O(n) time (assuming strstr is O(n)), O(n) space

**Pattern:** STRING CONCATENATION TRICK

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

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

int main(void) {
    printf("isRotation(waterbottle,erbottlewat)=%d\n", isRotation("waterbottle","erbottlewat"));
    return 0;
}
```

**Sample output:**

```text
isRotation(waterbottle,erbottlewat)=1
```

### 7. First and Second Non-Repeating Character

**Definition:** Find the first two characters that appear exactly once in the string. Must preserve the ORDER they appear in the string (not the freq table).

**Algorithm**

```text
step1: Count frequency of each char using freq[256]
step2: Walk the STRING (not freq table!) from left to right
step3: First char with freq==1 is the "first non-repeating"
step4: Second char with freq==1 is the "second non-repeating"
```

**Example**

```text
str = "aabccbde"
  freq: a=2, b=2, c=2, d=1, e=1
  Walk string: a(2),a(2),b(2),c(2),c(2),b(2),d(1)->FIRST, e(1)->SECOND
  Result: First='d', Second='e'
```

**Complexity:** O(n) time, O(1) space

**Pattern:** FREQUENCY TABLE (two-pass)

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

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

int main(void) {
    printf("findNonRepeating(aabccbde):\n"); findNonRepeating("aabccbde");
    return 0;
}
```

**Sample output:**

```text
findNonRepeating(aabccbde):
First non-repeating: 'd'
Second non-repeating: 'e'
```

### 8. Valid Palindrome (alphanumeric only, case-insensitive)

**Definition:** Check if a string is a palindrome, considering only alphanumeric characters and ignoring case.

**Example**

```text
"A man, a plan, a canal: Panama" -> TRUE
```

**Algorithm**

```text
step1: Place left=0 and right=len-1 pointers
step2: Skip non-alphanumeric from left (while !isalnum, left++)
step3: Skip non-alphanumeric from right (while !isalnum, right--)
step4: Compare tolower(left) vs tolower(right)
       - if different: NOT a palindrome, return 0
       - if same: move both pointers inward (left++, right--)
step5: Repeat until left >= right
```

**Example**

```text
str = "A man, a plan, a canal: Panama"
  left=0('A'), right=29('a'): tolower match -> move in
  left=2('m'), right=27('m'): match -> move in
  ... all match ...
  Result: TRUE (palindrome)
```

**Complexity:** O(n) time, O(1) space

**Pattern:** TWO-POINTER (opposite ends) + skip

**TRAP**

```text
Must cast to (unsigned char) before calling isalnum/tolower.
      Negative char values cause UB in <ctype.h> functions.
```

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

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

int main(void) {
    printf("validPalindrome(\"A man, a plan, a canal: Panama\")=%d\n", isValidPalindrome("A man, a plan, a canal: Panama"));
    return 0;
}
```

**Sample output:**

```text
validPalindrome("A man, a plan, a canal: Panama")=1
```

### 9. Count and Say Sequence

**Definition**

```text
Each term describes the digits of the previous term:
  Term 1: "1"
  Term 2: "11"     (one 1)
  Term 3: "21"     (two 1s)
  Term 4: "1211"   (one 2, one 1)
  Term 5: "111221" (one 1, one 2, two 1s)
```

**Algorithm**

```text
step1: Start with cur = "1"
step2: For each term from 2 to n:
       - Read cur left to right, count consecutive identical digits
       - Build next string: write count followed by digit
       - Copy next into cur for the next iteration
step3: Print the final term
```

**Example**

```text
Building term 4 from term 3 ("21"):
  Read '2': count=1 -> write "12"
  Read '1': count=1 -> write "11"
  next = "1211"
```

**Complexity:** O(n * L) where L is the length of each term

**Pattern**

```text
BUILD FROM PREVIOUS

BUG FIX from original: 'char next;' was declared as a single char
  but used as an array. Fixed to char next[512].
```

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

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

int main(void) {
    countAndSay(5);
    return 0;
}
```

**Sample output:**

```text
Term 5: 111221
```

### 10. Check If t Is a Subsequence of s

**Definition:** A subsequence is formed by deleting zero or more characters from a string WITHOUT changing the order of remaining characters.

**Example**

```text
"cgm" is a subsequence of "capgemini"
```

**Algorithm**

```text
step1: Use two pointers: i walks main string s, j walks subsequence t
step2: If s[i] == t[j]: match found, advance BOTH i and j
       If s[i] != t[j]: no match, advance ONLY i
step3: If j reaches end of t, ALL chars of t were matched -> return 1
       If i reaches end of s first -> return 0
```

**Example**

```text
s="capgemini", t="cgm"
  i=0('c')==t[0]('c'): match! j=1, i=1
  i=1('a')!=t[1]('g'): skip, i=2
  i=2('p')!=t[1]('g'): skip, i=3
  i=3('g')==t[1]('g'): match! j=2, i=4
  i=4('e')!=t[2]('m'): skip, i=5
  i=5('m')==t[2]('m'): match! j=3
  j==3==strlen(t) -> ALL matched, return 1
```

**Complexity:** O(n) time, O(1) space

**Pattern:** TWO-POINTER (merge walk)

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

int isSubsequence(const char *s, const char *t) {
    int i = 0, j = 0;
    int sLen = (int)strlen(s), tLen = (int)strlen(t);
    while (i < sLen && j < tLen) {
        if (s[i] == t[j]) j++;    /* match: advance subsequence pointer */
        i++;                      /* always advance main string pointer */
    }
    return j == tLen;             /* did we match ALL chars of t? */
}

int main(void) {
    printf("isSubsequence(capgemini,cgm)=%d\n", isSubsequence("capgemini","cgm"));
    return 0;
}
```

**Sample output:**

```text
isSubsequence(capgemini,cgm)=1
```

### 11. Reverse Words in a String (in-place, three-reversal trick)

**Definition**

```text
Reverse the order of words. "the sky is blue" -> "blue is sky the"
```

**Algorithm**

```text
  step1: Reverse the ENTIRE string
         "the sky is blue" -> "eulb si yks eht"
  step2: Reverse EACH WORD individually (between spaces)
         "eulb" -> "blue"
         "si"   -> "is"
         "yks"  -> "sky"
         "eht"  -> "the"
  Result: "blue is sky the"

Why it works:
  Reversing the whole string puts words in the right order but each
  word is backwards. Reversing each word fixes the letters.
```

**Complexity:** O(n) time, O(1) space (in-place!)

**Pattern:** REVERSAL TRICK (three reverses)

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

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

int main(void) {
    char s[]="the sky is blue"; reverseWords(s); printf("reverseWords=%s\n", s);
    return 0;
}
```

**Sample output:**

```text
reverseWords=blue is sky the
```

### 12. Longest Common Substring (brute force)

**Definition**

```text
Find the longest contiguous sequence of characters that appears in
BOTH strings. Example: "abcdfgh" and "zcdemgh" -> "cd"
```

**Algorithm**

```text
step1: For every pair (i, j) where i is index in str1, j in str2
step2: Count how many consecutive characters match starting at (i, j)
step3: Track the maximum match length and its starting index
step4: Extract the result substring
```

**Example**

```text
a="abcdfgh", b="zcdemgh"
  i=2,j=1: a[2]='c'==b[1]='c', a[3]='d'==b[2]='d', a[4]='f'!=b[3]='e'
  Match length = 2 ("cd") -> new max
  Result: "cd"
```

**Complexity:** O(m * n * min(m,n)) time, O(result) space

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

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

int main(void) {
    char *r=longestCommonSubstring("abcdfgh","zcdemgh"); printf("LCS substr=%s\n", r); free(r);
    return 0;
}
```

**Sample output:**

```text
LCS substr=cd
```

### 13. Validate an IPv4 Address

**Definition**

```text
Check if a string is a valid IPv4 address: four segments separated
by dots, each segment is a number 0-255, no leading zeros.
Valid:   "192.168.0.1"
Invalid: "256.1.2.3", "01.02.03.04", "1.2.3", ""
```

**Algorithm**

```text
step1: Walk char by char through the string
step2: On a digit: accumulate into 'num' (num = num*10 + digit)
step3: On a dot or end-of-string: validate the completed segment:
       - Must have at least 1 digit (no empty segments)
       - Must be 0-255
       - No leading zeros (if digits > 1, first digit can't be '0')
step4: After full walk, must have exactly 4 segments (3 dots + terminal)
```

**Example**

```text
ip = "192.168.0.1"
  Segment "192": digits=3, num=192, 0-255 OK
  Segment "168": digits=3, num=168, 0-255 OK
  Segment "0":   digits=1, num=0,   0-255 OK
  Segment "1":   digits=1, num=1,   0-255 OK
  dots = 4 (3 dots + 1 terminal) -> VALID
```

**Complexity:** O(n) time, O(1) space

**Pattern:** STATE MACHINE (single pass)

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

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

int main(void) {
    printf("isValidIPv4(192.168.1.10)=%d\n", isValidIPv4("192.168.1.10")); printf("isValidIPv4(1.2.3)=%d\n", isValidIPv4("1.2.3"));
    return 0;
}
```

**Sample output:**

```text
isValidIPv4(192.168.1.10)=1
isValidIPv4(1.2.3)=0
```

---

## Section 2 — Arrays


### 14. Find Second Largest Element

**Definition:** Find the second largest distinct value in an array.

**Algorithm**

```text
step1: Initialize first = INT_MIN, second = INT_MIN
step2: Walk the array once:
       - if arr[i] > first: second = first, first = arr[i]
       - else if arr[i] > second AND arr[i] != first: second = arr[i]
step3: Return second (or -1 if not found)
```

**Example**

```text
arr = [12, 35, 1, 10, 34, 1]
  i=0: 12 > INT_MIN -> second=INT_MIN, first=12
  i=1: 35 > 12      -> second=12, first=35
  i=2: 1 < 12       -> skip
  i=3: 10 < 12      -> skip
  i=4: 34 > 12      -> second=34  (34 > second=12 AND 34 != first=35)
  Result: second = 34
```

**Complexity:** O(n) time, O(1) space

**Pattern:** SINGLE PASS (two trackers)

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

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

int main(void) {
    int a[]={12,35,1,10,34,1}; printf("2nd largest=%d\n", findSecondLargest(a,6));
    return 0;
}
```

**Sample output:**

```text
2nd largest=34
```

### 15. Move All Zeros to End

**Definition:** Move all 0s to the end while maintaining relative order of non-zeros.

**Algorithm**

```text
step1: Use a write-index 'w' starting at 0
step2: Walk the array with read-index 'r':
       - if arr[r] != 0: copy arr[r] to arr[w], then w++
step3: After the loop, fill arr[w..n-1] with zeros
```

**Example**

```text
arr = [0, 1, 0, 3, 12]
  r=0: arr[0]=0, skip
  r=1: arr[1]=1, copy to arr[0], w=1 -> [1, 1, 0, 3, 12]
  r=2: arr[2]=0, skip
  r=3: arr[3]=3, copy to arr[1], w=2 -> [1, 3, 0, 3, 12]
  r=4: arr[4]=12, copy to arr[2], w=3 -> [1, 3, 12, 3, 12]
  Fill w=3 to n-1 with 0: [1, 3, 12, 0, 0]
```

**Complexity:** O(n) time, O(1) space

**Pattern:** TWO-POINTER (read/write)

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

static void pr(const int*a,int n){for(int i=0;i<n;i++)printf("%d ",a[i]);printf("\n");}

void moveZerosToEnd(int arr[], int n) {
    int w = 0;
    for (int r = 0; r < n; r++) {
        if (arr[r] != 0) arr[w++] = arr[r];
    }
    while (w < n) arr[w++] = 0;
}

int main(void) {
    int a[]={0,1,0,3,12}; moveZerosToEnd(a,5); printf("moveZeros: "); pr(a,5);
    return 0;
}
```

**Sample output:**

```text
moveZeros: 1 3 12 0 0
```

### 16. Rotate Array Left by d Positions (reversal trick)

**Definition:** Shift all elements left by d positions. Elements that fall off the left end wrap around to the right.

**Example**

```text
[1,2,3,4,5,6,7] d=2 -> [3,4,5,6,7,1,2]
```

**Algorithm**

```text
step1: Normalize d = d % n (handles d > n)
step2: Reverse first d elements:     [2,1,3,4,5,6,7]
step3: Reverse remaining n-d elems:  [2,1,7,6,5,4,3]
step4: Reverse the entire array:     [3,4,5,6,7,1,2]
```

**Example**

```text
arr = [1,2,3,4,5,6,7], d=2
  After rev(0..1):  [2,1,3,4,5,6,7]
  After rev(2..6):  [2,1,7,6,5,4,3]
  After rev(0..6):  [3,4,5,6,7,1,2]  <- correct!
```

**Complexity:** O(n) time, O(1) space

**Pattern:** REVERSAL TRICK (three reverses)

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

static void pr(const int*a,int n){for(int i=0;i<n;i++)printf("%d ",a[i]);printf("\n");}
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

int main(void) {
    int a[]={1,2,3,4,5,6,7}; rotateLeft(a,7,2); printf("rotateLeft2: "); pr(a,7);
    return 0;
}
```

**Sample output:**

```text
rotateLeft2: 3 4 5 6 7 1 2
```

### 17. Kadane's Algorithm (Maximum Subarray Sum)

**Definition:** Find the contiguous subarray with the largest sum.

**Algorithm**

```text
step1: Initialize maxEndingHere = arr[0], maxSoFar = arr[0]
step2: For each element from index 1:
       - Decision: should I EXTEND the current subarray or START fresh?
       - maxEndingHere = max(arr[i], maxEndingHere + arr[i])
       - if maxEndingHere > maxSoFar: update maxSoFar
step3: Return maxSoFar
```

**Example**

```text
arr = [-2, -3, 4, -1, -2, 1, 5, -3]
  i=0: maxHere=-2, maxSoFar=-2
  i=1: maxHere=max(-3, -2+-3=-5)=-3, maxSoFar=-2
  i=2: maxHere=max(4, -3+4=1)=4, maxSoFar=4
  i=3: maxHere=max(-1, 4+-1=3)=3, maxSoFar=4
  i=4: maxHere=max(-2, 3+-2=1)=1, maxSoFar=4
  i=5: maxHere=max(1, 1+1=2)=2, maxSoFar=4
  i=6: maxHere=max(5, 2+5=7)=7, maxSoFar=7  <- NEW MAX
  i=7: maxHere=max(-3, 7+-3=4)=4, maxSoFar=7
  Result: 7 (subarray: [4,-1,-2,1,5])
```

**TRAP**

```text
Init to arr[0], NOT 0. Otherwise all-negative arrays fail.
```

**Complexity:** O(n) time, O(1) space

**Pattern:** SINGLE PASS GREEDY (extend or restart)

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

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

int main(void) {
    int a[]={-2,-3,4,-1,-2,1,5,-3}; printf("kadane=%d\n", kadane(a,8));
    return 0;
}
```

**Sample output:**

```text
kadane=7
```

### 18. Remove Duplicates from Sorted Array

**Definition:** Given a SORTED array, remove duplicates in-place. Return new length.

**Algorithm**

```text
step1: slow = 0 (tracks tail of unique prefix)
step2: fast walks from 1 to n-1:
       - if arr[fast] != arr[slow]: slow++, copy arr[fast] to arr[slow]
step3: Return slow + 1 (length, not index)
```

**Example**

```text
arr = [1, 1, 2, 2, 3, 4, 4]
  fast=1: arr[1]=1 == arr[0]=1 -> skip
  fast=2: arr[2]=2 != arr[0]=1 -> slow=1, arr[1]=2
  fast=3: arr[3]=2 == arr[1]=2 -> skip
  fast=4: arr[4]=3 != arr[1]=2 -> slow=2, arr[2]=3
  fast=5: arr[5]=4 != arr[2]=3 -> slow=3, arr[3]=4
  fast=6: arr[6]=4 == arr[3]=4 -> skip
  Result: new length = 3+1 = 4, arr = [1,2,3,4,...]
```

**Complexity:** O(n) time, O(1) space

**Pattern:** TWO-POINTER (slow/fast)

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

static void pr(const int*a,int n){for(int i=0;i<n;i++)printf("%d ",a[i]);printf("\n");}

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

int main(void) {
    int a[]={1,1,2,2,3,4,4}; int n=removeDuplicates(a,7); printf("removeDups: "); pr(a,n);
    return 0;
}
```

**Sample output:**

```text
removeDups: 1 2 3 4
```

### 19. Majority Element (Boyer-Moore Voting)

**Definition:** Find the element that appears MORE than n/2 times.

**Algorithm**

```text
PHASE 1 (candidate selection):
  step1: candidate=0, count=0
  step2: For each element:
         - if count==0: candidate = arr[i], count = 1
         - else if arr[i]==candidate: count++
         - else: count--

PHASE 2 (verification - MANDATORY):
  step3: Count actual occurrences of candidate
  step4: If count > n/2, return candidate. Else return -1.
```

**Example**

```text
arr = [2, 2, 1, 1, 1, 2, 2]
  Phase 1: candidate ends as 2 (count survives)
  Phase 2: count of 2 = 4, n/2 = 3, 4 > 3 -> majority IS 2
```

**TRAP**

```text
Phase 2 is MANDATORY. Phase 1 alone can return wrong answer
      for arrays with no majority (e.g., [1,2,3]).
```

**Complexity:** O(n) time, O(1) space

**Pattern:** SINGLE PASS GREEDY (vote + verify)

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

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

int main(void) {
    int a[]={2,2,1,1,1,2,2}; printf("majority=%d\n", findMajority(a,7));
    return 0;
}
```

**Sample output:**

```text
majority=2
```

### 20. Missing Number in 0..n (XOR method)

**Definition:** Given n distinct numbers from {0, 1, ..., n}, find the missing one.

**Algorithm**

```text
step1: XOR all values 0 to n together
step2: XOR all array elements together
step3: XOR the two results -> missing number
Why: a^a=0, so all duplicates cancel; the missing one survives
```

**Example**

```text
arr = [3, 0, 1], n = 3 (should have 0,1,2,3)
  XOR(0..3) = 0^1^2^3 = 0
  XOR(arr)  = 3^0^1   = 2
  0 ^ 2 = 2 -> missing is 2
```

**Complexity:** O(n) time, O(1) space

**Pattern:** XOR CANCEL

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

int findMissing(const int arr[], int n) {
    int x = 0;
    for (int i = 0; i <= n; i++) x ^= i;
    for (int i = 0;  i < n; i++) x ^= arr[i];
    return x;
}

int main(void) {
    int a[]={3,0,1}; printf("missing in 0..3=%d\n", findMissing(a,3));
    return 0;
}
```

**Sample output:**

```text
missing in 0..3=2
```

### 21. Reverse Array in Groups of k

**Algorithm**

```text
step1: Walk array in strides of k (i=0, i+=k)
step2: For each stride, reverse from i to min(i+k-1, n-1)
       (last group may have fewer than k elements)
```

**Example**

```text
arr = [1,2,3,4,5,6,7,8,9], k=3
  i=0: reverse [0..2]: [3,2,1, 4,5,6, 7,8,9]
  i=3: reverse [3..5]: [3,2,1, 6,5,4, 7,8,9]
  i=6: reverse [6..8]: [3,2,1, 6,5,4, 9,8,7]
```

**Complexity:** O(n) time, O(1) space

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

static void pr(const int*a,int n){for(int i=0;i<n;i++)printf("%d ",a[i]);printf("\n");}
static void revArr(int a[], int i, int j) {
    while (i < j) { int t = a[i]; a[i] = a[j]; a[j] = t; i++; j--; }
}

void reverseInGroups(int arr[], int n, int k) {
    if (k <= 1) return;
    for (int i = 0; i < n; i += k) {
        int end = (i + k - 1 < n) ? i + k - 1 : n - 1;
        revArr(arr, i, end);
    }
}

int main(void) {
    int a[]={1,2,3,4,5,6,7,8,9}; reverseInGroups(a,9,3); printf("revGroups3: "); pr(a,9);
    return 0;
}
```

**Sample output:**

```text
revGroups3: 3 2 1 6 5 4 9 8 7
```

### 22. Find Minimum in Rotated Sorted Array (binary search)

**Definition:** A sorted array has been rotated at an unknown pivot. Find the minimum element in O(log n).

**Algorithm**

```text
step1: left=0, right=n-1
step2: While left < right:
       - mid = left + (right-left)/2  (overflow-safe!)
       - if arr[mid] > arr[right]: min is in RIGHT half -> left = mid + 1
       - else: min is mid or in LEFT half -> right = mid
step3: Return arr[left]
```

**Example**

```text
arr = [4, 5, 6, 7, 0, 1, 2]
  left=0, right=6, mid=3: arr[3]=7 > arr[6]=2 -> left=4
  left=4, right=6, mid=5: arr[5]=1 < arr[6]=2 -> right=5
  left=4, right=5, mid=4: arr[4]=0 < arr[5]=1 -> right=4
  left==right==4 -> arr[4] = 0 = MINIMUM
```

**TRAP**

```text
Compare with arr[right], NOT arr[left]. Using left is wrong!
```

**TRAP**

```text
Use left + (right-left)/2, NOT (left+right)/2 (overflow!)
```

**Complexity:** O(log n) time, O(1) space

**Pattern:** BINARY SEARCH

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

int findMinRotated(const int arr[], int n) {
    int left = 0, right = n - 1;
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] > arr[right]) left  = mid + 1;
        else                       right = mid;
    }
    return arr[left];
}

int main(void) {
    int a[]={4,5,6,7,0,1,2}; printf("minRotated=%d\n", findMinRotated(a,7));
    return 0;
}
```

**Sample output:**

```text
minRotated=0
```

### 23. Binary Search (iterative)

**Algorithm**

```text
step1: left=0, right=n-1
step2: While left <= right:
       - mid = left + (right-left)/2
       - if arr[mid] == target: return mid
       - if arr[mid] < target:  search right half (left = mid+1)
       - if arr[mid] > target:  search left half (right = mid-1)
step3: Return -1 (not found)
```

**TRAP**

```text
Condition is left <= right (not <)
```

**Complexity:** O(log n) time, O(1) space Precondition: array MUST be sorted

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

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

int main(void) {
    int a[]={1,3,5,7,9,11}; printf("binSearch(7)=%d\n", binarySearch(a,6,7));
    return 0;
}
```

**Sample output:**

```text
binSearch(7)=3
```

### 24. Quicksort (Lomuto partition)

**Algorithm**

```text
step1: Pick pivot = arr[high] (last element)
step2: Partition: walk j from low to high-1
       - if arr[j] <= pivot: swap arr[j] with arr[++i]
step3: Place pivot at arr[i+1] (its correct sorted position)
step4: Recurse on left partition (low..p-1) and right (p+1..high)
```

**Complexity:** O(n log n) average, O(n^2) worst (sorted input)

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

static void pr(const int*a,int n){for(int i=0;i<n;i++)printf("%d ",a[i]);printf("\n");}
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

int main(void) {
    int a[]={10,7,8,9,1,5}; quickSort(a,0,5); printf("quickSort: "); pr(a,6);
    return 0;
}
```

**Sample output:**

```text
quickSort: 1 5 7 8 9 10
```

### 25. Merge Two Sorted Arrays

**Algorithm**

```text
step1: Use three pointers: i for a[], j for b[], k for out[]
step2: Compare a[i] and b[j], take the smaller one into out[k++]
step3: When one array is exhausted, copy the remainder of the other
```

**Complexity:** O(m+n) time, O(m+n) space

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

static void pr(const int*a,int n){for(int i=0;i<n;i++)printf("%d ",a[i]);printf("\n");}

void mergeSorted(const int a[], int m, const int b[], int n, int out[]) {
    int i = 0, j = 0, k = 0;
    while (i < m && j < n)
        out[k++] = (a[i] <= b[j]) ? a[i++] : b[j++];
    while (i < m) out[k++] = a[i++];
    while (j < n) out[k++] = b[j++];
}

int main(void) {
    int a[]={1,3,5},b[]={2,4,6},o[6]; mergeSorted(a,3,b,3,o); printf("merge: "); pr(o,6);
    return 0;
}
```

**Sample output:**

```text
merge: 1 2 3 4 5 6
```

### 26. Heap Sort

**Algorithm**

```text
  step1: Build a max-heap from the array (bottom-up, starting at n/2-1)
  step2: Repeatedly:
         - Swap root (max) with last unsorted element
         - Shrink heap by 1
         - Heapify the root to restore max-heap property

Children of node i: left = 2*i+1, right = 2*i+2
```

**Complexity:** O(n log n) time, O(1) space

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

static void pr(const int*a,int n){for(int i=0;i<n;i++)printf("%d ",a[i]);printf("\n");}
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

int main(void) {
    int a[]={12,11,13,5,6,7}; heapSort(a,6); printf("heapSort: "); pr(a,6);
    return 0;
}
```

**Sample output:**

```text
heapSort: 5 6 7 11 12 13
```

---

## Section 3 — Bit Manipulation


### 27, 28, 29, 30. Set / Clear / Toggle / Check Bit

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

unsigned int setBit    (unsigned int n, int pos) { return n |  (1u << pos); }

unsigned int clearBit  (unsigned int n, int pos) { return n & ~(1u << pos); }

unsigned int toggleBit (unsigned int n, int pos) { return n ^  (1u << pos); }

int          checkBit  (unsigned int n, int pos) { return (n >> pos) & 1;   }

int main(void) {
    printf("set bit1 of 12=%u\n",setBit(12,1)); printf("clear bit2 of 12=%u\n",clearBit(12,2)); printf("toggle bit1 of 12=%u\n",toggleBit(12,1)); printf("check bit2 of 12=%d\n",checkBit(12,2));
    return 0;
}
```

**Sample output:**

```text
set bit1 of 12=14
clear bit2 of 12=8
toggle bit1 of 12=14
check bit2 of 12=1
```

### 31. Check if n is a Power of 2

**Definition:** Powers of 2 have exactly ONE set bit: 1, 2, 4, 8, 16, ...

**Algorithm**

```text
step1: A power of 2 in binary is 10...0 (one 1 followed by zeros)
step2: Subtracting 1 flips that bit and turns on all bits below:
       n = 1000, n-1 = 0111
step3: n & (n-1) == 0 iff n was a power of 2
step4: Must also exclude n == 0 (0 is NOT a power of 2)
```

**Example**

```text
n=8 -> 1000, n-1=7 -> 0111, 8 & 7 = 0 -> YES
         n=6 -> 0110, n-1=5 -> 0101, 6 & 5 = 4 -> NO
```

**Complexity:** O(1) time, O(1) space

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

int isPowerOfTwo(int n) {
    return n > 0 && (n & (n - 1)) == 0;
}

int main(void) {
    printf("isPow2(8)=%d isPow2(6)=%d\n", isPowerOfTwo(8), isPowerOfTwo(6));
    return 0;
}
```

**Sample output:**

```text
isPow2(8)=1 isPow2(6)=0
```

### 32. Count Set Bits (Brian Kernighan's Trick)

**Definition:** Count how many bits are 1 in the binary representation of n.

**Algorithm**

```text
  step1: While n != 0:
         - n = n & (n-1)  -- this clears the LOWEST set bit each pass
         - count++
  step2: Return count

Why n & (n-1) works:
  n   = ...1000  (lowest set bit)
  n-1 = ...0111  (flips lowest set bit and all below)
  AND clears that bit, leaving all higher bits untouched
```

**Example**

```text
n=13 (1101), count=0
  1101 & 1100 = 1100, count=1  (cleared bit 0)
  1100 & 1011 = 1000, count=2  (cleared bit 2)
  1000 & 0111 = 0000, count=3  (cleared bit 3)
  n==0, STOP. Result: 3 set bits
```

**Complexity:** O(number of set bits), NOT O(32)

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

int countSetBits(unsigned int n) {
    int count = 0;
    while (n) { n &= (n - 1); count++; }
    return count;
}

int main(void) {
    printf("countSetBits(13)=%d\n", countSetBits(13));
    return 0;
}
```

**Sample output:**

```text
countSetBits(13)=3
```

### 33. Single Non-Repeating Element (XOR)

**Definition:** Every element appears exactly twice except one. Find the unique one.

**Algorithm**

```text
step1: Initialize result = 0
step2: XOR every element into result
step3: Duplicates cancel (a^a=0), unique survives (x^0=x)
```

**Example**

```text
arr = [4, 1, 2, 1, 2]
  0 ^ 4 = 4
  4 ^ 1 = 5
  5 ^ 2 = 7
  7 ^ 1 = 6   (1 cancels)
  6 ^ 2 = 4   (2 cancels)
  Result: 4
```

**Complexity:** O(n) time, O(1) space

**Pattern:** XOR CANCEL

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

int findSingle(const int arr[], int n) {
    int result = 0;
    for (int i = 0; i < n; i++) result ^= arr[i];
    return result;
}

int main(void) {
    int a[]={4,1,2,1,2}; printf("single=%d\n", findSingle(a,5));
    return 0;
}
```

**Sample output:**

```text
single=4
```

### 34. Two Non-Repeating Elements

**Definition:** Every element appears twice except TWO distinct elements a and b. Find both.

**Algorithm**

```text
step1: XOR everything -> result = a ^ b (nonzero since a != b)
step2: Find any set bit in result. Easiest: diffBit = x & -x
       This bit is where a and b DIFFER
step3: Partition array by that bit:
       - Group1 (bit set): XOR all -> gives a
       - Group2 (bit clear): XOR all -> gives b
       Pairs within each group still cancel out
```

**Example**

```text
arr = [2, 3, 7, 9, 11, 2, 3, 11]
  XOR all = 7 ^ 9 = 14 = 1110
  diffBit = 14 & -14 = 2 = 0010
  Group1 (bit 1 set): {2,3,7,2,3} -> XOR = 7
  Group2 (bit 1 clear): {9,11,11} -> XOR = 9
  Result: 7 and 9
```

**Complexity:** O(n) time, O(1) space

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

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

int main(void) {
    int a[]={2,3,7,9,11,2,3,11},x,y; findTwoUniques(a,8,&x,&y); printf("two uniques=%d,%d\n",x,y);
    return 0;
}
```

**Sample output:**

```text
two uniques=7,9
```

### 35. Swap Two Numbers Without Temp (XOR)

**Algorithm**

```text
*a ^= *b  -- a now holds a^b
*b ^= *a  -- b = b^(a^b) = a  (original a)
*a ^= *b  -- a = (a^b)^a = b  (original b)
```

**TRAP**

```text
if a and b point to the SAME address, the result is 0 (not a swap!)
      Always guard with: if (a == b) return;
```

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

void swapXOR(int *a, int *b) {
    if (a == b) return;
    *a ^= *b;
    *b ^= *a;
    *a ^= *b;
}

int main(void) {
    int a=5,b=10; swapXOR(&a,&b); printf("after swap a=%d b=%d\n",a,b);
    return 0;
}
```

**Sample output:**

```text
after swap a=10 b=5
```

### 36. Reverse Bits of a 32-bit Number

**Algorithm**

```text
  step1: result = 0
  step2: Loop 32 times:
         - Shift result LEFT by 1 (make room)
         - OR in the LSB of n: result |= (n & 1)
         - Shift n RIGHT by 1 (move to next bit)
  step3: Return result

Example (4-bit demo): n = 0101 (5)
  iter1: result = 0000<<1 | 1 = 0001, n = 0010
  iter2: result = 0010<<1 | 0 = 0010, n = 0001
  iter3: result = 0100<<1 | 1 = 0101, n = 0000
  iter4: result = 1010<<1 | 0 = 1010
  Result: 1010 (10)
```

**Complexity:** O(32) = O(1) time

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

unsigned int reverseBits(unsigned int n) {
    unsigned int result = 0;
    for (int i = 0; i < 32; i++) {
        result = (result << 1) | (n & 1u);
        n >>= 1;
    }
    return result;
}

int main(void) {
    printf("reverseBits(5)=%u\n", reverseBits(5));
    return 0;
}
```

**Sample output:**

```text
reverseBits(5)=2684354560
```

### 37. Even / Odd via LSB

```text
The LSB (bit 0) tells you: 0 = even, 1 = odd
Works for negatives too (two's complement)
```

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

int isEven(int n) { return (n & 1) == 0; }

int main(void) {
    printf("isEven(4)=%d isEven(7)=%d\n", isEven(4), isEven(7));
    return 0;
}
```

**Sample output:**

```text
isEven(4)=1 isEven(7)=0
```

### 38. Position of Rightmost Set Bit (1-indexed)

**Algorithm**

```text
step1: Isolate lowest set bit: iso = n & -n
       In two's complement: -n = ~n + 1, so only the lowest 1 survives
step2: Count shifts until iso == 1: that's the 0-indexed position
step3: Return position + 1 (1-indexed)
```

**Example**

```text
n = 12 = 1100
  -n = ...0100 (two's complement)
  n & -n = 0100 = 4 -> isolated bit at position 2
  Shift: 4 >> 1 = 2, 2 >> 1 = 1 -> 2 shifts -> position 2+1 = 3
```

**Complexity:** O(position) time, O(1) space

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

int positionOfRightmostSetBit(unsigned int n) {
    if (n == 0) return 0;
    unsigned int iso = n & -n;
    int pos = 0;
    while (iso > 1) { iso >>= 1; pos++; }
    return pos + 1;
}

int main(void) {
    printf("rightmostSetBit(12)=%d\n", positionOfRightmostSetBit(12));
    return 0;
}
```

**Sample output:**

```text
rightmostSetBit(12)=3
```

### 39, 40, 41. Bit Range Operations (Set / Clear / Write bits in [start..end])

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

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

int main(void) {
    printf("setRange[1..3] of 0=0x%X\n", setBitsInRange(0,1,3)); printf("clearRange[1..3] of 0xFF=0x%X\n", clearBitsInRange(0xFF,1,3)); printf("write 5 into [1..3] of 0=0x%X\n", writeBitsInRange(0,1,3,5));
    return 0;
}
```

**Sample output:**

```text
setRange[1..3] of 0=0xE
clearRange[1..3] of 0xFF=0xF1
write 5 into [1..3] of 0=0xA
```

### 42. Add Two Numbers Without + Operator

**Algorithm**

```text
step1: XOR gives the sum WITHOUT carry:   sum = a ^ b
step2: AND-then-shift gives the carry:    carry = (a & b) << 1
step3: Repeat: a = sum, b = carry, until carry == 0
```

**Example**

```text
a=15 (1111), b=32 (100000)
  iter1: sum = 1111 ^ 100000 = 101111, carry = 0
  carry == 0, STOP. Result: 101111 = 47
```

**Complexity:** O(32) worst case = O(1)

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

int addNoPlus(int a, int b) {
    while (b != 0) {
        int carry = (a & b) << 1;
        a = a ^ b;
        b = carry;
    }
    return a;
}

int main(void) {
    printf("addNoPlus(15,32)=%d\n", addNoPlus(15,32));
    return 0;
}
```

**Sample output:**

```text
addNoPlus(15,32)=47
```

### 43. Multiply / Divide by Powers of 2

```text
n << k  ==  n * 2^k
n >> k  ==  n / 2^k  (for unsigned; for signed, implementation-defined)
```

**TRAP**

```text
n >> k on negative signed n is impl-defined (usually arithmetic
      shift = sign-extending). Cast to unsigned for logical shift.
```

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

int mul2k(int n, int k) { return n << k; }

int div2k(int n, int k) { return n >> k; }

int main(void) {
    printf("5*8=%d 40/4=%d\n", mul2k(5,3), div2k(40,2));
    return 0;
}
```

**Sample output:**

```text
5*8=40 40/4=10
```
***bitwise multiply***
This function uses an ancient algorithm known as **Egyptian Multiplication** or the **Russian Peasant Method**, which maps perfectly to how modern digital circuits handle multiplication at the hardware level.

The core rule of binary multiplication is simple: **Any decimal number can be broken down into a sum of powers of 2.**

For example, if you want to multiply $13 \times 5$:
1. Look at the multiplier, `5`. In binary, `5` is `0101`.
2. This means $5 = (4 + 1)$, or $(2^2 + 2^0)$.
3. Therefore, $13 \times 5$ is exactly the same as:
   $$(13 \times 4) + (13 \times 1)$$

---

## Step-by-Step Execution Trace

Let's look at exactly what happens inside the `while` loop when you pass `a = 13` and `b = 5`.

### **Initial State:**
* `a = 13` (Binary: `1101`)
* `b = 5`  (Binary: `0101`)
* `result = 0`

---

### **Iteration 1:**
* **Check Bit (`b & 1`):** `5 & 1` is **True** (the lowest bit of `0101` is `1`).
* **Action:** Add the current value of `a` to our result.
  * `result = 0 + 13 = 13`
* **Shift Operations:**
  * `a <<= 1` $\rightarrow$ `13` becomes **`26`** (Doubled)
  * `b >>= 1` $\rightarrow$ `5` (`0101`) becomes **`2`** (`0010`) (Halved)

---

### **Iteration 2:**
* **Check Bit (`b & 1`):** `2 & 1` is **False** (the lowest bit of `0010` is `0`).
* **Action:** Do nothing to `result`. We skip adding because this column in the multiplier is zero.
  * `result` remains **`13`**
* **Shift Operations:**
  * `a <<= 1` $\rightarrow$ `26` becomes **`52`** (Doubled)
  * `b >>= 1` $\rightarrow$ `2` (`0010`) becomes **`1`** (`0001`) (Halved)

---

### **Iteration 3:**
* **Check Bit (`b & 1`):** `1 & 1` is **True** (the lowest bit of `0001` is `1`).
* **Action:** Add the current scaled value of `a` to our result.
  * `result = 13 + 52 = 65`
* **Shift Operations:**
  * `a <<= 1` $\rightarrow$ `52` becomes **`104`**
  * `b >>= 1` $\rightarrow$ `1` (`0001`) becomes **`0`** (`0000`)

---

## **Loop Termination:**
The loop checks `while (b > 0)`. Because `b` is now `0`, the loop exits.

The function returns `result`, which is **65** ($13 \times 5 = 65$).
```c
#include <stdio.h>

/**
 * Multiplies two integers using only bitwise shifts and addition.
 * Works for any non-negative integers.
 */
int bitwise_multiply(int a, int b) {
    int result = 0; // Stores the final accumulated answer
    
    while (b > 0) {
        // Step 1: Check if the lowest bit of 'b' is 1 (is 'b' odd?)
        if (b & 1) {
            result += a; 
        }
        
        // Step 2: Prepare for the next bit
        a <<= 1;  // Double 'a' (Shift left by 1)
        b >>= 1;  // Halve 'b' (Shift right by 1)
    }
    
    return result;
}

int main(void) {
    int x = 13;
    int y = 5;
    printf("%d * %d = %d\n", x, y, bitwise_multiply(x, y));
    return 0;
}
```
### 44. Missing Number from 1..N (XOR variant)

```text
Same as #20 but for range 1..n instead of 0..n
Array has n-1 elements; one value from 1..n is missing
```

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

int findMissing1toN(const int arr[], int n) {
    int x = 0;
    for (int i = 1; i <= n; i++) x ^= i;
    for (int i = 0; i < n - 1; i++) x ^= arr[i];
    return x;
}

int main(void) {
    int a[]={1,2,4,5}; printf("missing 1..5=%d\n", findMissing1toN(a,5));
    return 0;
}
```

**Sample output:**

```text
missing 1..5=3
```

---

## Section 4 — Math / Number


### 45. Digit Extraction

**Algorithm**

```text
n%10 extracts last digit, n/10 removes it. Loop until n==0.
Digits come out in REVERSE order.
```

**Example**

```text
n = 5283
  5283 % 10 = 3,  5283 / 10 = 528
   528 % 10 = 8,   528 / 10 = 52
    52 % 10 = 2,    52 / 10 = 5
     5 % 10 = 5,     5 / 10 = 0 -> stop
  Digits: 3, 8, 2, 5
```

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

void extractDigits(int n) {
    if (n < 0) n = -n;
    if (n == 0) { printf("0\n"); return; }
    while (n > 0) {
        printf("%d ", n % 10);
        n /= 10;
    }
    printf("\n");
}

int main(void) {
    printf("digits of 5283: "); extractDigits(5283);
    return 0;
}
```

**Sample output:**

```text
digits of 5283: 3 8 2 5
```

### 46. Reverse a Number

**Algorithm**

```text
Build reversed number digit by digit:
  rev = rev * 10 + (n % 10),  n = n / 10
```

**TRAP**

```text
Overflow! Reversing 1999999999 overflows int.
      Check: if (rev > (INT_MAX - digit) / 10) return 0;
```

**Example**

```text
n = 1234
  rev=0:  rev = 0*10+4 = 4,     n=123
  rev=4:  rev = 4*10+3 = 43,    n=12
  rev=43: rev = 43*10+2 = 432,  n=1
  rev=432: rev = 432*10+1 = 4321, n=0
  Result: 4321
```

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

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

int main(void) {
    printf("reverse(1234)=%d\n", reverseNumber(1234));
    return 0;
}
```

**Sample output:**

```text
reverse(1234)=4321
```

### 47. Palindrome Number Check

**Algorithm**

```text
Reverse the number, compare to original.
  Negatives are NEVER palindromes.
```

**Example**

```text
121 -> reversed = 121 -> equal -> palindrome
         -121 -> negative -> NOT palindrome
```

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

int isPalindromeNumber(int n) {
    if (n < 0) return 0;
    int original = n, rev = 0;
    while (n > 0) { rev = rev * 10 + (n % 10); n /= 10; }
    return rev == original;
}

int main(void) {
    printf("palin(121)=%d palin(123)=%d\n", isPalindromeNumber(121), isPalindromeNumber(123));
    return 0;
}
```

**Sample output:**

```text
palin(121)=1 palin(123)=0
```

### 48. Armstrong Number (Narcissistic Number)

**Definition**

```text
Sum of each digit raised to the power of (number of digits)
  equals the number itself.
  153 = 1^3 + 5^3 + 3^3 = 1 + 125 + 27 = 153 -> Armstrong
  9474 = 9^4 + 4^4 + 7^4 + 4^4 = 9474 -> Armstrong
```

**Algorithm**

```text
step1: Count digits (d)
step2: For each digit: sum += digit^d
step3: Compare sum == original
```

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

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

int main(void) {
    printf("armstrong(153)=%d armstrong(123)=%d\n", isArmstrong(153), isArmstrong(123));
    return 0;
}
```

**Sample output:**

```text
armstrong(153)=1 armstrong(123)=0
```

### 49. Print All Divisors of N

**Algorithm**

```text
Loop i from 1 to sqrt(n). If n%i==0, both i and n/i are divisors.
```

**TRAP**

```text
Use i*i <= n instead of i <= sqrt(n) to avoid floating point on MCUs.
      Print n/i only when i != n/i to avoid duplicate for perfect squares.
```

**Example**

```text
n = 36
  i=1: 36%1==0 -> print 1, 36
  i=2: 36%2==0 -> print 2, 18
  i=3: 36%3==0 -> print 3, 12
  i=4: 36%4==0 -> print 4, 9
  i=5: 36%5!=0 -> skip
  i=6: 36%6==0 -> print 6 (6==36/6, so only once)
```

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

void printDivisors(int n) {
    for (int i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            printf("%d ", i);
            if (i != n / i) printf("%d ", n / i);
        }
    }
    printf("\n");
}

int main(void) {
    printf("divisors of 36: "); printDivisors(36);
    return 0;
}
```

**Sample output:**

```text
divisors of 36: 1 36 2 18 3 12 4 9 6
```

### 50. Prime Number Check (6k +/- 1 optimization)

```text
Why 6k+/-1: Every integer is 6k, 6k+1, 6k+2, 6k+3, 6k+4, or 6k+5.
  6k, 6k+2, 6k+4 are even (divisible by 2).
  6k+3 is divisible by 3.
  Only 6k+1 and 6k+5 (= 6(k+1)-1) can be prime.
  So after eliminating 2 and 3, check i and i+2 stepping by 6.
```

**Example**

```text
n = 29
  29 > 3, not divisible by 2 or 3
  i=5: 29%5=4 (no), 29%7=1 (no). 7*7=49 > 29 -> stop
  Result: PRIME
```

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

int isPrime(int n) {
    if (n <= 1) return 0;
    if (n <= 3) return 1;
    if (n % 2 == 0 || n % 3 == 0) return 0;
    for (int i = 5; i * i <= n; i += 6)
        if (n % i == 0 || n % (i + 2) == 0) return 0;
    return 1;
}

int main(void) {
    printf("isPrime(29)=%d isPrime(15)=%d\n", isPrime(29), isPrime(15));
    return 0;
}
```

**Sample output:**

```text
isPrime(29)=1 isPrime(15)=0
```

### 51. GCD - Euclidean Algorithm (iterative)

**Algorithm**

```text
while b != 0: temp=b, b=a%b, a=temp. Return a.
```

**Example**

```text
gcd(48, 18)
  48 % 18 = 12 -> gcd(18, 12)
  18 % 12 = 6  -> gcd(12, 6)
  12 % 6  = 0  -> gcd(6, 0)  -> answer = 6

LCM from GCD: lcm(a,b) = (a / gcd(a,b)) * b  (divide first to avoid overflow!)
```

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

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

int main(void) {
    printf("gcd(48,18)=%d lcm(12,18)=%d\n", gcd(48,18), lcm(12,18));
    return 0;
}
```

**Sample output:**

```text
gcd(48,18)=6 lcm(12,18)=36
```

### 52. Big Integer Addition (string-based)

**Algorithm**

```text
step1: Walk both strings from RIGHT to LEFT (least significant digit)
step2: Add digits + carry. Store (sum % 10), carry forward (sum / 10).
step3: If one string is shorter, treat missing digits as 0.
step4: After loop, if carry > 0, write it.
step5: Result is built in reverse -> reverse it at end.
```

**Example**

```text
"999" + "1"
  9+1+0=10 -> write 0, carry=1
  9+0+1=10 -> write 0, carry=1
  9+0+1=10 -> write 0, carry=1
  carry=1  -> write 1
  Reverse "0001" -> "1000"
```

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

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

int main(void) {
    char r[64]; addBigInt("999","1",r,sizeof r); printf("999+1=%s\n", r);
    return 0;
}
```

**Sample output:**

```text
999+1=1000
```

---

## Section 5 — Linked List


### 53. createNode - allocate + initialize a new node

```text
step1: Allocate memory using malloc. sizeof(*newNode) is safer than
       sizeof(Node) -- if you rename the type, allocation stays correct.
step2: Check for NULL (malloc can fail, especially on MCUs)
step3: Set id = value, next = NULL
```

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

typedef struct Node { int id; struct Node *next; } Node;

Node *createNode(int id) {
    Node *newNode = (Node *)malloc(sizeof(*newNode));
    if (newNode == NULL) return NULL;
    newNode->id   = id;
    newNode->next = NULL;
    return newNode;
}

int main(void) {
    Node*n=createNode(42); printf("createNode(42): id=%d next=%p\n", n->id,(void*)n->next); free(n);
    return 0;
}
```

**Sample output:**

```text
createNode(42): id=42 next=(nil)
```

### 54. insertAtHead - O(1) insertion at the beginning

```text
step1: Create a new node
step2: Point new node's next to current head: newNode->next = *head
step3: Update head to point to new node: *head = newNode

Why Node **head (double pointer)?
  Because we need to MODIFY the caller's head pointer.
  If we used Node *head, changes would be local to this function.
```

**Example**

```text
head -> [10] -> [20] -> NULL
  insertAtHead(&head, 5)
  Result: head -> [5] -> [10] -> [20] -> NULL
```

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

typedef struct Node { int id; struct Node *next; } Node;
Node *createNode(int id) {
    Node *newNode = (Node *)malloc(sizeof(*newNode));
    if (newNode == NULL) return NULL;
    newNode->id   = id;
    newNode->next = NULL;
    return newNode;
}

int insertAtHead(Node **head, int id) {
    Node *newNode = createNode(id);
    if (newNode == NULL) return -1;
    newNode->next = *head;
    *head = newNode;
    return 0;
}

int main(void) {
    Node*h=NULL; insertAtHead(&h,10); insertAtHead(&h,5); for(Node*c=h;c;c=c->next)printf("%d -> ",c->id); printf("NULL\n"); while(h){Node*t=h->next;free(h);h=t;}
    return 0;
}
```

**Sample output:**

```text
5 -> 10 -> NULL
```

### 55. insertAtEnd - O(n) insertion at the tail

```text
step1: Create new node
step2: If list is empty (*head == NULL): *head = newNode, done.
step3: Else walk to the last node (temp->next == NULL)
step4: Set last->next = newNode
```

**Example**

```text
head -> [10] -> [20] -> NULL
  insertAtEnd(&head, 30)
  Walk to [20], set [20]->next = [30]
  Result: head -> [10] -> [20] -> [30] -> NULL
```

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

typedef struct Node { int id; struct Node *next; } Node;
Node *createNode(int id) {
    Node *newNode = (Node *)malloc(sizeof(*newNode));
    if (newNode == NULL) return NULL;
    newNode->id   = id;
    newNode->next = NULL;
    return newNode;
}

int insertAtEnd(Node **head, int id) {
    Node *newNode = createNode(id);
    if (newNode == NULL) return -1;
    if (*head == NULL) { *head = newNode; return 0; }
    Node *temp = *head;
    while (temp->next != NULL) temp = temp->next;
    temp->next = newNode;
    return 0;
}

int main(void) {
    Node*h=NULL; insertAtEnd(&h,10); insertAtEnd(&h,20); insertAtEnd(&h,30); for(Node*c=h;c;c=c->next)printf("%d -> ",c->id); printf("NULL\n"); while(h){Node*t=h->next;free(h);h=t;}
    return 0;
}
```

**Sample output:**

```text
10 -> 20 -> 30 -> NULL
```

### 56. deleteNode - remove first node matching 'key'

```text
step1: Special case: if head itself matches, update *head and free old head
step2: Else walk with prev and cur pointers until cur->id == key
step3: Bypass: prev->next = cur->next, then free(cur)
```

**Example**

```text
head -> [10] -> [20] -> [30], delete 20
  prev=[10], cur=[20]: match!
  [10]->next = [30], free [20]
  Result: head -> [10] -> [30] -> NULL
```

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

typedef struct Node { int id; struct Node *next; } Node;
Node *createNode(int id) {
    Node *newNode = (Node *)malloc(sizeof(*newNode));
    if (newNode == NULL) return NULL;
    newNode->id   = id;
    newNode->next = NULL;
    return newNode;
}

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

int main(void) {
    Node*h=NULL; for(int i=1;i<=3;i++){Node*n=createNode(i*10);n->next=h;h=n;} /* h: 30 20 10 */ deleteNode(&h,20); for(Node*c=h;c;c=c->next)printf("%d -> ",c->id); printf("NULL\n"); while(h){Node*t=h->next;free(h);h=t;}
    return 0;
}
```

**Sample output:**

```text
30 -> 10 -> NULL
```

### 57. printList & 58. freeList

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

typedef struct Node { int id; struct Node *next; } Node;
Node *createNode(int id) {
    Node *newNode = (Node *)malloc(sizeof(*newNode));
    if (newNode == NULL) return NULL;
    newNode->id   = id;
    newNode->next = NULL;
    return newNode;
}

void printList(const Node *head) {
    for (const Node *cur = head; cur != NULL; cur = cur->next)
        printf("%d -> ", cur->id);
    printf("NULL\n");
}

void freeList(Node *head) {
    while (head) { Node *next = head->next; free(head); head = next; }
}

int main(void) {
    Node*h=NULL; for(int i=3;i>=1;i--){Node*n=createNode(i);n->next=h;h=n;} printList(h); freeList(h);
    return 0;
}
```

**Sample output:**

```text
1 -> 2 -> 3 -> NULL
```

### 59. reverseList - THE three-pointer classic

**Definition:** Reverse a singly linked list in-place.

**Algorithm**

```text
step1: Initialize prev = NULL, cur = head
step2: Loop while cur != NULL:
       - Save next: next = cur->next
       - Flip the link: cur->next = prev
       - Advance prev: prev = cur
       - Advance cur: cur = next
step3: When cur is NULL, prev points to the new head. Return prev.
```

**Example**

```text
head -> [1] -> [2] -> [3] -> NULL
  prev=NULL, cur=[1]: next=[2], [1]->next=NULL,   prev=[1], cur=[2]
  prev=[1],  cur=[2]: next=[3], [2]->next=[1],    prev=[2], cur=[3]
  prev=[2],  cur=[3]: next=NULL,[3]->next=[2],    prev=[3], cur=NULL
  Return prev=[3]
  Result: head -> [3] -> [2] -> [1] -> NULL
```

**TRAP**

```text
Return prev, NOT cur. cur is NULL at the end.
      NEVER use recursion for long lists -- blows the stack.
```

**Complexity:** O(n) time, O(1) space

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

typedef struct Node { int id; struct Node *next; } Node;

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

int main(void) {
    Node*h=NULL; for(int i=3;i>=1;i--){Node*n=malloc(sizeof*n);n->id=i;n->next=h;h=n;} h=reverseList(h); for(Node*c=h;c;c=c->next)printf("%d -> ",c->id); printf("NULL\n"); while(h){Node*t=h->next;free(h);h=t;}
    return 0;
}
```

**Sample output:**

```text
3 -> 2 -> 1 -> NULL
```

### 60. findMiddle - slow & fast pointer

**Algorithm**

```text
step1: slow = head, fast = head
step2: Move slow by 1, fast by 2 each iteration
step3: When fast reaches end (NULL or last node), slow is at the middle
```

**Example**

```text
[1] -> [2] -> [3] -> [4] -> [5]
  slow=[1],fast=[1]: slow=[2],fast=[3]
  slow=[2],fast=[3]: slow=[3],fast=[5]
  fast->next == NULL, STOP. Middle = [3]
```

**Complexity:** O(n) time, O(1) space

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

typedef struct Node { int id; struct Node *next; } Node;

Node *findMiddle(Node *head) {
    if (head == NULL) return NULL;
    Node *slow = head, *fast = head;
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

int main(void) {
    Node*h=NULL; for(int i=5;i>=1;i--){Node*n=malloc(sizeof*n);n->id=i;n->next=h;h=n;} Node*m=findMiddle(h); printf("middle=%d\n", m->id); while(h){Node*t=h->next;free(h);h=t;}
    return 0;
}
```

**Sample output:**

```text
middle=3
```

### 61. hasCycle - Floyd's Tortoise and Hare

**Algorithm**

```text
step1: slow and fast both start at head
step2: slow moves 1 step, fast moves 2 steps
step3: If cycle exists: fast will eventually lap slow (they meet)
       If no cycle: fast hits NULL
```

**Complexity:** O(n) time, O(1) space

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

typedef struct Node { int id; struct Node *next; } Node;

int hasCycle(const Node *head) {
    const Node *slow = head, *fast = head;
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) return 1;
    }
    return 0;
}

int main(void) {
    Node*h=NULL; for(int i=3;i>=1;i--){Node*n=malloc(sizeof*n);n->id=i;n->next=h;h=n;} printf("hasCycle(linear)=%d\n", hasCycle(h)); while(h){Node*t=h->next;free(h);h=t;}
    return 0;
}
```

**Sample output:**

```text
hasCycle(linear)=0
```

---

## Section 6 — Binary Search Tree


### 62. createBstNode

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

typedef struct BstNode { int id; struct BstNode *left,*right; } BstNode;

BstNode *createBstNode(int id) {
    BstNode *n = (BstNode *)malloc(sizeof(*n));
    if (n == NULL) return NULL;
    n->id = id; n->left = n->right = NULL;
    return n;
}

int main(void) {
    BstNode*n=createBstNode(5); printf("createBstNode(5): id=%d\n", n->id); free(n);
    return 0;
}
```

**Sample output:**

```text
createBstNode(5): id=5
```

### 63. bstInsert - recursive, return-root pattern

**Definition:** Insert a value into a BST maintaining the invariant: left subtree < root < right subtree

**Algorithm**

```text
  step1: If root == NULL, this is the insertion point. Create & return node.
  step2: If id < root->id: recurse LEFT, assign result to root->left
  step3: If id > root->id: recurse RIGHT, assign result to root->right
  step4: If id == root->id: duplicate, do nothing
  step5: Return root (unchanged or with updated child pointer)

Why "return-root" pattern?
  The caller writes: root = bstInsert(root, 42);
  This handles the empty-tree case (root was NULL, now it's the new node)
  without needing a special check.
```

**Example**

```text
Insert 5 into: [10] -> left=[3], right=[15]
  5 < 10 -> recurse left with root=[3]
  5 > 3  -> recurse right with root=NULL
  root==NULL -> create [5], return it
  [3]->right = [5]
  Result: [10] -> left=[3 -> right=[5]], right=[15]
```

**Complexity:** O(h) where h = height. Balanced: O(log n). Worst: O(n).

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

typedef struct BstNode { int id; struct BstNode *left,*right; } BstNode;
BstNode *createBstNode(int id) {
    BstNode *n = (BstNode *)malloc(sizeof(*n));
    if (n == NULL) return NULL;
    n->id = id; n->left = n->right = NULL;
    return n;
}

BstNode *bstInsert(BstNode *root, int id) {
    if (root == NULL) return createBstNode(id);
    if      (id <  root->id) root->left  = bstInsert(root->left,  id);
    else if (id >  root->id) root->right = bstInsert(root->right, id);
    return root;
}

int main(void) {
    BstNode*r=NULL; int k[]={50,30,70,20,40}; for(int i=0;i<5;i++) r=bstInsert(r,k[i]); printf("inserted 5 keys; root=%d left=%d right=%d\n", r->id, r->left->id, r->right->id); /* leak ok for demo */
    return 0;
}
```

**Sample output:**

```text
inserted 5 keys; root=50 left=30 right=70
```

### 64. bstSearch

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

typedef struct BstNode { int id; struct BstNode *left,*right; } BstNode;
BstNode *createBstNode(int id) {
    BstNode *n = (BstNode *)malloc(sizeof(*n));
    if (n == NULL) return NULL;
    n->id = id; n->left = n->right = NULL;
    return n;
}
BstNode *bstInsert(BstNode *root, int id) {
    if (root == NULL) return createBstNode(id);
    if      (id <  root->id) root->left  = bstInsert(root->left,  id);
    else if (id >  root->id) root->right = bstInsert(root->right, id);
    return root;
}

BstNode *bstSearch(BstNode *root, int key) {
    if (root == NULL || root->id == key) return root;
    if (key < root->id) return bstSearch(root->left,  key);
    else                return bstSearch(root->right, key);
}

int main(void) {
    BstNode*r=NULL; int k[]={50,30,70,20,40}; for(int i=0;i<5;i++) r=bstInsert(r,k[i]); printf("search 40: %s\n", bstSearch(r,40)?"found":"not found"); printf("search 99: %s\n", bstSearch(r,99)?"found":"not found");
    return 0;
}
```

**Sample output:**

```text
search 40: found
search 99: not found
```

### 65. bstMin / bstMax

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

typedef struct BstNode { int id; struct BstNode *left,*right; } BstNode;
BstNode *createBstNode(int id) {
    BstNode *n = (BstNode *)malloc(sizeof(*n));
    if (n == NULL) return NULL;
    n->id = id; n->left = n->right = NULL;
    return n;
}
BstNode *bstInsert(BstNode *root, int id) {
    if (root == NULL) return createBstNode(id);
    if      (id <  root->id) root->left  = bstInsert(root->left,  id);
    else if (id >  root->id) root->right = bstInsert(root->right, id);
    return root;
}

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

int main(void) {
    BstNode*r=NULL; int k[]={50,30,70,20,80}; for(int i=0;i<5;i++) r=bstInsert(r,k[i]); printf("min=%d max=%d\n", bstMin(r)->id, bstMax(r)->id);
    return 0;
}
```

**Sample output:**

```text
min=20 max=80
```

### 66, 67, 68. Traversals: inorder (sorted!), preorder, postorder

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

typedef struct BstNode { int id; struct BstNode *left,*right; } BstNode;
BstNode *createBstNode(int id) {
    BstNode *n = (BstNode *)malloc(sizeof(*n));
    if (n == NULL) return NULL;
    n->id = id; n->left = n->right = NULL;
    return n;
}
BstNode *bstInsert(BstNode *root, int id) {
    if (root == NULL) return createBstNode(id);
    if      (id <  root->id) root->left  = bstInsert(root->left,  id);
    else if (id >  root->id) root->right = bstInsert(root->right, id);
    return root;
}

void inorder  (const BstNode *r) { if(r){ inorder(r->left);  printf("%d ",r->id); inorder(r->right); }}

void preorder (const BstNode *r) { if(r){ printf("%d ",r->id); preorder(r->left);  preorder(r->right);}}

void postorder(const BstNode *r) { if(r){ postorder(r->left); postorder(r->right); printf("%d ",r->id);}}

int main(void) {
    BstNode*r=NULL; int k[]={50,30,70,20,40}; for(int i=0;i<5;i++) r=bstInsert(r,k[i]); printf("inorder: "); inorder(r); printf("\npreorder: "); preorder(r); printf("\npostorder: "); postorder(r); printf("\n");
    return 0;
}
```

**Sample output:**

```text
inorder: 20 30 40 50 70 
preorder: 50 30 20 40 70 
postorder: 20 40 30 70 50
```

### 69. bstDelete - the three cases

```text
Case 1: LEAF (no children) -> just free it
Case 2: ONE child -> splice: parent bypasses this node to the child
Case 3: TWO children -> copy inorder successor's value here,
        then recursively delete the successor (which has at most one child)

Inorder successor = smallest node in the RIGHT subtree = leftmost in right
```

**Example**

```text
Delete 10 from:      [10]
                            /      \
                         [5]       [15]
                                  /
                               [12]
  Case 3: two children. Successor = bstMin(right) = 12
  Copy: root->id = 12. Delete 12 from right subtree (Case 1: leaf)
  Result:     [12]
            /      \
         [5]       [15]
```

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

typedef struct BstNode { int id; struct BstNode *left,*right; } BstNode;
BstNode *createBstNode(int id) {
    BstNode *n = (BstNode *)malloc(sizeof(*n));
    if (n == NULL) return NULL;
    n->id = id; n->left = n->right = NULL;
    return n;
}
BstNode *bstInsert(BstNode *root, int id) {
    if (root == NULL) return createBstNode(id);
    if      (id <  root->id) root->left  = bstInsert(root->left,  id);
    else if (id >  root->id) root->right = bstInsert(root->right, id);
    return root;
}
BstNode *bstMin(BstNode *root) {
    if (root == NULL) return NULL;
    while (root->left) root = root->left;
    return root;
}
void inorder  (const BstNode *r) { if(r){ inorder(r->left);  printf("%d ",r->id); inorder(r->right); }}

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

int main(void) {
    BstNode*r=NULL; int k[]={50,30,70,20,40,60,80}; for(int i=0;i<7;i++) r=bstInsert(r,k[i]); r=bstDelete(r,50); printf("after delete 50, inorder: "); inorder(r); printf("\n");
    return 0;
}
```

**Sample output:**

```text
after delete 50, inorder: 20 30 40 60 70 80
```

### 70. freeTree - MUST use postorder (children before parent!)

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

typedef struct BstNode { int id; struct BstNode *left,*right; } BstNode;
BstNode *createBstNode(int id) {
    BstNode *n = (BstNode *)malloc(sizeof(*n));
    if (n == NULL) return NULL;
    n->id = id; n->left = n->right = NULL;
    return n;
}
BstNode *bstInsert(BstNode *root, int id) {
    if (root == NULL) return createBstNode(id);
    if      (id <  root->id) root->left  = bstInsert(root->left,  id);
    else if (id >  root->id) root->right = bstInsert(root->right, id);
    return root;
}

void freeTree(BstNode *root) {
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main(void) {
    BstNode*r=NULL; int k[]={50,30,70}; for(int i=0;i<3;i++) r=bstInsert(r,k[i]); freeTree(r); printf("tree freed (postorder)\n");
    return 0;
}
```

**Sample output:**

```text
tree freed (postorder)
```

---

## Section 7 — Queues & Stacks


### 71. Linked Queue

**Definition:** A FIFO (first-in-first-out) queue built from a linked list. Enqueue adds at the **rear**, dequeue removes from the **front** — both O(1) because we keep pointers to both ends.

**Algorithm**

```text
struct: front pointer, rear pointer, size
enqueue(x): make node; if empty, front=rear=node;
            else rear->next=node, rear=node; size++
dequeue() : if empty, fail; take front->id; front=front->next;
            if front becomes NULL, set rear=NULL too; free old; size--
peek()    : return front->id without removing
```

**Why keep a rear pointer:** without it, enqueue would walk the whole list to find the tail (O(n)). The rear pointer makes it O(1).

**Trap:** when dequeue empties the queue (`front` becomes NULL), you must also reset `rear` to NULL — otherwise rear dangles at a freed node.

**Complexity:** O(1) enqueue, dequeue, and peek.

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

typedef struct QNode{int id;struct QNode*next;}QNode;
typedef struct{QNode*front,*rear;int size;}Queue;

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

int main(void) {
    Queue*q=qCreate(); qEnqueue(q,10); qEnqueue(q,20); qEnqueue(q,30); int v; qDequeue(q,&v); printf("dequeue=%d\n",v); qPeek(q,&v); printf("peek=%d\n",v); qDestroy(q);
    return 0;
}
```

**Sample output:**

```text
dequeue=10
peek=20
```

### 77. Ring Buffer Queue

**Definition:** A FIFO queue backed by a fixed-size array reused in a circle. Indices wrap with modulo, so no memory is allocated per element after creation — ideal for embedded/real-time use.

**Algorithm**

```text
struct: data[capacity], front, rear, size
enqueue(x): if full (size==capacity) fail;
            rear=(rear+1)%capacity; data[rear]=x; size++
dequeue() : if empty (size==0) fail;
            x=data[front]; front=(front+1)%capacity; size--; return x
```

**Ring buffer vs linked queue:** the linked queue allocates a node per element (flexible size, pointer overhead); the ring buffer uses one fixed array (bounded size, zero per-element allocation, cache-friendly).

**Trap:** use a `size` counter (or waste one slot) to distinguish full from empty — both states otherwise look like `front == rear`.

**Complexity:** O(1) enqueue and dequeue; O(capacity) fixed memory.

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

typedef struct{int*data;int capacity,front,rear,size;}RingQ;

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

int main(void) {
    RingQ*q=rqCreate(4); rqEnqueue(q,1); rqEnqueue(q,2); rqEnqueue(q,3); int v; rqDequeue(q,&v); printf("ring dequeue=%d\n",v); rqPeek(q,&v); printf("ring peek=%d\n",v); rqDestroy(q);
    return 0;
}
```

**Sample output:**

```text
ring dequeue=1
ring peek=2
```

### 81. Linked Stack

**Definition:** A LIFO (last-in-first-out) stack built from a linked list. Both push and pop happen at the **head**, so both are O(1).

**Algorithm**

```text
struct: top pointer, size
push(x): make node; node->next=top; top=node; size++
pop()  : if empty fail; x=top->id; old=top; top=top->next;
         free(old); size--; return x
```

**Why the head:** inserting/removing at the head of a singly linked list is O(1) (no traversal). That maps perfectly onto stack push/pop.

**Complexity:** O(1) push and pop.

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

typedef struct SNode{int id;struct SNode*next;}SNode;
typedef struct{SNode*top;int size;}Stack;

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

int main(void) {
    Stack s={NULL,0}; sPush(&s,100); sPush(&s,200); int v; sPop(&s,&v); printf("pop=%d\n",v); sPop(&s,&v); printf("pop=%d\n",v);
    return 0;
}
```

**Sample output:**

```text
pop=200
pop=100
```

---

## Section 8 — Parsing & Formatting


### 82. Parse three integers from a string (sscanf basics)

**Definition:** Extract structured numbers out of a text line into variables.

**Algorithm**

```text
step1: call sscanf(str, "%d %d %d", &a, &b, &c)
step2: check the return value == 3 (all three matched)
step3: if fewer matched, the input was malformed
```

**Example**

```text
str = "10 20 30"
  sscanf matches 3 items -> a=10, b=20, c=30, returns 3
```

**Example**

```text
str = "10 xx 30"
  sscanf matches only "10", stops at "xx" -> returns 1 (malformed)
```

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

int parseThreeInts(const char *str, int *a, int *b, int *c) {
    int matched = sscanf(str, "%d %d %d", a, b, c);
    return matched;                       /* caller checks == 3 */
}

int main(void) {
    int a,b,c; int n=parseThreeInts("10 20 30",&a,&b,&c); printf("matched=%d -> %d,%d,%d\n",n,a,b,c);
    return 0;
}
```

**Sample output:**

```text
matched=3 -> 10,20,30
```

### 83. Parse a "key=value" configuration line (sscanf with %[ ])

**Definition:** Split a line like "timeout=30" into key string and value string.

**Algorithm**

```text
  step1: use a scanset %[^=] to read everything up to '=' into key
  step2: skip the '=' literally
  step3: %s (or %[^\n]) reads the value
  step4: check sscanf returned 2 (both fields parsed)

The %[^=] means "match any char that is NOT '='". The width limits
(%63[^=]) prevent buffer overflow -- ALWAYS bound scanset/string widths.
```

**Example**

```text
line = "timeout=30"
  key="timeout", value="30", returns 2
```

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

int parseKeyValue(const char *line, char *key, size_t keySz,
                  char *value, size_t valSz) {
    /* Build a format string with widths derived from the buffer sizes.
     * For a fixed example we hardcode safe widths; in real code you would
     * snprintf the format string itself. Here keySz/valSz are assumed >= 64. */
    (void)keySz; (void)valSz;
    int matched = sscanf(line, "%63[^=]=%63s", key, value);
    return matched;                       /* caller checks == 2 */
}

int main(void) {
    char k[64],val[64]; if(parseKeyValue("timeout=30",k,sizeof k,val,sizeof val)==2) printf("key=%s value=%s\n",k,val);
    return 0;
}
```

**Sample output:**

```text
key=timeout value=30
```

### 84. Parse an IPv4 address into four octets (sscanf with field count)

**Definition:** Convert "192.168.1.10" into four integers, validating the structure.

**Algorithm**

```text
step1: sscanf(str, "%d.%d.%d.%d", &o1,&o2,&o3,&o4)
step2: require return value == 4 (exactly four octets)
step3: validate each octet is in range 0..255
```

**Example**

```text
"192.168.1.10" -> 192,168,1,10 (valid)
         "192.168.1"     -> returns 3 (invalid - missing octet)
         "300.1.2.3"     -> returns 4 but 300 > 255 (invalid range)
```

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

int parseIPv4(const char *str, int octets[4]) {
    int matched = sscanf(str, "%d.%d.%d.%d",
                         &octets[0], &octets[1], &octets[2], &octets[3]);
    if (matched != 4) return 0;           /* wrong number of octets */
    for (int i = 0; i < 4; i++)
        if (octets[i] < 0 || octets[i] > 255) return 0;  /* out of range */
    return 1;                             /* valid */
}

int main(void) {
    int o[4]; int ok=parseIPv4("192.168.1.10",o); printf("valid=%d -> %d.%d.%d.%d\n",ok,o[0],o[1],o[2],o[3]);
    return 0;
}
```

**Sample output:**

```text
valid=1 -> 192.168.1.10
```

### 85. Parse "HH:MM:SS" time and convert to total seconds (sscanf)

**Algorithm**

```text
step1: sscanf(str, "%d:%d:%d", &h, &m, &s)
step2: require 3 matched
step3: total = h*3600 + m*60 + s
```

**Example**

```text
"01:30:45" -> 1*3600 + 30*60 + 45 = 5445 seconds
```

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

long parseTimeToSeconds(const char *str) {
    int h, m, s;
    if (sscanf(str, "%d:%d:%d", &h, &m, &s) != 3) return -1;  /* malformed */
    return (long)h * 3600 + (long)m * 60 + s;
}

int main(void) {
    printf("01:30:45 -> %ld sec\n", parseTimeToSeconds("01:30:45"));
    return 0;
}
```

**Sample output:**

```text
01:30:45 -> 5445 sec
```

### 86. Safe string building with snprintf (no overflow)

**Definition:** Build a formatted string into a fixed buffer WITHOUT ever overflowing it.

**Algorithm**

```text
step1: snprintf(buf, size, fmt, ...) writes at most size-1 chars + '\0'
step2: it returns how many chars it WOULD have written
step3: if return value >= size, output was TRUNCATED -> handle it
```

**Example**

```text
buffer size 20, formatting "User: Alice (age 30)"
  fits -> returns 20-ish, no truncation
  tiny buffer -> returns full length, output truncated, still safe
```

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

int buildUserString(char *buf, size_t size, const char *name, int age) {
    int n = snprintf(buf, size, "User: %s (age %d)", name, age);
    /* n = number of chars that WOULD be written (excluding '\0') */
    if (n < 0) return -1;                 /* encoding error */
    if ((size_t)n >= size) return 1;      /* truncated (output too long) */
    return 0;                             /* success, fully written */
}

int main(void) {
    char buf[40]; int rc=buildUserString(buf,sizeof buf,"Alice",30); printf("rc=%d buf=%s\n",rc,buf);
    return 0;
}
```

**Sample output:**

```text
rc=0 buf=User: Alice (age 30)
```

### 87. Build a CSV row safely by appending with snprintf

**Definition:** Concatenate several fields into one CSV line, tracking remaining space so we never overflow. This is the safe pattern for incremental string build.

**Algorithm**

```text
step1: keep an offset into the buffer (chars written so far)
step2: each snprintf writes at (buf + offset) with (size - offset) space
step3: advance offset by the return value
step4: if offset >= size, stop (buffer full)
```

**Example**

```text
fields {"id","name","age"} -> "id,name,age"
```

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

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

int main(void) {
    char csv[64]; const char*f[]={"id","name","age"}; buildCSVRow(csv,sizeof csv,f,3); printf("csv=%s\n",csv);
    return 0;
}
```

**Sample output:**

```text
csv=id,name,age
```

### 88. Integer to string conversion (snprintf instead of itoa)

**Definition:** C has no standard itoa(). snprintf is the portable, safe way to convert a number to its string form.

**Algorithm**

```text
snprintf(buf, size, "%d", value)
```

**Example**

```text
42 -> "42",  -7 -> "-7"
```

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

void intToStr(int value, char *buf, size_t size) {
    snprintf(buf, size, "%d", value);
}

int main(void) {
    char b[16]; intToStr(-42,b,sizeof b); printf("intToStr(-42)=%s\n",b);
    return 0;
}
```

**Sample output:**

```text
intToStr(-42)=-42
```

### 89. Round-trip: format with snprintf, then parse back with sscanf

**Definition:** Demonstrate serialization (snprintf) and deserialization (sscanf) as inverse operations -- the core of any text protocol or config file.

**Algorithm**

```text
step1: snprintf packs three ints into "a,b,c"
step2: sscanf unpacks "a,b,c" back into three ints
step3: verify the round-trip preserved the values
```

**Example**

```text
(1,2,3) -> "1,2,3" -> (1,2,3)  [matches]
```

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

int roundTripInts(int a, int b, int c) {
    char buf[32];
    snprintf(buf, sizeof(buf), "%d,%d,%d", a, b, c);   /* serialize */
    int x, y, z;
    if (sscanf(buf, "%d,%d,%d", &x, &y, &z) != 3) return 0;  /* deserialize */
    return (x == a && y == b && z == c);               /* round-trip OK? */
}

int main(void) {
    printf("roundTrip(1,2,3)=%s\n", roundTripInts(1,2,3)?"MATCHED":"FAILED");
    return 0;
}
```

**Sample output:**

```text
roundTrip(1,2,3)=MATCHED
```

---
## Section 9 — Buffers & Driver Patterns

> These four programs build from the linked list you already know up to real driver data structures. Read them in order — each one reuses the idea before it.


### SLL — Insert in Ascending and Descending (Sorted) Order

**Problem:** Insert values into a singly linked list so it stays *sorted* — one version keeps it ascending (smallest first), the other descending (largest first).

**Approach / Logic:**
- This is the same SLL you know, but instead of always inserting at head/tail, you find the *correct position* and splice the node in.
- step1: make the new node.
- step2: handle the head case — if the list is empty, or the new value belongs before the current head, the new node becomes the head.
- step3: otherwise walk with `cur` until the *next* node should come after the new value, i.e. stop right before the first node that is `>= v` (ascending) or `<= v` (descending).
- step4: splice: `n->next = cur->next; cur->next = n;`
- The ONLY difference between ascending and descending is the comparison operator. Flip `<`/`<=` to `>`/`>=`.

**Complexity:** O(n) per insert (you may walk the whole list to find the spot), O(1) extra space.

```c
/* SLL: insert in ASCENDING and DESCENDING (sorted) order */
#include <stdio.h>
#include <stdlib.h>

typedef struct Node { int data; struct Node *next; } Node;

static Node *makeNode(int v) {
    Node *n = malloc(sizeof *n);
    if (n) { n->data = v; n->next = NULL; }
    return n;
}

/* Insert keeping list ASCENDING (smallest first).
 * Walk until we find the first node whose data is >= v; insert before it. */
static Node *insertAscending(Node *head, int v) {
    Node *n = makeNode(v);
    if (!n) return head;
    if (!head || v <= head->data) {        /* empty or new head */
        n->next = head;
        return n;
    }
    Node *cur = head;
    while (cur->next && cur->next->data < v) /* stop before first >= v */
        cur = cur->next;
    n->next = cur->next;
    cur->next = n;
    return head;
}

/* Insert keeping list DESCENDING (largest first).
 * Same logic, comparison flipped. */
static Node *insertDescending(Node *head, int v) {
    Node *n = makeNode(v);
    if (!n) return head;
    if (!head || v >= head->data) {
        n->next = head;
        return n;
    }
    Node *cur = head;
    while (cur->next && cur->next->data > v)
        cur = cur->next;
    n->next = cur->next;
    cur->next = n;
    return head;
}

static void printList(const char *label, Node *head) {
    printf("%s", label);
    for (Node *c = head; c; c = c->next) printf("%d -> ", c->data);
    printf("NULL\n");
}

static void freeList(Node *head) {
    while (head) { Node *t = head->next; free(head); head = t; }
}

int main(void) {
    int vals[] = {30, 10, 50, 20, 40};
    int n = (int)(sizeof(vals) / sizeof(vals[0]));

    Node *asc = NULL, *desc = NULL;
    for (int i = 0; i < n; i++) {
        asc  = insertAscending(asc,  vals[i]);
        desc = insertDescending(desc, vals[i]);
    }
    printList("Ascending : ", asc);
    printList("Descending: ", desc);

    freeList(asc);
    freeList(desc);
    return 0;
}
```

**Sample output:**

```text
Ascending : 10 -> 20 -> 30 -> 40 -> 50 -> NULL
Descending: 50 -> 40 -> 30 -> 20 -> 10 -> NULL
```

### Circular Ring Buffer

**Problem:** A fixed-size FIFO queue that reuses one array in a circle — when you reach the end, you wrap back to index 0. Used everywhere in embedded/streaming code (UART buffers, audio, logs).

**Approach / Logic — relate it to the SLL you know:**
- An SLL grows by allocating new nodes. A ring buffer does the opposite: **fixed memory, reused in a circle.** No malloc per element.
- Two cursors: `head` = where we WRITE next, `tail` = where we READ next. Both advance with `index = (index + 1) % CAP`, which is what makes it wrap around.
- The tricky part is telling EMPTY from FULL, because in both cases `head == tail` could be true. Two common solutions:
  1. keep a `count` of stored items (used here — simplest to reason about): EMPTY is `count==0`, FULL is `count==CAP`.
  2. waste one slot so FULL is `(head+1)%CAP == tail` (used in the lock-free version in the systems guide).
- step1 (put): if full, reject. Else write at `head`, advance head, `count++`.
- step2 (get): if empty, reject. Else read at `tail`, advance tail, `count--`.

**Complexity:** O(1) put and get. O(CAP) fixed memory, zero allocations after init.

```c
/* CIRCULAR RING BUFFER (single-threaded FIFO over a fixed array)
 *
 * Idea: a fixed array reused in a circle. head = where we WRITE next,
 * tail = where we READ next. Both advance modulo capacity and wrap to 0.
 * We track 'count' so we can tell EMPTY (count==0) from FULL (count==cap)
 * - this avoids the "waste one slot" trick and is easy to reason about.
 *
 *   cap = 5
 *   index:  0    1    2    3    4
 *         [ A ][ B ][ C ][   ][   ]
 *           ^tail          ^head     count=3
 *   write D -> head goes 3->4 ; read A -> tail goes 0->1 (wraps at 5)
 */
#include <stdio.h>
#include <stdbool.h>

#define CAP 5

typedef struct {
    int  buf[CAP];
    int  head;     /* next write index */
    int  tail;     /* next read index  */
    int  count;    /* items currently stored */
} Ring;

static void ring_init(Ring *r) { r->head = r->tail = r->count = 0; }
static bool ring_empty(const Ring *r) { return r->count == 0; }
static bool ring_full (const Ring *r) { return r->count == CAP; }

static bool ring_put(Ring *r, int v) {
    if (ring_full(r)) return false;          /* reject when full */
    r->buf[r->head] = v;
    r->head = (r->head + 1) % CAP;           /* advance + wrap */
    r->count++;
    return true;
}

static bool ring_get(Ring *r, int *out) {
    if (ring_empty(r)) return false;         /* nothing to read */
    *out = r->buf[r->tail];
    r->tail = (r->tail + 1) % CAP;           /* advance + wrap */
    r->count--;
    return true;
}

int main(void) {
    Ring r; ring_init(&r);
    int v;

    /* fill past capacity to show FULL rejection */
    for (int i = 1; i <= 7; i++)
        printf("put %d -> %s\n", i, ring_put(&r, i) ? "ok" : "FULL (rejected)");

    /* read two (frees space), then wrap-around writes */
    ring_get(&r, &v); printf("get -> %d\n", v);
    ring_get(&r, &v); printf("get -> %d\n", v);
    printf("put 6 -> %s (wraps to index 0)\n", ring_put(&r, 6) ? "ok" : "FULL");
    printf("put 7 -> %s\n", ring_put(&r, 7) ? "ok" : "FULL");

    /* drain everything */
    printf("drain: ");
    while (ring_get(&r, &v)) printf("%d ", v);
    printf("\n");
    return 0;
}
```

**Sample output:**

```text
put 1 -> ok
put 2 -> ok
put 3 -> ok
put 4 -> ok
put 5 -> ok
put 6 -> FULL (rejected)
put 7 -> FULL (rejected)
get -> 1
get -> 2
put 6 -> ok (wraps to index 0)
put 7 -> ok
drain: 3 4 5 6 7
```

### DMA Descriptor Ring (NIC / hardware-driver style)

**Problem:** How a network card (NIC) and its driver exchange packets without locking, using a ring of *descriptors* in shared memory. This is the real-world structure behind every Ethernet/WiFi driver.

**Approach / Logic — build up from what you know:**
- **SLL** links *data nodes* with pointers.
- **Ring buffer** is a fixed array of *data* reused in a circle.
- **DMA descriptor ring** is a ring buffer whose elements are *descriptors* — tiny structs that don't hold the data themselves but say: *where* the packet buffer is (`addr`), *how big* it is (`len`), and *who owns this slot right now* (`own`).
- **The OWN bit is the whole trick.** Each descriptor has an owner:
  - `OWN = HW` → the NIC owns it; the driver must not touch it.
  - `OWN = SW` → the driver owns it; safe to read and recycle.
  - This single bit lets CPU and hardware share the ring with **no lock** — it's a single-producer/single-consumer handoff, exactly like a ring buffer's head/tail, but encoded per-slot.

**RX (receive) flow:**
- step1: driver sets up N descriptors, each pointing at an empty buffer, all `OWN=HW` (armed).
- step2: the NIC receives a packet, DMA-copies it into the slot's buffer, writes `len`, flips `OWN=SW`, and moves to the next slot.
- step3: the driver polls for slots with `OWN=SW`, processes the packet, then **re-arms** the slot (`OWN=HW`) so the NIC can reuse it. The index wraps modulo ring size — same `% N` wrap as the ring buffer.

(The program simulates the NIC in software so it runs on a normal PC.)

**Why it matters:** lock-free, zero-copy, and the producer/consumer never block each other — the design goal of high-speed I/O.

```c
/* DMA DESCRIPTOR RING (NIC / hardware-driver style)
 *
 * HOW TO THINK ABOUT IT (building on what you know):
 *   - An SLL links nodes with pointers; you walk node->next.
 *   - A ring buffer is a fixed array reused in a circle (head/tail wrap).
 *   - A DMA DESCRIPTOR RING is a ring buffer whose elements are not plain
 *     data, but DESCRIPTORS: small structs that tell the hardware WHERE a
 *     packet buffer lives (address + length) and WHO owns the slot right now.
 *
 * THE OWNERSHIP IDEA (the heart of it):
 *   Each descriptor has an OWN bit:
 *       OWN = HW  -> the NIC owns this slot (driver must NOT touch it)
 *       OWN = SW  -> the driver (software) owns it (safe to read/recycle)
 *   This bit is how CPU and hardware share the ring without a lock - it is a
 *   single-producer/single-consumer handoff, exactly like a ring buffer's
 *   head/tail, but the "head/tail" is encoded per-slot by the OWN bit.
 *
 * RX FLOW (receive):
 *   1. Driver sets up N descriptors, each pointing at an empty buffer, OWN=HW.
 *   2. NIC receives a packet, DMA-copies it into the buffer at 'tail',
 *      writes the length, flips OWN=SW, advances its internal index.
 *   3. Driver walks slots with OWN=SW, processes the packet, then RE-ARMS the
 *      slot (OWN=HW) so the NIC can reuse it. Index wraps modulo ring size.
 *
 * We simulate the NIC in software here so it runs on a normal PC.
 */
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define RING_SIZE 4
#define BUF_SIZE  64

enum { OWN_SW = 0, OWN_HW = 1 };

typedef struct {
    uint8_t *addr;     /* DMA buffer this descriptor points at */
    uint16_t len;      /* bytes the NIC wrote (valid when OWN=SW) */
    uint8_t  own;      /* OWN_HW or OWN_SW */
} Descriptor;

static Descriptor ring[RING_SIZE];
static uint8_t    buffers[RING_SIZE][BUF_SIZE];

/* Driver: build the ring, hand every slot to HW */
static void rx_ring_init(void) {
    for (int i = 0; i < RING_SIZE; i++) {
        ring[i].addr = buffers[i];
        ring[i].len  = 0;
        ring[i].own  = OWN_HW;       /* armed: NIC may fill it */
    }
}

/* Simulated NIC: deliver a packet into the slot it currently owns. */
static void nic_receive(int slot, const char *packet) {
    if (ring[slot].own != OWN_HW) { printf("  [nic] slot %d not mine\n", slot); return; }
    uint16_t n = (uint16_t)strlen(packet);
    if (n > BUF_SIZE) n = BUF_SIZE;
    memcpy(ring[slot].addr, packet, n);   /* DMA copy */
    ring[slot].len = n;
    ring[slot].own = OWN_SW;              /* hand back to driver */
    printf("  [nic] wrote %u bytes into slot %d, OWN->SW\n", n, slot);
}

int main(void) {
    rx_ring_init();
    int tail = 0;   /* driver's read cursor, like a ring-buffer tail */

    const char *packets[] = {"PKT-alpha", "PKT-bravo", "PKT-charlie",
                             "PKT-delta", "PKT-echo"};
    int np = (int)(sizeof(packets)/sizeof(packets[0]));

    for (int p = 0; p < np; p++) {
        /* NIC fills the slot at the hardware's current position (we mirror tail) */
        nic_receive(tail % RING_SIZE, packets[p]);

        /* Driver polls: is the slot at 'tail' now owned by SW? */
        Descriptor *d = &ring[tail % RING_SIZE];
        if (d->own == OWN_SW) {
            char tmp[BUF_SIZE + 1];
            memcpy(tmp, d->addr, d->len);
            tmp[d->len] = '\0';
            printf("[drv] slot %d received \"%s\" (%u bytes)\n",
                   tail % RING_SIZE, tmp, d->len);
            d->own = OWN_HW;            /* RE-ARM: give slot back to NIC */
            tail++;                     /* advance; wraps via % RING_SIZE */
        }
    }
    printf("Processed %d packets through a %d-slot descriptor ring.\n", np, RING_SIZE);
    return 0;
}
```

**Sample output:**

```text
  [nic] wrote 9 bytes into slot 0, OWN->SW
[drv] slot 0 received "PKT-alpha" (9 bytes)
  [nic] wrote 9 bytes into slot 1, OWN->SW
[drv] slot 1 received "PKT-bravo" (9 bytes)
  [nic] wrote 11 bytes into slot 2, OWN->SW
[drv] slot 2 received "PKT-charlie" (11 bytes)
  [nic] wrote 9 bytes into slot 3, OWN->SW
[drv] slot 3 received "PKT-delta" (9 bytes)
  [nic] wrote 8 bytes into slot 0, OWN->SW
[drv] slot 0 received "PKT-echo" (8 bytes)
Processed 5 packets through a 4-slot descriptor ring.
```

### WiFi Driver — Pack / Unpack / Extract

**Problem:** Drivers constantly convert between *C structs* (easy to work with) and *raw bytes on the wire* (what the hardware sends/receives). Three core skills, shown on real 802.11 WiFi structures.

**The three operations:**
- **PACK** = take fields from C variables and write them into a byte buffer in a fixed wire layout (serialize: host → bytes).
- **UNPACK** = read a byte buffer back into C variables (deserialize: bytes → host).
- **EXTRACT** = pull a sub-field of *bits* out of a packed word using shift + mask.

**Approach / Logic:**

*Part A — EXTRACT (bitfields in the 802.11 Frame Control word):*
- A single 16-bit word packs many sub-fields (protocol version, type, subtype, ToDS, FromDS…).
- Extract any field with `(word >> shift) & ((1u << bits) - 1)` — shift it down to bit 0, then mask off the width you want. This is the same bit-masking from Section 3.

*Part B — PACK / UNPACK (the 24-byte MAC header):*
- step1 (pack): write each field at its fixed byte offset. Multi-byte fields go **little-endian** (802.11 wire order) using explicit `buf[0]=low; buf[1]=high`, which is portable on any CPU. Copy the 6-byte MAC addresses with `memcpy`.
- step2 (unpack): read the same offsets back into the struct, reconstructing 16-bit fields with `buf[0] | (buf[1]<<8)`.
- A round-trip (`pack` then `unpack`) must reproduce the original struct — the program asserts this.

*Part C — PACK / UNPACK (TLV information elements):*
- WiFi management frames carry variable options as **TLV**: `[type:1][len:1][value:len bytes]`, repeated.
- Pack: write type, write len, `memcpy` the value; return total bytes.
- Unpack: walk the buffer, read type+len, print `len` value bytes, advance by `2+len`. Always guard against a `len` that runs past the buffer (malformed-frame defense).

**Why endianness is called out:** if you just `memcpy` a `uint16_t` you get the host's byte order, which breaks on a big-endian CPU. Explicit byte placement makes the wire format deterministic.

```c
/* WIFI DRIVER: PACK / UNPACK / EXTRACT
 *
 * THREE skills every driver needs, shown on real WiFi-style structures:
 *
 *   PACK    = take fields from C variables and write them into a byte buffer
 *             in a fixed wire layout (serialize, host -> bytes).
 *   UNPACK  = read a byte buffer back into C variables (deserialize, bytes -> host).
 *   EXTRACT = pull a sub-field of bits out of a packed word (bit masking/shift).
 *
 * Endianness matters: 802.11 is LITTLE-ENDIAN on the wire. We pack bytes
 * explicitly (buf[0]=low byte) so the code is portable regardless of the CPU.
 */
#include <stdio.h>
#include <stdint.h>
#include <string.h>

/* ----- helpers: explicit little-endian put/get (portable) ----- */
static void put_u16_le(uint8_t *b, uint16_t v) { b[0]=(uint8_t)v; b[1]=(uint8_t)(v>>8); }
static uint16_t get_u16_le(const uint8_t *b)    { return (uint16_t)(b[0] | (b[1]<<8)); }

/* ============================================================
 * PART A: 802.11 Frame Control field - EXTRACT bitfields
 * ------------------------------------------------------------
 * The 16-bit Frame Control word packs many sub-fields:
 *   bits 0-1  : Protocol Version
 *   bits 2-3  : Type        (0=mgmt, 1=ctrl, 2=data)
 *   bits 4-7  : Subtype
 *   bit  8    : ToDS
 *   bit  9    : FromDS
 *   ... (more flags above)
 * EXTRACT = (word >> shift) & mask
 * ============================================================ */
#define FC_GET(fc, shift, bits)  (((fc) >> (shift)) & ((1u << (bits)) - 1u))

static void extract_frame_control(uint16_t fc) {
    printf("PART A - EXTRACT 802.11 Frame Control = 0x%04X\n", fc);
    printf("  Protocol Version: %u\n", FC_GET(fc, 0, 2));
    printf("  Type            : %u\n", FC_GET(fc, 2, 2));
    printf("  Subtype         : %u\n", FC_GET(fc, 4, 4));
    printf("  ToDS            : %u\n", FC_GET(fc, 8, 1));
    printf("  FromDS          : %u\n", FC_GET(fc, 9, 1));
}

/* ============================================================
 * PART B: 802.11 MAC header - PACK and UNPACK
 * ------------------------------------------------------------
 * Simplified MAC header layout (24 bytes):
 *   off 0 : frame_control (2 bytes, LE)
 *   off 2 : duration      (2 bytes, LE)
 *   off 4 : addr1 (6 bytes)  - receiver MAC
 *   off 10: addr2 (6 bytes)  - transmitter MAC
 *   off 16: addr3 (6 bytes)  - BSSID
 *   off 22: seq_ctrl (2 bytes, LE)
 * ============================================================ */
typedef struct {
    uint16_t frame_control;
    uint16_t duration;
    uint8_t  addr1[6];
    uint8_t  addr2[6];
    uint8_t  addr3[6];
    uint16_t seq_ctrl;
} MacHeader;

#define MAC_HDR_LEN 24

static void pack_mac_header(const MacHeader *h, uint8_t *buf) {
    put_u16_le(buf + 0,  h->frame_control);
    put_u16_le(buf + 2,  h->duration);
    memcpy(buf + 4,  h->addr1, 6);
    memcpy(buf + 10, h->addr2, 6);
    memcpy(buf + 16, h->addr3, 6);
    put_u16_le(buf + 22, h->seq_ctrl);
}

static void unpack_mac_header(const uint8_t *buf, MacHeader *h) {
    h->frame_control = get_u16_le(buf + 0);
    h->duration      = get_u16_le(buf + 2);
    memcpy(h->addr1, buf + 4,  6);
    memcpy(h->addr2, buf + 10, 6);
    memcpy(h->addr3, buf + 16, 6);
    h->seq_ctrl      = get_u16_le(buf + 22);
}

static void print_mac(const uint8_t *m) {
    printf("%02X:%02X:%02X:%02X:%02X:%02X", m[0],m[1],m[2],m[3],m[4],m[5]);
}

/* ============================================================
 * PART C: TLV (Type-Length-Value) - PACK and UNPACK
 * ------------------------------------------------------------
 * WiFi management frames carry "information elements" as TLVs:
 *   [type:1][len:1][value:len bytes] ... repeated
 * e.g. SSID element: type=0, len=4, value="Home"
 * ============================================================ */
static int pack_tlv(uint8_t *buf, uint8_t type, const uint8_t *val, uint8_t len) {
    buf[0] = type;
    buf[1] = len;
    memcpy(buf + 2, val, len);
    return 2 + len;                  /* total bytes written */
}

static void unpack_tlvs(const uint8_t *buf, int total) {
    int off = 0;
    while (off + 2 <= total) {
        uint8_t type = buf[off];
        uint8_t len  = buf[off + 1];
        if (off + 2 + len > total) break;       /* malformed guard */
        printf("  TLV type=%u len=%u value=\"", type, len);
        for (int i = 0; i < len; i++) putchar(buf[off + 2 + i]);
        printf("\"\n");
        off += 2 + len;
    }
}

int main(void) {
    /* ---- PART A: extract bitfields from a Frame Control word ---- */
    /* 0x0108 = data frame (type 2), ToDS=1: typical uplink data frame */
    extract_frame_control(0x0108);

    /* ---- PART B: pack a MAC header, then unpack it back ---- */
    printf("\nPART B - PACK then UNPACK MAC header\n");
    MacHeader tx = {
        .frame_control = 0x0108,
        .duration      = 0x002C,
        .addr1 = {0x00,0x11,0x22,0x33,0x44,0x55},
        .addr2 = {0xAA,0xBB,0xCC,0xDD,0xEE,0xFF},
        .addr3 = {0x66,0x77,0x88,0x99,0xAA,0xBB},
        .seq_ctrl = 0x0010
    };
    uint8_t wire[MAC_HDR_LEN];
    pack_mac_header(&tx, wire);
    printf("  packed %d bytes: ", MAC_HDR_LEN);
    for (int i = 0; i < MAC_HDR_LEN; i++) printf("%02X", wire[i]);
    printf("\n");

    MacHeader rx;
    unpack_mac_header(wire, &rx);
    printf("  unpacked FC=0x%04X dur=0x%04X seq=0x%04X\n",
           rx.frame_control, rx.duration, rx.seq_ctrl);
    printf("  addr1 (RA) = "); print_mac(rx.addr1); printf("\n");
    printf("  addr2 (TA) = "); print_mac(rx.addr2); printf("\n");
    printf("  addr3 (BSSID) = "); print_mac(rx.addr3); printf("\n");
    printf("  round-trip %s\n",
           memcmp(&tx, &rx, sizeof tx) == 0 ? "MATCHED" : "FAILED");

    /* ---- PART C: pack TLV information elements, then unpack ---- */
    printf("\nPART C - PACK then UNPACK TLV information elements\n");
    uint8_t ie[64];
    int off = 0;
    off += pack_tlv(ie + off, 0, (const uint8_t*)"Home",  4);  /* SSID */
    off += pack_tlv(ie + off, 1, (const uint8_t*)"\x02\x04\x0b\x16", 4); /* rates */
    printf("  packed %d TLV bytes\n", off);
    unpack_tlvs(ie, off);

    return 0;
}
```

**Sample output:**

```text
PART A - EXTRACT 802.11 Frame Control = 0x0108
  Protocol Version: 0
  Type            : 2
  Subtype         : 0
  ToDS            : 1
  FromDS          : 0

PART B - PACK then UNPACK MAC header
  packed 24 bytes: 08012C00001122334455AABBCCDDEEFF66778899AABB1000
  unpacked FC=0x0108 dur=0x002C seq=0x0010
  addr1 (RA) = 00:11:22:33:44:55
  addr2 (TA) = AA:BB:CC:DD:EE:FF
  addr3 (BSSID) = 66:77:88:99:AA:BB
  round-trip MATCHED

PART C - PACK then UNPACK TLV information elements
  packed 12 TLV bytes
  TLV type=0 len=4 value="Home"
  TLV type=1 len=4 value=""
```

---
## Section 10 — Memory, DMA, mmap & Reimplementing libc

> Practice with raw memory operations, the standard `mem*`/`str*` functions, custom reimplementations of them (a classic interview drill), and the systems calls behind buffer copies (`DMA`) and memory mapping (`mmap`). Every program is standalone and was compiled `-Wall -Wextra -Wpedantic` and run to produce the output shown.


### memset / memcpy / memmove (standard functions)

```text
memset(dst, byte, n) : fill n bytes with a single byte value
memcpy(dst, src, n)  : copy n bytes; src and dst MUST NOT overlap
memmove(dst, src, n) : copy n bytes; overlap IS safe (handles direction)

The key interview point: memcpy is undefined if the regions overlap;
memmove detects the direction and copies so no byte is clobbered early.
```

```c
/* Standard memory functions: memset, memcpy, memmove
 *
 * memset(dst, byte, n) : fill n bytes with a single byte value
 * memcpy(dst, src, n)  : copy n bytes; src and dst MUST NOT overlap
 * memmove(dst, src, n) : copy n bytes; overlap IS safe (handles direction)
 *
 * The key interview point: memcpy is undefined if the regions overlap;
 * memmove detects the direction and copies so no byte is clobbered early.
 */
#include <stdio.h>
#include <string.h>

static void dump(const char *label, const char *a, int n) {
    printf("%s: ", label);
    for (int i = 0; i < n; i++) putchar(a[i] ? a[i] : '.');
    printf("\n");
}

int main(void) {
    char buf[16];

    /* memset: fill */
    memset(buf, 'A', 5);
    buf[5] = '\0';
    printf("memset 'A' x5 -> %s\n", buf);

    /* memcpy: non-overlapping copy */
    char src[] = "HELLO", dst[8] = {0};
    memcpy(dst, src, 6);                 /* includes the '\0' */
    printf("memcpy HELLO -> %s\n", dst);

    /* overlap demo: shift "ABCDEF" right by 2 within the same array */
    char ov[] = "ABCDEF..";
    /* memmove handles overlap correctly: move 6 bytes from ov to ov+2 */
    memmove(ov + 2, ov, 6);
    ov[8 - 1] = '\0';
    dump("memmove overlap (shift right 2)", ov, 8);
    /* With memcpy this overlap would be UNDEFINED (may copy a byte after
       it was already overwritten). memmove is the correct tool here. */

    return 0;
}
```

**Sample output:**

```text
memset 'A' x5 -> AAAAA
memcpy HELLO -> HELLO
memmove overlap (shift right 2): ABABCDE.
```

### Custom memcpy

**Algorithm**

```text
  step1: cast void* to unsigned char* so we copy byte by byte
  step2: loop n times copying d[i] = s[i]
  step3: return the original dst (standard contract)

Why unsigned char*: void* can't be dereferenced; char is 1 byte so
the loop counts exact bytes regardless of the real data type.
```

**Example**

```text
copy 4 bytes of "ABCD" -> dst
  i=0: d[0]='A'  i=1: d[1]='B'  i=2: d[2]='C'  i=3: d[3]='D'
```

```c
/* Custom memcpy: copy n bytes from src to dst (no overlap allowed)
 *
 * Algorithm:
 *   step1: cast void* to unsigned char* so we copy byte by byte
 *   step2: loop n times copying d[i] = s[i]
 *   step3: return the original dst (standard contract)
 *
 * Why unsigned char*: void* can't be dereferenced; char is 1 byte so
 * the loop counts exact bytes regardless of the real data type.
 *
 * Example: copy 4 bytes of "ABCD" -> dst
 *   i=0: d[0]='A'  i=1: d[1]='B'  i=2: d[2]='C'  i=3: d[3]='D'
 */
#include <stdio.h>
#include <stddef.h>

void *my_memcpy(void *dst, const void *src, size_t n) {
    unsigned char *d = (unsigned char *)dst;
    const unsigned char *s = (const unsigned char *)src;
    for (size_t i = 0; i < n; i++)
        d[i] = s[i];
    return dst;
}

int main(void) {
    char src[] = "ABCDEFG";
    char dst[8] = {0};
    my_memcpy(dst, src, 8);             /* 7 chars + '\0' */
    printf("my_memcpy(ABCDEFG) -> %s\n", dst);
    return 0;
}
```

**Sample output:**

```text
my_memcpy(ABCDEFG) -> ABCDEFG
```

### Custom memmove (overlap-safe)

```text
The whole trick is COPY DIRECTION:
  - if dst < src : copy FORWARD (low to high) - the bytes we read next
                   haven't been overwritten yet.
  - if dst > src : copy BACKWARD (high to low) - same reason in reverse.
  - if dst == src: nothing to do.
```

**Algorithm**

```text
step1: cast to unsigned char*
step2: if dst < src, loop i = 0..n-1 forward
step3: else loop i = n-1..0 backward
```

**Example**

```text
array "ABCDEF", move 6 bytes from index 0 to index 2 (dst>src)
  copy BACKWARD: F first, then E, D, C, B, A
  -> "ABABCDEF" region, no byte clobbered before it is read.
```

```c
/* Custom memmove: copy n bytes; SAFE even if src and dst overlap
 *
 * The whole trick is COPY DIRECTION:
 *   - if dst < src : copy FORWARD (low to high) - the bytes we read next
 *                    haven't been overwritten yet.
 *   - if dst > src : copy BACKWARD (high to low) - same reason in reverse.
 *   - if dst == src: nothing to do.
 *
 * Algorithm:
 *   step1: cast to unsigned char*
 *   step2: if dst < src, loop i = 0..n-1 forward
 *   step3: else loop i = n-1..0 backward
 *
 * Example: array "ABCDEF", move 6 bytes from index 0 to index 2 (dst>src)
 *   copy BACKWARD: F first, then E, D, C, B, A
 *   -> "ABABCDEF" region, no byte clobbered before it is read.
 */
#include <stdio.h>
#include <stddef.h>

void *my_memmove(void *dst, const void *src, size_t n) {
    unsigned char *d = (unsigned char *)dst;
    const unsigned char *s = (const unsigned char *)src;
    if (d < s) {                        /* forward copy */
        for (size_t i = 0; i < n; i++) d[i] = s[i];
    } else if (d > s) {                 /* backward copy */
        for (size_t i = n; i > 0; i--) d[i - 1] = s[i - 1];
    }
    return dst;
}

int main(void) {
    char a[] = "ABCDEF..";
    my_memmove(a + 2, a, 6);            /* overlapping shift right by 2 */
    a[8 - 1] = '\0';
    printf("my_memmove(shift right 2) -> %s\n", a);

    char b[] = "XYZ123";
    my_memmove(b, b + 3, 3);            /* shift left, dst<src, forward */
    b[3] = '\0';
    printf("my_memmove(shift left 3) -> %s\n", b);
    return 0;
}
```

**Sample output:**

```text
my_memmove(shift right 2) -> ABABCDE
my_memmove(shift left 3) -> 123
```

### Custom memset

**Algorithm**

```text
step1: cast dst to unsigned char*
step2: store the low 8 bits of c into each of the n bytes
step3: return dst
```

**Note**

```text
memset works on BYTES. memset(arr, 1, n) on an int array does NOT
set each int to 1 - it sets every byte to 0x01, giving 0x01010101.
Only 0 (and -1) are "safe" fill values for non-char arrays.
```

**Example**

```text
my_memset(buf, '*', 4) -> buf = "****"
```

```c
/* Custom memset: fill n bytes of dst with byte value c
 *
 * Algorithm:
 *   step1: cast dst to unsigned char*
 *   step2: store the low 8 bits of c into each of the n bytes
 *   step3: return dst
 *
 * Note: memset works on BYTES. memset(arr, 1, n) on an int array does NOT
 * set each int to 1 - it sets every byte to 0x01, giving 0x01010101.
 * Only 0 (and -1) are "safe" fill values for non-char arrays.
 *
 * Example: my_memset(buf, '*', 4) -> buf = "****"
 */
#include <stdio.h>
#include <stddef.h>

void *my_memset(void *dst, int c, size_t n) {
    unsigned char *d = (unsigned char *)dst;
    unsigned char byte = (unsigned char)c;
    for (size_t i = 0; i < n; i++)
        d[i] = byte;
    return dst;
}

int main(void) {
    char buf[8] = {0};
    my_memset(buf, '*', 4);
    printf("my_memset('*',4) -> %s\n", buf);

    /* show the byte-fill gotcha on ints */
    int arr[2];
    my_memset(arr, 1, sizeof arr);      /* each BYTE = 0x01 */
    printf("my_memset(arr,1) -> arr[0]=0x%08X (NOT 1!)\n", arr[0]);
    return 0;
}
```

**Sample output:**

```text
my_memset('*',4) -> ****
my_memset(arr,1) -> arr[0]=0x01010101 (NOT 1!)
```

### Custom strncpy

```text
Mirrors the real strncpy's quirky contract:
  - copies at most n chars
  - if src is shorter than n, the remainder of dst is PADDED with '\0'
  - if src is n or longer, dst is NOT null-terminated (the famous trap!)
```

**Algorithm**

```text
step1: copy chars while i<n AND src[i] != '\0'
step2: for the rest up to n, write '\0' (padding)
```

**Example**

```text
my_strncpy(dst, "Hi", 5)
  i=0:'H' i=1:'i' i=2:'\0' i=3:'\0' i=4:'\0'  -> "Hi" + 3 nulls

SAFE-USE TRAP: always do dst[n-1]='\0' yourself if src might be >= n.
```

```c
/* Custom strncpy: copy up to n chars from src to dst
 *
 * Mirrors the real strncpy's quirky contract:
 *   - copies at most n chars
 *   - if src is shorter than n, the remainder of dst is PADDED with '\0'
 *   - if src is n or longer, dst is NOT null-terminated (the famous trap!)
 *
 * Algorithm:
 *   step1: copy chars while i<n AND src[i] != '\0'
 *   step2: for the rest up to n, write '\0' (padding)
 *
 * Example: my_strncpy(dst, "Hi", 5)
 *   i=0:'H' i=1:'i' i=2:'\0' i=3:'\0' i=4:'\0'  -> "Hi" + 3 nulls
 *
 * SAFE-USE TRAP: always do dst[n-1]='\0' yourself if src might be >= n.
 */
#include <stdio.h>
#include <stddef.h>

char *my_strncpy(char *dst, const char *src, size_t n) {
    size_t i = 0;
    for (; i < n && src[i] != '\0'; i++)
        dst[i] = src[i];
    for (; i < n; i++)                  /* pad remainder with '\0' */
        dst[i] = '\0';
    return dst;
}

int main(void) {
    char dst[6];
    my_strncpy(dst, "Hi", 6);
    printf("my_strncpy(Hi,6) -> \"%s\" (padded with nulls)\n", dst);

    char dst2[4];
    my_strncpy(dst2, "Hello", 4);       /* src longer than n: NOT terminated */
    dst2[3] = '\0';                      /* SAFE-USE: terminate ourselves */
    printf("my_strncpy(Hello,4)+manual NUL -> \"%s\"\n", dst2);
    return 0;
}
```

**Sample output:**

```text
my_strncpy(Hi,6) -> "Hi" (padded with nulls)
my_strncpy(Hello,4)+manual NUL -> "Hel"
```

### Custom strstr

```text
Returns pointer to the start of the match, or NULL if not found.
(This is the simple O(n*m) approach - clear and interview-friendly.
 Production uses KMP/Boyer-Moore for O(n+m).)
```

**Algorithm**

```text
step1: empty needle -> return haystack (by convention)
step2: for each start position i in haystack:
       - walk j over needle; while chars match, advance
       - if we reached needle's end, all matched -> return &haystack[i]
step3: no start matched -> return NULL
```

**Example**

```text
haystack="hello world", needle="wor"
  i=0..5: mismatch early
  i=6: 'w'=='w','o'=='o','r'=='r' -> needle done -> return ptr to "world"
```

```c
/* Custom strstr: find first occurrence of needle in haystack
 *
 * Returns pointer to the start of the match, or NULL if not found.
 * (This is the simple O(n*m) approach - clear and interview-friendly.
 *  Production uses KMP/Boyer-Moore for O(n+m).)
 *
 * Algorithm:
 *   step1: empty needle -> return haystack (by convention)
 *   step2: for each start position i in haystack:
 *          - walk j over needle; while chars match, advance
 *          - if we reached needle's end, all matched -> return &haystack[i]
 *   step3: no start matched -> return NULL
 *
 * Example: haystack="hello world", needle="wor"
 *   i=0..5: mismatch early
 *   i=6: 'w'=='w','o'=='o','r'=='r' -> needle done -> return ptr to "world"
 */
#include <stdio.h>

char *my_strstr(const char *haystack, const char *needle) {
    if (*needle == '\0') return (char *)haystack;   /* empty needle */
    for (int i = 0; haystack[i] != '\0'; i++) {
        int j = 0;
        while (needle[j] != '\0' && haystack[i + j] == needle[j])
            j++;
        if (needle[j] == '\0')                       /* matched all of needle */
            return (char *)&haystack[i];
    }
    return NULL;
}

int main(void) {
    const char *h = "hello world";
    char *p = my_strstr(h, "wor");
    printf("my_strstr(\"%s\",\"wor\") -> \"%s\"\n", h, p ? p : "(null)");
    p = my_strstr(h, "xyz");
    printf("my_strstr(\"%s\",\"xyz\") -> %s\n", h, p ? p : "(null)");
    return 0;
}
```

**Sample output:**

```text
my_strstr("hello world","wor") -> "world"
my_strstr("hello world","xyz") -> (null)
```

### Custom snprintf (bounded, returns would-be length)

```text
Supports a useful subset: %d, %s, %c, %% (enough to show the mechanics).
Contract like real snprintf:
  - writes at most size-1 chars + a '\0'
  - returns the number of chars it WOULD have written (so caller can
    detect truncation: returned >= size means it was cut off)
```

**Algorithm**

```text
step1: walk the format string
step2: on '%', read the conversion and emit the argument's text
step3: a helper 'put' writes one char only if room remains, but ALWAYS
       increments the would-be length counter
step4: null-terminate within the buffer; return the total count
```

**Example**

```text
my_snprintf(buf,8,"x=%d",42) -> buf="x=42", returns 4
```

```c
/* Custom mini-snprintf: format into a bounded buffer, never overflow
 *
 * Supports a useful subset: %d, %s, %c, %% (enough to show the mechanics).
 * Contract like real snprintf:
 *   - writes at most size-1 chars + a '\0'
 *   - returns the number of chars it WOULD have written (so caller can
 *     detect truncation: returned >= size means it was cut off)
 *
 * Algorithm:
 *   step1: walk the format string
 *   step2: on '%', read the conversion and emit the argument's text
 *   step3: a helper 'put' writes one char only if room remains, but ALWAYS
 *          increments the would-be length counter
 *   step4: null-terminate within the buffer; return the total count
 *
 * Example: my_snprintf(buf,8,"x=%d",42) -> buf="x=42", returns 4
 */
#include <stdio.h>
#include <stdarg.h>
#include <stddef.h>

static void put(char *buf, size_t size, size_t *len, char ch) {
    if (*len + 1 < size)               /* leave room for '\0' */
        buf[*len] = ch;
    (*len)++;                          /* count even if not written */
}

static void put_int(char *buf, size_t size, size_t *len, int v) {
    char tmp[16];
    int n = 0;
    unsigned int u;
    if (v < 0) { put(buf, size, len, '-'); u = (unsigned int)(-(long)v); }
    else u = (unsigned int)v;
    if (u == 0) tmp[n++] = '0';
    while (u) { tmp[n++] = (char)('0' + u % 10); u /= 10; }
    while (n--) put(buf, size, len, tmp[n]);   /* digits are reversed */
}

int my_snprintf(char *buf, size_t size, const char *fmt, ...) {
    va_list ap; va_start(ap, fmt);
    size_t len = 0;
    for (const char *p = fmt; *p; p++) {
        if (*p != '%') { put(buf, size, &len, *p); continue; }
        p++;                            /* skip '%' */
        switch (*p) {
            case 'd': put_int(buf, size, &len, va_arg(ap, int)); break;
            case 's': { const char *s = va_arg(ap, const char *);
                        while (*s) put(buf, size, &len, *s++); } break;
            case 'c': put(buf, size, &len, (char)va_arg(ap, int)); break;
            case '%': put(buf, size, &len, '%'); break;
            default:  put(buf, size, &len, '%'); put(buf, size, &len, *p); break;
        }
    }
    if (size > 0) buf[(len < size) ? len : size - 1] = '\0';
    va_end(ap);
    return (int)len;                    /* would-be length */
}

int main(void) {
    char buf[16];
    int n = my_snprintf(buf, sizeof buf, "x=%d s=%s", 42, "hi");
    printf("my_snprintf -> \"%s\" (returned %d)\n", buf, n);

    char small[5];
    n = my_snprintf(small, sizeof small, "%d", 123456);   /* truncates */
    printf("truncated -> \"%s\" (would-be %d, %s)\n",
           small, n, (size_t)n >= sizeof small ? "TRUNCATED" : "fit");
    return 0;
}
```

**Sample output:**

```text
my_snprintf -> "x=42 s=hi" (returned 9)
truncated -> "1234" (would-be 6, TRUNCATED)
```

### Understanding sizeof (compile-time operator)

```text
sizeof is a COMPILE-TIME OPERATOR, not a function - the compiler replaces
it with a constant. You cannot truly reimplement it as a function, but a
classic pointer-arithmetic trick reveals how it could be computed:

  MY_SIZEOF(x):  (char*)(&(x) + 1) - (char*)&(x)
    - &(x)     : address of x
    - &(x) + 1 : address ONE ELEMENT past x (pointer arithmetic scales by
                 the type's size - this is the key insight)
    - subtract as char* (byte pointers) -> the size in bytes

It also explains the #1 array gotcha:
  sizeof(array) = total bytes;  sizeof(array)/sizeof(array[0]) = length.
  BUT once an array DECAYS to a pointer (e.g. a function parameter),
  sizeof gives the POINTER size, not the array size.
```

**Example**

```text
int x; MY_SIZEOF(x) -> 4 on a 32-bit-int machine.
```

```c
/* "Custom sizeof": understand what sizeof really is
 *
 * sizeof is a COMPILE-TIME OPERATOR, not a function - the compiler replaces
 * it with a constant. You cannot truly reimplement it as a function, but a
 * classic pointer-arithmetic trick reveals how it could be computed:
 *
 *   MY_SIZEOF(x):  (char*)(&(x) + 1) - (char*)&(x)
 *     - &(x)     : address of x
 *     - &(x) + 1 : address ONE ELEMENT past x (pointer arithmetic scales by
 *                  the type's size - this is the key insight)
 *     - subtract as char* (byte pointers) -> the size in bytes
 *
 * It also explains the #1 array gotcha:
 *   sizeof(array) = total bytes;  sizeof(array)/sizeof(array[0]) = length.
 *   BUT once an array DECAYS to a pointer (e.g. a function parameter),
 *   sizeof gives the POINTER size, not the array size.
 *
 * Example: int x; MY_SIZEOF(x) -> 4 on a 32-bit-int machine.
 */
#include <stdio.h>

#define MY_SIZEOF(x)  ((char *)(&(x) + 1) - (char *)&(x))

int main(void) {
    int   i;
    double d;
    int   arr[10];

    printf("MY_SIZEOF(int)    = %ld (real sizeof = %zu)\n",
           MY_SIZEOF(i), sizeof i);
    printf("MY_SIZEOF(double) = %ld (real sizeof = %zu)\n",
           MY_SIZEOF(d), sizeof d);
    printf("MY_SIZEOF(arr)    = %ld (real sizeof = %zu)\n",
           MY_SIZEOF(arr), sizeof arr);
    printf("array length = sizeof(arr)/sizeof(arr[0]) = %zu\n",
           sizeof arr / sizeof arr[0]);
    return 0;
}
```

**Sample output:**

```text
MY_SIZEOF(int)    = 4 (real sizeof = 4)
MY_SIZEOF(double) = 8 (real sizeof = 8)
MY_SIZEOF(arr)    = 40 (real sizeof = 40)
array length = sizeof(arr)/sizeof(arr[0]) = 10
```

### DMA-style buffer copy (descriptor + scatter-gather)

```text
WHAT THIS MODELS:
  Real DMA (Direct Memory Access) lets a hardware engine copy a block of
  memory from a source to a destination WITHOUT the CPU copying byte by
  byte. The CPU just programs a "descriptor" (src address, dst address,
  length) and starts the engine. Here we SIMULATE that engine in software
  so it runs on a normal PC, but the structure mirrors a real driver.

THE DESCRIPTOR (what the CPU hands the DMA engine):
  src : where to read from
  dst : where to write to
  len : how many bytes
  done: status flag the "engine" sets when finished

Algorithm (one transfer):
  step1: CPU fills a descriptor (src, dst, len), done = 0
  step2: CPU "starts" the engine (dma_run)
  step3: engine copies len bytes src->dst (memcpy stands in for hardware)
  step4: engine sets done = 1
  step5: CPU polls done, then uses the data

SCATTER-GATHER (the real-world extension):
  One logical transfer can be split across several descriptors chained
  together - e.g. a packet whose header and payload live in different
  buffers. We show a 3-descriptor chain gathering into one output.
```

**Example**

```text
gather "GET ", "/index ", "HTTP/1.1" into one contiguous buffer.
```

```c
/* DMA-style buffer copy practice (descriptor-driven block transfer)
 *
 * WHAT THIS MODELS:
 *   Real DMA (Direct Memory Access) lets a hardware engine copy a block of
 *   memory from a source to a destination WITHOUT the CPU copying byte by
 *   byte. The CPU just programs a "descriptor" (src address, dst address,
 *   length) and starts the engine. Here we SIMULATE that engine in software
 *   so it runs on a normal PC, but the structure mirrors a real driver.
 *
 * THE DESCRIPTOR (what the CPU hands the DMA engine):
 *   src : where to read from
 *   dst : where to write to
 *   len : how many bytes
 *   done: status flag the "engine" sets when finished
 *
 * Algorithm (one transfer):
 *   step1: CPU fills a descriptor (src, dst, len), done = 0
 *   step2: CPU "starts" the engine (dma_run)
 *   step3: engine copies len bytes src->dst (memcpy stands in for hardware)
 *   step4: engine sets done = 1
 *   step5: CPU polls done, then uses the data
 *
 * SCATTER-GATHER (the real-world extension):
 *   One logical transfer can be split across several descriptors chained
 *   together - e.g. a packet whose header and payload live in different
 *   buffers. We show a 3-descriptor chain gathering into one output.
 *
 * Example: gather "GET ", "/index ", "HTTP/1.1" into one contiguous buffer.
 */
#include <stdio.h>
#include <string.h>
#include <stdint.h>

typedef struct {
    const void *src;
    void       *dst;
    size_t      len;
    volatile int done;     /* set by the engine when the copy completes */
} DmaDescriptor;

/* Simulated DMA engine: performs the block copy the hardware would do. */
static void dma_run(DmaDescriptor *d) {
    memcpy(d->dst, d->src, d->len);    /* stands in for the hardware transfer */
    d->done = 1;                       /* signal completion */
}

int main(void) {
    /* ---- single block transfer ---- */
    char source[] = "DMA_PAYLOAD_DATA";
    char dest[32] = {0};
    DmaDescriptor d = { source, dest, strlen(source) + 1, 0 };
    dma_run(&d);                        /* start engine */
    while (!d.done) { /* CPU would poll or wait for an IRQ here */ }
    printf("single transfer -> \"%s\" (%zu bytes)\n", dest, d.len);

    /* ---- scatter-gather: 3 descriptors gather into one buffer ---- */
    const char *parts[] = { "GET ", "/index ", "HTTP/1.1" };
    char gathered[64];
    size_t off = 0;
    for (int i = 0; i < 3; i++) {
        DmaDescriptor sg = { parts[i], gathered + off, strlen(parts[i]), 0 };
        dma_run(&sg);
        while (!sg.done) { }
        off += sg.len;                  /* advance the gather cursor */
    }
    gathered[off] = '\0';
    printf("scatter-gather -> \"%s\" (%zu bytes in 3 descriptors)\n",
           gathered, off);
    return 0;
}
```

**Sample output:**

```text
single transfer -> "DMA_PAYLOAD_DATA" (17 bytes)
scatter-gather -> "GET /index HTTP/1.1" (19 bytes in 3 descriptors)
```

### mmap (anonymous memory + file mapping)

```text
WHAT mmap DOES:
  mmap() asks the kernel to map a region into your process's virtual
  address space. After that you access it with ordinary pointers - no
  read()/write() calls. Two common uses shown here:
    A) ANONYMOUS mapping  - raw memory (like malloc, but page-granular;
       the basis of allocators and shared-memory IPC).
    B) FILE mapping       - the file's bytes appear as an array in memory;
       the kernel pages data in/out on demand (zero-copy file I/O).

KEY APIS:
  mmap(addr, length, prot, flags, fd, offset)
    prot  : PROT_READ | PROT_WRITE | PROT_EXEC
    flags : MAP_SHARED (writes go back to file/other procs)
            MAP_PRIVATE (copy-on-write, changes stay local)
            MAP_ANONYMOUS (no file; just memory)
  msync()  : flush a file mapping's dirty pages back to disk
  munmap() : unmap when done

Algorithm (file mapping):
  step1: open() the file, get a fd
  step2: size it (here we write some bytes first)
  step3: mmap() it into memory with PROT_READ|PROT_WRITE, MAP_SHARED
  step4: read/modify it through the returned pointer like a normal array
  step5: msync() to flush, munmap() to release, close() the fd
```

**Example**

```text
map a small file, flip its first char to uppercase via a pointer.
```

```c
/* mmap practice: map memory and files directly into the address space
 *
 * WHAT mmap DOES:
 *   mmap() asks the kernel to map a region into your process's virtual
 *   address space. After that you access it with ordinary pointers - no
 *   read()/write() calls. Two common uses shown here:
 *     A) ANONYMOUS mapping  - raw memory (like malloc, but page-granular;
 *        the basis of allocators and shared-memory IPC).
 *     B) FILE mapping       - the file's bytes appear as an array in memory;
 *        the kernel pages data in/out on demand (zero-copy file I/O).
 *
 * KEY APIS:
 *   mmap(addr, length, prot, flags, fd, offset)
 *     prot  : PROT_READ | PROT_WRITE | PROT_EXEC
 *     flags : MAP_SHARED (writes go back to file/other procs)
 *             MAP_PRIVATE (copy-on-write, changes stay local)
 *             MAP_ANONYMOUS (no file; just memory)
 *   msync()  : flush a file mapping's dirty pages back to disk
 *   munmap() : unmap when done
 *
 * Algorithm (file mapping):
 *   step1: open() the file, get a fd
 *   step2: size it (here we write some bytes first)
 *   step3: mmap() it into memory with PROT_READ|PROT_WRITE, MAP_SHARED
 *   step4: read/modify it through the returned pointer like a normal array
 *   step5: msync() to flush, munmap() to release, close() the fd
 *
 * Example: map a small file, flip its first char to uppercase via a pointer.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <ctype.h>

int main(void) {
    /* ---- A) anonymous mapping: raw page-aligned memory, no file ---- */
    size_t n = 4096;                    /* one page */
    char *mem = mmap(NULL, n, PROT_READ | PROT_WRITE,
                     MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
    if (mem == MAP_FAILED) { perror("mmap anon"); return 1; }
    strcpy(mem, "anonymous mmap memory works like an array");
    printf("anonymous map -> \"%s\"\n", mem);
    munmap(mem, n);

    /* ---- B) file mapping: file bytes appear as a memory array ---- */
    const char *path = "/tmp/mmap_demo.txt";
    int fd = open(path, O_RDWR | O_CREAT | O_TRUNC, 0600);
    if (fd < 0) { perror("open"); return 1; }
    const char *init = "hello mmap file";
    if (write(fd, init, strlen(init)) < 0) { perror("write"); close(fd); return 1; }

    size_t flen = strlen(init);
    char *fmap = mmap(NULL, flen, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (fmap == MAP_FAILED) { perror("mmap file"); close(fd); return 1; }

    printf("file map (before) -> \"%.*s\"\n", (int)flen, fmap);
    fmap[0] = (char)toupper((unsigned char)fmap[0]);   /* edit via pointer */
    msync(fmap, flen, MS_SYNC);          /* flush change back to the file */
    printf("file map (after)  -> \"%.*s\"\n", (int)flen, fmap);

    munmap(fmap, flen);
    close(fd);
    unlink(path);
    return 0;
}
```

**Sample output:**

```text
anonymous map -> "anonymous mmap memory works like an array"
file map (before) -> "hello mmap file"
file map (after)  -> "Hello mmap file"
```

---
## Compile Notes

- Most programs: `gcc -Wall -Wextra -o prog prog.c`
- The math section is fine without `-lm` here, but add `-lm` if you extend with `<math.h>` functions.
- Every program above was compiled with `-Wall -Wextra` (zero warnings) and run to produce the sample output shown.

*Companion single-file version: `interview_all.c` (all 89 programs under one `main`).*
