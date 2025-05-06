What Are Variables?
-------------------

          A variable is a named storage in memory to hold a value. Think of it as a labeled box.
          int age = 25;

This declares a variable named age of type int (integer), and stores the value 25 in it.


Basic Data Types in C++
------------------------
          Type	Size	Description
          int	4 bytes	Whole numbers
          float	4 bytes	Numbers with decimal points
          double	8 bytes	More precise decimal numbers
          char	1 byte	A single character ('a')
          bool	1 byte	Boolean values (true/false)
          void	—	No value (used in functions)

🛠 Example: Declaring Different Types
-------------------------------------
          #include <iostream>
          using namespace std;
          
          int main() {
              int age = 25;
              float height = 5.9f;
              double weight = 70.55;
              char grade = 'A';
              bool isPassed = true;
          
              cout << "Age: " << age << endl;
              cout << "Height: " << height << endl;
              cout << "Weight: " << weight << endl;
              cout << "Grade: " << grade << endl;
              cout << "Passed: " << isPassed << endl;
          
              return 0;
          }

⚠️ Common Mistakes
-----------------
Uninitialized variables: using variables before assigning a value can lead to garbage output.

Incorrect type assignments:
--------------------------
int x = 3.5; // OK but will truncate to 3

🧠 Interview Tip
----------------
Understanding data types is foundational. Interviewers may ask:
          
          - Memory sizes and ranges (e.g. range of int)
          
          - Type conversions (implicit and explicit)

🧪 Mini Practice Task
---------------------
          Can you write a small program that:
          Stores your name (string), age (int), height (float)
          Prints them all nicely formatted?

🔢 C++ Operators and Expressions (Subtopic 2)
---------------------------------------------

Operators are symbols that perform operations on variables and values.
An expression is any valid combination of variables, operators, and literals that computes a value.

✅ 1. Types of Operators in C++
-------------------------------
          Category	        Operators	                   Description
          -----------------------------------------------------------------------
          Arithmetic	+, -, *, /, %	          Basic math operations
          Relational	==, !=, <, >, <=, >=	Comparison (true/false)
          Logical	          &&, `	
          Assignment	=, +=, -=, *=, /=, %=	Assign values
          Increment/Decrement	++, --	                    Increase or decrease value by 1
          Bitwise	          &, `	                    , ^, ~, <<, >>`
          Ternary	          ? :	                    Shortcut for if-else
          Comma	          ,	                    Evaluate multiple expressions
          Sizeof	          sizeof()	                    Returns size of type/variable

🧠 2. Operator Examples and Behavior
-------------------------------------
➕ Arithmetic Operators
-----------------------
          int a = 10, b = 3;
          cout << a + b;  // 13
          cout << a - b;  // 7
          cout << a * b;  // 30
          cout << a / b;  // 3 (integer division)
          cout << a % b;  // 1 (modulo)
          ⚠️ Note: a / b when both are integers does integer division. Use float for accurate decimals.

🧾 Assignment and Compound Operators
------------------------------------
          int x = 5;
          x += 3;   // x = x + 3 → 8
          x *= 2;   // x = x * 2 → 16

🧮 Increment and Decrement
--------------------------
          int a = 5;
          ++a;  // pre-increment: a becomes 6
          a++;  // post-increment: a used first, then becomes 7
🔁 Relational and Logical Operators
-----------------------------------
          int a = 5, b = 10;
          cout << (a < b);       // 1 (true)
          cout << (a == b);      // 0 (false)
          cout << (a != b);      // 1 (true)
          
          bool result = (a < b) && (b < 20);  // true
❓ Ternary Operator
-------------------
          int age = 18;
          string status = (age >= 18) ? "Adult" : "Minor";
          cout << status;
          This is a shortcut for:
          
          cpp
          Copy
          Edit
          if (age >= 18)
              status = "Adult";
          else
              status = "Minor";
📏 Sizeof Operator
------------------
          cout << sizeof(int);     // typically 4
          cout << sizeof(double);  // typically 8
🧠 3. Expressions in C++
------------------------
An expression could be:

          int a = 5 + 2;      // arithmetic expression
          bool b = (a > 3);   // logical expression
          a += 10;            // assignment expression
🔥 4. Operator Precedence and Associativity
-------------------------------------------

Operator precedence determines the order in which expressions are evaluated.

Example:
          int result = 5 + 3 * 2;  // 3 * 2 = 6, then 5 + 6 = 11
          
🧠 Multiplication has higher precedence than addition.
------------------------------------------------------
Parentheses () can override default precedence.

🧪 Mini Practice Task
---------------------
Write a program that:

          - Takes two integers as input.
          Displays:
          -Their sum, product, and quotient.
          - Which one is greater (using if or ternary).
          - Whether the first is divisible by the second.
🔁 Control Flow Statements in C++
---------------------------------
These statements allow your program to make decisions and repeat tasks.

✅ 1. Conditional Statements
----------------------------
These are used to execute different code blocks based on conditions.
          
          🔹 if / else if / else
          int age = 20;
          
          if (age < 18) {
              cout << "Minor";
          } else if (age == 18) {
              cout << "Exactly 18!";
          } else {
              cout << "Adult";
          }
✔️ Use else if when you have multiple conditions.
✔️ Conditions must be inside (), and code blocks inside {}.

          🔹 Nested if
          if (x > 0) {
              if (x < 10) {
                  cout << "Single-digit positive number";
              }
          }
🔸 Avoid deeply nested if statements when possible (use else if or switch).

🔹 Ternary Operator (Shortcut)
          string result = (score >= 50) ? "Pass" : "Fail";
          
✅ 2. switch Statement
----------------------
Useful for checking a variable against multiple constant values (integers or chars).

          int day = 3;
          
          switch (day) {
              case 1: cout << "Monday"; break;
              case 2: cout << "Tuesday"; break;
              case 3: cout << "Wednesday"; break;
              default: cout << "Invalid day";
          }
⚠️ Always include break; to prevent "fall-through"
✔️ default is optional but recommended as a fallback

✅ 3. Looping Statements
-------------------------
Used to repeat a block of code.

🔁 for Loop (when number of iterations is known)
-----------------------------------------------
          for (int i = 0; i < 5; i++) {
              cout << "i = " << i << '\n';
          }
🔁 while Loop (when condition is checked before each iteration)
--------------------------------------------------------------
          int i = 0;
          while (i < 5) {
              cout << i << '\n';
              i++;
          }
🔁 do-while Loop (runs at least once)
-------------------------------------
          int i = 0;
          do {
              cout << i << '\n';
              i++;
          } while (i < 5);
🔁 Break and Continue
---------------------
break: exits the loop early

continue: skips current iteration

          for (int i = 1; i <= 5; i++) {
              if (i == 3) continue;
              if (i == 5) break;
              cout << i << ' ';
          }  // Output: 1 2 4
