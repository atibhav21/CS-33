/* 
 * CS:APP Data Lab 
 * 
 * Name: Atibhav Mittal
 * ID: 804598987
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#include "btest.h"

/*
 * Instructions to Students:
 *
 * STEP 1: Fill in the following struct with your identifying info.
 */
id_struct studentID =
{
  /* UID number: */
  "804598987",
  /* Last Name: */
  "Mittal",
  /* First Name: */
  "Atibhav"
};

#if 0
/*
 * Instructions to Students:
 *
 * STEP 2: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the btest harness to check your solutions for correctness.
 */


#endif
/*
 * bitParity - returns 1 if x contains an odd number of 0's
 *   Examples: bitParity(5) = 0, bitParity(7) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int bitParity(int x) {
       //algorithm: Two numbers, x and y contain odd number of 0s if x ^ y contains odd number of 0s. 
       //in this case the two numbers are first half of x and last half of x
       x = (x ^ ( x >> 16)); //
       x = (x ^ ( x >> 8));
       x = (x ^ ( x >> 4));
       x = (x ^ ( x >> 2));
       x = (x ^ ( x >> 1));
       x = x & ~((~0 << 1)); //discard all bits except the least significant bit.
       // all bits except least significant bit are irrelevant as they are XORd with arithmetic right shifts
       return !!(x & 1);
}
/* 
 * rotateRight - Rotate x to the right by n
 *   Can assume that 0 <= n <= 31
 *   Examples: rotateRight(0x87654321,4) = 0x76543218
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 25
 *   Rating: 3 
 */
int rotateRight(int x, int n) {
  //get n most significant digits
  int rotatedDigits = (x>> n) & ~( (~0) << (32 + (~n + 1)));
  int lx = x << (32 + (~n + 1));
  return lx | rotatedDigits;
}
/* 
 * byteSwap - swaps the nth byte and the mth byte
 *  Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *            byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *  You may assume that 0 <= n <= 3, 0 <= m <= 3
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 25
 *  Rating: 2
 */
int byteSwap(int x, int n, int m) {
  int m_n = (x >> (n << 3)) & 0xFF; //extract nth byte
  int m_m = (x >> (m << 3)) & 0xFF; //extract mth byte
  
  //swap m_n and m_m
  m_n = m_n ^ m_m;
  m_m = m_n ^ m_m;
  m_n = m_n ^ m_m;
  
  m_n = m_n << (n<<3) ; 
  m_m = m_m << (m<<3);

  //form a single number with m_n and m_m swaped
  
  //make nth byte 0 and mth byte 0
  x  = x &  (~(0xFF << (n << 3)) & (~(0xFF << (m << 3))));

  return (x | (m_n | m_m)); 
}
/* 
 * fitsShort - return 1 if x can be represented as a 
 *   16-bit, two's complement integer.
 *   Examples: fitsShort(33000) = 0, fitsShort(-32768) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 1
 */
int fitsShort(int x) {
  // can fits in a short if the first 17 bits are the same.
  //extract first 17 bits
  x = x >> 15; 
  return ! ( x + ( ~(x>>1) + 1));
  //int k = (x & ( (~0) << 15)) >> 15;
  // k is now either all 0s or all 1s if x can fit in short
  //return !(k + (~ (k>> 1)+ 1)); //return k - k>>1. if 0 then it can fit in short
  //int mx = (x >> 15);
  //int mask = ~(-1 << 17);
  //int r = (mask ^ mx) >> 15; //r is either all 0s or all 1s
  //return (r == 0 || r == -1);
}
/* 
 * bitAnd - x&y using only ~ and | 
 *   Example: bitAnd(6, 5) = 4
 *   Legal ops: ~ |
 *   Max ops: 8
 *   Rating: 1
 */
int bitAnd(int x, int y) {
  return ~(~x | ~y);
}
/* 
 * subOK - Determine if can compute x-y without overflow
 *   Example: subOK(0x80000000,0x80000000) = 1,
 *            subOK(0x80000000,0x70000000) = 0, 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int subOK(int x, int y) {
  int diff = (x + (~y+ 1)); // x - y
  // overflow can only happen if x > 0 and y < 0 or if x < 0 and y > 0
  // ie x and y have opposite signs
  int sign = (x >> 31) ^ (y >> 31); //sign = -1 if they have opposite signs and 0 if they have the same sign
  // if x is positive and diff is negative, then overflow has happened if signs were opposite
  // if x is negative and diff is positive, then overflow has happened
  int overflowSign = (x>>31) ^ (diff>>31);
  //int firstX = x & ( 1 << 31); //first bit of x
  //int firstY = y & ( 1 << 31); //first bit of y
  //int sign = firstX ^ firstY;
  //diff = (diff & (1<<31)) ^ firstX; //sign of diff has to be same as sign of x
  return !(overflowSign & sign);
}
/* 
 * isGreater - if x > y  then return 1, else return 0 
 *   Example: isGreater(4,5) = 0, isGreater(5,4) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isGreater(int x, int y) {
  int mask = 1 << 31;
  //int m_diff = x + (~y + 1);
  int diff = x ^ y; //discard all the bits that are the same. 
  
  diff |= diff >> 1;
  diff |= diff >> 2;
  diff |= diff >> 4;
  diff |= diff >> 8;
  diff |= diff >> 16;

  diff &= ~(diff>> 1) | (mask);
  diff &= ( x ^ (mask)) & ( y ^ ~(mask));

  return !!diff;
}
/* 
 * fitsBits - return 1 if x can be represented as an 
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int fitsBits(int x, int n) {
  // can fit in n bits if first 33 - n bits are the same
  x = x >> (n + ( ~1 + 1)) ; //right shift x by n-1 bits to check if the first 33-n bits are the same
  return !( x + (~(x>>1) + 1)); //if first 33-n bits are the same then x = x arithmetically right shifted by 1
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
  return ~x + 1;
}
/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmax(int x) {
  int addOne = x+1;
  //addOne is now equal to Tmin if x is T max

  x = addOne + x; //if x equals Tmax, x now equals -1
  addOne  = !(addOne); //addOne now equals 0 if x equals Tmax
  x = ~x; //if x now equals -1, then after this operation, x equals 0. If not, then x will have some non 0 value
  x = x|addOne; //x equals 0 if and only if x was initially Tmax. If not, then this operation will lead to some non zero value being stored in x
  return !x;
}
