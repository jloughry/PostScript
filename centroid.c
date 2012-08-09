#include <math.h>
#include <stdio.h>
#include <stdlib.h>

double f1(double x, double r);
double indefinite_integral_f1_dx(double r, double x);
double definite_integral_f1_dx(double r, double x, double a, double b);
double square(double x);
double x_intercept(double r);


double f1(double x, double r)
{
   if (x < -1.0) {
      fprintf (stderr, "f1(x) is undefined for x < -1\n");
      exit (EXIT_FAILURE);
   }
   else if (x < 0.0) {
      return (r / 2.0);
   }
   else if (x < x_intercept(r)) {
      return (sqrt(square(r) - square(x)) - (r / 2.0));
   }
   else {
      fprintf (stderr, "f1(x) is undefined for x > %lf\n", x_intercept(r));
      exit (EXIT_FAILURE);
   }
}

double indefinite_integral_f1_dx(double r, double x)
{
   return (-0.5 * atan((x * sqrt(square(r) - square(x))) / (square(x) - square(r)))
                * square(r)
            - (x * r) / 2.0 + 0.5 * x * sqrt(square(r) - square(x)));
}

double definite_integral_f1_dx(double r, double x, double a, double b)
{
   double value_at_point_b = 0.0;
   double value_at_point_a = 0.0;

   value_at_point_a = indefinite_integral_f1_dx(r, a);
   value_at_point_b = indefinite_integral_f1_dx(r, b);

   return (value_at_point_b - value_at_point_a);
}

double square(double x)
{
   return (x * x);
}

double x_intercept(double r)
{
   return (sqrt (square(r) - (square(r) / 4.0)));
}

#define RADIUS	3.0
#define USAGE	"Usage: %s x"

int main(int argc, char ** argv)
{
	double x = 0.0;
	double r = RADIUS;
	double a = -1.0;
	double b = 0.0;

   switch (argc) {
      case 2:
         x = atof(argv[1]);
			break;
      default:
			fprintf (stderr, USAGE "\n", argv[0]);
			exit (EXIT_FAILURE);
         break;
   }

	fprintf (stdout, "x = %lf\n", x);
	fprintf (stdout, "r = %lf\n", r);

	a = 0.0;
	b = x_intercept(r);

	fprintf (stdout, "x-intercept is at %lf\n", b);

	fprintf (stdout, "area under curve(-1.0, 0.0] = 1.5\n");

	fprintf (stdout, "area under curve(%lf, %lf) = %lf\n",
		a, b, definite_integral_f1_dx(r, x, a, b));

	fprintf (stdout, "total area under curve(-1.0,x-intercept) = %lf\n",
		1.5 + definite_integral_f1_dx(r, x, a, b));

   return (EXIT_SUCCESS);
}

