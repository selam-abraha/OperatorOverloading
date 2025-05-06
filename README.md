# OperatorOverloading
This project implements arbitrary-precision integer arithmetic using dynamically allocated character arrays. It mimics built-in integer behavior by overloading arithmetic and comparison operators. It's designed for handling very large numbers that exceed native data type limits.

## Features
- Arbitrary size integer stored using char
- Overloaded "==", "!=", "+", "-", "=", "++", "+="
- Deep Copy with safe memory handling

### Example
```cpp
#include <iostream>
#include "bigNum.h"

using namespace std;

int main(){
  bigNum number1("12345678910110");
  bigNum number2(10);
  bigNum sum = number1 + number2;
  cout<<sum<<endl;
}
