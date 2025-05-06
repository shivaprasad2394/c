What Are Variables?
-------------------

          A variable is a named storage in memory to hold a value. Think of it as a labeled box.
          int age = 25;

This declares a variable named age of type int (integer), and stores the value 25 in it.


Basic Data Types in C++
Type	Size	Description
int	4 bytes	Whole numbers
float	4 bytes	Numbers with decimal points
double	8 bytes	More precise decimal numbers
char	1 byte	A single character ('a')
bool	1 byte	Boolean values (true/false)
void	—	No value (used in functions)

🛠 Example: Declaring Different Types
cpp
Copy
Edit
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
Uninitialized variables: using variables before assigning a value can lead to garbage output.

Incorrect type assignments:

cpp
Copy
Edit
int x = 3.5; // OK but will truncate to 3
🧠 Interview Tip
Understanding data types is foundational. Interviewers may ask:

Memory sizes and ranges (e.g. range of int)

Type conversions (implicit and explicit)

🧪 Mini Practice Task
Can you write a small program that:

Stores your name (string), age (int), height (float)

Prints them all nicely formatted?

