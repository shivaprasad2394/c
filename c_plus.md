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

<img src="https://media.geeksforgeeks.org/wp-content/uploads/20230302091959/Arrays-in-C.png" alt="A sample image" width="280"/><img src="https://media.geeksforgeeks.org/wp-content/uploads/20230302092603/c-array-declaration.png" alt="A sample image" width="270"/>
<img src="https://media.geeksforgeeks.org/wp-content/uploads/20250510151101341950/access-array-element.webp" alt="A sample image" width="250"/>
<img src="https://media.geeksforgeeks.org/wp-content/uploads/20230215172222/indexing_in_array.png" alt="A sample image" width="200"/>

- When a pointers is incremented,it actually increments by the number equal to the size of the data type for which it is a pointer.
<img src="https://media.geeksforgeeks.org/wp-content/uploads/20230424100855/Pointer-Increment-Decrement.webp" alt="A sample image" width="320"/>

          // CPP program to demonstrate the addition of a constant to a pointer
          #include <iostream>
          using namespace std;
          
          int main()
          {
          
              int n = 20;
              int* ptr = &n;
          
              cout << "Address stored in ptr: " << ptr << endl;
          
              // Adding the integer value 1 to the pointer ptr
              ptr = ptr + 1;
              cout << "Adding 1 to ptr: " << ptr << endl;
          
              // Adding the integer value 2 to the pointer ptr
              ptr = ptr + 2;
              cout << "Adding 2 to ptr: " << ptr;
          
              return 0;
          }

- When a pointers is added/subtracted with an integer value,the value is first multiplied by the size of the data type and then added to the pointer.

 <img src="https://media.geeksforgeeks.org/wp-content/uploads/20230424100935/Pointer-Addition.webp" alt="A sample image" width="320"/><img src="https://media.geeksforgeeks.org/wp-content/uploads/20230424101002/Pointer-Subtraction.webp" alt="A sample image" width="320"/> 

<img src="https://example.com/image.png" alt="A sample image" width="100"/>

**Strings in C++**

- strings are sequences of characters that are used to store words and text. They are also used to store data, such as numbers and other types of information in the form of text. Strings are provided by <string> header file in the form of std::string class.
- syntax
            string str_name;

**c++ strings v/s c strings**
  
| String | Character Array | 
| :--------- | :----------: |
| Strings define objects that can be represented as string streams. | The null character terminates a character array of characters. |
| No Array decay occurs in strings as strings are represented as objects.  | The threat of array decay(The loss of type and dimensions of an array ) is present in the case of the character array.    |
| A string class provides numerous functions for manipulating strings.  | Character arrays do not offer inbuilt functions to manipulate strings.    |
| Memory is allocated dynamically.  | The size of the character array has to be allocated statically.more memory cannot be allocated at run time if required. Unused allocated memory is also wasted     | 

**string Function & Example**

|  Function Name | Description | Example |
| :--------- | :----------: | ----------: |
| length()       | This function returns the length of the string.         | std::string text = "geeksforGeeks";int length = text.length(); //orint length = text.size(); std::string str = "GEEKSFORGEEKS";std::cout << str.at(3);       |
| swap()  | This function is used to swap the values of 2 strings.  | More text   |
| size()        | Used to find the size of string         |More text   |
| resize()       | This function is used to resize the length of the string up to the given number of characters.         |More text   |
| find()       | Used to find the string which is passed in parameters         |More text   |
| push_back()       | This function is used to push the passed character at the end of the string         |More text   |
| pop_back()       | This function is used to pop the last character from the string         |More text   |
| clear()        | This function is used to remove all the elements of the string.         |More text   |
| strncmp()       | This function compares at most the first num bytes of both passed strings.         |More text   |
| strncpy()       | This function is similar to strcpy() function, except that at most n bytes of src are copied         |More text   |
| strrchr()       | This function locates the last occurrence of a character in the string.         |More text   |
| strcat()       | This function appends a copy of the source string to the end of the destination string         |More text   |
| find()       | This function is used to search for a certain substring inside a string and returns the position of the first character of the substring.     |More text   |
| replace()       | This function is used to replace each element in the range [first, last) that is equal to old value with new value.         |More text   |
| substr()       | This function is used to create a substring from a given string.          |More text   |
| compare()       | This function is used to compare two strings and returns the result in the form of an integer.         |More text   |
| erase()       | This function is used to remove a certain part of a string.         |More text   |
| rfind()       | This function is used to find the string's last occurrence.         |More text   |

--------------------------
C++
C++ Classes and Objects
C++ Polymorphism
C++ Inheritance
C++ Abstraction
C++ Encapsulation
C++ OOPs Interview Questions
C++ OOPs MCQ
C++ Interview Questions
C++ Function Overloading
C++ Programs
C++ Preprocessor
C++ Templates

In C++, classes and objects are the basic building block that leads to Object-Oriented programming in C++. 

C++ Classes

A class is a user-defined data type, which holds its own data members and member functions that can be accessed and used by creating an instance of that class. A C++ class is like a blueprint for an object.

For Example: Consider the Class of Cars. There may be many cars with different names and brands but all of them will share some common properties like all of them will have 4 wheels, Speed Limit, Mileage range, etc. The car can also accelerate, turn, apply brakes, etc. So here, the Car is the class, wheels, speed limits, and mileage are its attributes (data members) and accelerate, turn, apply brakes are its methods (member functions).

Create a Class

A class must be defined before its use. C++ class is defined using the keyword class keyword as shown:


    class className {
     access_specifier:

    // data member

    // member method
    };

where,

Data Members: These are the variables that are defined inside the class.

Member Functions: Functions declared inside a class. Also referred to as a member method.
Example:


    class GfG {
     public:

    // Data member
    int val;
    
    // Member function
    void show() {
        cout << "Value: " << val          << endl;
    }
    };

In the above, GfG class is created with a data member val and member function show(). Here, member function is defined inside the class, but they can also be just declared in the class and then defined outside using scope resolution operator ::

The above is called class definition or template.

C++ Objects

When a class is defined, only the specification (attributes and behaviour) for the object is defined. No memory is allocated to the class definition. To use the data and access functions defined in the class, we need to create its objects.

Objects are the actual entities that are created as an instance of a class. There can be as many objects of a class as desired. For example, in the above, we discussed the class of Cars. If we create an actual car based on the properties of the Car class, the car we made is the object of that class.

Create Object

Once the class is defined, we can create its object in the same way we declare the variables of any other inbuilt data type.


className objectName;

This statement creates an object of className class.

Member Access

Members of the class can be accessed inside the class itself simply by using their assigned name.

To access them outside, the (.) dot operator is used with the object of the class.


obj.member1 // For data members
obj.member2(..) // For functions

There obj is the name of the object of the given class, member1 is data member and member2 is member function.

Access Modifiers

In C++ classes, we can control the access to the members of the class using Access Specifiers. Also known as access modifier, they are the keywords that are specified in the class and all the members of the class under that access specifier will have particular access level.

In C++, there are 3 access specifiers that are as follows:

Public: Members of the class can be accessed from outside the class.

Private: Private members can only be accessed within the class itself.

Protected: Protected members can be accessed within the class and by derived classes.
If we do not specify the access specifier, the private specifier is applied to every member by default.

Example:
     #include <bits/stdc++.h>
     using namespace std;

      // Creating a class
     class GfG {
     public:

    // Data member
    int val;
    
    // Member function
    void show() {
        cout << "Value: " << val          << endl;
    }
    
    };

    int main() {
    
    // Create Object
    GfG obj;
    
    // Access data member and assign
    // it some value
    obj.val = 10;
    
    // Access member method
    obj.show();
    
    return 0;
    }


Output
Value: 10

Whether we can access a member of a class depends on the access specifier in which it is declared. In the above example, if the val variable was declared as private, then we would not have been able to access it in the main function.

Explanation:

Special Member Functions
In C++ classes, there are some special member functions that are essential to manage objects and provide some basic functionalities.

Constructor

Constructors are special class members which are called by the compiler every time an object of that class is instantiated. They are used to construct the objects and making them ready for use. Constructors have the same name as the class.

Example:

    #include <bits/stdc++.h>
    using namespace std;

     class MyClass {
     public:
    // Constructor
    MyClass() {
        cout << "Constructor called!";
    }
    };
    int main() {
    // Constructor automatically 
    // called when object is created.
    MyClass obj;
    return 0;
    }

Destructors
Destructor is another special member function that is called by the compiler when the scope of the object ends. It deallocates all the memory previously used by the object of the class so that there will be no memory leaks. The destructor also has the same name as the class but with tilde (~) as prefix.

Example:

     #include <bits/stdc++.h>
     using namespace std;

     class MyClass {
     public:
     MyClass() {
        cout << "Constructor called!" << endl;
    }
    // Destructor
    ~MyClass() {
        cout << "Destructor called!";
    }
    };

   int main() {
    MyClass obj;
    // Destructor will be called 
    // automatically when obj goes out of scope
    return 0;
    }

Static Members

Members of the class can be declared as static. These static members of a class are not associated with the objects of the class but with the class itself. The main feature of these members is that they are accessible directly through the class without creating any objects.

Both data members and member methods can be static:

Static Data Members
Static data members shared by all objects of the class, meaning only one copy exists for all objects of the class and they are declared with the static keyword.

Example:

#include <iostream>
using namespace std;

class GfG {
public:
    static int val;
};
// Initialize static member
int GfG::val = 22;
int main() {
    // Access without creating object
    cout << GfG::val << endl;
}

Output
22

Static Member Function
Static member functions are associated with the class itself rather than any specific object. They can only access static data members and cannot access instance data members. Static member functions are called using the class name, not the object.

We defined the member function inside the class, but we can also define the member function outside the class. To define a member function outside the class definition, we use scop resolution (::) operator.

Example:
#include <iostream>
using namespace std;

class GfG {
public:
    static void printHello(); 
};
// Definintion of static member function
void GfG::printHello() {
    cout << "Hello World";
}
int main() {
    // Access without creating object
    GfG::printHello();
    return 0;
}

Output
Hello World

Friend Class and Function
In C++, friend classes and functions allow access to the private and protected members of other classes:

A friend class has the ability to access the private and protected members of other classes where it is declared as a friend. This feature can be useful when it is necessary for one class to access the private and protected members of another class.

A friend function in C++ is similar to a friend class. It can be given special permission to access the private and protected members of a class. Although it is not a member function of the class, it can still access and modify those private and protected members because it is declared as a friend.

Local Class

Classes are generally declared in global scope and are accessible to every function or other classes once they are defined. But C++ also provides facility to define a class within a function. It is called local class in C++ and is only accessible in that function.

Nested Class

A nested class is a class defined within another enclosing class. As a member of the enclosing class, it has the same access rights as any other member. The members of the enclosing class do not have special access to the members of the nested class; the standard access rules apply.

Enum Class

Enum classes in C++ are a safer and more organized way of using enums. They help to group related constants together while avoiding naming problems and ensuring better type safety.

this Pointer

In C++, this pointer is a pointer that points to the current instance of a class. It is used within the member functions of a class to refer to the object of that class. This pointer allows access to the calling object's data and methods within its own member functions.


    class A{
    int n;
    A(int n) {
        this->n = n;
    }
    }

Class vs Object

The following table lists the primary differences between the classes and objects in C++:

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
