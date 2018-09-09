#pragma once

struct String{
    static const unsigned char INITIAL_BUFFER_SIZE = 255;
private:
    // 1.
    // Three (3) private member variables are needed.
    // -a char pointer that will point to the first character in the string.
    // -an unsigned int to keep count of how many characters are in the string.
    // -an unsigned long to keep the size of the allotted space for the string in memory (known as the buffer). 
    char* charPointer;
    unsigned int length;
    unsigned long buffer;

    // 2.
    // the getLengthOfCharString function is a private helper function that 
    // returns the number of chars (bytes) before v points to the
    // null termination character '\0';
    unsigned int getLengthOfCharString(const char* v){
        unsigned int size = 0;
        while (*v != '\0') {
            size++;
            v++;
        }
        return size;
    }

public:
    // 3.
    // the default constructor initializes the member variables
    // the buffer size should be initialized to the INITIAL_BUFFER_SIZE
    // the char pointer should point to a new char array that is the size of the buffer
    // the character count is 0
    String(){
        buffer = INITIAL_BUFFER_SIZE;
        charPointer = new char[buffer];
        length = 0;
    }

    // 4.
    // this constructor initializes this string object with the data 
    // referenced by the char pointer
    String(const char* v){
        

        // 4a: get the length of v

        // 4b: if that length is less than the initial buffer size,
        //     initialize the char pointer member variable to point at 
        //     a new char array that is the size of the initial buffer size.
        //     Also, initialize the buffer size variable.
        if (getLengthOfCharString(v) < INITIAL_BUFFER_SIZE) {
            charPointer = new char[INITIAL_BUFFER_SIZE];
            buffer = INITIAL_BUFFER_SIZE;
        }


        // 4c: otherwise, initialize the char pointer to poibnt at a new
        //     char array that is the size of v's length * 2.
        //     This is to give our string room to grow without having to 
        //     reallocate memory as often.
        else {
            charPointer = new char[length * 2];
        }

        // 4d: initialize the char count variable to equal the length of v.
        length = getLengthOfCharString(v);

        // 4e: copy that characters from v into the char array pointed to by the 
        // member variable (for loop)
        for (int i = 0; i < length; i++) {
            charPointer[i] = v[i];
        }
    }

    // 5.
    // This constructor copies the passed in string to this string. Since it is
    // being passed by reference, we have access to its private member variables.
    String(const String& s){
        // 5a: Initialize the char count and buffer size variables to match those of s.
        length = s.length;
        buffer = s.buffer;

        // 5b: initialize the char pointer member variable to point at 
        //     a new char array that is the size of the buffer size variable
        charPointer = new char[buffer];

        // 5c: copy the contents from s into the char array
        for (int i = 0; i < length; i++) {
            charPointer[i] = s.charPointer[i];
        }
    }

    // 6.
    // The destructor should check if the char pointer is null.
    // If not, delete the array it points to.
    ~String(){
        if (charPointer == 0) {
            delete[] charPointer;
        }
    }

    // 7. 
    // This function appends the contents of v to this string.
    void append(const char* v){
        // 7a:
        // First, check to make sure that adding the characters
        // to this string won't overflow the buffer.
        // If it will, then we need to reallocate new memory for the string.
        // Don't forget to clean up the old memory and to update the character count.
        unsigned int oldLength = length;
        unsigned int vLength = getLengthOfCharString(v);

        if (oldLength + vLength > buffer) {
            buffer = (unsigned long) oldLength + (unsigned long) vLength;
            length =  (unsigned int) buffer;
            
            char* newCharPointer = new char[buffer];

            for (int i = 0; i < oldLength; i++) {
                newCharPointer[i] = charPointer[i];
            }
            for (int i = length; i < buffer; i++) {
                newCharPointer[i] = v[i - oldLength];
            }

            delete[] charPointer;
            charPointer = newCharPointer;
        } else {
            for (int i = length; i < buffer; i++) {
                charPointer[i] = v[i - oldLength];
            }
        }
    }

    // 8. 
    // This function appends the contents of str to this string.
    void append(const String& str){
        append(str.charPointer);
    }

    //9. getter function for the length of the string (total chars).
    unsigned int getLength(){
        return length;
    }

    //10. getter function that returns the location of the char array
    const char* getCharArray(){
        return charPointer;
    }

    //11. function that returns true if v contains all the same characters
    //    as this string
    bool equals(const char* v) {
        if (this->length != getLengthOfCharString(v)) {
            return false;
        } else {
            for (int i = 0; i < this->length; i++) {
                if (charPointer[i] != v[i]) {
                    return false;
                }
            }
        }

        return true;
    }

    //12. function that returns true if s contains all the same characters
    //    as this string
    bool equals(const String& s) {
        return equals(s.charPointer);
    }

};