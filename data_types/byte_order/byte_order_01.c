/*
Byte Order (Endianness) Overview

Byte order refers to the sequence in which bytes are arranged and interpreted in memory when representing multi-byte 
data types (like int, float, double, etc.). The two main types of byte order are:

1. Big Endian: In Big Endian systems, the most significant byte (MSB) is stored at the lowest memory address, and the 
   least significant byte (LSB) is stored at the highest memory address.

2. Little Endian: In Little Endian systems, the least significant byte (LSB) is stored at the lowest memory address, 
   and the most significant byte (MSB) is stored at the highest memory address.

Why Is Byte Order Important?
Byte order is important for data exchange between different systems. If two systems use different byte 
orders (one is Big Endian, and the other is Little Endian), they may misinterpret the binary data if proper 
conversion is not done. For example, when transmitting or storing data that consists of multiple 
bytes (like int, long, float), the byte order must be considered to ensure correct interpretation.

Examples of Endian Systems:

Big Endian:
Most significant byte first.
Used by some RISC architectures (e.g., SPARC).

Little Endian:
Least significant byte first.
Used by Intel and AMD processors.
Checking the Byte Order in C
The easiest way to check the byte order in C is to store a known multi-byte value (like an integer) in memory 
and examine how its bytes are arranged in memory.

*/

//C Program to Check Byte Order:

#include <stdio.h>

int main() {
    unsigned int x = 0x12345678;  // A known multi-byte value
    unsigned char *byte_ptr = (unsigned char *)&x;

    // Checking the byte order
    if (byte_ptr[0] == 0x78) {
        printf("Little Endian\n");
    } else if (byte_ptr[0] == 0x12) {
        printf("Big Endian\n");
    } else {
        printf("Unknown Endian\n");
    }

    return 0;
}

/*
Explanation of the Program:
unsigned int x = 0x12345678;: We declare a 4-byte integer with the value 0x12345678, which has a known byte sequence 
when viewed in memory:

In hexadecimal, the number is represented as:

0x12  0x34  0x56  0x78

In memory, this number will be represented differently depending on the system's byte order.
unsigned char *byte_ptr = (unsigned char *)&x;: We cast the address of the integer x to a pointer to unsigned 
char (a byte). This allows us to inspect each byte of the integer in memory.

if (byte_ptr[0] == 0x78): If the first byte pointed to by byte_ptr is 0x78, we know that the system is Little Endian. 
This is because in Little Endian, the least significant byte (LSB) is stored at the lowest memory address.

else if (byte_ptr[0] == 0x12): If the first byte is 0x12, the system is Big Endian, where the most significant 
byte (MSB) is stored at the lowest memory address.

Output: The program prints the byte order of the system:

If the first byte of the integer is 0x78, it prints Little Endian.
If the first byte of the integer is 0x12, it prints Big Endian.
*/

/*
Key Points:
Little Endian: The least significant byte (LSB) is stored at the lowest memory address, so for 0x12345678, 
the memory will look like:

0x78  0x56  0x34  0x12

Big Endian: The most significant byte (MSB) is stored at the lowest memory address, so for 0x12345678, 
the memory will look like:

0x12  0x34  0x56  0x78

*/

/*
Importance of Byte Order:
1. Interoperability: When exchanging data between systems with different endianness, you must ensure the data is 
   properly converted.
2. Network Protocols: Many network protocols (like TCP/IP) specify a particular byte order called Network Byte 
   Order (which is Big Endian). This is why the conversion between Big Endian and Little Endian is important when 
   transmitting data over a network.
*/