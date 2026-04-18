#include <stdio.h>
int countdigits(long n) {
  if ( n == 0 )
      return 0;
  else
      return 1+ countdigits(n / 10 );
}
int main () {
    long number ;
    printf("Enter your number :");
    scanf("%ld", &number );
    if (number  == 0) {
         printf("The number of digits is: 1\n");
    } else {
        long temp = (number < 0) ? -number : number;
        printf("The number of digits is: %d\n", countdigits(number));
    }

    return 0;
}


