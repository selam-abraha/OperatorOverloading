
#include <iostream>
#include <string.h>
using namespace std;

class bigNum {
    char* digits;
    int length;
    string disp_mode;
    bool invalidNumber;
    void adjustSize(int size);
public:
    void setMode(string mode);
    bigNum();
    bigNum(string number);
    bigNum(unsigned long int);
    bigNum(const bigNum& original);
    ~bigNum();
    friend ostream& operator<<(ostream&,const bigNum&);
    friend istream& operator>>(istream&, bigNum&);
    bool operator==(const bigNum&);
    bool operator!=(const bigNum&);
    bigNum operator+( bigNum&);
    bigNum operator-(bigNum&);
    bigNum operator=(const bigNum&);
    bigNum operator++();
    bigNum operator++(int);
    bigNum operator+=(bigNum&);
    bigNum operator-=(bigNum&);
    bigNum operator()(int);
};
/*
* adjustSize: this function will be given a size and it will
extend the digit array to be desired length
* parameters: the size that we I want my digits to be
extended to. it will add extra 0s in the front of digits
*/
void bigNum::adjustSize(int size) {
    if (size > length) {//we want to add extra zeros to make two numbers same length
        bigNum temp;
        temp.digits = new char[size];//temporary holder that is size
        for (int i = 0; i < size - length; i++) {
            temp.digits[i] = '0';
            //if size is 4 and digit length is 2, it will fill first two spots with 0
        }
        int j = 0;
        for (int i = size - length; i < size; i++) {
            temp.digits[i] = digits[j];
            j += 1;
            if (j == length)
                break;
            //this will fill the remaining digits with actual digits
        }
        if (digits != NULL) {//deallocate digits before overwriting the information
            delete[]digits;
            digits = NULL;
        }
        digits = new char[size];//allocating memory
        length = size;
        for (int i = 0; i < size; i++) {//copying from temporary array back to original array
            digits[i] = temp.digits[i];
        }
        if (temp.digits != NULL) {//deallocating temporary holder
            delete[]temp.digits;
            temp.digits = NULL;
        }
    }
    if (size == 0) {//this will be used to remove trailing zeros
        int counter=0;//this will count how many 0s we have
	    string hold;//this will hold the digits so that we can use erase
	    for(int i=0; i<length; i++){
	        hold += digits[i];//copying into string
	    }
        for (int i = 0; i < length; i++) {
                if (digits[i] == '0')
                    counter += 1;//counting how many 0s we have
        }
        hold.erase(0, counter);
	    delete[] digits;//deallocate
	    digits = new char[length-counter];//allocate
	    length-=counter;//update length
	    for(int i=0; i<length; i++){
	        digits[i]=hold[i];//updating digits
	    }
    }
}
/*
* setMode: this will set the display mode to decimal or scientific
* parameters: the mode that we want the objects to be
*/
void bigNum::setMode(string mode) {
    if (mode == "decimal") {//setting mode to decimal
        // cout<<"setting display mode to decimal"<<endl;
        this->disp_mode = "decimal";
    }
    if (mode == "scientific") {//setting mode to scientific
        // cout<<"setting display mode to scientific"<<endl;
        this->disp_mode = "scientific";
    }
}
/*
* bigNum(): this is the default constructor it sets digits pointer to
NULL and length to 1
*/
bigNum::bigNum() {
    digits = NULL;
    this->setMode("decimal");
    this->length = 1;
    invalidNumber=false;
}
/*
* bigNum(string): this constructor takes a string and stores it into digits
* parameters: the number we want to be stored into digits
* return value: what the function returns, if any
*/
bigNum::bigNum(string number) {
    length = number.length();
    digits = new char[length];
    for (int i = 0; i < length; i++) {//saving the string into digits
        digits[i] = number[i];
    }
    invalidNumber = false;
}
/*
* bigNum(unsigned long int): this constructor takes an unsigned long int
and saves it into the object's digit.
* parameters: the unsigned long int we want to save
*/
bigNum::bigNum(unsigned long int number) {
    string sNumber = to_string(number);//change the number to string
    length = sNumber.length();
    digits = new char[length];
    for (int i = 0; i < length; i++) {
        digits[i] = sNumber[i];//saving the passed number into digits
    }
    invalidNumber = false;
}
/*
* bigNum(const bigNum&): this is the copy constructor. It will run when we
have a new object of type bigNum and we set it equal to an existing object
* parameters: the object that we are trying to copy
*/
bigNum::bigNum(const bigNum& original) {
    //in this function we copy from original object to current object
    length = original.length;
    digits = new char[length];
    for (int i = 0; i < length; i++) {
        digits[i] = original.digits[i];
    }
    invalidNumber = original.invalidNumber;
    disp_mode = original.disp_mode;
}
/*
* ~bigNum: this is going to run at the end and it will deallocate memory
of pointers being used
*/
bigNum::~bigNum() {
    if (digits != NULL) {//deallocting memory
        delete[]digits;
        digits = NULL;
    }
}
/*
* operator==: this function will compare two objects and evaluate true
if they are equal and false if they are not equal.
* parameters: the object we want to compare to
* return value: true/false depending on if they are equal or not
*/
bool bigNum::operator==(const bigNum& num) {
    if (strcmp(digits, num.digits) == 0) {//will equal 0 if they are equal
        return true;
    }
    else {
        return false;
    }
}
/*
* operator!=: this function will compare two objects and evaluate true
if they are not equal and false if they are equal.
* parameters: the object we want to compare to
* return value: true/false depending on if they are equal or not
*/
bool bigNum::operator!=(const bigNum& num) {
    if (*this == num) {//using overloaded == to check.
        //if we enter this if statemnet it means the two objects are equal
        return false;
    }
    else {
        return true;
    }
}
/*
* operator+: this function will go character by character and add the
digits of the the two objects (accoring to their index)
* parameters: object being added to the calling object's digits
* return value: an object that holds sum of the two objects digits
*/
bigNum bigNum::operator+(bigNum& number) {
    bigNum temp;//this is going to hold the sum of two numbers
    int holder = 0;//this is going to hold the sum of the two digits at index i
    int carry = 0;//this is going to be used if holder is >9
    int size = 0;//this is going to be used to adjust the size of the two digits
    if (length > number.length) {
        size = length;
        number.adjustSize(size);//if number2 is shorter, we fill it with 0s
    }
    else if (length < number.length) {
        size = number.length;
        adjustSize(size);//if number1 is shorter, we fill it with 0s
    }
    else if (length = number.length) {
        size = length;
    }

    bigNum num1 = *this;//creating a copy of number1 so that I don't alter original
    bigNum num2 = number;//copy of number2

    temp.digits = new char[size];
    temp.length = size;
    for (int i = size - 1; i >= 0; i--) {//since index starts at 0 and goes to size-1
        //adding the two chars at index i and carry (if there is one)
        holder = ((int)num1.digits[i] - 48) + ((int)num2.digits[i] - 48) + carry;
        carry = 0;//resetting so that carry is not one after we already add it in
        if (holder > 9) {
            holder -= 10;
            carry = 1;
        }
        temp.digits[i] = static_cast<char> (holder + 48);
        if (i == 0 && carry == 1) {//if we reach 0 and carry is 1 we need a larger array
            bigNum temp2;
            temp2.length = size + 1;//this array will be one size larger to include the carry
            int j = size - 1;
            for (int i = size; i > 0; i--) {//copying into our new array
                temp2.digits[i] = temp.digits[j];
                if (j = 0)
                    break;
            }
            temp2.digits[0] = static_cast<char> (carry + 48);
            delete[] temp.digits;//no need to check if temp is NULL
            temp = temp2;//same process as the above for loop except using = operator
            delete[] temp2.digits;//deallocating
        }
    }
    if (num1.digits != NULL) {//deallocating copy of number1
        delete[] num1.digits;
        num1.digits = NULL;
    }
    if (num2.digits != NULL) {//deallocating copy of number2
        delete[] num2.digits;
        num2.digits = NULL;
    }
    return temp;
}
/*
* operator-: this function will subtract the the two given objects' digits
* parameters: the object that is subtracting
* return value: an object that has the difference of number1 and number2
*/
bigNum bigNum::operator-(bigNum& number) {
    bigNum temp;//this will be holding their difference
    bigNum num1 = *this;//making a copy of number1 so that I don't alter num1
    bigNum num2 = number;//making a copy of number2 so that I don't alter num2
    int size = 0;
    int holder = 0;
    int borrow = 0;//used in the case that num2's digit is larger than num1's
    if (length > number.length) {
        size = length;
        number.adjustSize(size);//adding extra 0s to number so that it is the same size
    }
    else if (length < number.length) {
        size = number.length;//making them same size
        adjustSize(size);
    }
    else if (length = number.length) {
        size = length;
    }
    temp.digits = new char[size];
    temp.length = size;
    if (strcmp(num1.digits, num2.digits) >= 0) {//either num1 and num2 are equal or num1>num2
        for (int i = size - 1; i >= 0; i--) {
            if (((int)num1.digits[i] - 48) >= ((int)num2.digits[i] - 48)) {
                holder = ((int)num1.digits[i] - 48) - ((int)num2.digits[i] - 48);
                temp.digits[i] = (holder + 48);
            }
            if (((int)num1.digits[i] - 48) < ((int)num2.digits[i] - 48)) {
                holder = (((int)num1.digits[i] - 48) + 10) - ((int)num2.digits[i] - 48);
                borrow = (((int)num1.digits[i - 1] - 48) - 1);//borrow will be the number to the left-1
                if (i != 0)
                    num1.digits[i - 1] = borrow + '0';//saving this number to num1's array
                temp.digits[i] = (holder + 48);
            }
        }
        temp.invalidNumber = false;
        if (num1.digits != NULL) {
            delete[] num1.digits;
            num1.digits = NULL;
        }
        if (num2.digits != NULL) {
            delete[] num2.digits;
            num2.digits = NULL;
        }
        return temp;
    }
    else {//means that we have calling object is less than obj we trying to subtract
        string inval = "INVALID";//since answer is negative
        invalidNumber = true;
        delete[] digits;
        digits = new char[7];
        length = 7;
        for (int i = 0; i < 7; i++) {//saving string "INVALID"
            digits[i] = inval[i];
        }
    cout << "number num4=" << *this << endl;//only have this here since its on ouput but not in main
        return *this;
    }
}
/*
* operator=: this function is basically the same thing as a copy
constructor as it copies all the information of one object into another
* parameters: the object we want to make a copy of
* return value: it returns the object that called it (after update)
*/
bigNum bigNum:: operator=(const bigNum& original) {
    if (digits != NULL) {//object calling it might already have allocated memory
        delete[] digits;
        digits = NULL;
    }
    length = original.length;
    digits = new char[original.length];
    for (int i = 0; i < original.length; i++) {
        digits[i] = original.digits[i];
    }
    invalidNumber = original.invalidNumber;
    this->disp_mode=original.disp_mode;
    return *this;
}
/*
* operator++: this function will increment the object's digit by 1
* return value: the object that called it after increment
*/
bigNum bigNum::operator++() {
    bigNum holder(1);//creating an object that has digit=1
    *this = *this + holder;//using already overloaded + to add holder to object
    return *this;
}
/*
* operator++(int): brief description of what the function does.
* parameters: a random integer. its used to differentiate from pre++
* return value: the object that called
*/
bigNum bigNum::operator++(int unwanted){
    bigNum temp(*this);//running copy constructor
    ++*this;//using already defined ++ to increment
    return temp;//returing the copy of original
}
/*
* operator+=: this function will take the object that comes
after += and add it to the calling object's digit
* parameters: the object we want to add to our calling object
* return value: the object that called it after addition
*/
bigNum bigNum::operator+=(bigNum& number) {
    *this = *this + number;//using already created + to add two objects
    return  *this;
}
/*
* operator-=: this function will take the object that comes
after += and subtract it from the calling object's digit
* parameters: the object we want to subtract from our calling object
* return value: the object that called it after subtracting second object
*/
bigNum bigNum::operator-=(bigNum& number) {
    *this = *this - number;//using already overloaded - to subtract this number2 from number1
    if(digits[0]=='0')
        adjustSize(0);
    return *this;
}
/*
* operator(): this funciton will reset objects from invalid state
* parameters: the object we are going to save into calling object
* return value: the reset object
*/
bigNum bigNum::operator()(int number) {
    if (digits != NULL) {
        delete[] digits;
        digits = NULL;
    }
    string sNumber = to_string(number);//converting number passed to string
    length = sNumber.length();
    digits = new char[length];
    for (int i = 0; i < length; i++) {//copying string
        digits[i] = sNumber[i];
    }
//    invalidNumber = false;//changing invalid state back to false
    return *this;
}
/*
* operator>>: this function overloads >> so that it can read user's
input into object
* parameters: istream and the object we want to save into
* return value: the istream
*/
istream& operator>>(istream& in, bigNum& number){
    if(number.digits!=NULL){//deallocating
      delete[] number.digits;
      number.digits=NULL;
    }
    string num;
    in>>num;//reading in as a string
    number.length=num.length();
    number.digits=new char[number.length];
    for(int i=0; i<num.length(); i++){//saving the string into object
        number.digits[i]=num[i];
    }
    return in;
}
/*
* operator<<: this function overloads << so that it is able to
print out objects
* parameters: ostream and the object we want to output
* return value: the ostream
*/
ostream& operator<<(ostream& out, const bigNum& number) {
    for(int i=0; i<number.length; i++){
        out<<number.digits[i];
     }
    return out;
}
