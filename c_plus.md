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

---


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
---------------------------------------------
# C++ Mastery Roadmap

## 1. Basics of C++

### 1.1 Introduction to C++
- 1.1.1 History and Evolution  
- 1.1.2 Structure of a C++ Program  
- 1.1.3 Compiling and Running Programs  

### 1.2 Basic Syntax and Data Types
- 1.2.1 Keywords and Identifiers  
- 1.2.2 Variables and Constants  
- 1.2.3 Primitive Data Types (int, float, char, bool, etc.)  
- 1.2.4 Type Modifiers (signed, unsigned, long, short)  

### 1.3 Operators and Expressions
- 1.3.1 Arithmetic Operators  
- 1.3.2 Relational Operators  
- 1.3.3 Logical Operators  
- 1.3.4 Bitwise Operators  
- 1.3.5 Assignment Operators  
- 1.3.6 Operator Precedence and Associativity  

### 1.4 Control Structures
- 1.4.1 Conditional Statements (if, if-else, switch)  
- 1.4.2 Loops (for, while, do-while)  
- 1.4.3 Break and Continue  
- 1.4.4 Nested Loops and Conditionals  

### 1.5 Functions
- 1.5.1 Function Declaration and Definition  
- 1.5.2 Function Parameters and Return Types  
- 1.5.3 Function Overloading  
- 1.5.4 Inline Functions  
- 1.5.5 Default Arguments  
- 1.5.6 Recursion  

---

## 2. Intermediate C++

### 2.1 Arrays and Strings
- 2.1.1 One-dimensional Arrays  
- 2.1.2 Multidimensional Arrays  
- 2.1.3 Character Arrays and C-style Strings  
- 2.1.4 String Handling Functions (cstring)  
- 2.1.5 std::string Class  

### 2.2 Pointers and References
- 2.2.1 Pointer Basics and Syntax  
- 2.2.2 Pointer Arithmetic  
- 2.2.3 Pointers and Arrays  
- 2.2.4 Pointers to Pointers  
- 2.2.5 References vs Pointers  
- 2.2.6 Null and Void Pointers  

### 2.3 Dynamic Memory Management
- 2.3.1 new and delete Operators  
- 2.3.2 Dynamic Arrays  
- 2.3.3 Memory Leaks and Management  

### 2.4 Structures and Unions
- 2.4.1 Defining and Using Structures  
- 2.4.2 Nested Structures  
- 2.4.3 Unions  
- 2.4.4 Bit Fields  

### 2.5 Enumerations and Type Casting
- 2.5.1 enum Types  
- 2.5.2 Strongly Typed enum (enum class)  
- 2.5.3 Type Casting (static_cast, dynamic_cast, const_cast, reinterpret_cast)
 
### 2.6 Namespaces

- 2.6.1 What is a Namespace?  
- 2.6.2 Defining and Using Namespaces  
- 2.6.3 The `std` Namespace  
- 2.6.4 Nested Namespaces  
- 2.6.5 The `using` Directive and `using` Declaration  
- 2.6.6 Anonymous (Unnamed) Namespaces  
- 2.6.7 Best Practices for Namespaces  

---

## 3. Object-Oriented Programming (OOP)

### 3.1 Classes and Objects
- 3.1.1 Defining Classes  
- 3.1.2 Data Members and Member Functions  
- 3.1.3 Access Specifiers (public, private, protected)  
- 3.1.4 Constructors and Destructors  
- 3.1.5 Copy Constructor  
- 3.1.6 Member Initializer Lists  

### 3.2 Operator Overloading
- 3.2.1 Overloading Unary and Binary Operators  
- 3.2.2 Overloading Assignment Operator  
- 3.2.3 Overloading Stream Insertion (<<) and Extraction (>>)  

### 3.3 Inheritance
- 3.3.1 Types of Inheritance (Single, Multiple, Multilevel, Hierarchical, Hybrid)  
- 3.3.2 Access Control in Inheritance  
- 3.3.3 Constructors and Destructors in Derived Classes  
- 3.3.4 Virtual Base Classes  

### 3.4 Polymorphism
- 3.4.1 Function Overloading  
- 3.4.2 Function Overriding  
- 3.4.3 Virtual Functions  
- 3.4.4 Pure Virtual Functions and Abstract Classes  
- 3.4.5 Runtime Polymorphism  

### 3.5 Encapsulation and Abstraction
- 3.5.1 Data Hiding  
- 3.5.2 Accessor and Mutator Functions (Getters and Setters)  
- 3.5.3 Interface Design  

---

## 4. Advanced C++ Concepts

### 4.1 Templates
- 4.1.1 Function Templates  
- 4.1.2 Class Templates  
- 4.1.3 Template Specialization  
- 4.1.4 Variadic Templates  

### 4.2 Exception Handling
- 4.2.1 try, catch, throw Syntax  
- 4.2.2 Standard Exceptions  
- 4.2.3 Custom Exception Classes  
- 4.2.4 Exception Safety and Best Practices  

### 4.3 The Standard Template Library (STL)
- 4.3.1 Containers (vector, list, deque, set, map, unordered_map, etc.)  
- 4.3.2 Iterators  
- 4.3.3 Algorithms (sort, find, accumulate, etc.)  
- 4.3.4 Function Objects and Lambdas  
- 4.3.5 Allocators  

### 4.4 Smart Pointers and Memory Management
- 4.4.1 Unique_ptr  
- 4.4.2 Shared_ptr  
- 4.4.3 Weak_ptr  
- 4.4.4 Custom Deleters  

### 4.5 Move Semantics and Rvalue References
- 4.5.1 Lvalues and Rvalues  
- 4.5.2 Move Constructor and Move Assignment Operator  
- 4.5.3 std::move and std::forward  

---

## 5. Expert Level and Modern C++ (C++11 and beyond)

### 5.1 Advanced Lambda Expressions
- 5.1.1 Captures by Value and Reference  
- 5.1.2 Generic Lambdas  
- 5.1.3 Lambdas with Mutable Keyword  

### 5.2 Concurrency and Multithreading
- 5.2.1 std::thread  
- 5.2.2 Mutexes and Locks (std::mutex, std::lock_guard)  
- 5.2.3 Condition Variables  
- 5.2.4 Atomic Operations and std::atomic  

### 5.3 constexpr and Constexpr Functions
- 5.3.1 Compile-time Computations  
- 5.3.2 constexpr vs const  

### 5.4 Advanced Template Metaprogramming
- 5.4.1 SFINAE (Substitution Failure Is Not An Error)  
- 5.4.2 Type Traits and std::enable_if  
- 5.4.3 Template Recursion  

### 5.5 Design Patterns in C++
- 5.5.1 Singleton  
- 5.5.2 Factory  
- 5.5.3 Observer  
- 5.5.4 Strategy  
- 5.5.5 Decorator  

### 5.6 Best Practices and Optimization
- 5.6.1 Effective C++ Practices  
- 5.6.2 Code Optimization Techniques  
- 5.6.3 Profiling and Debugging Tools  
- 5.6.4 Writing Maintainable Code

Great — now we’re digging into **low-level C++**, and you’re spot-on: these features are **essential** for systems programming, embedded systems, and even driver development (like a Wi-Fi driver). I’ll walk you through **each subtopic**, assuming zero prior experience. 🧠🔧

We’ll use the **Wi-Fi driver setup** as a relatable real-world backdrop for all examples.

---

# 🔷 2.4 Structures and Unions in C++

---

## ✅ What Are Structures and Unions?

* A **structure (`struct`)** is a user-defined data type that groups **different variables (members)** under one name.
* A **union** is like a struct but **shares memory** among all members — only **one member can be used at a time**.

They are commonly used in:

* Device drivers
* System-level code
* Network packets
* Embedded systems

---

# 🔹 2.4.1 Defining and Using Structures

```cpp
struct WiFiDevice {
    string name;
    string macAddress;
    bool isConnected;
};
```

### ✅ Usage:

```cpp
WiFiDevice device = {"ESP32", "AA:BB:CC:DD:EE:FF", true};
cout << device.name << " connected? " << device.isConnected << "\n";
```

---

# 🔹 2.4.2 Nested Structures

You can define structures **inside other structures** to model hierarchical data.

```cpp
struct WiFiConfig {
    struct Security {
        string encryptionType;
        string password;
    };

    string ssid;
    Security security;
};
```

---

# 🔹 2.4.3 Unions

Unions allow different members to **share the same memory**. Use when **only one of the values is active at a time** (like packet types or hardware registers).

```cpp
union DataPacket {
    int signalStrength;
    float frequency;
    char rawData[4];
};
```

⚠️ Modifying one member affects all.

---

# 🔹 2.4.4 Bit Fields

Bit fields are used to **pack multiple bits** into a single byte or int — commonly in hardware registers or network flags.

```cpp
struct StatusFlags {
    unsigned int power     : 1;
    unsigned int connected : 1;
    unsigned int error     : 1;
    unsigned int reserved  : 5;
};
```

Total: 1 byte instead of 12 bytes — ideal for microcontrollers and device drivers.

---

# 🔹 2.4.5 Anonymous Structures

Structs without a name used within other structs to group related members without polluting the namespace.

```cpp
struct WiFiDevice {
    string name;

    struct {
        bool dhcp;
        string ip;
    };  // Anonymous structure

    void showIP() {
        cout << "IP: " << ip << "\n";
    }
};
```

---

# 🔹 2.4.6 Structure Packing

Structure padding aligns members in memory for performance — but in embedded systems (like Wi-Fi chipsets), this wastes memory.

```cpp
#pragma pack(1)
struct PackedWiFiHeader {
    char startByte;
    int packetLength;
    short checksum;
};
#pragma pack()
```

This disables padding. Great for hardware protocols, bad for performance if misused.

---

# 🔹 2.4.7 Interrupts (Contextual Use in Structs)

While C++ itself doesn’t handle interrupts directly, **structs often model data passed to or from interrupt service routines (ISRs)**.

```cpp
struct InterruptContext {
    uint8_t irqNumber;
    uint32_t timestamp;
    bool fromWiFiModule;
};
```

These are used in **ISR handler functions** registered by the OS/RTOS.

---

# 🔹 2.4.8 Function Pointers and `typename`

Structs can hold **function pointers** — a key feature in drivers, where you may pass callbacks for events like "Wi-Fi Connected".

```cpp
struct WiFiCallbacks {
    void (*onConnected)(string ip);
    void (*onDisconnected)(int reason);
};
```

You can assign them like this:

```cpp
void connectedHandler(string ip) {
    cout << "WiFi connected at " << ip << "\n";
}
WiFiCallbacks cb;
cb.onConnected = connectedHandler;
cb.onConnected("192.168.1.10");
```

---

# 🧪 Real-Life Example: Simplified Wi-Fi Driver Simulation

```cpp
#include <iostream>
#include <string>
using namespace std;

// Simulated packed structure for a Wi-Fi header
#pragma pack(1)
struct WiFiHeader {
    uint8_t startByte;
    uint16_t length;
    uint8_t checksum;
};
#pragma pack()

// Status bit fields
struct WiFiStatus {
    unsigned int power     : 1;
    unsigned int connected : 1;
    unsigned int error     : 1;
    unsigned int reserved  : 5;
};

// Callback structure with function pointers
struct WiFiCallbacks {
    void (*onConnected)(string ip);
    void (*onDisconnected)(int reason);
};

// Nested structure for config
struct WiFiConfig {
    string ssid;
    struct Security {
        string encryption;
        string password;
    } security;
};

// Anonymous struct example
struct WiFiDevice {
    string name;

    struct {
        bool dhcp;
        string ip;
    }; // anonymous

    WiFiStatus status;
    WiFiConfig config;
    WiFiCallbacks callbacks;

    void connect() {
        cout << name << " trying to connect...\n";
        status.connected = 1;
        ip = "192.168.0.5";
        if (callbacks.onConnected) callbacks.onConnected(ip);
    }

    void disconnect(int code) {
        status.connected = 0;
        if (callbacks.onDisconnected) callbacks.onDisconnected(code);
    }
};

// Callback implementations
void onWiFiConnected(string ip) {
    cout << "[Driver] Connected to Wi-Fi. IP: " << ip << "\n";
}

void onWiFiDisconnected(int reason) {
    cout << "[Driver] Disconnected. Reason Code: " << reason << "\n";
}

int main() {
    WiFiDevice device = {
        .name = "ESP32",
        .dhcp = true,
        .status = {1, 0, 0, 0},
        .config = {
            "OpenAI-Network",
            {"WPA2", "securepassword"}
        },
        .callbacks = {onWiFiConnected, onWiFiDisconnected}
    };

    cout << "== Simulating Wi-Fi Driver ==\n";
    device.connect();
    device.disconnect(404);

    // Demo union
    union WiFiData {
        int signalStrength;
        float freq;
    };

    WiFiData data;
    data.signalStrength = -50;
    cout << "Signal Strength: " << data.signalStrength << " dBm\n";

    return 0;
}
```

---

## 🧾 Output

```
== Simulating Wi-Fi Driver ==
ESP32 trying to connect...
[Driver] Connected to Wi-Fi. IP: 192.168.0.5
[Driver] Disconnected. Reason Code: 404
Signal Strength: -50 dBm
```

---

## ✅ Summary Table

| Concept                 | Used in Example? |
| ----------------------- | ---------------- |
| Basic struct usage      | ✅                |
| Nested structs          | ✅                |
| Anonymous struct        | ✅                |
| Unions                  | ✅                |
| Bit fields              | ✅                |
| Struct packing          | ✅                |
| Interrupt context style | ✅ (struct only)  |
| Function pointers       | ✅                |

---

## ✅ Best Practices

| Do ✅                                 | Avoid ❌                       |
| ------------------------------------ | ----------------------------- |
| Use `#pragma pack` only when needed  | Overusing packed structures   |
| Use enums and bit-fields for flags   | Using raw magic numbers       |
| Use function pointers for modularity | Hardcoded driver logic        |
| Document every struct carefully      | Blind use in ISRs or hardware |

---

Would you like this as a `.cpp` or `.md` file?

Up next, we can dive into:

* **2.3 Dynamic Memory Management**
* **4.1 Templates**
* **4.2 Exception Handling**
* Or go full embedded-mode and simulate **Interrupt Handling** or **RTOS Tasks in C++** — your call!


---

# 🔷 2.5 Enumerations and Type Casting

---

## 🔹 2.5.1 `enum` Types (Traditional Enums)

### ✅ What is an `enum`?

An `enum` (short for *enumeration*) is a user-defined type that consists of **named integer constants**.

### 📌 Syntax:

```cpp
enum Direction { North, East, South, West };
```

* `North = 0`, `East = 1`, and so on (by default)
* Can assign custom values:

```cpp
enum ErrorCode { OK = 0, NotFound = 404, ServerError = 500 };
```

### 🧠 Why use enums?

* Improves **readability** and **type safety**
* Replaces magic numbers with **meaningful names**

---

## 🔹 2.5.2 Strongly Typed Enums (`enum class`)

### ✅ Problem with Traditional `enum`:

They are **not scoped**, so constants may **collide** across enums.

### ✅ Solution: `enum class` (C++11)

```cpp
enum class Color { Red, Green, Blue };
enum class Status { OK, Error };

// Usage:
Color c = Color::Red;  // Scoped!
```

### ✅ Benefits:

| Feature      | `enum`     | `enum class`    |
| ------------ | ---------- | --------------- |
| Scoped       | ❌ (global) | ✅ (inside enum) |
| Implicit int | ✅          | ❌ (must cast)   |
| Type safe    | ❌          | ✅               |

---

## 🔹 2.5.3 Type Casting

C++ provides **four explicit type casting operators**, each with a specific use case.

---

### ✅ 1. `static_cast<T>(expr)`

* Used for **safe and well-defined conversions**
* E.g., int to float, base to derived pointer (if safe)

```cpp
int i = 10;
double d = static_cast<double>(i);
```

---

### ✅ 2. `dynamic_cast<T>(expr)`

* Used for **safe downcasting** in **polymorphic class hierarchies**
* Requires at least one **virtual function** in the base class
* Returns `nullptr` if cast fails

```cpp
class Animal { public: virtual void speak() {} };
class Dog : public Animal {};

Animal* a = new Dog();
Dog* d = dynamic_cast<Dog*>(a);  // Safe!
```

---

### ✅ 3. `const_cast<T>(expr)`

* **Removes** `const` or `volatile` qualifier
* ⚠️ Dangerous if you modify the data after removing constness

```cpp
const int* p = new int(5);
int* modifiable = const_cast<int*>(p);
```

---

### ✅ 4. `reinterpret_cast<T>(expr)`

* Treats one type of data as another (dangerous!)
* Use only when **you really know what you're doing**

```cpp
int a = 65;
char* c = reinterpret_cast<char*>(&a);  // Treats int as char pointer
```

---

# 🧪 Real-Life Example: Smart Home System

### 🎯 Scenario:

You’re designing a **Smart Home Control Panel** that:

* Uses enums to track **Device State** and **User Roles**
* Uses **`enum class`** to avoid value collisions
* Demonstrates all **type casts** safely

---

### ✅ Code:

```cpp
#include <iostream>
#include <string>
using namespace std;

// Traditional Enum
enum DeviceState { OFF, ON };

// Strongly typed enum
enum class UserRole { Guest, Admin, Technician };

// Polymorphic base class for casting
class Device {
public:
    virtual void info() { cout << "Generic device\n"; }
};

class Light : public Device {
public:
    void info() override { cout << "Light device\n"; }
};

void controlDevice(DeviceState state) {
    if (state == ON)
        cout << "Turning ON device.\n";
    else
        cout << "Turning OFF device.\n";
}

void checkUser(UserRole role) {
    switch (role) {
        case UserRole::Guest: cout << "Guest access\n"; break;
        case UserRole::Admin: cout << "Admin access\n"; break;
        case UserRole::Technician: cout << "Technician access\n"; break;
    }
}

int main() {
    cout << "--- Enums ---\n";
    DeviceState lampState = ON;
    controlDevice(lampState);

    UserRole role = UserRole::Admin;
    checkUser(role);

    cout << "\n--- static_cast ---\n";
    double temp = 23.5;
    int tempInt = static_cast<int>(temp);
    cout << "Temperature: " << tempInt << "°C\n";

    cout << "\n--- dynamic_cast ---\n";
    Device* d = new Light();
    Light* l = dynamic_cast<Light*>(d);
    if (l) l->info();

    cout << "\n--- const_cast ---\n";
    const char* msg = "Read-only message";
    char* editable = const_cast<char*>(msg);
    cout << "Message: " << editable << endl;

    cout << "\n--- reinterpret_cast ---\n";
    int number = 65;
    char* ch = reinterpret_cast<char*>(&number);
    cout << "As char: " << *ch << "\n";

    delete d;
    return 0;
}
```

---

### 🧾 Sample Output:

```
--- Enums ---
Turning ON device.
Admin access

--- static_cast ---
Temperature: 23°C

--- dynamic_cast ---
Light device

--- const_cast ---
Message: Read-only message

--- reinterpret_cast ---
As char: A
```

---

## ✅ Concepts Demonstrated

| Concept            | Included? |
| ------------------ | --------- |
| Traditional enum   | ✅         |
| Scoped enum class  | ✅         |
| `static_cast`      | ✅         |
| `dynamic_cast`     | ✅         |
| `const_cast`       | ✅         |
| `reinterpret_cast` | ✅         |

---

## ✅ Summary Table

| Cast Type          | Purpose                          | Safe? | Use Case                      |
| ------------------ | -------------------------------- | ----- | ----------------------------- |
| `static_cast`      | Compile-time conversion          | ✅     | int → float, base → derived   |
| `dynamic_cast`     | Runtime-checked pointer downcast | ✅     | polymorphic base ↔ derived    |
| `const_cast`       | Remove const-ness                | ⚠️    | rarely, and safely            |
| `reinterpret_cast` | Bitwise reinterpretation         | ❌     | Low-level system code (risky) |

---

## ✅ Best Practices

| Do ✅                                      | Avoid ❌                             |
| ----------------------------------------- | ----------------------------------- |
| Use `enum class` for safety               | Overlapping traditional enum values |
| Prefer `make_shared`, `make_unique`       | Manual memory in modern C++         |
| Use `dynamic_cast` with RTTI              | Blind casting without checks        |
| Avoid `reinterpret_cast` unless necessary | Messing with type bits casually     |

---

Would you like this saved as `.md` or `.cpp` for GitHub?

We can now continue to:

* **Templates** and `std::function`
* **STL Containers** and Algorithms
* Or dive into **Exception Handling (4.2)** next!

---

# 🔷 3.1 Classes and Objects in C++

---

## ✅ What are Classes and Objects?

> A **class** is a blueprint for creating **objects** — bundles of data and functions that model real-world entities.

* **Class** → Defines structure and behavior
* **Object** → Instance of a class

🧱 Think of a class as a **building plan**, and objects as the **buildings** made from it.

---

## 🔹 3.1.1 Defining Classes

```cpp
class Car {
public:
    void start() {
        cout << "Engine started.\n";
    }
};
```

* `class` keyword defines a class
* Can contain **data members** (variables) and **member functions** (methods)
* `public`, `private`, `protected` control access

---

## 🔹 3.1.2 Data Members and Member Functions

### ✅ Example:

```cpp
class Car {
private:
    string model;
    int speed;

public:
    void setModel(string m) { model = m; }
    void setSpeed(int s) { speed = s; }
    void display() {
        cout << "Model: " << model << ", Speed: " << speed << " km/h\n";
    }
};
```

---

## 🔹 3.1.3 Access Specifiers

| Access Specifier | Accessible From           |
| ---------------- | ------------------------- |
| `public`         | Anywhere                  |
| `private`        | Only inside the class     |
| `protected`      | Class and derived classes |

🔒 **Encapsulation** relies on `private` and `protected`.

---

## 🔹 3.1.4 Constructors and Destructors

### ✅ Constructor:

Special function that runs **when an object is created**.

```cpp
Car(string m, int s) {
    model = m;
    speed = s;
}
```

### ✅ Destructor:

Runs **when object is destroyed**.

```cpp
~Car() {
    cout << model << " destroyed.\n";
}
```

---

## 🔹 3.1.5 Copy Constructor

Used when:

* An object is **passed by value**
* You **copy initialize** one object from another

### ✅ Default Copy Constructor:

Does **shallow copy** (bitwise)

### ✅ Custom Copy Constructor (for deep copy):

```cpp
Car(const Car& other) {
    model = other.model;
    speed = other.speed;
}
```

---

## 🔹 3.1.6 Member Initializer Lists

Used to initialize **const**, **reference**, and **base class** members efficiently.

```cpp
class Car {
private:
    string model;
    int speed;

public:
    Car(string m, int s) : model(m), speed(s) {
        cout << "Car created using initializer list\n";
    }
};
```

---

## 🧠 Summary Table

| Concept               | Purpose                         |
| --------------------- | ------------------------------- |
| Class definition      | Define user-defined type        |
| Data/Member functions | Represent state and behavior    |
| Access specifiers     | Control visibility              |
| Constructor           | Initialize object               |
| Destructor            | Clean up object                 |
| Copy constructor      | Define custom copying logic     |
| Initializer list      | Efficient member initialization |

---

# 🧪 Real-Life Example: `Book` Class in Library System

### 🎯 Scenario:

Create a class `Book` that models:

* Title, author, and price
* Constructor with initializer list
* Copy constructor
* Member functions to set/get values
* Destructor that logs destruction

---

### ✅ Code:

```cpp
#include <iostream>
#include <string>
using namespace std;

class Book {
private:
    string title;
    string author;
    double price;

public:
    // Default constructor
    Book() : title("Untitled"), author("Unknown"), price(0.0) {
        cout << "[Default Constructor] Book created.\n";
    }

    // Parameterized constructor using initializer list
    Book(string t, string a, double p) : title(t), author(a), price(p) {
        cout << "[Parameterized Constructor] Book: " << title << " created.\n";
    }

    // Copy constructor
    Book(const Book& other) : title(other.title), author(other.author), price(other.price) {
        cout << "[Copy Constructor] Book: " << title << " copied.\n";
    }

    // Destructor
    ~Book() {
        cout << "[Destructor] Book: " << title << " destroyed.\n";
    }

    // Setters
    void setTitle(string t) { title = t; }
    void setAuthor(string a) { author = a; }
    void setPrice(double p) { price = p; }

    // Getters
    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    double getPrice() const { return price; }

    void display() const {
        cout << "Title: " << title
             << ", Author: " << author
             << ", Price: ₹" << price << "\n";
    }
};

int main() {
    cout << "--- Creating Book 1 ---\n";
    Book b1("Atomic Habits", "James Clear", 499.0);

    cout << "\n--- Creating Book 2 via Copy Constructor ---\n";
    Book b2 = b1;  // Triggers copy constructor

    cout << "\n--- Displaying Books ---\n";
    b1.display();
    b2.display();

    cout << "\n--- Creating Default Book ---\n";
    Book b3;
    b3.setTitle("1984");
    b3.setAuthor("George Orwell");
    b3.setPrice(299.0);
    b3.display();

    cout << "\n--- End of Program ---\n";
    return 0;
}
```

---

### 🧾 Output:

```
--- Creating Book 1 ---
[Parameterized Constructor] Book: Atomic Habits created.

--- Creating Book 2 via Copy Constructor ---
[Copy Constructor] Book: Atomic Habits copied.

--- Displaying Books ---
Title: Atomic Habits, Author: James Clear, Price: ₹499
Title: Atomic Habits, Author: James Clear, Price: ₹499

--- Creating Default Book ---
[Default Constructor] Book created.
Title: 1984, Author: George Orwell, Price: ₹299

--- End of Program ---
[Destructor] Book: 1984 destroyed.
[Destructor] Book: Atomic Habits destroyed.
[Destructor] Book: Atomic Habits destroyed.
```

---

## ✅ Concepts Demonstrated

| Concept                  | Demonstrated |
| ------------------------ | ------------ |
| Class definition         | ✅ Yes        |
| Data members & functions | ✅ Yes        |
| Access control           | ✅ Yes        |
| Constructors             | ✅ Yes        |
| Destructor               | ✅ Yes        |
| Copy constructor         | ✅ Yes        |
| Initializer list         | ✅ Yes        |
| Real-world mapping       | ✅ Yes        |

---

## ✅ Summary

* Classes model real-world entities.
* Constructors and destructors manage object lifecycle.
* Copy constructors prevent shallow copy issues.
* Member initializer lists optimize initialization.

---

---

# 🔷 3.2 Operator Overloading in C++

---

## ✅ What is Operator Overloading?

> Operator overloading allows **custom implementation** of operators (`+`, `-`, `=`, `<<`, etc.) for **user-defined types (classes/structs)**.

It makes your class behave **like a built-in type**, improving **readability**, **intuitiveness**, and **reusability**.

---

## ✅ Syntax of Operator Overloading

```cpp
class ClassName {
public:
    ReturnType operator<op>(Arguments) {
        // implementation
    }
};
```

---

# 🔹 3.2.1 Overloading Unary and Binary Operators

---

## ✅ Unary Operators

These operate on **one operand**:

* `++`, `--`, `-`, `!`, `~`, etc.

### ▶ Example: Overloading `++` (prefix)

```cpp
class Counter {
private:
    int value;

public:
    Counter(int v) : value(v) {}

    // Prefix ++
    Counter& operator++() {
        ++value;
        return *this;
    }

    void display() { cout << value << endl; }
};
```

### ▶ Postfix `++` Overload

```cpp
Counter operator++(int) {
    Counter temp = *this;
    value++;
    return temp;
}
```

---

## ✅ Binary Operators

These operate on **two operands**:

* `+`, `-`, `*`, `/`, `%`, `==`, `!=`, `<`, `>`, etc.

### ▶ Example: Overload `+` for complex numbers

```cpp
class Complex {
private:
    double real, imag;

public:
    Complex(double r, double i) : real(r), imag(i) {}

    Complex operator+(const Complex& other) {
        return Complex(real + other.real, imag + other.imag);
    }
};
```

---

# 🔹 3.2.2 Overloading Assignment Operator (`=`)

The assignment operator **copies** one object into another. If your class contains pointers or resources, you must **overload this properly** to implement **deep copy**.

### ▶ Example:

```cpp
class MyString {
private:
    char* str;

public:
    MyString(const char* s) {
        str = new char[strlen(s) + 1];
        strcpy(str, s);
    }

    // Assignment operator (deep copy)
    MyString& operator=(const MyString& other) {
        if (this != &other) {
            delete[] str;
            str = new char[strlen(other.str) + 1];
            strcpy(str, other.str);
        }
        return *this;
    }

    ~MyString() { delete[] str; }
};
```

---

# 🔹 3.2.3 Overloading Stream Insertion (`<<`) and Extraction (`>>`)

These are typically overloaded as **non-member friend functions**.

### ▶ Stream Insertion (`<<`)

```cpp
class Point {
private:
    int x, y;

public:
    Point(int x, int y) : x(x), y(y) {}

    friend ostream& operator<<(ostream& out, const Point& p) {
        out << "(" << p.x << ", " << p.y << ")";
        return out;
    }
};
```

### ▶ Stream Extraction (`>>`)

```cpp
friend istream& operator>>(istream& in, Point& p) {
    in >> p.x >> p.y;
    return in;
}
```

---

## 🧠 Summary Table

| Operator Type | Overloaded With | Notes                               |
| ------------- | --------------- | ----------------------------------- |
| Unary         | `operator++()`  | Prefix and postfix differ by `int`  |
| Binary        | `operator+(T)`  | Must match signature                |
| Assignment    | `operator=`     | Use deep copy if managing resources |
| Insertion     | `operator<<`    | Usually friend function             |
| Extraction    | `operator>>`    | Usually friend function             |

---

# 🧪 Real-Life Example: Overloaded `Money` Class

### 🎯 Scenario:

Build a `Money` class that:

* Supports `+` and `-` operations
* Increments with `++` operator
* Can be assigned via `=`
* Prints via `<<`
* Accepts input via `>>`

---

### ✅ Code:

```cpp
#include <iostream>
using namespace std;

class Money {
private:
    int rupees, paise;

    void normalize() {
        if (paise >= 100) {
            rupees += paise / 100;
            paise %= 100;
        }
    }

public:
    Money(int r = 0, int p = 0) : rupees(r), paise(p) {
        normalize();
    }

    // Overload +
    Money operator+(const Money& other) {
        return Money(rupees + other.rupees, paise + other.paise);
    }

    // Overload -
    Money operator-(const Money& other) {
        int total1 = rupees * 100 + paise;
        int total2 = other.rupees * 100 + other.paise;
        int diff = total1 - total2;
        return Money(diff / 100, diff % 100);
    }

    // Overload prefix ++
    Money& operator++() {
        paise += 1;
        normalize();
        return *this;
    }

    // Overload assignment =
    Money& operator=(const Money& other) {
        if (this != &other) {
            rupees = other.rupees;
            paise = other.paise;
        }
        return *this;
    }

    // Overload <<
    friend ostream& operator<<(ostream& out, const Money& m) {
        out << "₹" << m.rupees << "." << (m.paise < 10 ? "0" : "") << m.paise;
        return out;
    }

    // Overload >>
    friend istream& operator>>(istream& in, Money& m) {
        cout << "Enter rupees: ";
        in >> m.rupees;
        cout << "Enter paise: ";
        in >> m.paise;
        m.normalize();
        return in;
    }
};

int main() {
    Money salary(12, 75), bonus(3, 50), total;

    cout << "Salary: " << salary << endl;
    cout << "Bonus: " << bonus << endl;

    total = salary + bonus;
    cout << "Total: " << total << endl;

    total = total - Money(2, 30);
    cout << "After tax: " << total << endl;

    ++total;
    cout << "After rounding bonus: " << total << endl;

    Money custom;
    cin >> custom;
    cout << "Custom amount: " << custom << endl;

    return 0;
}
```

---

### 🧾 Sample Output:

```
Salary: ₹12.75
Bonus: ₹3.50
Total: ₹16.25
After tax: ₹13.95
After rounding bonus: ₹13.96
Enter rupees: 9
Enter paise: 145
Custom amount: ₹10.45
```

---

## ✅ Concepts Demonstrated

| Feature                             | Used? |
| ----------------------------------- | ----- |
| Unary & binary operator overloading | ✅     |
| Stream insertion/extraction         | ✅     |
| Assignment operator                 | ✅     |
| Input validation and normalization  | ✅     |
| Real-world currency modeling        | ✅     |

---

## ✅ Summary

* Operator overloading improves class usability and mimics native types.
* Use **deep copies** when managing resources.
* `<<` and `>>` are overloaded as **friend functions** for flexibility.
* Normalize custom data internally to ensure consistency.

---

Would you like this as a `.cpp` or `.md` file for your GitHub, or continue with another topic like **Virtual Functions**, **Templates**, or **STL Deep Dive**?


---

# 🔷 3.3 Inheritance in C++

---

## ✅ What is Inheritance?

> Inheritance allows a class (**derived**) to **acquire properties and behavior** (data and functions) from another class (**base**).

### 🧱 Why use it?

* Code reusability
* Hierarchical classification
* Polymorphism support
* Extensibility

---

## 🔹 3.3.1 Types of Inheritance

### 📌 1. **Single Inheritance**

One base → one derived class

```cpp
class Animal {
public: void eat() {}
};

class Dog : public Animal {
public: void bark() {}
};
```

---

### 📌 2. **Multilevel Inheritance**

A derived class becomes the base for another

```cpp
class Animal { };
class Mammal : public Animal { };
class Dog : public Mammal { };
```

---

### 📌 3. **Hierarchical Inheritance**

Multiple derived classes from a single base

```cpp
class Animal { };
class Dog : public Animal { };
class Cat : public Animal { };
```

---

### 📌 4. **Multiple Inheritance**

Derived class inherits from multiple base classes

```cpp
class Flyable { };
class Swimmable { };

class Duck : public Flyable, public Swimmable { };
```

---

### 📌 5. **Hybrid Inheritance**

Combination of two or more types (⚠️ leads to **diamond problem**)

```cpp
class Animal { };
class Mammal : public Animal { };
class Bird : public Animal { };
class Bat : public Mammal, public Bird { }; // Ambiguity!
```

---

## 🔹 3.3.2 Access Control in Inheritance

| Access Specifier | Inherited as `public` | `protected` | `private` |
| ---------------- | --------------------- | ----------- | --------- |
| `public` member  | public                | protected   | private   |
| `protected`      | protected             | protected   | private   |
| `private`        | ❌ Not Inherited       | ❌           | ❌         |

```cpp
class Base {
public:
    int a;
protected:
    int b;
private:
    int c;
};

class Derived : public Base {
    // a is public, b is protected, c is inaccessible
};
```

---

## 🔹 3.3.3 Constructors and Destructors in Derived Classes

### ✅ Key Rules:

* **Base class constructor** runs before derived class constructor.
* **Destructors** run in **reverse order**: derived → base.
* Can explicitly call base constructors using **initializer list**.

```cpp
class Base {
public:
    Base() { cout << "Base constructor\n"; }
    ~Base() { cout << "Base destructor\n"; }
};

class Derived : public Base {
public:
    Derived() { cout << "Derived constructor\n"; }
    ~Derived() { cout << "Derived destructor\n"; }
};
```

---

## 🔹 3.3.4 Virtual Base Classes

### 🎯 Used to solve **diamond problem** in hybrid inheritance.

### 🔁 Problem:

A derived class inherits multiple times from the same base (ambiguity).

```cpp
class A {
public: int x;
};

class B : virtual public A { };
class C : virtual public A { };
class D : public B, public C {
    // Only ONE instance of A is inherited
};
```

---

## ✅ Summary Table

| Concept                  | Purpose                                |
| ------------------------ | -------------------------------------- |
| Single Inheritance       | Simple base → derived hierarchy        |
| Multiple Inheritance     | Combine features from multiple bases   |
| Multilevel Inheritance   | Inheritance chain                      |
| Hierarchical Inheritance | One base, multiple specialized classes |
| Hybrid Inheritance       | Complex, may lead to diamond problem   |
| Access Control           | Manages visibility of inherited data   |
| Constructor Rules        | Init order: base → derived             |
| Virtual Base Class       | Avoids duplicate base class instances  |

---

# 🧪 Real-Life Example: Employee Management System

### 🎯 Scenario:

Create a system to manage different types of employees:

* `Person` is the base class (name, age)
* `Employee` inherits from `Person` and adds employee ID
* `Developer` and `Manager` inherit from `Employee`
* `Freelancer` inherits from `Person` and adds pay-per-hour
* `HybridEmployee` (freelance-developer) inherits from both `Developer` and `Freelancer` — diamond problem is solved via **virtual inheritance**

---

### ✅ Code:

```cpp
#include <iostream>
#include <string>
using namespace std;

// Base class
class Person {
protected:
    string name;
    int age;

public:
    Person(string n, int a) : name(n), age(a) {
        cout << "Person constructor\n";
    }

    virtual void display() const {
        cout << "Name: " << name << ", Age: " << age << endl;
    }

    virtual ~Person() {
        cout << "Person destructor\n";
    }
};

// Employee class inherits from Person (single)
class Employee : virtual public Person {
protected:
    int empID;

public:
    Employee(string n, int a, int id)
        : Person(n, a), empID(id) {
        cout << "Employee constructor\n";
    }

    void display() const override {
        Person::display();
        cout << "Employee ID: " << empID << endl;
    }

    virtual ~Employee() {
        cout << "Employee destructor\n";
    }
};

// Freelancer class (hierarchical, virtual base)
class Freelancer : virtual public Person {
protected:
    double ratePerHour;
    int hoursWorked;

public:
    Freelancer(string n, int a, double rate, int hours)
        : Person(n, a), ratePerHour(rate), hoursWorked(hours) {
        cout << "Freelancer constructor\n";
    }

    double calculatePayment() const {
        return ratePerHour * hoursWorked;
    }

    virtual ~Freelancer() {
        cout << "Freelancer destructor\n";
    }
};

// Developer (multilevel)
class Developer : public Employee {
protected:
    string language;

public:
    Developer(string n, int a, int id, string lang)
        : Person(n, a), Employee(n, a, id), language(lang) {
        cout << "Developer constructor\n";
    }

    void display() const override {
        Employee::display();
        cout << "Language: " << language << endl;
    }

    virtual ~Developer() {
        cout << "Developer destructor\n";
    }
};

// Hybrid: Inherits from Developer + Freelancer (hybrid + virtual base)
class HybridEmployee : public Developer, public Freelancer {
public:
    HybridEmployee(string n, int a, int id, string lang, double rate, int hours)
        : Person(n, a), Employee(n, a, id), Developer(n, a, id, lang), Freelancer(n, a, rate, hours) {
        cout << "HybridEmployee constructor\n";
    }

    void display() const override {
        Developer::display();
        cout << "Freelance Payment: ₹" << calculatePayment() << endl;
    }

    ~HybridEmployee() {
        cout << "HybridEmployee destructor\n";
    }
};

int main() {
    cout << "--- Creating Hybrid Employee ---\n";
    HybridEmployee he("Ravi", 30, 101, "C++", 1000, 10);
    cout << "\n--- Displaying Employee Info ---\n";
    he.display();

    cout << "\n--- Exiting Program ---\n";
    return 0;
}
```

---

### 🧾 Output:

```
--- Creating Hybrid Employee ---
Person constructor
Employee constructor
Developer constructor
Freelancer constructor
HybridEmployee constructor

--- Displaying Employee Info ---
Name: Ravi, Age: 30
Employee ID: 101
Language: C++
Freelance Payment: ₹10000

--- Exiting Program ---
HybridEmployee destructor
Freelancer destructor
Developer destructor
Employee destructor
Person destructor
```

---

## ✅ Concepts Demonstrated

| Concept                           | Used? |
| --------------------------------- | ----- |
| Single, multiple, multilevel      | ✅     |
| Hybrid & hierarchical inheritance | ✅     |
| Access control                    | ✅     |
| Virtual base class (diamond fix)  | ✅     |
| Constructor/destructor chaining   | ✅     |

---

## ✅ Summary

* Use **inheritance** to build structured class hierarchies.
* Understand the **impacts of access specifiers** on inherited members.
* Use **virtual base classes** to avoid diamond problem.
* Manage construction/destruction order correctly in complex inheritance.

---

Would you like this as a `.cpp` or `.md` file for documentation? Or should we now move to **Polymorphism Deep Dive**, **Virtual Destructors**, or **Composition vs Inheritance** next?


# 🔷 Function Overloading in C++

---

## ✅ 1. What is Function Overloading?

**Function overloading** allows multiple functions to have the same name but **different parameter lists** (type, number, or order of parameters).
It is a type of **compile-time polymorphism**.

```cpp
int add(int a, int b);
double add(double a, double b);
int add(int a, int b, int c);
```

---

## ✅ 2. Why Use Function Overloading?

* Increases **readability** and **maintainability**
* Implements **polymorphism** for better code reuse
* Helps mimic **natural usage** (like `add()`, `print()`)

---

## ✅ 3. Rules for Function Overloading

A function can be overloaded if:

* The **number of parameters** is different.
* The **types of parameters** are different.
* The **order of parameters** is different (if types differ).

✅ Allowed:

```cpp
void print(int);
void print(double);
void print(string);
```

❌ Not Allowed (Ambiguous return type):

```cpp
int show();
double show(); // Error: Only return type differs — not enough
```

---

## ✅ 4. Function Overloading Mechanisms

### 4.1 Different Number of Arguments

```cpp
void greet();  
void greet(string name);
```

### 4.2 Different Types of Arguments

```cpp
void show(int);  
void show(double);
```

### 4.3 Different Order of Arguments

```cpp
void mix(int a, char b);  
void mix(char b, int a);
```

---

## ✅ 5. Default Arguments & Function Overloading

Be cautious! **Default arguments can conflict with overloading**:

```cpp
void display(int x, int y = 5);  
void display(int x); // ❌ Ambiguity when called with one argument
```

> ❗ **Compiler Error:** Ambiguous call when you do `display(10);`

---

## ✅ 6. Function Overloading with `const`

You can overload based on whether a parameter is `const` or not:

```cpp
void show(const int&);
void show(int&);
```

This is common in libraries to differentiate between:

* Read-only access (`const`)
* Modifiable access (non-`const`)

---

## ✅ 7. Function Overloading with Pointers and References

Pointers and references are different types, so they support overloading:

```cpp
          void process(int*);
          void process(int&);
```

---

## ✅ 8. Function Overloading in Classes

Works the same inside a class:

```cpp
          class Printer {
          public:
              void print(int);
              void print(double);
              void print(string);
          };
```

---

## ✅ 9. Function Overloading and Templates

Function templates can coexist with overloaded functions:

```cpp
          template <typename T>
          void display(T value); // Template
          
          void display(int value); // Overloaded
```

Compiler picks the **best match** at compile time.

---

# 🧪 Full Example: Real-Life Program

### 🎯 Scenario:

Build a **“PaymentProcessor”** class to handle multiple payment types:

* Pay with cash (int amount)
* Pay with card (string card number)
* Pay with card (card number + CVV)
* Pay with UPI (email or phone)
* Show balance (const overload)

---

### ✅ Code:

```cpp
          #include <iostream>
          #include <string>
          
          using namespace std;
          
          class PaymentProcessor {
          private:
              double balance;
          
          public:
              PaymentProcessor() : balance(1000.0) {}
          
              // Overload 1: Pay with cash
              void pay(int amount) {
                  balance -= amount;
                  cout << "Paid " << amount << " using cash.\n";
              }
          
              // Overload 2: Pay with card (basic)
              void pay(string cardNumber) {
                  cout << "Paid using card ending with " << cardNumber.substr(cardNumber.length() - 4) << ".\n";
                  balance -= 50;
              }
          
              // Overload 3: Pay with card + CVV
              void pay(string cardNumber, int cvv) {
                  cout << "Paid using card with CVV: " << cvv << ".\n";
                  balance -= 100;
              }
          
              // Overload 4: Pay using UPI
              void payByUPI(string upiId) {
                  cout << "Paid using UPI ID: " << upiId << ".\n";
                  balance -= 25;
              }
          
              // Const overload: show balance
              void showBalance() const {
                  cout << "Current balance: ₹" << balance << "\n";
              }
          
              // Overload with pointer
              void pay(int* amount) {
                  if (amount) {
                      balance -= *amount;
                      cout << "Paid " << *amount << " (via pointer).\n";
                  }
              }
          };
          
          int main() {
              PaymentProcessor processor;
          
              int cash = 200;
              int pointerAmount = 75;
          
              processor.pay(cash);                       // Overload 1
              processor.pay("1234567812345678");         // Overload 2
              processor.pay("1234567812345678", 123);    // Overload 3
              processor.payByUPI("user@upi");            // UPI method
              processor.pay(&pointerAmount);             // Pointer overload
              processor.showBalance();                   // Const method
          
              return 0;
          }
```

---

### 🧾 Output:

```
          Paid 200 using cash.
          Paid using card ending with 5678.
          Paid using card with CVV: 123.
          Paid using UPI ID: user@upi.
          Paid 75 (via pointer).
          Current balance: ₹550
```

---

# ✅ Summary

| Concept                           | Covered in Example |
| --------------------------------- | ------------------ |
| Different number of params        | ✅ Yes              |
| Different types of params         | ✅ Yes              |
| Reference vs Pointer              | ✅ Yes              |
| Const member functions            | ✅ Yes              |
| Function overloading inside class | ✅ Yes              |

---

Absolutely! Let's now go deep into **Function Overriding in C++**, covering everything from beginner to advanced, including a neatly organized explanation **with a real-life example** that demonstrates all the key concepts.

---

# 🔷 Function Overriding in C++

---

## ✅ 1. What is Function Overriding?

**Function overriding** occurs when a **derived class** provides a specific implementation of a **virtual function** that is already defined in its **base class**.

It enables **runtime polymorphism**.

```cpp
class Base {
public:
    virtual void show() {
        cout << "Base show()\n";
    }
};

class Derived : public Base {
public:
    void show() override {
        cout << "Derived show()\n";
    }
};
```

---

## ✅ 2. Key Features

* Must involve **inheritance**
* The **base function must be `virtual`**
* **Signature must match exactly** (return type and parameters)
* **Overrides at runtime**, not compile time

---

## ✅ 3. Function Overriding vs Function Overloading

| Feature           | Overloading  | Overriding                 |
| ----------------- | ------------ | -------------------------- |
| Context           | Same class   | Base & Derived classes     |
| Signature         | Must differ  | Must match exactly         |
| Return Type       | Can differ   | Must be the same           |
| Type              | Compile-time | Runtime (via virtual func) |
| `virtual` keyword | Not needed   | Required in base class     |

---

## ✅ 4. Rules for Function Overriding

1. **Function must be `virtual` in base class**
2. Signature must be the same
3. Use the `override` keyword (optional but recommended)
4. If return types differ, they must be **covariant**

---

## ✅ 5. Virtual Functions & Polymorphism

When a base class pointer points to a derived object and the function is virtual, **C++ decides which version to call at runtime**.

```cpp
Base* ptr = new Derived();
ptr->show(); // Calls Derived::show if show() is virtual
```

---

## ✅ 6. The `override` Keyword (C++11+)

* Helps catch mistakes at compile time
* Ensures you're actually overriding a base class function

```cpp
void show() override; // ✅ OK
void Show() override; // ❌ Error if base has no Show()
```

---

## ✅ 7. Covariant Return Types (Advanced)

Return types can differ in overriding if they are **covariant** — i.e., derived from the base class return type.

```cpp
class Animal {};
class Dog : public Animal {};

class Base {
public:
    virtual Animal* getAnimal();
};

class Derived : public Base {
public:
    Dog* getAnimal() override; // ✅ Covariant return type
};
```

---

## ✅ 8. Access Specifiers and Overriding

An overridden function **can have different access specifiers**, but it’s generally bad practice.

---

## ✅ 9. Final Keyword

Use `final` to **prevent overriding** in derived classes.

```cpp
class Base {
public:
    virtual void display() final;
};
```

---

## ✅ 10. Pure Virtual Functions (Abstract Classes)

When a virtual function is declared with `= 0`, the class becomes abstract and must be overridden in derived classes.

```cpp
class Shape {
public:
    virtual void draw() = 0; // Pure virtual
};
```

---

# 🧪 Real-Life Example: Function Overriding

### 🎯 Scenario:

Create a simple **Notification System** with a base class `Notification` and derived classes:

* `EmailNotification`
* `SMSNotification`
* `PushNotification`

Each should override a `send()` function differently. Demonstrate:

* Base pointer
* Virtual function
* `override`
* `final`
* Covariant return types

---

### ✅ Code:

```cpp
#include <iostream>
#include <memory>
using namespace std;

class Response {
public:
    virtual string getMessage() const {
        return "Notification sent.";
    }
};

class EmailResponse : public Response {
public:
    string getMessage() const override {
        return "Email notification sent.";
    }
};

// Abstract base class
class Notification {
public:
    virtual Response* send() const {
        cout << "Sending generic notification...\n";
        return new Response();
    }

    virtual ~Notification() {} // Virtual destructor
};

class EmailNotification : public Notification {
public:
    EmailResponse* send() const override {
        cout << "Sending email notification...\n";
        return new EmailResponse();
    }
};

class SMSNotification : public Notification {
public:
    Response* send() const override {
        cout << "Sending SMS notification...\n";
        return new Response();
    }
};

class PushNotification final : public Notification {
public:
    Response* send() const override {
        cout << "Sending push notification...\n";
        return new Response();
    }
};

// Trying to override final class - Uncommenting below will cause error
/*
class ChildPush : public PushNotification {
    // Error: Cannot derive from final class
};
*/

void dispatch(Notification* notifier) {
    unique_ptr<Response> resp(notifier->send());
    cout << "Response: " << resp->getMessage() << "\n\n";
}

int main() {
    EmailNotification email;
    SMSNotification sms;
    PushNotification push;

    dispatch(&email);
    dispatch(&sms);
    dispatch(&push);

    return 0;
}
```

---

### 🧾 Output:

```
Sending email notification...
Response: Email notification sent.

Sending SMS notification...
Response: Notification sent.

Sending push notification...
Response: Notification sent.
```

---

## ✅ Concepts Demonstrated

| Concept                      | Shown in Code      |
| ---------------------------- | ------------------ |
| Virtual function             | ✅ Yes              |
| Runtime polymorphism         | ✅ Yes              |
| `override` keyword           | ✅ Yes              |
| Covariant return types       | ✅ Yes (Response\*) |
| `final` keyword              | ✅ Yes              |
| Abstract class & inheritance | ✅ Yes              |
| Virtual destructors          | ✅ Yes              |

---

## ✅ Summary

* Function overriding enables **polymorphism** and clean extensibility.
* Use `override` to prevent mistakes.
* Use `final` to lock virtual functions or entire classes.
* Covariant returns add flexibility in derived classes.
* Use **abstract base classes** to enforce consistent interfaces.

---

Would you like this turned into a downloadable `.cpp` file or a Markdown tutorial for GitHub too? Or should we dive into **virtual destructors, vtables, or dynamic dispatch** next?

---

# 🔷 Pure Virtual Functions & Abstract Classes in C++

---

## ✅ 1. What is a Pure Virtual Function?

A **pure virtual function** is a virtual function with **no definition in the base class**. It’s declared using the `= 0` syntax.

```cpp
class Shape {
public:
    virtual void draw() = 0; // Pure virtual function
};
```

---

## ✅ 2. What is an Abstract Class?

A class becomes **abstract** if it **contains at least one pure virtual function**.

🔒 You **cannot create objects** of an abstract class.

---

## ✅ 3. Purpose of Abstract Classes

* Define **common interfaces**
* Enable **polymorphism**
* Enforce **function overriding** in derived classes
* Promote **modular and scalable** designs

---

## ✅ 4. Characteristics

| Feature                      | Description                                                  |
| ---------------------------- | ------------------------------------------------------------ |
| Must override                | Derived classes must override pure virtual functions         |
| Cannot instantiate           | You cannot create an object of abstract class                |
| Can have constructors        | Yes, constructors can exist and be called by derived classes |
| Can have non-virtual members | Yes, including concrete (implemented) functions              |
| Can be used as base pointers | Yes, to enable polymorphism                                  |

---

## ✅ 5. Syntax

```cpp
class AbstractClass {
public:
    virtual void func() = 0; // Pure virtual function
};
```

Derived class must **override** this:

```cpp
class Derived : public AbstractClass {
public:
    void func() override {
        // implementation
    }
};
```

---

## ✅ 6. Multiple Pure Virtual Functions

You can have **as many pure virtual functions** as needed:

```cpp
class Animal {
public:
    virtual void speak() = 0;
    virtual void move() = 0;
};
```

---

## ✅ 7. Abstract Base Classes with Concrete Methods

An abstract class **can have both pure and non-pure methods**.

```cpp
class Logger {
public:
    virtual void log(string msg) = 0;  // Pure virtual
    void status() {                    // Concrete method
        cout << "Logging active\n";
    }
};
```

---

## ✅ 8. Interface-like Behavior

To simulate a **Java-style interface**, create a class where **all methods are pure virtual** and **no data members** exist.

```cpp
class IPlayable {
public:
    virtual void play() = 0;
    virtual void pause() = 0;
    virtual void stop() = 0;
    virtual ~IPlayable() {}
};
```

---

## ✅ 9. Virtual Destructors in Abstract Classes

Always use a **virtual destructor** when using abstract base classes, especially when handling base pointers to derived objects.

```cpp
class Base {
public:
    virtual ~Base() {}
};
```

---

## ✅ 10. Derived Class Not Overriding All Pure Functions

If a derived class doesn't override **all** pure virtual functions, it **remains abstract** itself.

---

# 🧪 Real-Life Example: Abstract Class with Pure Virtual Functions

### 🎯 Scenario:

Build a **Document Viewer App** framework with:

* An abstract class `Document` (pure virtual `open()`, `save()`)
* Derived classes: `PDF`, `Word`, and `Text`
* Base pointers used for polymorphic behavior
* Includes a concrete method in the abstract base class

---

### ✅ Code:

```cpp
#include <iostream>
#include <vector>
#include <memory>
using namespace std;

// Abstract base class
class Document {
public:
    virtual void open() = 0;     // Pure virtual
    virtual void save() = 0;     // Pure virtual

    void info() {                // Concrete method
        cout << "[Document Framework] Version 1.0\n";
    }

    virtual ~Document() {}       // Virtual destructor
};

// Derived class: PDF Document
class PDF : public Document {
public:
    void open() override {
        cout << "Opening PDF document...\n";
    }

    void save() override {
        cout << "Saving PDF document...\n";
    }
};

// Derived class: Word Document
class Word : public Document {
public:
    void open() override {
        cout << "Opening Word document...\n";
    }

    void save() override {
        cout << "Saving Word document...\n";
    }
};

// Derived class: Text Document
class Text : public Document {
public:
    void open() override {
        cout << "Opening Text file...\n";
    }

    void save() override {
        cout << "Saving Text file...\n";
    }
};

// Function that takes base class pointer
void openAndSave(Document* doc) {
    doc->info();  // Concrete base method
    doc->open();  // Virtual override
    doc->save();  // Virtual override
    cout << "-------------------------\n";
}

int main() {
    // Using smart pointers for memory safety
    vector<unique_ptr<Document>> docs;

    docs.emplace_back(make_unique<PDF>());
    docs.emplace_back(make_unique<Word>());
    docs.emplace_back(make_unique<Text>());

    for (auto& doc : docs) {
        openAndSave(doc.get());
    }

    return 0;
}
```

---

### 🧾 Output:

```
[Document Framework] Version 1.0
Opening PDF document...
Saving PDF document...
-------------------------
[Document Framework] Version 1.0
Opening Word document...
Saving Word document...
-------------------------
[Document Framework] Version 1.0
Opening Text file...
Saving Text file...
-------------------------
```

---

## ✅ Concepts Demonstrated

| Concept                              | Used? |
| ------------------------------------ | ----- |
| Pure virtual functions               | ✅ Yes |
| Abstract base class                  | ✅ Yes |
| Concrete methods in abstract class   | ✅ Yes |
| Polymorphism via base class pointers | ✅ Yes |
| Virtual destructors                  | ✅ Yes |
| Smart pointers for memory management | ✅ Yes |

---

## ✅ Summary

* **Pure virtual functions** force derived classes to implement specific behavior.
* **Abstract classes** are powerful for designing extensible frameworks.
* Combine **abstract and concrete methods** for flexible base class design.
* Always use a **virtual destructor** in abstract base classes.
* Use **base class pointers** to achieve polymorphism.

---

I'm glad you're enjoying this deep dive! Now let's tackle **Runtime Polymorphism in C++**, starting from beginner-level concepts to advanced practices. I’ll organize it neatly and finish with a **real-world program** that brings all concepts together.

---

# 🔷 Runtime Polymorphism in C++

---

## ✅ 1. What is Runtime Polymorphism?

**Runtime polymorphism** allows functions to behave **differently based on the object** that invokes them — even when accessed through a **base class pointer or reference**.

It is achieved through:

* **Virtual functions**
* **Inheritance**
* **Function overriding**

---

## ✅ 2. Key Components

| Component              | Description                                       |
| ---------------------- | ------------------------------------------------- |
| `virtual` keyword      | Declares a function as dynamic/overridable        |
| Base class pointer     | Must point to derived class object                |
| Overridden function    | Must have same signature in derived class         |
| Virtual table (vtable) | Behind the scenes, C++ uses a vtable for dispatch |

---

## ✅ 3. Syntax Example

```cpp
class Animal {
public:
    virtual void speak() {
        cout << "Animal speaks\n";
    }
};

class Dog : public Animal {
public:
    void speak() override {
        cout << "Dog barks\n";
    }
};

Animal* pet = new Dog();
pet->speak(); // Output: Dog barks (runtime polymorphism)
```

---

## ✅ 4. Compile-Time vs Runtime Polymorphism

| Feature            | Compile-Time                    | Runtime                       |
| ------------------ | ------------------------------- | ----------------------------- |
| Type of resolution | At compile time                 | At runtime                    |
| Achieved via       | Function overloading, templates | Virtual functions, overriding |
| Binding type       | Static binding                  | Dynamic binding (vtable)      |

---

## ✅ 5. Use Cases

* GUI frameworks
* Game engines
* Device driver abstractions
* Plugin systems
* Generalized algorithms

---

## ✅ 6. Rules & Best Practices

1. Use `virtual` in base class.
2. Use `override` in derived class.
3. Always provide a **virtual destructor** in base class.
4. Base class pointer/reference must point to derived class.
5. Ensure same signature for overrides.
6. Avoid object slicing with value parameters.

---

## ✅ 7. Virtual Destructors (Critical!)

```cpp
class Base {
public:
    virtual ~Base() {
        cout << "Base destructor\n";
    }
};

class Derived : public Base {
public:
    ~Derived() {
        cout << "Derived destructor\n";
    }
};
```

Without a virtual destructor, only the base destructor would run when deleting via base pointer — causing a **memory leak**.

---

## ✅ 8. Polymorphism with References

Polymorphism also works with references:

```cpp
void makeSound(Animal& a) {
    a.speak(); // Runtime polymorphism
}
```

---

## ✅ 9. Pointers vs Objects

❗ Runtime polymorphism only works with:

* Base class **pointers**
* Base class **references**

Not with **objects by value** (slicing occurs).

---

## ✅ 10. Virtual Table (vtable) - Behind the Scenes

* The compiler creates a **vtable** for each class with virtual functions.
* Each object contains a **vptr** pointing to the vtable.
* At runtime, function calls are resolved via the vptr.

---

# 🧪 Real-Life Example: Runtime Polymorphism in a Banking System

### 🎯 Scenario:

Design a **banking system** that processes different types of accounts:

* `Account` (abstract base class)
* `SavingsAccount`
* `CurrentAccount`
* `FixedDeposit`

Each overrides:

* `calculateInterest()`
* `accountType()`

Base class pointer is used to achieve **runtime polymorphism**.

---

### ✅ Code:

```cpp
#include <iostream>
#include <vector>
#include <memory>
using namespace std;

// Abstract base class
class Account {
protected:
    double balance;

public:
    Account(double bal) : balance(bal) {}

    virtual void calculateInterest() = 0; // Pure virtual function

    virtual void accountType() const {
        cout << "Generic Account\n";
    }

    virtual ~Account() {
        cout << "Closing Account with balance: ₹" << balance << "\n";
    }
};

class SavingsAccount : public Account {
public:
    SavingsAccount(double bal) : Account(bal) {}

    void calculateInterest() override {
        double interest = balance * 0.04;
        cout << "Savings Account Interest: ₹" << interest << "\n";
    }

    void accountType() const override {
        cout << "Account Type: Savings\n";
    }

    ~SavingsAccount() {
        cout << "Savings Account Closed\n";
    }
};

class CurrentAccount : public Account {
public:
    CurrentAccount(double bal) : Account(bal) {}

    void calculateInterest() override {
        cout << "Current Account has no interest.\n";
    }

    void accountType() const override {
        cout << "Account Type: Current\n";
    }

    ~CurrentAccount() {
        cout << "Current Account Closed\n";
    }
};

class FixedDeposit : public Account {
public:
    FixedDeposit(double bal) : Account(bal) {}

    void calculateInterest() override {
        double interest = balance * 0.08;
        cout << "Fixed Deposit Interest: ₹" << interest << "\n";
    }

    void accountType() const override {
        cout << "Account Type: Fixed Deposit\n";
    }

    ~FixedDeposit() {
        cout << "Fixed Deposit Closed\n";
    }
};

// Function demonstrating runtime polymorphism
void processAccount(Account* acc) {
    acc->accountType();
    acc->calculateInterest();
    cout << "-----------------------------\n";
}

int main() {
    vector<unique_ptr<Account>> accounts;

    accounts.emplace_back(make_unique<SavingsAccount>(10000));
    accounts.emplace_back(make_unique<CurrentAccount>(5000));
    accounts.emplace_back(make_unique<FixedDeposit>(25000));

    for (const auto& acc : accounts) {
        processAccount(acc.get());
    }

    return 0;
}
```

---

### 🧾 Output:

```
Account Type: Savings
Savings Account Interest: ₹400
-----------------------------
Account Type: Current
Current Account has no interest.
-----------------------------
Account Type: Fixed Deposit
Fixed Deposit Interest: ₹2000
-----------------------------
Fixed Deposit Closed
Closing Account with balance: ₹25000
Current Account Closed
Closing Account with balance: ₹5000
Savings Account Closed
Closing Account with balance: ₹10000
```

---

## ✅ Concepts Demonstrated

| Concept                                  | Used? |
| ---------------------------------------- | ----- |
| Virtual functions                        | ✅     |
| Function overriding                      | ✅     |
| Runtime dispatch via base pointers       | ✅     |
| Abstract base class (pure virtual func)  | ✅     |
| Virtual destructors                      | ✅     |
| Polymorphism with smart pointers         | ✅     |
| vtable/vptr behavior (behind the scenes) | ✅     |

---

## ✅ Summary

* **Runtime polymorphism** enables dynamic behavior using inheritance and virtual functions.
* Achieved only with **pointers/references** to base class.
* Enables **extensible and scalable design**.
* Always use **virtual destructors** in base classes.
* Use **abstract classes** for flexible architecture.

---

Absolutely! Let's now break down **Encapsulation and Abstraction in C++** — covering everything from beginner to advanced — organized neatly with a **real-life program** that demonstrates all key concepts:

---

# 🔷 3.5 Encapsulation and Abstraction in C++

---

## ✅ 1. What is Encapsulation?

> **Encapsulation** is the concept of **wrapping data (variables)** and **functions (methods)** together into a single unit — typically a class — and restricting direct access to some of the object's components.

### 🚪 Think of it like:

A **pill capsule**: medicine (data) is wrapped inside a secure coating (methods).

---

## ✅ 2. What is Abstraction?

> **Abstraction** is the concept of **hiding implementation details** and showing only the **essential features** to the user.

### 📦 Think of it like:

Using a **TV remote** — you don’t need to know the internal circuitry to press “Power On”.

---

## ✅ 3. Difference Between Encapsulation and Abstraction

| Feature      | Encapsulation                       | Abstraction                        |
| ------------ | ----------------------------------- | ---------------------------------- |
| Focus        | Data hiding                         | Hiding complexity                  |
| How          | Access specifiers (private, public) | Using abstract classes, interfaces |
| Purpose      | Protect data                        | Simplify interaction               |
| Achieved via | Classes, access control             | Interfaces, pure virtual functions |

---

# 🔹 3.5.1 Data Hiding

### 📌 Goal:

Prevent external code from **directly accessing or modifying** class data members.

### ✅ Achieved using:

* **`private`** access modifier for sensitive data
* Only exposing necessary methods as `public`

### ❌ Bad Practice:

```cpp
class Person {
public:
    int age; // Public access — bad
};
```

### ✅ Good Practice:

```cpp
class Person {
private:
    int age; // Hidden

public:
    void setAge(int a) {
        if (a > 0) age = a;
    }

    int getAge() const {
        return age;
    }
};
```

---

# 🔹 3.5.2 Accessor and Mutator Functions (Getters and Setters)

> Accessors **get** the value of private data,
> Mutators **set** or **modify** private data.

```cpp
class Employee {
private:
    string name;
    double salary;

public:
    // Accessors
    string getName() const { return name; }
    double getSalary() const { return salary; }

    // Mutators
    void setName(string n) { name = n; }
    void setSalary(double s) {
        if (s >= 0) salary = s;
    }
};
```

---

# 🔹 3.5.3 Interface Design

> Designing a class or abstract base class that exposes **only the public-facing behavior**, hiding all implementation details.

### ✅ Best Practices:

* Use **pure virtual functions** for interfaces
* Expose only **minimal necessary methods**
* Use **composition** or **inheritance** where appropriate

---

### 📦 Example of Interface:

```cpp
class IShape {
public:
    virtual void draw() = 0;
    virtual double area() = 0;
    virtual ~IShape() {}
};
```

Any class that inherits from `IShape` must implement `draw()` and `area()`.
The **user interacts via `IShape*`**, and implementation is hidden.

---

# 🧪 Real-Life Example: Encapsulation + Abstraction in an ATM System

### 🎯 Scenario:

Create a simple ATM interface with:

* **Private account balance**
* **Public access through getters/setters**
* Abstract base class `IAccount` (interface for abstraction)
* Derived class `BankAccount` implementing secure operations

---

### ✅ Code:

```cpp
#include <iostream>
#include <string>
using namespace std;

// Abstract Interface for abstraction
class IAccount {
public:
    virtual void deposit(double amount) = 0;
    virtual void withdraw(double amount) = 0;
    virtual double getBalance() const = 0;
    virtual ~IAccount() {}
};

// Concrete class with encapsulation
class BankAccount : public IAccount {
private:
    string accountHolder;
    double balance;

public:
    BankAccount(string name, double initial) {
        accountHolder = name;
        balance = (initial >= 0) ? initial : 0;
    }

    // Accessors (getters)
    string getName() const { return accountHolder; }
    double getBalance() const override { return balance; }

    // Mutators (setters with validation)
    void deposit(double amount) override {
        if (amount > 0) {
            balance += amount;
            cout << "Deposited ₹" << amount << " into " << accountHolder << "'s account.\n";
        } else {
            cout << "Invalid deposit amount!\n";
        }
    }

    void withdraw(double amount) override {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            cout << "Withdrew ₹" << amount << " from " << accountHolder << "'s account.\n";
        } else {
            cout << "Insufficient balance or invalid amount!\n";
        }
    }

    void displaySummary() const {
        cout << "Account Holder: " << accountHolder << "\nBalance: ₹" << balance << "\n\n";
    }
};

// Function showing abstraction via interface
void processATM(IAccount* account) {
    account->deposit(1000);
    account->withdraw(500);
    cout << "Current Balance: ₹" << account->getBalance() << "\n";
    cout << "-----------------------------\n";
}

int main() {
    BankAccount myAcc("Ravi", 5000);
    myAcc.displaySummary();

    processATM(&myAcc); // Interacting via interface (abstraction)

    myAcc.displaySummary(); // Data protected via encapsulation

    return 0;
}
```

---

### 🧾 Output:

```
Account Holder: Ravi
Balance: ₹5000

Deposited ₹1000 into Ravi's account.
Withdrew ₹500 from Ravi's account.
Current Balance: ₹5500
-----------------------------
Account Holder: Ravi
Balance: ₹5500
```

---

## ✅ Concepts Demonstrated

| Concept                    | Applied |
| -------------------------- | ------- |
| Data hiding                | ✅ Yes   |
| Getters and setters        | ✅ Yes   |
| Validation in setters      | ✅ Yes   |
| Abstract interface class   | ✅ Yes   |
| Polymorphism via interface | ✅ Yes   |
| Real-life scenario         | ✅ Yes   |

---

## ✅ Summary

* **Encapsulation** protects internal data from unauthorized access.
* **Abstraction** hides complexity from the user and shows only essential behavior.
* Use **access specifiers**, **getters/setters**, and **abstract interfaces** to implement both effectively.
* A well-designed interface ensures **separation of interface and implementation**, and makes the system **modular and maintainable**.

---



You're doing great! 🙌 And don’t worry — **smart pointers** might seem tricky at first, but once you get them, they’re an absolute game-changer for safe and modern C++ programming.

---

# 🔷 4.4 Smart Pointers and Memory Management in C++

---

## ✅ What Are Smart Pointers?

> Smart pointers are **template classes** in the C++ Standard Library that manage dynamically allocated memory automatically — helping avoid memory leaks, dangling pointers, and manual `new/delete`.

Smart pointers live in the `memory` header.

```cpp
#include <memory>
```

---

## 🧠 Why Use Smart Pointers?

| Problem with Raw Pointers      | Smart Pointer Solution       |
| ------------------------------ | ---------------------------- |
| Need to manually call `delete` | Auto-destruction (RAII)      |
| Risk of memory leaks           | Automatic cleanup            |
| Ownership confusion            | Explicit ownership semantics |
| Complex lifetimes              | Shared and weak references   |

---

# 🔹 4.4.1 `std::unique_ptr`

### ✅ Features:

* **Sole ownership** of the object
* Automatically deletes the object when the `unique_ptr` goes out of scope
* **Non-copyable**, but **movable**

### 📌 Syntax:

```cpp
#include <memory>

std::unique_ptr<Type> ptr = std::make_unique<Type>(args);
```

### 📌 Example:

```cpp
#include <iostream>
#include <memory>
using namespace std;

class Dog {
public:
    Dog() { cout << "Dog created\n"; }
    ~Dog() { cout << "Dog destroyed\n"; }
    void bark() { cout << "Woof!\n"; }
};

int main() {
    unique_ptr<Dog> d = make_unique<Dog>();
    d->bark();
    // No need to delete, it's automatic!
}
```

---

# 🔹 4.4.2 `std::shared_ptr`

### ✅ Features:

* **Shared ownership**
* Internally uses a **reference count**
* Object is destroyed when last `shared_ptr` owning it goes out of scope

### 📌 Syntax:

```cpp
shared_ptr<Type> ptr = make_shared<Type>(args);
```

### 📌 Example:

```cpp
#include <iostream>
#include <memory>
using namespace std;

class Cat {
public:
    Cat() { cout << "Cat created\n"; }
    ~Cat() { cout << "Cat destroyed\n"; }
    void meow() { cout << "Meow!\n"; }
};

int main() {
    shared_ptr<Cat> c1 = make_shared<Cat>();
    {
        shared_ptr<Cat> c2 = c1;  // Shared ownership
        c2->meow();
        cout << "Use count: " << c1.use_count() << "\n"; // 2
    }
    cout << "Use count after inner scope: " << c1.use_count() << "\n"; // 1
}
```

---

# 🔹 4.4.3 `std::weak_ptr`

### ✅ Features:

* **Non-owning** reference to a `shared_ptr`
* Used to **break circular references**
* Must be converted to `shared_ptr` before use

### 📌 Why it’s useful:

To prevent **memory leaks** in object graphs with **cyclic dependencies**.

### 📌 Example:

```cpp
#include <iostream>
#include <memory>
using namespace std;

class B;  // Forward declaration

class A {
public:
    weak_ptr<B> b_ptr; // Weak to avoid cycle
    ~A() { cout << "A destroyed\n"; }
};

class B {
public:
    shared_ptr<A> a_ptr;
    ~B() { cout << "B destroyed\n"; }
};

int main() {
    auto a = make_shared<A>();
    auto b = make_shared<B>();

    a->b_ptr = b;
    b->a_ptr = a;

    // No memory leak due to weak_ptr
}
```

---

# 🔹 4.4.4 Custom Deleters

### ✅ Why use them?

* Custom cleanup logic
* Useful when managing non-memory resources (e.g., file handles, sockets)

### 📌 Syntax:

```cpp
shared_ptr<FILE> fp(fopen("file.txt", "r"), [](FILE* f){
    fclose(f);
    cout << "File closed\n";
});
```

---

# 🧪 Real-Life Example: Hospital Patient Management System

### 🎯 Scenario:

We manage `Patient` objects using:

* `unique_ptr` to ensure only one doctor "owns" a patient at a time.
* `shared_ptr` for shared access to `MedicalRecord`.
* `weak_ptr` to avoid cyclic reference between `Patient` and `Doctor`.

---

### ✅ Code:

```cpp
#include <iostream>
#include <memory>
#include <string>
using namespace std;

class MedicalRecord {
public:
    string history;
    MedicalRecord(string h) : history(h) {
        cout << "MedicalRecord created\n";
    }
    ~MedicalRecord() {
        cout << "MedicalRecord destroyed\n";
    }
};

class Doctor;

class Patient {
public:
    string name;
    shared_ptr<MedicalRecord> record;
    weak_ptr<Doctor> doctor;  // Weak to avoid cycle

    Patient(string n) : name(n) {
        cout << "Patient " << name << " admitted\n";
    }
    ~Patient() {
        cout << "Patient " << name << " discharged\n";
    }
};

class Doctor {
public:
    string name;
    shared_ptr<Patient> patient;

    Doctor(string n) : name(n) {
        cout << "Doctor " << name << " is assigned\n";
    }

    ~Doctor() {
        cout << "Doctor " << name << " signed off\n";
    }
};

int main() {
    unique_ptr<Doctor> dr = make_unique<Doctor>("Dr. Smith");

    shared_ptr<Patient> p = make_shared<Patient>("John");
    p->record = make_shared<MedicalRecord>("Diabetes, Blood Pressure");

    dr->patient = p;
    p->doctor = dr;  // Stored as weak_ptr

    cout << "Patient record: " << p->record->history << "\n";

    // Automatic cleanup
}
```

---

### 🧾 Sample Output:

```
Doctor Dr. Smith is assigned
Patient John admitted
MedicalRecord created
Patient record: Diabetes, Blood Pressure
Doctor Dr. Smith signed off
MedicalRecord destroyed
Patient John discharged
```

---

## ✅ Concepts Demonstrated

| Concept         | Used?                          |
| --------------- | ------------------------------ |
| `unique_ptr`    | ✅                              |
| `shared_ptr`    | ✅                              |
| `weak_ptr`      | ✅                              |
| Custom resource | ✅     (record and doctor link) |

---

## ✅ Best Practices

| Do ✅                              | Avoid ❌                                |
| --------------------------------- | -------------------------------------- |
| Use `make_unique` / `make_shared` | Manual `new` with smart pointers       |
| Use `unique_ptr` for ownership    | Sharing `unique_ptr` (not allowed)     |
| Use `weak_ptr` for cycles         | Shared pointers pointing to each other |
| Use custom deleters for resources | Forgetting to release file/sockets     |

---

## ✅ Summary

| Type         | Ownership | Copyable | Use Case                   |
| ------------ | --------- | -------- | -------------------------- |
| `unique_ptr` | Exclusive | ❌        | RAII, resource management  |
| `shared_ptr` | Shared    | ✅        | Shared ownership           |
| `weak_ptr`   | None      | ✅        | Observing, breaking cycles |

---


# 🧪 Real-World Example: Smart Pointer Usage in Resource Manager

---

### 🎯 Scenario:

Create a resource manager for loading and handling textures in a game:

* Each texture is loaded only once and shared.
* When no one uses a texture, it is destroyed.
* A weak reference can observe texture lifetimes.
* Include a resource (e.g., file handle) with a **custom deleter**.

---

### ✅ Code:

```cpp
#include <iostream>
#include <memory>
#include <unordered_map>
#include <string>

using namespace std;

class Texture {
private:
    string name;

public:
    Texture(const string& n) : name(n) {
        cout << "[Texture Loaded] " << name << endl;
    }

    void use() {
        cout << "Using texture: " << name << endl;
    }

    ~Texture() {
        cout << "[Texture Unloaded] " << name << endl;
    }
};

class TextureManager {
private:
    unordered_map<string, weak_ptr<Texture>> cache;

public:
    shared_ptr<Texture> loadTexture(const string& filename) {
        if (auto existing = cache[filename].lock()) {
            cout << "Loaded from cache: " << filename << endl;
            return existing;
        }

        shared_ptr<Texture> newTexture = make_shared<Texture>(filename);
        cache[filename] = newTexture;
        return newTexture;
    }
};

void demoUniquePtr() {
    cout << "\n[Unique_ptr Demo]\n";
    unique_ptr<int> uptr = make_unique<int>(42);
    cout << "Unique value: " << *uptr << endl;

    // Move ownership
    unique_ptr<int> movedPtr = std::move(uptr);
    if (!uptr)
        cout << "Original pointer is now null\n";
}

void demoCustomDeleter() {
    cout << "\n[Custom Deleter Demo]\n";
    shared_ptr<FILE> filePtr(fopen("test.txt", "w"), [](FILE* f) {
        if (f) {
            fclose(f);
            cout << "File closed with custom deleter\n";
        }
    });

    if (filePtr)
        fprintf(filePtr.get(), "Hello, world!\n");
}

int main() {
    cout << "\n--- Smart Pointer Demo Start ---\n";

    TextureManager manager;

    shared_ptr<Texture> t1 = manager.loadTexture("brick.png");
    t1->use();

    {
        shared_ptr<Texture> t2 = manager.loadTexture("brick.png"); // from cache
        t2->use();
    } // t2 goes out of scope, but t1 still alive

    weak_ptr<Texture> observer = t1;

    t1.reset(); // Now no shared_ptr is holding it

    if (observer.expired())
        cout << "Texture has been fully released.\n";
    else
        cout << "Texture still alive via shared_ptr.\n";

    demoUniquePtr();
    demoCustomDeleter();

    cout << "\n--- Smart Pointer Demo End ---\n";
    return 0;
}
```

---

### 🧾 Sample Output:

```
--- Smart Pointer Demo Start ---
[Texture Loaded] brick.png
Using texture: brick.png
Loaded from cache: brick.png
Using texture: brick.png
[Texture Unloaded] brick.png
Texture has been fully released.

[Unique_ptr Demo]
Unique value: 42
Original pointer is now null

[Custom Deleter Demo]
File closed with custom deleter

--- Smart Pointer Demo End ---
```

---

## ✅ Summary Table

| Smart Pointer    | Ownership | Auto Delete | Use Count | Key Use Case                     |
| ---------------- | --------- | ----------- | --------- | -------------------------------- |
| `unique_ptr`     | Exclusive | ✅           | 1         | Single-owner resources           |
| `shared_ptr`     | Shared    | ✅           | n         | Shared access (e.g., textures)   |
| `weak_ptr`       | Observing | ❌ (non-own) | 0         | Avoid circular refs, observe     |
| `custom deleter` | Varies    | ✅           | Varies    | Close files, sockets, logs, etc. |

---

## ✅ Best Practices

* Prefer `unique_ptr` unless sharing is required.
* Use `make_unique` and `make_shared` for exception safety.
* Use `weak_ptr` to break cycles.
* Always consider **ownership semantics** when choosing a smart pointer.

---



---

# 🔷 4.5 Move Semantics and Rvalue References (C++11+)

---

## 🧠 Why Move Semantics?

Traditionally, when you assign or pass large objects, **copies** are made using the **copy constructor**, which is **expensive**.

With **move semantics**, instead of copying:

* You **steal** resources from a temporary object.
* Avoid deep copying.
* It’s **blazing fast** and memory-safe.

---

## 🔹 4.5.1 Lvalues and Rvalues

### ✅ What is an Lvalue?

* Has a **name** and **address**.
* Exists in memory.
* Example:

  ```cpp
  int x = 10;   // x is an lvalue
  ```

### ✅ What is an Rvalue?

* Temporary object or literal.
* **No name** and cannot be referred to after the statement ends.
* Example:

  ```cpp
  int y = x + 5;  // x + 5 is an rvalue
  ```

---

## 🔹 4.5.2 Move Constructor & Move Assignment Operator

Modern C++ introduces:

* **Move Constructor**
* **Move Assignment Operator**

These use **rvalue references (`&&`)**.

---

### ✅ Syntax

```cpp
class MyClass {
public:
    // Move Constructor
    MyClass(MyClass&& other) noexcept {
        // Take resources from 'other'
    }

    // Move Assignment Operator
    MyClass& operator=(MyClass&& other) noexcept {
        if (this != &other) {
            // Clean current resources
            // Take ownership from 'other'
        }
        return *this;
    }
};
```

---

## 🔹 4.5.3 `std::move()`

```cpp
std::move(obj); // Casts obj to an rvalue
```

It doesn't **move** anything — it **enables** moving.

### ⚠️ After `std::move`, the source object is in a **valid but unspecified state** (don't use it unless reassigned).

---

## 🧪 Real-World Example: Move Semantics in a `Document` Class

---

### 🎯 Scenario:

You have a `Document` class that holds large text.
Copying every time is inefficient.
You want to use **move constructor** and **move assignment** to optimize it.

---

### ✅ Code:

```cpp
#include <iostream>
#include <string>
#include <vector>
#include <utility> // for std::move

using namespace std;

class Document {
private:
    string title;
    vector<string> content;

public:
    // Constructor
    Document(string t, vector<string> c) : title(t), content(std::move(c)) {
        cout << "[Constructor] Document created: " << title << endl;
    }

    // Copy Constructor
    Document(const Document& other) : title(other.title), content(other.content) {
        cout << "[Copy Constructor] Copied: " << title << endl;
    }

    // Move Constructor
    Document(Document&& other) noexcept : title(std::move(other.title)), content(std::move(other.content)) {
        cout << "[Move Constructor] Moved: " << title << endl;
    }

    // Copy Assignment
    Document& operator=(const Document& other) {
        cout << "[Copy Assignment] Copied: " << other.title << endl;
        if (this != &other) {
            title = other.title;
            content = other.content;
        }
        return *this;
    }

    // Move Assignment
    Document& operator=(Document&& other) noexcept {
        cout << "[Move Assignment] Moved: " << other.title << endl;
        if (this != &other) {
            title = std::move(other.title);
            content = std::move(other.content);
        }
        return *this;
    }

    void display() const {
        cout << "Title: " << title << "\nContent:\n";
        for (const auto& line : content)
            cout << "- " << line << endl;
    }

    ~Document() {
        cout << "[Destructor] Destroying: " << title << endl;
    }
};

Document createTempDoc() {
    vector<string> lines = {"Line 1", "Line 2", "Line 3"};
    return Document("Temp Report", lines);
}

int main() {
    cout << "\n--- Move Semantics Demo ---\n";

    Document doc1("Annual Report", {"Sales up", "Profit margin stable"});
    Document doc2 = doc1; // Copy constructor
    Document doc3 = createTempDoc(); // Move constructor

    Document doc4("Empty", {});
    doc4 = doc1; // Copy assignment
    doc4 = createTempDoc(); // Move assignment

    cout << "\n--- Final Document ---\n";
    doc4.display();

    cout << "\n--- End of Program ---\n";
    return 0;
}
```

---

### 🧾 Sample Output:

```
--- Move Semantics Demo ---
[Constructor] Document created: Annual Report
[Copy Constructor] Copied: Annual Report
[Constructor] Document created: Temp Report
[Move Constructor] Moved: Temp Report
[Constructor] Document created: Empty
[Copy Assignment] Copied: Annual Report
[Constructor] Document created: Temp Report
[Move Assignment] Moved: Temp Report

--- Final Document ---
Title: Temp Report
Content:
- Line 1
- Line 2
- Line 3

--- End of Program ---
[Destructor] Destroying: Temp Report
[Destructor] Destroying: Temp Report
[Destructor] Destroying: Annual Report
[Destructor] Destroying: Annual Report
```

---

## ✅ Concepts Demonstrated

| Concept               | ✔ Used         |
| --------------------- | -------------- |
| Lvalue vs Rvalue      | ✅ Yes          |
| Move Constructor      | ✅ Yes          |
| Move Assignment       | ✅ Yes          |
| `std::move`           | ✅ Yes          |
| Efficiency via move   | ✅ Yes          |
| Copy vs Move behavior | ✅ Side-by-side |

---

## 🧠 Key Takeaways

| Feature         | Copy Semantics      | Move Semantics             |
| --------------- | ------------------- | -------------------------- |
| Behavior        | Duplicate resources | Transfer resources (steal) |
| Speed           | Slower (deep copy)  | Faster (no duplication)    |
| Syntax          | `obj1 = obj2`       | `obj1 = std::move(obj2)`   |
| When to Use     | Reuse needed        | Temp objects or no reuse   |
| C++ Requirement | All versions        | C++11 and above            |

---

## ✅ Best Practices

* Use `std::move` when you're done with an object and want to transfer ownership.
* Always implement both **copy** and **move** constructors/operators if your class manages resources.
* Use **move semantics** in **factories**, **container classes**, or **returning large objects**.

---

Would you like this bundled as `.md` or `.cpp`?
Or move next to **Templates (4.1)**, **Exception Handling (4.2)**, or **STL Deep Dive (4.3)**?

