/* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
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

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
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
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.
  4. Interprets integer expressions using the Data Lab 32-bit bit-vector
     model: results outside the signed range retain their low 32 bits.


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

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

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
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
#include "bits.h"

// P1
/* 
 * signMask - return a mask with only the most significant bit set (0x80000000)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 2
 *   Rating: 1
 */
int signMask(void) {
  return 1<<31;
}

// P2
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1, bitXor(7, 7) = 0
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 2
 */
int bitXor(int x, int y) {
  int a = x & ~y;
  int b = ~x & y;
  int c = ~a & ~b;
  int d = ~c;
	return d;
}

// P3
/*
 * negativePart - return -x if x < 0, otherwise return 0
 *   Examples: negativePart(-10) = 10, negativePart(5) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 3
 */
int negativePart(int x){
  int signing = x >> 31;
  int positive = ~x +1;
  int result = signing & positive;
  return result;
}


// P4
/*
 * copyByteWithin - copy byte src of x to byte dst, leaving all other bytes unchanged
 *   Bytes are numbered from 0 (least significant) to 3 (most significant).
 *   You can assume 0 <= src <= 3 and 0 <= dst <= 3.
 *   Example: copyByteWithin(0x11223344, 0, 2) = 0x11443344
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4
 */
int copyByteWithin(int x, int src, int dst) {
  int byte_src = ( x >> (src << 3)) & 255;
  int byte_dst = byte_src << (dst << 3);
  int com = 255 << (dst << 3);
  int reverse = ~com;
  int result = (reverse & x) | (byte_dst);
  return result;
}

// P5
/* 
 * logicalShift - shift x to the right by n bits, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int logicalShift(int x, int n) {
  int origin = ~ ((( 1 << 31) >> n) << 1);
  return ( x >> n ) & origin;
}

// P6
/*
 * swapNibblePairs - swap the low and high 4 bits within each byte of x
 *   Examples: swapNibblePairs(0xAB) = 0xBA
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 18
 *   Rating: 4
 */
int swapNibblePairs(int x) {
  int m = 0x0F;
  m = m | ( m << 8);
  m = m | ( m << 16);
  int lower = ( x & m ) << 4;
  int upper = ( x >> 4) & m;
  return lower | upper;
} 

// P7
/*
 * secondLowestZeroBit - return a mask that marks the position of the second least significant 0 bit
 *   Examples: secondLowestZeroBit(0xFFFFFFFA) = 0x4, secondLowestZeroBit(0x7FFFFFFF) = 0
 *             secondLowestZeroBit(-1) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 4
 */
int secondLowestZeroBit(int x){
  int r = ~x & ( x + 1);
  int r_n = x | r;
  int m = ~r_n & (r_n +1);
  return m;
}

// P8
/*
 * oddParity - return the odd parity bit of x, that is,
 *      when the number of 1s in the binary representation of x is even, then the return 1, otherwise return 0.
 *   Examples: oddParity(5) = 1, oddParity(7) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 56
 *   Rating: 5
 */
int oddParity(int x) {
  int num_16 = (x >> 16)^ x ;
  int num_8 = (num_16 >>8) ^ num_16;
  int num_4 = (num_8 >>4) ^ num_8;
  int num_2 = (num_4 >> 2) ^ num_4;
  int num_1 = (num_2 >> 1) ^ num_2;
  int result = (~num_1) & 1;
  return result;
}

// P9
/* 
 * rotateRightBits - rotate x to right by n bits
 *   you can assume n >= 0
 *   Examples: rotateRightBits(0x12345678, 8) = 0x78123456
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 5
 */
int rotateRightBits(int x, int n) {
  int minus_1 = ~1 + 1;
  int n_mode = n & 31;
  int move = (32 + (~n_mode + 1)) & 31;
  //int keep   = (1 << move) + ~0; 
  int num_r = ( 1 << move) + minus_1;//低move位全1掩码
  //int num_l = ~num_r;//高n_move位全1掩码
  int l_to_r = (x >> n_mode) & num_r;
  int r_to_l = (x << move) ;
  int result = r_to_l | l_to_r;
  return result;
}

// P10
/*
 * roundEvenPow2 - round nonnegative x to the nearest multiple of 2^n.
 *   If x is exactly halfway between two multiples, choose the multiple whose
 *   quotient by 2^n is even.
 *   You can assume 0 <= x <= 0x3fffffff and 1 <= n <= 16.
 *   Examples: roundEvenPow2(10, 2) = 8, roundEvenPow2(14, 2) = 16
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 5
 */
int roundEvenPow2(int x, int n) {
  int minus_1 = ~1 + 1;
  int divi = 1 << n; // 2^n
  int remain = x & (divi + minus_1); //余数
  int quo = x >> n; //商
  int shift = n + minus_1;
  int half = 1 << shift;
  int bigger_than_half = ( remain >> ( shift)) & 1;
  int lower = remain & (half + minus_1);
  int low_nonzero = !!lower; // 低位非零标记：非零=1（余数>一半），零=0（余数=一半）
  int quo_odd = quo & 1;        // 商的奇偶标记：奇数=1，偶数=0
  int carry = bigger_than_half & (low_nonzero | quo_odd); // 合并进位条件
  return (quo + carry) << n;
}

// P11
/* 
 * midpointTowardFirst - return the exact mathematical midpoint (x+y)/2
 *   without overflow. If the exact midpoint lies halfway between two
 *   integers, choose the adjacent integer that is closer to the first
 *   argument x.
 *   Examples: midpointTowardFirst(4, 7) = 5,
 *             midpointTowardFirst(7, 4) = 6
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 32
 *   Rating: 5
 */
int midpointTowardFirst(int x, int y) {
  int half = ( x & y) + (( x ^ y) >> 1);
  int if_odd = (( x ^ y ) & 1);
  
  int x_sign = (x >> 31) & 1;          
  int y_sign = (y >> 31) & 1;          
  int sign_diff = x_sign ^ y_sign;     
    
  int sub = x + (~y + 1);              
  int sub_non_neg = !((sub >> 31) & 1);
  int x_gt_y = ((!sign_diff) & sub_non_neg) | (sign_diff & !x_sign);
  int carry = if_odd & x_gt_y;
  return half + carry;
  
}


// P12
/* 
 * isBetweenEitherOrder - return 1 when x lies in the inclusive interval whose
 *   endpoints are a and b. The endpoints may be given in either order.
 *   Example: isBetweenEitherOrder(5, 8, 3) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 48
 *   Rating: 7
 */
int isBetweenEitherOrder(int x, int a, int b) {
  int x_sign = !((x >> 31) & 1);//1表示正数，0表示负数
  int a_sign = !((a >> 31) & 1);
  int b_sign = !((b >> 31) & 1);
  int x_sub_a = !((( x + ~a + 1) >> 31) & 1);//1表示x>a
  int x_gt_a = ( x_sign & !a_sign) | ((!(x_sign ^ a_sign)) & x_sub_a);
  int x_sub_b = !((( x + ~b + 1) >> 31) & 1);//1表示x>b
  int x_gt_b = ( x_sign & !b_sign) | ((!(x_sign ^ b_sign)) & x_sub_b);
  int eq_a = !(x ^ a);  // x == a 则为1
  int eq_b = !(x ^ b);
  int result = (x_gt_a ^ x_gt_b) | eq_a |eq_b;
  return result;
}

// P13
/* 
 * mul5Sat - return x*5, and if x*5 overflow, change the result to 
 * INT_MAX(0x7fffffff) or INT_MIN(0x80000000) correspondingly
 *   Examples: mul5Sat(1) = 0x5, mul5Sat(0x40000000) = 0x7fffffff
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 30
 *   Rating: 7
 */
int mul5Sat(int x) {
    int x_sign = x >> 31;                          
    int abs_x = (x + x_sign) ^ x_sign;             
    int high_overflow = !!(abs_x >> 29);           

    int prod = x + (x << 2);                       
    int prod_sign = prod >> 31;                    
    int add_overflow = (x_sign ^ prod_sign) & 1;   

    int overflow = high_overflow | add_overflow;   
    int overflow_mask = ~overflow + 1;             

    int sat_max = ~(1 << 31);                      
    int sat_val = sat_max + (x_sign & 1);          

    return (~overflow_mask & prod) | (overflow_mask & sat_val); 
}

// P14
/* 
 * classifyAdd3 - classify the exact mathematical sum x+y+z.
 *   Return 1 if the sum is greater than INT_MAX, -1 if it is less than
 *   INT_MIN, and 0 otherwise. You may not use a wider integer type.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 52
 *   Rating: 7
 */
int classifyAdd3(int x, int y, int z) {
    int x_sign = x >> 31;
    int y_sign = y >> 31;
    int z_sign = z >> 31;   
    int s  = x + y;                                 
    int s_sign = s >> 31;                           
    int t  = s + z;                                 
    int t_sign = t >> 31;                           
  
    int p1 = ~( x_sign | y_sign) & s_sign;         
    int n1 = ( x_sign & y_sign) & ~s_sign;         
    int c1 = ( p1 & 1) + n1;                       

    int p2 = ~( s_sign | z_sign) & t_sign;         
    int n2 = ( s_sign & z_sign) & ~t_sign;         
    int c2 = ( p2 & 1) + n2;                       

    return c1 + c2;
}

// P15
/*
 * floatScaleThreeHalves - Return bit-level equivalent of expression f*3/2 for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   Use round-to-nearest-even. Preserve the sign of both +0 and -0.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 60
 *   Rating: 7
 */
unsigned floatScaleThreeHalves(unsigned uf) {
  //提取指数、frac
  unsigned s = uf & 0x80000000U;
  unsigned e1 = ( uf >> 23 ) & 0xFF;
  unsigned frac1 = uf & 0x7FFFFF; //8位
  //unsigned frac2 = 0;
  unsigned M, e_sum, G , R= 0;
  if ( e1 ==0xFF ){
    return uf;
  }
  if (e1 == 0 && frac1 == 0) {
    return uf;
  }
    if (e1 == 0) {                                 
    unsigned T = frac1 * 3;
    e_sum = 0;
    G = T & 1;
    M = T >> 1;                                    
    if (M >= (1U << 23)) e_sum = 1;                
    if (G && (M & 1)) M++;                         
    if (e_sum == 0 && M >= (1U << 23)) e_sum = 1;  
    if (e_sum) return s | (1U << 23) | (M - (1U << 23));
    return s | M;
  }

  M = ((1U << 23) | frac1);
  M = M + (M >> 1);                                
  G = frac1 & 1;                                   
  e_sum = e1;
  if (M >= (1U << 24)) {                           
    R = G;                                         
    G = M & 1;
    M >>= 1;
    e_sum += 1;
  }
  if (G && (R || (M & 1))) M++;  
  if (M >= (1U << 24)) { M >>= 1; e_sum += 1; }                  
  if (e_sum >= 255) return s | 0x7F800000U;        
  return s | (e_sum << 23) | (M & 0x7FFFFF);

  
  
}

// P16
/* 
 * floatRoundEven - round the floating-point value represented by uf to the
 *   nearest integer, with halfway cases rounded to the even integer. Return
 *   the bit-level representation of that integer as a single-precision float.
 *   If rounding produces zero, preserve the input sign; thus a negative
 *   value that rounds to zero returns -0. When uf is NaN or infinity,
 *   return uf unchanged.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 65
 *   Rating: 10
 */
unsigned floatRoundEven(unsigned uf) {
  unsigned s = uf & 0x80000000U;
  int e1 = ( uf >> 23 ) & 0xFF;
  int exp = e1 - 127;
  unsigned frac = uf & 0x7FFFFF; 
  unsigned M, e_sum, G = 0;

  if ( e1 ==0xFF ){
    return uf;
  }

  if (e1 == 0 && frac == 0) {
    return uf;
  }

  if (exp >= 23){ //本来表示的就是整数
    M = frac;
    G = M & 1;
    return uf;
  }
  else if (exp >= 0 && exp < 23) {
    e_sum = e1;
    M = ( 1 << exp )| (frac >> (23 - exp));//有效的、能化成整数的部分
    G = M & 1; //整数末尾奇偶
    unsigned left = frac % ( 1 << ( 23 - exp));// 剩下的部分，用来判断舍入
    unsigned half = 1 << ( 22 - exp );
    if  (left > half || (left == half && G)){
      M ++ ;  
    }
    if (M >= (1U << (exp + 1))) { M >>= 1; e_sum += 1; }                  
    if (e_sum >= 255) return s | 0x7F800000U;        
    return s | (e_sum << 23) | ((M - (1 << exp)) << ( 23 - exp));
  }
  else if ( exp == -1 && frac != 0){
    return s|(127 << 23);//对于大于0.5且小于1的数，返回1
  }
  else {
    return s|0; //对于大于0且小于等于0.5的数，返回0；
  }
}

// P17
/*
 * float_i2f - Return bit-level equivalent of expression (float) x.
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 40
 *   Rating: 10
 */
unsigned float_i2f(int x) {
  unsigned s = x & 0x80000000U;
  if (x == 0) return 0;

  unsigned ux = (x < 0) ? (0u - (unsigned)x) : (unsigned)x;

  unsigned exp = 0;
  unsigned t = ux;
  while (t >>= 1) exp++;

  unsigned M = ux - (1U << exp);

  if (exp < 24) {
    return s | ((exp + 127) << 23) | (M << (23 - exp));
  } else {
    int move = exp - 23;
    M >>= move;
    unsigned left = ux & ((1U << move) - 1);  
    unsigned half = 1U << (move - 1);
    unsigned G = ux & (1U << move);           
    if (left > half || (left == half && G)) {
      M++;
    }
    if (M >= (1U << 23)) { M = 0; exp += 1; }
    return s | ((exp + 127) << 23) | M;
  }
}




// P18
/*
 * bitCount - return count of number of 1's in the binary representation of x
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 10
 */
int bitCount(int x) {
  int m1 = 85 | ( 85 << 8);
  m1 = m1 | (m1 << 16);
  int m2 = 51 | ( 51 << 8);
  m2 = m2 | (m2 << 16);
  int m4 = 15 | ( 15 << 8);
  m4 = m4 | (m4 << 16);
  x = ( x & m1) + ((x >> 1) & m1);
  x = ( x & m2) + ((x >> 2) & m2);
  x = ( x & m4) + ((x >> 4) & m4);
  x = x + ( x >> 8);
  x = x + ( x >> 16);
  return x & 63;
}

// P19
/*
 * bitReverse - Reverse bits in an 32-bit integer
 *   Examples: bitReverse(0x80000004) = 0x20000001
 *             bitReverse(0x7FFFFFFF) = 0xFFFFFFFE
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 34
 *   Rating: 10
 */
int bitReverse(int x)
{
  int m1 = 255 | ( 255 << 8);
  int m2 = m1 ^ ( m1 << 8); 
  int m3 = m2 ^ ( m2 << 4);
  int m4 = m3 ^ ( m3 << 2); 
  int m5 = m4 ^ ( m4 << 1);  

  x = ( x << 16) | (( x >> 16) & m1);
  x = (( x & m2) << 8) | (( x >> 8) & m2);
  x = (( x & m3) << 4) | (( x >> 4) & m3);
  x = (( x & m4) << 2) | (( x >> 2) & m4);
  x = (( x & m5) << 1) | (( x >> 1) & m5);
  return x;
}
