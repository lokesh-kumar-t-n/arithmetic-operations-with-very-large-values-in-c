//A sample client for intal.h

/*
First intal: 4999
Second intal: 2001
Two intals after increment and decrement:
5000
2000
Max of two intals: 5000
Sum: 7000
Diff: 3000
Product: 10000000
Quotient: 2
5000 ^ 2: 25000000
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "intal.h"
int main(int argc, char const *argv[]) {
	char *str1 = "4999";
	char *str2 = "2001";
	void *intal1;
	void *intal2;
	void *sum;
	void *diff;
	void *product;
	void *quotient;
	void *exp;
	void *str;
	intal1 = intal_create(str1); //4999
	intal2 = intal_create(str2); //2001
	str = intal2str(intal1);
	printf("First intal: %s\n", str); //4999
	free(str);
	str = intal2str(intal2);
	printf("Second intal: %s\n", str); //2001
	free(str);

	intal1 = intal_increment(intal1); //5000
	intal2 = intal_decrement(intal2); //2000

	printf("Two intals after increment and decrement:\n");
	str = intal2str(intal1);
	printf("%s\n", str); //5000
	free(str);
	str = intal2str(intal2);
	printf("%s\n", str); //2000
  free(str);

	str=(intal_compare(intal1, intal2) > 0) ? intal2str(intal1) : intal2str(intal2);
	printf("Max of two intals: %s\n", str);//5000
	free(str);
	sum = intal_add(intal1,intal2); //7000
	str = intal2str(sum);
	printf("Sum: %s\n", str);
	free(str);

	diff = intal_diff(intal1, intal2); //3000
	str = intal2str(diff);
	printf("Diff: %s\n", str);
	free(str);

	product = intal_multiply(intal1, intal2); //10000000
	str = intal2str(product);
	printf("Product: %s\n", str);
	free(str);

	quotient = intal_divide(intal1, intal2); //2
	str = intal2str(quotient);
	printf("Quotient: %s\n", str);
	free(str);

	exp = intal_pow(intal1, quotient); //5000^2 = 25000000
	str = intal2str(exp);
	printf("%s ^ %s: %s\n", intal2str(intal1), intal2str(quotient), intal2str(exp));

	//Make sure you destroy all the intals created.
	intal_destroy(sum);
	intal_destroy(diff);
	intal_destroy(product);
	intal_destroy(quotient);
	intal_destroy(exp);
	intal_destroy(intal1);
	intal_destroy(intal2);
	return 0;
}
