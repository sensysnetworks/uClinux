
#include <stdio.h>

#define PSH(X) (*(buf++)=(X))
#define PSH1(X) (*(buf--)=(X))
#define PEEK() buf[-1]
#define POP() *(--buf) = '\0'

#define PLUS 1
#define SPACE 2

char * gcvt(double f, size_t ndigit, char * buf)
{
  int i;
  int l1,l2; //length of float before and after
  unsigned long long z,k,k2;
  int exp = 0;
  char *c = buf;
  double f2,t,scal;
  int   sign = 0;

  if((int)ndigit == -1)
    ndigit = 5;

  /* Unsigned long long only allows for 20 digits of precision
   * which is already more than double supports, so we limit the
   * digits to this.  long double might require an increase if it is ever
   * implemented.
   */
  if (ndigit > 20)
	  ndigit = 20;
  
  if (f < 0.0) {
    sign = 1;
    f = -f;

	 buf++;
  }

  scal = 1;
  for (i=ndigit; i>0; i--)
	  scal *= 10;
  k = f + 0.5 / scal;
  f2 = f - k;
  if (!f) {
    PSH('0');
    if(ndigit > 0)
      PSH('.');
    for (i=0;i<ndigit;i++)
      PSH('0');
  	   PSH(0);
  	 return c;
  }

  i = 1;
  while (f >= 10.0) {
  	f /= 10.0;
  	i++;
  }

  l1 = i;

  k2 = k;

  l2 = 1;
  do {
	if(k2>=10) {
		l2++;
	}
    k2 /= 10;
  }while (k2);

/* increase pointer if it rolls over an extra digit */
  if(l2>l1) {
  	buf += i + ndigit + 2; 
  } else {
  	buf += i + ndigit + 1; 
  }

  PSH1(0);

  if(ndigit > 0) {	
	  t = f2 * scal;
	 z = t + 0.5;
    for (i = 0;i < ndigit;i++)
    {
      PSH1('0'+ (z % 10));
	   z /= 10;
    }
    PSH1('.');
  }
  else
    PSH1(0);

  l2 = 1;
  do {
    PSH1('0'+ (k % 10));
	if(k>=10) {
		l2++;
	}
    k /= 10;
  }while (k);

  if (sign)
    PSH1('-');
  return c;
}


