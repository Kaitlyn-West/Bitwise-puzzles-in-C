/* 
 * CS2011 Lab1
 * 
 * Kaitlyn West 
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
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
//1
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) {
// we want true when x = 0 and y = 1, and when x = 1 and y = 0. 
// to acheive this i first looked at ~x & y, which was only 1 for y = 1 and x = 0.
// combining this with its mirror using an or would have been enough, if the use of bitwise or were allowed
// to find how to replace an or using only nots and Ands, i considered the simpler case with a and b as inputs, intstead of what will go in later
// ~(~a & ~b) is only false when a and b are both false, making it a substitue for an or gate
// plugging in the ~x & y and ~y & x from before we get:
// ~(~(~x & y) & ~(~y & x))
// this final form works as it only returns true for x = 1 and y = 0, And x = 0 and y = 1
 	return ~(~(~x & y) & ~(~y & x));
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
// the minimum value that can be encoded with two's compliment interpretation has a leading
// 1 and every other bit is 0.

	int output = 0x01; //a 1 in the least significant bit only
	output <<= 31; //bitshift the 1 all the way to the most significant bit (since we assumed 32 bit ints)		   
	
	return output;

}
//2
/* 
 * allOddBits - return 1 if all odd-numbered bits in word set to 1
 *   where bits are numbered from 0 (least significant) to 31 (most significant)
 *   Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allOddBits(int x) {
// since we want to know if all the odd bits are 1 we can do bitwise or with a number that
// has 1 in all the even bits and 0 in all the odd bits. if the result of that 'or' operation
// is 0xFFFFFFFF then all of the odd bits were 1. the bitwise not of that will be 0. we can
// then use the logical ! to get a 1. if the result isn't 0xFFFFFFFF then then the same
// process of a bitwise ~ will give something that is not 0, the logical ! of which will be 0,
// or false
// since we can't use constants greater than 0xFF, we'll use bitshift to do each section of
// two bytes at a time

	int onlyEvenOnes = 0x55;
	int result = x | onlyEvenOnes; 		//first 2 bytes

	onlyEvenOnes <<= 8;
	result = result | onlyEvenOnes; 	// bytes 3 and 4
	onlyEvenOnes <<= 8;
	result = result | onlyEvenOnes;		// bytes 5 and 6
	onlyEvenOnes <<= 8;
	result = result | onlyEvenOnes; 	// bytes 7 and 8

	return !(~(result));
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
// negation is covered in class as being ~x + 1. this is is identical to performing
// the two's compliment (since one's comliment is ~x, and two's compliment is the
// one's compliment + 1)
      
	return ~x + 1;
}
//3
/* 
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to '9')
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int isAsciiDigit(int x) {
// I did this in probably not the most intuitive way - but it works
// first - !(a ^ b) is equivalint to a==b.
// I noticed two things while thinking about true cases:
// 	a) all the bytes aside from the first stay the same for all true cases
// 	b) for 8 of the ten true cases, bit 3 0
// 	c) if bit 3 isn't 0, then it must be 0x38 or 0x39	
// Rephrased:
// 	if bit 3 is 0 AND all bytes aside from the first are as they should be
// 	OR if x is 0x38
// 	OR if x is 0x39
// 	Then we should return true
// knowing !(a ^b) is equivilant to a==b makes the second 2 conditions easy to check,
// only the first one was difficult.
// I ended up doing this to check if all the bytes aside from the first are what they need
// to be: !((x >> 4) ^ 0x03) This checks if x (aside from the first byte) matches the true
// cases. to check if bit three is 0 we can do this: !(x & 0x08), since 0x08 only has 1 in
// bit 3.
// put togther we get this:
// (!(x & 0x08) & !((x >> 4) ^ 0x03)) | !(x ^ 0x38) | !(x ^ 0x39)

	return ((!(x & 0x08) & !((x >> 4) ^ 0x03)) | !(x ^ 0x38) | !(x ^ 0x39));
 
}
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
// standardize x to always be 0x00 or 0x01
	x = !(!x);	
// make x either all 0s or all 1s (arithmatic shifting)
	x <<= 31;
	x >>= 31;
// make y and z disolve into all 0s if they aren't supposed to be the result
	y =  x & y;
	z = ~x & z;
// since x is all 0s or all 1s, we just need to take away the ones or zeros as appropriate
	x = x & y;
	x = x | z;
  	return x;
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
// a good starting point is to notice that x <= y is equivalant to
// y - x >= 0. we can easily check if something is not >= 0 by 
// checking the sign bit. the sign bit will be the opposite of 
// what we want - so fliping it will be neccesary

// starting by finding the difference	
	int lessOrEqual = y + (~x + 1);
// then propogate sign bit
	lessOrEqual >>= 31;
// then logically flip
	lessOrEqual = !lessOrEqual;

// This would normally be enough to know if x <= y, but due to
// overflow sometimes being an issue we can do some general
// checks too, like if checking if x is negative and y is 
// positive, or if y is negative and x is positive

// check if x < 0 and y >= 0	
	lessOrEqual = lessOrEqual |  (!!(x >> 31) & !(y >> 31));
// ensure y is not < 0 while x >= 0	
	lessOrEqual = lessOrEqual & !(!!(y >> 31) & !(x >> 31));	

	return lessOrEqual;
}
//4
/* 
 * logicalNeg - implement the ! operator, using all of 
 *              the legal operators except !
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int logicalNeg(int x) {
// we first want to standardize all inputs, making any nonzero input
// into the same value, while simultaneously only sending 0 to a
// different value
// to do this we look at the sign bit - if x is negative it will be
// a 1, to check if it is positive we can add the max signed int
// value, which will make any positive non-zero number overflow into
// a negative value, but 0 will stay positive. taking the bitwise
// or will make the sign bit 1 for any non-zero value.
// we can use arithmatic bit shifting to propogate the sign bit to 
// every other bit. 
// at this point any non zero value is converted into just 1s and
// inputs of 0 stay 0. if we were to take the xor of either of
// those and themself shifted a bit left it would keep 0 as 0, and
// turn the all 1 value into a single 1 in bit 0.
// doing that wouldn't not the given value though - just convert it
// to 0 or 1. to not it, we can bitwise not our ourput before the
// xor. 

// make var's sign bit 1 for any non-zero value	
	int var = x | (x + ~(0x01 << 31));
	var >>= 31;
// var is either all 0 or all 1, matching as it was
	var = ~var;
// var is 1s if it was 0, otherwise 0
	var = var ^ (var << 1);	

	return var;
}
/* howManyBits - return the minimum number of bits required to represent x in
 *             two's complement
 *  Examples: howManyBits(12) = 5
 *            howManyBits(298) = 10
 *            howManyBits(-5) = 4
 *            howManyBits(0)  = 1
 *            howManyBits(-1) = 1
 *            howManyBits(0x80000000) = 32
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 90
 *  Rating: 4
 */
int howManyBits(int x) {
// The idea for this function is to count the leading bits and subtract how many there
// are from 32. it will be easist to do this if we make sure the leading bit is always
// 0, which we can do using XOR. x ^ (x >> 1), makes the first non-leading bit 1, and
// potentially some of the other non-leading bits. we use Or in combination with right
// bit shifting to propogate that 1 to all the following bits, so that the number is
// some 0s followed by 1s. this makes the value of the variable one less than some
// whole number power of two. because of this we can add 1 and then we are left with a
// single bit we need to find the location of. I chose to do this by chekcing if the
// bit is in such a location that I will need to add a particularlar power of 2 to the
// total number of leading bits. for example, if the bit is in the last 16 bits of the
// number, we will need to at 16 to the number of leading bits. for 8, we can break 
// the 32 bit variable up into 4 8 bit sections. if we label the sections 0123, we 
// will need to add 8 if the bit is in secion 1 or 3, but not for secition 0, or 2.
// the same process can be applied for 4, 2, and 1. we can perform the actual check
// by computing the & of our variable and the numbers designed for 16, 8, 4, 2, and 1.
// using logical not and arithmatic bit shifting we can make variables that are either
// all 1s or all 0s depending on whether or not we are adding a particular power of 2.
// we can then add the actual power of 2 ANDed with the corresponding variable to the
// total number of leading variables. once we subtract that from 32 we have our answer.

 



	int add16 = 0;
	int add8 = 0;
	int add4 = 0;
	int add2 = 0;
	int add1 = 0;
	int n16 = 0;
	int n8  = 0;
	int n4  = 0;
	int n2  = 0;
	int n1  = 0;
	int t = 0;
	int total = 0;

//	printf("given: %x\n", x);

	int a = x ^ (x >> 1);

//	printf("XORed: %x\n", a);
	
	a = a | (a >> 1);
	a = a | (a >> 2);
	a = a | (a >> 4);
	a = a | (a >> 8);
	a = a | (a >> 16);

//	printf("shifted: %x\n", a);

	a += 1;

//	printf("plus 1: %x\n", a);

//	a = a >> 1;

	n16 = 1 << 31 >> 15;
//	t   = 1 << 31 >> 7;
//	n8  = t | (t >> 16);
	t   = 0xF0 | (0xF0 << 8);
	n4  = t | (t << 16);
	t   = 0xCC | (0xCC << 8);
	n2  = t | (t << 16);
	t   = 0xAA | (0xAA << 8);
	n1  = t | (t << 16);

	n8 = (1 << 31 >> 7) | (0xFF << 8);

//	printf("n16: %x\n", n16);
//	printf("n8 : %x\n", n8);
//	printf("n4 : %x\n", n4);
//	printf("n2 : %x\n", n2);
//	printf("n1 : %x\n", n1);

	add16 = !(n16 & a) << 31 >> 31;
	add8  = !(n8  & a) << 31 >> 31;
	add4  = !(n4  & a) << 31 >> 31;
	add2  = !(n2  & a) << 31 >> 31;
	add1  = !(n1  & a) << 31 >> 31;

//	printf("a16: %x\n", add16);
//	printf("a8 : %x\n", add8);
//	printf("a4 : %x\n", add4);
//	printf("a2 : %x\n", add2);
//	printf("a1 : %x\n", add1);

	total = (16 & add16) + (8 & add8) + (4 & add4) + (2 & add2) + (1 & add1);

//	return 33;
	
//	printf("output: %d\n\n\n\n", 32 + (~total + 1));

	return 32 + (~total + 1); 
	
}
//float
/* 
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned floatScale2(unsigned uf) {
// there are essentially three cases:
//     special      - +/-inf or NAN - either way return input
//     normalized   - add 1 to exp, if becomes +inf, set mantissa to 0
//     denormalized - shift mantissa left 1, if leading 1, also add 1 to exp

	//separate uf into the sign, exp and mantissa, each as right as can be
	unsigned sign = 0x01 & (uf >> 31);               // shifts fully right and makes sure to
				                         // eliminate 1s from algor right shift
	unsigned exp = (uf >> 23) & 0xFF;                // pulls left and masks non - exp bits
	unsigned mantissa = uf & (~((0x01 << 31) >> 8)); // maskes all non-mantissa bits

	//check for special cases:
	if (exp == 255) //255 is 8 1s in binary
	{
		return uf;
	}

	//check for denormalized cases:
	if (exp == 0)
	{
		return (sign << 31) | (mantissa << 1); // doubles mantissa's value, and
						       // sets exp's value to 1 when
						       // there is a leading 1
	}

	//must be a normalized value:
	//check if doubling goes to infinity:
	if(exp == 254)
	{
		return (0xFF << 23) | (sign << 31); // preserves sign bit while setting
							 // exp to all 1s and mantissa to 0
	}
	//must not go to infinity when doubled:
	return (sign << 31) | ((exp + 1) << 23) | mantissa; // preserves sign bit, adds 1 to
							    // exp and preserves mantissa
}
/* 
 * floatFloat2Int - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
 *   Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
int floatFloat2Int(unsigned uf) {
// again we have three cases:
//     special      - +/-inf or NAN return 0x80000000
//     normalized   - if e < 0 then 0
//                  - if e > 31 - 23 (8) then  0x80000000
//                  - otherwise
//                  	mantissa << (e - 24) ( >> if e - 24 is neg)
//                  	if neg return 2's compliment
//     denormalized - return 0

	// separate uf into the sign, exp and mantissa, each as right as can be
	unsigned sign = 0x01 & (uf >> 31);               // shifts fully right and makes sure to
				                         // eliminate 1s from algor right shift
	unsigned exp = (uf >> 23) & 0xFF;                // pulls left and masks non - exp bits
	unsigned mantissa = uf & (~((0x01 << 31) >> 8)); // maskes all non-mantissa bits

	// insert leading 1 into mantissa:
	mantissa = mantissa | (0x01 << 24);

	if(exp > 31 - 23 + 127) // accounts for specials and overflow
	{
		return 0x80000000;
	}

	if(exp < 0 + 127) // accounts for denormalization and values rounding down to 0
			  // dealing with denormalization like this allows us to have
			  // already inserted a leading 1
	{
		return 0;
	}

	if(exp < 127 + 23) // making sure shifts are always positive
	{

		mantissa >>= exp - 127 + 24;
	}
	else
	{
		mantissa <<= exp - 127 - 24;
	}

	if(sign) //negating if neccesary
	{
		return ~mantissa + 1;
	}
	return mantissa;
	

  return 2;
}
