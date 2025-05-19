Intro
-----
          - Origns:-Bell Labs(1979)
          - Scope of languague:-compiler,OS & games
          - c v/s c++
          - C is Procedure/process oriented, structured
          - C++ is Object oriented


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

🛠 Namespace
------------
          Namespace:-C++  Namespace are used to group logically related functions,variables and other entities to avoid name conflicts.

⚠️ Examples
-----------------
          Namespace Graphics{
                    class image{
                              //Image processing code
                    };
          }
          Namespace Audio{
                    class image{//same name ,different namespace
                              //Audio related code
                    };
          }
          Graphics::Image img1;//No conflict
          Audio::Image img2;

Namespace Alias:
---------------
          To simplify long namespace name ,you can use aliases.
          Namespace LongNamespaceName{
                    class Example{//same name ,different namespace
                          //Audio related code
                    };}
                    namespace LNN=LongNamespaceName;//Alias
                    LNN::Example  obj;//Easier to use.

🧠 Const & Macros
-----------------
          #define directive can also be used to define symbolic constants that do not require a data type. 
          They are called macros and are replaced by their values at compile time.
          Syntax:
          #define CONSTANT_NAME value

          constant variables in c are immutable after its definition, i.e., they can be initialized only once in the whole program. 
          After that, we cannot modify the value stored inside that variable.

🧪 Static
---------
**Static Variables in a Function**

          - Memory space is Aloocated only once in static storage.
          - The value of the variable is persistent.
          - Scope is Lifetime of the Program.

**Static Member Variable in a Class**

          - static member variables in a class are shared by the objects. 
          * There cannot be multiple copies of the same static variables for different objects. 
          + Also because of this reason static variables cannot be initialized using constructors.
          + static variable inside a class should be initialized explicitly by the user using the class name and scope resolution operator outside the class

**Example**

          #include <iostream>
          using namespace std;
          
          class GfG {
          public:
            
              // Static data member
              static int i;
          
              GfG(){
                  // Do nothing
              };
          };
          
          // Static member inintialization
          int GfG::i = 1;//OK
          
          int main() {
            GfG obj1;
            GfG obj2;
            obj1.i=2;//❗ **Not possible**
              // Prints value of i
              cout << GfG::i;//OK
          }


**Static Member Functions in a Class**

          - Static member functions are allowed to access only the static data members or other static member functions, 
          - they cannot access the non-static data members or member functions of the class. 

**Applications**

The static member functions have the following uses in C++:

- Accessing Static Member Variables
- Implement helper functions that do not depend on specific instances.
- Singleton Pattern Implementation
- Factory Methods to create and return objects without requiring an instance of the class.
- Logging and Debugging

**Global Static Variable**

- static variable declared outside of any class or function.
- global static variable has internal linkage, meaning it is accessible only within the file where it is defined. 
- This Also means you cant use extern to access the variable across folder.

🔢 C++ Lambda Expressions
---------------------------------------------

C++ 11 introduced lambda expressions to allow inline functions which can be used for short snippets of code that are not going to be reused. Therefore, they do not require a name.

**Syntax**

          [capture-clause] (parameters) -> return-type { 
              // definition
          }

**Example**

          #include <bits/stdc++.h>
          using namespace std;
          
          int main() {
              
              // Defining a lambda
              auto res = [](int x) {
                  return x + x;
              };
              cout << res(5);
              
              return 0;
          }

**Capture Clause**

A lambda expression can have more power than an ordinary function by having access to variables from the enclosing scope. We can capture external variables from the enclosing scope in three ways using capture clause:

- [&]: capture all external variables by reference.
- [=]: capture all external variables by value.
- [a, &b]: capture 'a' by value and 'b' by reference.

A lambda with an empty capture clause [] can only access variables which are local to it.

**Eaxmple2**

          #include <bits/stdc++.h>
          using namespace std;
          
          void print(vector<int> v) {
              for (auto x : v) cout << x << " ";
              cout << endl;
          }
          
          int main() {
              vector<int> v1, v2;
          
              // Capture v1 and v2 by reference
              auto byRef = [&] (int m) {
                  v1.push_back(m);
                  v2.push_back(m);
              };
              
              // Capture v1 and v2 by value
              auto byVal = [=] (int m) mutable {
                  v1.push_back(m);
                  v2.push_back(m);
              };
              
              // Capture v1 by reference and v2 by value
              auto mixed = [=, &v1] (int m) mutable {
                  v1.push_back(m);
                  v2.push_back(m);
              };
          
              // Push 20 in both v1 and v2
              byRef(20);
              
              // Push 234 in both v1 and v2
              byVal(234);
              
              // Push 10 in both v1 and v2
              mixed(10);
              
              print(v1);
              print(v2);
              
              return 0;
          }

**Examples**

Lamda expressions are extensively used in STL in place of callback i.e. functions passed as arguments. The below examples demonstrate that:

**Sort Vector in Descending Order**

          #include <bits/stdc++.h>
          using namespace std;
          
          int main() {
          	vector<int> v = {5, 1, 8, 3, 9, 2};
          
          	// Sort in descending order
                     //sort(v.begin,v,end,comparator)
          	sort(v.begin(), v.end(), [] (const int& a, const int&b) {
          		return a > b;
          	});
          
          	for (int x : v)
          		cout << x << " ";
          	return 0;
          }
Pointers & refernce
-------------------
- pointers and refrence both are mechanism used to deal with Memory.
- **pointers** are used to Store the memory Address of the variable wheras,
- **Reference** are used to Create an Alias(Alternative name) for an already existing variable.
- **Double pointers** are those pointers which store the Address of Another pointer.

| Pointers | Reference |
| -------- | -------- |
| a pointer can be declared as void | a reference can never be void |
| a pointer can be made to point to another | Once a refrence is created,it cannot be later made to refernce another object |
| a pointer are often made NULL | a refernce cannot be NULL |
| No restriction with pointers for init | A refernce must be initialized when declared |

Arrays pointers & Arthematic
----------------------------
- Arrays are Derived Data type that is used to store multiple values of similar data types in a contigous memory location.

<img src="https://media.geeksforgeeks.org/wp-content/uploads/20230302091959/Arrays-in-C.png" alt="A sample image" width="100"/>
<img src="https://media.geeksforgeeks.org/wp-content/uploads/20230302092603/c-array-declaration.png" alt="A sample image" width="100"/>

- When a pointers is incremented,it actually increments by the number equal to the size of the data type for which it is a pointer.
![A sample image](https://example.com/image.png "Sample Image")

- When a pointers is added/subtracted with an integer value,the value is first multiplied by the size of the data type and then added to the pointer.
![A sample image](https://example.com/image.png "Sample Image")
  

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
🧠 Interview Tip
-----------------
You’ll often use these in:
          
          - Pattern printing
          - Searching/sorting
          - State machines
          - Menu-driven programs

🧪 Mini Practice Task
----------------------
Write a menu-driven program that:

          Asks user for 2 integers
          
          Shows a menu:
          
          markdown
          Copy
          Edit
          1. Add
          2. Subtract
          3. Multiply
          4. Divide
          5. Exit
          Executes the selected operation using switch

Loops until user chooses Exit
