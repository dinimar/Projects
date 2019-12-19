//
// Created by Dinir Imameev on 11/21/19.
// Github: @dinimar
//

#include <cstring> // string.h for some
#include <cctype>
#include "string2.h" // includes <iostream>

using std::cin;
using std::cout;
// initializing static class member
int String::num_strings = 0;
// static method
int String::HowMany()
{
    return num_strings;
}

// class methods
String::String(const char * s)
{
    len = std::strlen(s);
    str = new char[len + 1];
    std::strcpy(str, s);
    num_strings++;
}
String::String()            // default constructor
{
    len = 4;
    str = new char[1];
    str[0] = '\0';          // default string
    num_strings++;
}

String::String(const String & st)
{
    num_strings++;
// handle static member update
    len = st.len;
// same length
    str = new char [len + 1]; // allot space
    std::strcpy(str, st.str); // copy string to new location
}

String::~String()
{
    --num_strings;
    delete [] str;
}

// functions
int String::has(const char &c) {
    int k = 0; // counter of chars equal to c
    // Iterate over all chars
    for(int i=0; i<len; i++) {
        if (*(str+i) == c) k++;
    }

    return k;
}

void String::stringLow() {
    for(int i=0; i<len; i++) {
        *(str+i) = tolower(*(str+i));
    }
}

void String::stringUp() {
    for(int i=0; i<len; i++) {
        *(str+i) = toupper(*(str+i));
    }
}

// overloaded operator methods
// add a String to a String
String String::operator+(const String & st) const
{
    return str+st;
}

// add a C string to a String
//String String::operator+(const char* s) const
//{
//}

// overloaded operator methods
// assign a String to a String
String & String::operator=(const String & st)
{
    if (this == &st)
        return *this;
    delete [] str;
    len = st.len;
    str = new char[len + 1];
    std::strcpy(str, st.str);
    return *this;
}

// assign a C string to a String
String & String::operator=(const char * s)
{
    delete [] str;
    len = std::strlen(s);
    str = new char[len + 1];
    std::strcpy(str, s);
    return *this;
}

// read-only char access for const String
const char & String::operator[](int i) const
{
    return str[i];
}
// overloaded operator friends
String operator+(char * s, const String &st)
{
    char * tmpStr = new char[std::strlen(s)+st.len+1];
    std::strcpy(tmpStr, s);
    std::strcat(tmpStr, st.str);
    String res(tmpStr);
    delete [] tmpStr;

    return res;
}

bool operator<(const String &st1, const String &st2)
{
    return (std::strcmp(st1.str, st2.str) < 0);
}

bool operator>(const String &st1, const String &st2)
{
    return st2 < st1;
}

bool operator==(const String &st1, const String &st2)
{
    return (std::strcmp(st1.str, st2.str) == 0);
}
// simple String output
ostream & operator<<(ostream & os, const String & st)
{
    os << st.str;
    return os;
}
// quick and dirty String input
istream & operator>>(istream & is, String & st)
{
    char temp[String::CINLIM];
    is.get(temp, String::CINLIM);
    if (is)
        st = temp;
    while (is && is.get() != '\n')
        continue;
    return is;
}
