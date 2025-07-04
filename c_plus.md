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
          Namespace:-C++  Namespace is a feature used to group logically related functions,variables and other entities to avoid name conflicts.

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


🧪 Static :-storage class specifier
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

---

This example demonstrates both concepts clearly, showing how scope and linkage affect variable visibility and lifetime in C++.

---

## Example: Global Static vs Local Static

### `file1.cpp`

```cpp
#include 

static int global_static_var = 0; // Global static: internal linkage

void increment_and_print_global() {
    global_static_var++;
    std::cout 

// extern int global_static_var; // ERROR: cannot access, internal linkage

void increment_and_print_global();
void increment_and_print_local();

int main() {
    std::cout << "Calling from file2.cpp:" << std::endl;

    // Try to access global_static_var directly (uncommenting next line will cause error)
    // std::cout << global_static_var << std::endl; // ERROR

    increment_and_print_global(); // Increments and prints file1.cpp's global_static_var
    increment_and_print_global();

    increment_and_print_local();  // Increments and prints file1.cpp's local_static_var
    increment_and_print_local();

    return 0;
}
```

---

## What Will Happen

- **Global static variable (`global_static_var`)** is only accessible within `file1.cpp` due to internal linkage. `file2.cpp` cannot access it directly, even with `extern`.
- **Local static variable (`local_static_var`)** is initialized once and persists across multiple calls to the function within the same translation unit.
- Each call to `increment_and_print_global()` or `increment_and_print_local()` will increment and print the respective static variable.

---

## Expected Output

```
Calling from file2.cpp:
[file1.cpp] global_static_var: 1
[file1.cpp] global_static_var: 2
[file1.cpp] local_static_var: 1
[file1.cpp] local_static_var: 2
```

---

## Key Takeaways

- **Global static variables** have internal linkage: only visible within their source file, not accessible from other files.
- **Local static variables** persist their value across function calls, but their scope is limited to the function in which they are declared.
- Attempting to access a global static variable from another file will result in a linker error.




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



| Function Name | Description | Example |
| :------------ | :---------- | ------- |
| `length()` | This function returns the length of the string. | `std::string text = "geeksforGeeks"; int length = text.length();` |
| `swap()` | This function is used to swap the values of 2 strings. | `std::string str1 = "Hello", str2 = "World"; str1.swap(str2);` |
| `size()` | Used to find the size of string. | `std::string str = "Hello"; int sz = str.size();` |
| `resize()` | This function is used to resize the length of the string up to the given number of characters. | `std::string str = "HelloWorld"; str.resize(5);` |
| `find()` | Used to find the string which is passed in parameters. | `std::string str = "HelloWorld"; size_t pos = str.find("World");` |
| `push_back()` | This function is used to push the passed character at the end of the string. | `std::string str = "Hello"; str.push_back('!');` |
| `pop_back()` | This function is used to pop the last character from the string. | `std::string str = "Hello!"; str.pop_back();` |
| `clear()` | This function is used to remove all the elements of the string. | `std::string str = "Hello"; str.clear();` |
| `strncmp()` | This function compares at most the first num bytes of both passed strings. | `int result = strncmp("abc", "abd", 2);` |
| `strncpy()` | This function is similar to strcpy() function, except that at most n bytes of src are copied. | `char dest[10]; strncpy(dest, "Hello", 5);` |
| `strrchr()` | This function locates the last occurrence of a character in the string. | `char *ptr = strrchr("Hello World", 'o');` |
| `strcat()` | This function appends a copy of the source string to the end of the destination string. | `char str1[20] = "Hello "; strcat(str1, "World");` |
| `find()` | This function is used to search for a certain substring inside a string and returns the position of the first character of the substring. | `std::string str = "This is a test"; size_t found = str.find("test");` |
| `replace()` | This function is used to replace each element in the range [first, last) that is equal to old value with new value. | `std::string str = "I love apples"; str.replace(7, 6, "oranges");` |
| `substr()` | This function is used to create a substring from a given string. | `std::string str = "HelloWorld"; std::string sub = str.substr(0, 5);` |
| `compare()` | This function is used to compare two strings and returns the result in the form of an integer. | `std::string a = "abc", b = "abd"; int result = a.compare(b);` |
| `erase()` | This function is used to remove a certain part of a string. | `std::string str = "HelloWorld"; str.erase(5, 5);` |
| `rfind()` | This function is used to find the string's last occurrence. | `std::string str = "Hello World Hello"; size_t pos = str.rfind("Hello");` |







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


````markdown
# C++ Classes and Objects

Classes and objects are the basic building blocks that lead to Object-Oriented Programming in C++.

---

## C++ Classes

A *class* is a user-defined data type which holds its own **data members** and **member functions**.
These members can be accessed and used by creating an instance (object) of that class.
A C++ class acts like a blueprint for objects.

### Example

Consider a **Class of Cars**. There may be many cars with different names and brands,
but all of them share some common properties like:

- All have 4 wheels
- Speed limit
- Mileage range

The car can also perform actions like:

- Accelerate
- Turn
- Apply brakes

Here:
- **Car** is the class.
- Wheels, speed limits, and mileage are its **attributes (data members)**.
- Accelerate, turn, apply brakes are its **methods (member functions)**.

---

## Create a Class

A class must be defined before it is used.  
Syntax:

```cpp
class className {
  access_specifier:
    // data members
    // member functions
};
````

* **Data Members:** Variables defined inside the class.
* **Member Functions:** Functions declared inside the class (also called member methods).

### Example:

```cpp
class GfG {
public:
    // Data member
    int val;

    // Member function
    void show() {
        cout << "Value: " << val << endl;
    }
};
```

In this example, the `GfG` class has:

* a data member `val`
* a member function `show()` which prints the value of `val`.

> Note: Member functions can be defined inside the class or declared inside and defined outside the class using the scope resolution operator `::`.

This is called a **class definition** or **template**.

---

## C++ Objects

When a class is defined, only the specification (attributes and behavior) is set.
**No memory is allocated** to the class itself until an object is created.

* Objects are instances of a class.
* You can create many objects of a class.

### Example:

If `Car` is a class, then an actual car made based on this class is an **object** of the `Car` class.

---

## Create Object

After the class is defined, objects are created similarly to variables of built-in types.

```cpp
className objectName;
```

This statement creates an object of the `className` class.

---



Got it! Here's the markdown-formatted version of your explanation about **Member Access** and **Access Modifiers** in C++, including the example and a placeholder for the explanation section for you to fill in:

````markdown
# Member Access and Access Modifiers in C++

---

## Member Access

- Members of a class can be accessed **inside the class** simply by using their names.
- To access members **outside the class**, use the **dot operator (.)** with the object of the class.

```cpp
obj.member1      // For data members
obj.member2(...) // For member functions
````

Where:

* `obj` is the name of the object
* `member1` is a data member
* `member2` is a member function

---

## Access Modifiers

Access modifiers, also known as access specifiers, in C++ are used to define the accessibility of class members. They play a crucial role in implementing the principle of data hiding in object-oriented programming.

## Example

```cpp
#include <bits/stdc++.h>
using namespace std;

// Creating a class
class GfG {
public:
    // Data member
    int val;

    // Member function
    void show() {
        cout << "Value: " << val << endl;
    }
};

int main() {
    // Create Object
    GfG obj;

    // Access data member and assign it a value
    obj.val = 10;

    // Access member function
    obj.show();

    return 0;
}
```

### Output

```
Value: 10
```
---

## Explanation

Whether we can access a member of a class depends on the access specifier under which it is declared.
In the above example, the variable `val` is declared as **public**, so it can be accessed and modified directly through the object `obj` in `main()`. If `val` were declared **private**, then `obj.val = 10;` would cause a compilation error because private members cannot be accessed outside the class.

---

# Access Modifiers in C++


There are three types of access modifiers in C++:

1. **Public**
2. **Private** (default)
3. **Protected**

---

## 1. Public Specifier

* Members declared as `public` are accessible from anywhere in the program.
* Both data members and member functions can be accessed using the object of the class.

**Example:**

```cpp
#include <iostream>
using namespace std;

class Circle {
public:
    double radius;

    double compute_area() {
        return 3.14 * radius * radius;
    }
};

int main() {
    Circle obj;
    obj.radius = 5.5;
    cout << "Radius is: " << obj.radius << "\n";
    cout << "Area is: " << obj.compute_area();
    return 0;
}
```

**Output:**

```
Radius is: 5.5
Area is: 94.985
```

In this example, the `radius` and `compute_area()` are public members, allowing them to be accessed directly using the object `obj`.

---

## 2. Private Specifier

* Members declared as `private` are accessible only within the class itself.
* They cannot be accessed directly from outside the class.
* Only member functions or friend functions/classes can access private members.

**Example:**

```cpp
#include <iostream>
using namespace std;

class Circle {
private:
    double radius;

    double compute_area() {
        return 3.14 * radius * radius;
    }
};

int main() {
    Circle obj;
    obj.radius = 1.5; // Error: 'radius' is private
    cout << "Area is: " << obj.compute_area(); // Error: 'compute_area' is private
    return 0;
}
```

**Output:**

```
main.cpp: In function ‘int main()’:
main.cpp:22:9: error: ‘double Circle::radius’ is private within this context
   22 |     obj.radius = 1.5;
      |         ^~~~~~
main.cpp:7:16: note: declared private here
    7 |         double radius;
      |                ^~~~~~
main.cpp:23:43: error: ‘double Circle::compute_area()’ is private within this context
   23 |     cout << "Area is:" << obj.compute_area();
      |                                           ^
main.cpp:8:16: note: declared private here
    8 |         double compute_area() {
      |                ^~~~~~~~~~~~
```

In this example, attempting to access private members `radius` and `compute_area()` from outside the class results in compilation errors.

---

## 3. Protected Specifier

* Members declared as `protected` are similar to private members but can be accessed in derived classes.
* They are not accessible from outside the class hierarchy.

**Example:**

```cpp
#include <iostream>
using namespace std;

class Parent {
protected:
    int id_protected;
};

class Child : public Parent {
public:
    void setId(int id) {
        id_protected = id;
    }

    void displayId() {
        cout << "id_protected is: " << id_protected << endl;
    }
};

int main() {
    Child obj1;
    obj1.setId(81);
    obj1.displayId();
    return 0;
}
```

**Output:**

```
id_protected is: 81
```

In this example, the `Child` class inherits from `Parent` and can access the protected member `id_protected`.


There are **3 access specifiers** in C++:

| Access Specifier | Access Level Description                                         |
| ---------------- | ---------------------------------------------------------------- |
| **public**       | Members can be accessed from outside the class.                  |
| **private**      | Members can only be accessed within the class itself.            |
| **protected**    | Members can be accessed within the class and by derived classes. |

---
---

## Summary Table

| Access Modifier | Accessible Within Class | Accessible in Derived Classes | Accessible Outside Class |
| --------------- | ----------------------- | ----------------------------- | ------------------------ |
| `public`        | Yes                     | Yes                           | Yes                      |
| `protected`     | Yes                     | Yes                           | No                       |
| `private`       | Yes                     | No                            | No                       |

---

**Note:** If no access modifier is specified for class members, they are `private` by default in C++.

---



---

# Special Member Functions in C++ Classes

In C++, some **special member functions** are essential to manage objects and provide basic functionalities.

---

## Constructor

Constructors are special class members called automatically by the compiler whenever an object of the class is instantiated. They prepare the object for use and have the **same name as the class**.

### Example:

```cpp
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
    // Constructor automatically called when object is created
    MyClass obj;
    return 0;
}
```
Here's a neatly structured `.md` (Markdown) version of the GeeksforGeeks article on **Constructors in C++** based on the provided URL: [https://www.geeksforgeeks.org/constructors-c/](https://www.geeksforgeeks.org/constructors-c/)

---

````markdown
# Constructors in C++

A **constructor** in C++ is a special member function of a class that is automatically called when an object of the class is created. It has the same name as the class and does not have a return type (not even `void`).

## Features of Constructors

- Automatically invoked during object creation
- No return type
- Can be overloaded
- Can have default parameters

## Types of Constructors

### 1. **Default Constructor**
---

A **default constructor** is a constructor that either takes no arguments or has default values for all its parameters. It is also referred to as a **zero-argument constructor** when it explicitly accepts no arguments.([GeeksforGeeks][1])

If a default constructor is not explicitly defined by the programmer in the source code, the compiler automatically generates one during the compilation process. However, if a programmer explicitly defines a default constructor, the compiler does not generate it. Instead, the explicitly defined default constructor is called implicitly wherever needed.([GeeksforGeeks][1])

```cpp
#include <iostream>
using namespace std;

class Demo {
public:
    Demo() {
        cout << "Default constructor called" << endl;
    }
};

int main() {
    Demo obj;
    return 0;
}

````

In cases where a class is derived from a base class with a default constructor, or a class contains an object of another class with a default constructor, the compiler must insert code to ensure these default constructors are invoked appropriately for the base class or the embedded objects.([GeeksforGeeks][1])

---

## Default Constructors and Inheritance

```cpp
#include <iostream>
using namespace std;

class Base {
public:
    // Compiler "declares" constructor
};

class A {
public:
    // User defined constructor
    A() { cout << "A Constructor" << endl; }

    // Uninitialized
    int size;
};

class B : public A {
    // Compiler defines default constructor of B,
    // and inserts stub to call A constructor
    // Compiler won't initialize any data of A
};

class C : public A {
public:
    C()
    {
        // User defined default constructor of C
        // Compiler inserts stub to call A's constructor
        cout << "C Constructor" << endl;

        // Compiler won't initialize any data of A
    }
};

class D {
    A a;
public:
    D()
    {
        // User defined default constructor of D
        // a - constructor to be called, compiler inserts
        // stub to call A constructor
        cout << "D Constructor" << endl;

        // Compiler won't initialize any data of 'a'
    }
};

// Driver Code
int main()
{
    Base base; // Only Base constructor (default provided by the compiler) is called
    B b; // Calls A's constructor due to inheritance (compiler-generated constructor for B)
    C c; // Calls A's constructor first, then C's constructor
    D d; // Calls A's constructor for member 'a', then D's constructor

    return 0;
}
```

### Output

```
A Constructor
A Constructor
C Constructor
A Constructor
D Constructor
```
---

## Constructors and Default Arguments

```cpp
// CPP code to demonstrate constructor can have default arguments
#include <iostream>
using namespace std;

class A {
public:
    int sum = 0;
    A(); // default constructor with no argument
    A(int a, int x = 0) // default constructor with one default argument
    {
        sum = a + x;
    }
    void print() { cout << "Sum =" << sum << endl; }
};

int main()
{
    // This construct has two arguments. Second argument is
    // initialized with a value of 0 Now we can call the constructor
    // with one or two arguments
    A obj1(5); // x will take default value 0
    obj1.print();

    A obj2(5, 5); // x will take value 5
    obj2.print();

    return 0;
}
```

### Output

```
Sum =5
Sum =10
```
---

## FAQs

**1. What is the significance of the default constructor?**

> They are used to create objects, which do not have any specific initial value.

**2. Is a default constructor automatically provided?**

> If no constructors are explicitly declared in the class, a default constructor is provided automatically by the compiler.

---



### 2. **Parameterized Constructor**

Takes arguments to initialize an object.

```cpp
class Demo {
    int a;
public:
    Demo(int x) {
        a = x;
        cout << "Parameterized constructor called: " << a << endl;
    }
};

int main() {
    Demo obj(10);
    return 0;
}
```

### 3. **Copy Constructor**

Initializes a new object as a copy of an existing object.

```cpp
class Demo {
    int a;
public:
    Demo(int x) { a = x; }
    Demo(const Demo &d) {
        a = d.a;
        cout << "Copy constructor called" << endl;
    }
};

int main() {
    Demo obj1(10);
    Demo obj2 = obj1;
    return 0;
}
```

## Constructor Overloading

Multiple constructors can be defined with different parameters.

```cpp
class Demo {
public:
    Demo() {
        cout << "Default constructor" << endl;
    }
    Demo(int x) {
        cout << "Parameterized constructor: " << x << endl;
    }
};

int main() {
    Demo obj1;
    Demo obj2(20);
    return 0;
}
```

## Constructors with Default Arguments

```cpp
class Demo {
public:
    Demo(int x = 10, int y = 20) {
        cout << "x: " << x << ", y: " << y << endl;
    }
};

int main() {
    Demo obj1;
    Demo obj2(30);
    Demo obj3(40, 50);
    return 0;
}
```

## Explicit Constructor

Prevents implicit conversions.

```cpp
class Demo {
public:
    explicit Demo(int x) {
        cout << "Explicit constructor called: " << x << endl;
    }
};

int main() {
    Demo obj1(10);
    // Demo obj2 = 20; // Error: conversion not allowed
    return 0;
}
```

## Summary

| Constructor Type          | Description                                     |
| ------------------------- | ----------------------------------------------- |
| Default Constructor       | No arguments                                    |
| Parameterized Constructor | Takes arguments                                 |
| Copy Constructor          | Creates a copy of an object                     |
| Overloaded Constructor    | Multiple constructors with different parameters |
| Explicit Constructor      | Prevents implicit conversions                   |

---

**Note**: If a class does not have a constructor, the compiler provides a default constructor.

```

---
You're absolutely right — the **move constructor** is an important part of modern C++ (C++11 and later). Here's an updated and neatly formatted Markdown section **specifically for the move constructor**, with clear explanation and a good example:

---

````markdown
## Move Constructor (C++11 and later)

A **move constructor** is a special constructor introduced in C++11 that enables the resources of a **temporary (rvalue)** object to be moved rather than copied, improving performance, especially when dealing with dynamic memory.

### Syntax

```cpp
ClassName(ClassName&& other);
````

It takes an **rvalue reference** (denoted by `&&`) to another object of the same class.

### When is a Move Constructor Called?

* When an object is initialized using an **rvalue** (e.g., a temporary object or `std::move()`).
* During **return by value** when the compiler performs move semantics instead of copy.

### Example: Move Constructor

```cpp
#include <iostream>
#include <cstring>
using namespace std;

class String {
    char* str;

public:
    // Constructor
    String(const char* s) {
        str = new char[strlen(s) + 1];
        strcpy(str, s);
        cout << "Constructor: Allocated for " << str << endl;
    }

    // Copy Constructor
    String(const String& other) {
        str = new char[strlen(other.str) + 1];
        strcpy(str, other.str);
        cout << "Copy Constructor: Copied " << str << endl;
    }

    // Move Constructor
    String(String&& other) noexcept {
        str = other.str;
        other.str = nullptr;
        cout << "Move Constructor: Moved" << endl;
    }

    // Destructor
    ~String() {
        if (str) {
            cout << "Destructor: Deleting " << str << endl;
            delete[] str;
        } else {
            cout << "Destructor: Null pointer" << endl;
        }
    }
};

int main() {
    String a = "Hello";
    String b = std::move(a);  // Move constructor is called
    return 0;
}
```

### Output:

```
Constructor: Allocated for Hello
Move Constructor: Moved
Destructor: Null pointer
Destructor: Deleting Hello
```

### Explanation

* `String a = "Hello";` uses the normal constructor.
* `String b = std::move(a);` transfers ownership of the internal `char*` from `a` to `b` using the move constructor.
* After the move, `a.str` is set to `nullptr`, preventing double deletion.
* Efficient for classes managing dynamic resources (e.g., memory, file handles).

### Why Use Move Constructor?

* **Performance**: Avoids expensive deep copies.
* **Efficiency**: Transfers ownership of resources.
* **Mandatory**: For full compliance with the Rule of Five (C++11+).

### Rule of Five Reminder

If a class manages resources, it should define:

1. Destructor
2. Copy Constructor
3. Copy Assignment Operator
4. Move Constructor
5. Move Assignment Operator

---



---

## Destructor

A destructor is called by the compiler when the scope of the object ends. It deallocates memory used by the object to prevent memory leaks. It has the **same name as the class**, prefixed by a tilde `~`.

### Example:

```cpp
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
    MyClass obj;  // Destructor called automatically when obj goes out of scope
    return 0;
}
```

---

## Static Members

Static members belong to the class itself rather than any particular object. They can be accessed without creating an object.

### Static Data Members

Shared by all objects, only one copy exists for all instances.

```cpp
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
    cout << GfG::val << endl;  // Output: 22
    return 0;
}
```

### Static Member Functions

Static member functions can only access static data members and are called using the class name.

```cpp
#include <iostream>
using namespace std;

class GfG {
public:
    static void printHello();
};

// Definition of static member function
void GfG::printHello() {
    cout << "Hello World";
}

int main() {
    // Call static member function without creating object
    GfG::printHello();  // Output: Hello World
    return 0;
}
```

---

## Friend Class and Friend Function

* **Friend Class:** Can access private and protected members of another class if declared as a friend.
* **Friend Function:** Not a member of the class but granted access to private and protected members.

This is useful for close cooperation between classes or functions.
# Friend Class and Function in C++

In C++, **friend functions** and **friend classes** allow certain functions or classes to access the private and protected members of another class. These concepts are useful when you need to grant access to internal data while still keeping it hidden from the outside world.

---

## Friend Class in C++

A **friend class** can access private and protected members of another class in which it is declared as a friend. Note that friendship is not mutual; if class A is a friend of class B, then class B is not automatically a friend of class A.

We declare a friend class using the `friend` keyword.

![Friend class](https://media.geeksforgeeks.org/wp-content/uploads/20200506141034/Friend-class.png)

### Example:

```cpp
#include <iostream>
using namespace std;

class Geeks {
private:
    int private_variable;

protected:
    int protected_variable;

public:
    Geeks() {
        private_variable = 10;
        protected_variable = 99;
    }

    // Friend class declaration
    friend class GFG;
};

// Class GFG is a friend of class Geeks
class GFG {
public:
    void display(Geeks& t) {
        cout << "The value of Private Variable = " << t.private_variable << endl;
        cout << "The value of Protected Variable = " << t.protected_variable;
    }
};

int main() {
    Geeks g;
    GFG fri;
    fri.display(g);
    return 0;
}
The value of Private Variable = 10
The value of Protected Variable = 99

Friend Function in C++
Like friend classes, a friend function can access private and protected members of a class in which it is declared a friend. It is not a member function but is given access through the friend keyword.


Types of Friend Functions:
Global function

Member function of another class

1. Global Function as a Friend Function
We can declare any global function as a friend. The keyword friend is used only in the declaration within the class.

Example:
#include <iostream>
using namespace std;

class base {
private:
    int private_variable;

protected:
    int protected_variable;

public:
    base() {
        private_variable = 10;
        protected_variable = 99;
    }

    // Friend function declaration
    friend void friendFunction(base& obj);
};

// Friend function definition
void friendFunction(base& obj) {
    cout << "Private Variable: " << obj.private_variable << endl;
    cout << "Protected Variable: " << obj.protected_variable;
}

int main() {
    base obj;
    friendFunction(obj);
    return 0;
}
Output:-
Private Variable: 10
Protected Variable: 99


| Feature       | Friend Class                                    | Friend Function                                           |
| ------------- | ----------------------------------------------- | --------------------------------------------------------- |
| Access        | Private and protected members                   | Private and protected members                             |
| Declaration   | Inside the class using `friend class ClassName` | Inside the class using `friend ReturnType functionName()` |
| Nature        | Entire class gets access                        | Only specific function gets access                        |
| Mutual Access | No                                              | No                                                        |

---

## Local Class

A class defined **inside a function** is called a local class and can only be accessed within that function.

---

## Nested Class

A **nested class** is defined inside another class. It behaves like any other member of the enclosing class but does not grant special access back to the enclosing class.

---

## Enum Class

Enum classes provide a **safer and more organized** way to group related constants, preventing naming conflicts and improving type safety.

---

## `this` Pointer

`this` is a pointer available inside all non-static member functions that points to the current instance of the class.

### Example:

```cpp
class A {
    int n;
public:
    A(int n) {
        this->n = n;
    }
};
```

---


# Comprehensive C++ Demo: Special Member Functions and Concepts

This C++ program demonstrates several essential features and special member functions in C++ classes.

## ✅ Features Demonstrated

- Constructor and Destructor
- Static Data Member and Static Member Function
- Friend Class and Friend Function
- Local Class
- Nested Class
- Enum Class
- `this` Pointer

---

## 📄 Complete C++ Code

```cpp
#include <iostream>
using namespace std;

// Forward declaration for friend function
class MainClass;
void showPrivateData(const MainClass& obj);

// ----------------------------
// Enum Class Example
enum class Status {
    SUCCESS,
    FAILURE
};

// ----------------------------
// Main Class Declaration
class MainClass {
private:
    int privateData;

    // Nested Class Example
    class Nested {
    public:
        void display() {
            cout << "Inside Nested Class" << endl;
        }
    };

public:
    static int count;  // Static data member

    // Constructor
    MainClass(int data) {
        this->privateData = data;  // using this pointer
        count++;
        cout << "Constructor called. Object count: " << count << endl;
    }

    // Destructor
    ~MainClass() {
        count--;
        cout << "Destructor called. Remaining objects: " << count << endl;
    }

    // Static member function
    static void printCount() {
        cout << "Current object count (static): " << count << endl;
    }

    // Member function to use enum
    void checkStatus(Status s) {
        if (s == Status::SUCCESS)
            cout << "Operation was successful!" << endl;
        else
            cout << "Operation failed!" << endl;
    }

    // Friend function declaration
    friend void showPrivateData(const MainClass& obj);

    // Friend class declaration
    friend class FriendViewer;

    // Function to demonstrate nested class
    void useNestedClass() {
        Nested nestedObj;
        nestedObj.display();
    }

    // Function demonstrating local class
    void localClassDemo() {
        class Local {
        public:
            void message() {
                cout << "Inside Local Class (Only accessible in this function)" << endl;
            }
        };

        Local localObj;
        localObj.message();
    }
};

// Initialize static member
int MainClass::count = 0;

// Friend function definition
void showPrivateData(const MainClass& obj) {
    cout << "Accessed by Friend Function - Private Data: " << obj.privateData << endl;
}

// Friend class
class FriendViewer {
public:
    void displayPrivateData(const MainClass& obj) {
        cout << "Accessed by Friend Class - Private Data: " << obj.privateData << endl;
    }
};

// ----------------------------
// Main Function
int main() {
    cout << "=== Object Creation ===" << endl;
    MainClass obj1(10);
    obj1.checkStatus(Status::SUCCESS);

    cout << "\\n=== Static Members ===" << endl;
    MainClass::printCount();

    cout << "\\n=== Friend Function and Class ===" << endl;
    showPrivateData(obj1);
    FriendViewer fv;
    fv.displayPrivateData(obj1);

    cout << "\\n=== Nested Class ===" << endl;
    obj1.useNestedClass();

    cout << "\\n=== Local Class ===" << endl;
    obj1.localClassDemo();

    cout << "\\n=== Creating Another Object ===" << endl;
    MainClass obj2(20);
    MainClass::printCount();

    cout << "\\n=== Exiting Main ===" << endl;
    return 0;  // Destructor will be called automatically
}
=== Object Creation ===
Constructor called. Object count: 1
Operation was successful!

=== Static Members ===
Current object count (static): 1

=== Friend Function and Class ===
Accessed by Friend Function - Private Data: 10
Accessed by Friend Class - Private Data: 10

=== Nested Class ===
Inside Nested Class

=== Local Class ===
Inside Local Class (Only accessible in this function)

=== Creating Another Object ===
Constructor called. Object count: 2
Current object count (static): 2

=== Exiting Main ===
Destructor called. Remaining objects: 1
Destructor called. Remaining objects: 0


Class vs Object

The following table lists the primary differences between the classes and objects in C++:
| **Class**                                                                 | **Object**                                                                 |
|---------------------------------------------------------------------------|----------------------------------------------------------------------------|
| A blueprint or template for creating objects.                             | An instance of a class with actual values.                                |
| No memory is allocated for a class until an object is created.            | Memory is allocated when an object is created.                            |
| Conceptual entity describing structure and behaviour.                     | A real-world entity created from the class.                               |
| Defines properties and functions common to all objects of that type.      | Stores specific data and manipulates it using class functions.            |
| Represents a general concept or type.                                     | Represents a specific instance of the class.                              |


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
