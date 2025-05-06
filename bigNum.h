/*
* bigNum: This class holds a characher pointer that is going to dynamically
allocate memory of size length and run the appropriate constructor.
once the constructor runs, the various operation overloads can be used to manipulate
the characters stored in the char array.
*/

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
