/*----------------------------------------------------------
 *				HTBLA-Leonding / Class: 2dhif
 * ---------------------------------------------------------
 * Exercise Number: 3
 * Title:			Pyramid of Numbers
 * Author:		Robin Fuchshofer
 * ----------------------------------------------------------
 * Description:
 * Calculates a pyramid of numbers, i.e., it multiplies a big
 * integer by the number 2, its result by 3, etc. and then
 * returns to the original value by subsequently dividing,
 * again starting by 2, 3, etc.
 * ----------------------------------------------------------
 */
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
/// The maximum number of digits allowed in a big int.
#define MAX_DIGITS 80

/** BigInt represents an integer number which can have MAX_DIGITS digits
*** @see MAX_DIGITS
*/
struct BigInt {
	/** number of digits of the big int. */
	int digits_count;

	/** array of digits of big int. */
	unsigned int the_int[MAX_DIGITS];
};

/** strtobig_int converts a string into a BigInt. If strtobig_int runs
*** against a character not between '0' and '9' the conversion stops
*** at this point.
*** @param *str The string to be converted.
*** @param len Number of characters in string to be converted.
*** @param *big_int The converted string now as BigInt.
* @return The number of characters converted.
*/
int strtobig_int(const char *str, int len, struct BigInt *big_int)
{
	int convert =0;
	int count = len;
	len -= 1;
	for (size_t i = 0; i < count; i++) {
		if (str[len] < '0' || str[len] > '9')
		{
			return 0;
		}
		big_int->the_int[i] = str[len] - '0';
		convert++;
		len--;
	}
	big_int->digits_count = convert;
	return convert;
}
/** print_big_int() prints a BigInt.
*** @param *big_int The BigInt to be printed.
*/
void print_big_int(const struct BigInt *big_int)
{
	bool notnulldigitfound = false;
		for (int i = 0; i < big_int->digits_count; i++) {
			if (big_int->the_int[i] > 0 || notnulldigitfound == true)
			{
							printf("%d",big_int->the_int[i]);
							notnulldigitfound = true;
			}
		}
}

/** multiply() multiplies a BigInt by an int.
*** @param big_int The BigInt to be multiplied.
*** @param factor The int value which is multiplied by BigInt.
*** @param *big_result The result of the multiplication.
*/
void multiply(const struct BigInt *big_int, int factor, struct BigInt *big_result)
{
	int overflowNumber=0;
	int tempResult = 0;
	int counter = big_int->digits_count;
	big_result->digits_count = big_int->digits_count;
	for (int i = 0; i < counter; i++) {
		tempResult=big_int->the_int[i]*factor+overflowNumber;
		overflowNumber = 0;
		if (tempResult>9) {
			if (i == big_int->digits_count-1) // last digit > 9
			{
				big_result->digits_count++;
				big_result->the_int[i]=tempResult%10;
				big_result->the_int[i+1]=tempResult/10;
			} else {
				overflowNumber=tempResult/10;
				big_result->the_int[i]=tempResult%10;
			}
		}
		else
		{
			big_result->the_int[i]=tempResult;
		}
	}

}

/** divide() multiplies a BigInt by an int.
*** @param big_int The BigInt to be divided.
*** @param divisor The int value by which we want to devide big_int.
*** @param *big_result The result of the division.
*/
void divide(const struct BigInt *big_int, int divisor, struct BigInt *big_result)
{
	int overflowNumber = 0;
	int tempResult;
		for (size_t i = 0; i < big_int->digits_count; i++) {
			big_result->the_int[i] = 0;
			big_result->digits_count = i+1;
			tempResult = overflowNumber*10 + big_int->the_int[i];
			if (tempResult >= divisor) {
				big_result->the_int[i] = tempResult / divisor;
				overflowNumber = tempResult % divisor;
			}
			else
			{
				overflowNumber = big_int->the_int[i];
			}

		}
}

/** copy_big_int() copies a BigInt to another BigInt.
*** @param from The source where we want to copy from.
*** @param *to The target where we want to copy to.
*/
void copy_big_int(const struct BigInt *from, struct BigInt *to)
{
	from = to;
}

void bigintarray_reverse(struct BigInt *big_int)
{
	int i = big_int->digits_count-1;
  int j = 0;
   while(i > j)
   {
     int temp = big_int->the_int[i];
		 int temp2 = big_int->the_int[j];
     big_int->the_int[i] = temp2;
     big_int->the_int[j] = temp;
     i--;
     j++;
   }
}

/**
*** main() reads the base number from which the pyramid has to be calculated
*** into an array of char. The max. length of this number is MAX_DIGITS.
*** The number is checked to contain only digits. If not the program exits.
*** Then the inputted number is converted into a big int by calling the
*** function strtobig_int().
*** After the conversion the tower is calculated by calling the functions
*** multiply(), print_big_int(), and copy_big_int() consecutively from 2 to
*** 9 and then again with divide() instead of multiply() from 2 to 9.
***
*/
int main(int argc, char *argv[])
{
	char user_input[MAX_DIGITS];
	int length;
	int convert;
	struct BigInt bigint;
	struct BigInt bigint_result;
	struct BigInt bigint_result_devide;
	int factor = 2;
	int divisor = 2;
	printf("Pyramid of Numbers\n");
	printf("==================\n");
	printf("Please enter a number: ");
	scanf("%s", user_input);

	length = strlen(user_input);
	convert = strtobig_int(user_input,length,&bigint);

	if (convert == 0 || user_input[length] == 0)
	{
		return 0;
	}


	//multiply converted number
	for (size_t i = 0; i < 8; i++) {
		multiply(&bigint,factor,&bigint_result);
		bigintarray_reverse(&bigint_result);
		bigintarray_reverse(&bigint);
		print_big_int(&bigint);
		printf(" * %d = ",factor);
		print_big_int(&bigint_result);
		printf("\n");
		bigintarray_reverse(&bigint_result);
		bigintarray_reverse(&bigint);
		bigint = bigint_result;
		factor++;
	}
	bigintarray_reverse(&bigint_result);
	//divide multiplied number
	for (size_t i = 0; i < 8; i++) {
		print_big_int(&bigint_result);
		divide(&bigint_result,divisor,&bigint_result_devide);
		bigint_result = bigint_result_devide;
		printf(" / %d = ",divisor);
		print_big_int(&bigint_result_devide);
		printf("\n");
		divisor++;
	}
	return 0;
}
