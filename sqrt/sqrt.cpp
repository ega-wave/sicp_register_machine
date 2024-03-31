
/**
sqrt -- compute sqrt(d) with "the register machine."

"The register machine" is introduced in the Chapter 5 of the
book "Structure and Interpretation of Computer Programs" by
Harold Abelson and Gerald Jay Sussman with Julie Sussman.

Copyright (C) 2024 Yoshitaka Egawa.

This program is free software: you can redistribute it and/or
modify it under the terms of the GNU General Public License as
published by the Free Software Foundation, either
version 3 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.
If not, see <https://www.gnu.org/licenses/>.
*/

/**
 * Written by Yoshitaka Egawa.
 */

#include <cstdio>

// registers
double reg_x;
double reg_guess;
int reg_flag;
int reg_pc;

void do0();
void do1();
void do2();
void do3();

typedef void (*func)();
func controller[] = {
/*  0: fact-start: */ do0 // good_enough?(reg_guess);
/*  1:             */,do1 // if true goto sqrt-done;
/*  2:             */,do2 // improve(guess);
/*  3:             */,do3 // goto sqrt-start;
/*  4: sqrt-done:  */,0
};

#define LABEL_SQRT_START 0
#define LABEL_SQRT_DONE  4

static
double
abs(double d)
{
  return d > 0 ? d : -d;
}

/**
 * good_enough?(reg_guess);
 */
void do0()
{
  reg_flag = ((abs(reg_guess * reg_guess - reg_x) < 0.001) ? 1 : 0);
  reg_pc++;
}

/**
 * if true goto sqrt-done;
 */
void do1()
{
  if (reg_flag) {
    reg_pc = LABEL_SQRT_DONE;
  } else {
    reg_pc++;
  }
}

static
double
average(double d1, double d2)
{
  return (d1+d2)/2;
}

/**
 * improve(guess);
 */
void do2()
{
  reg_guess = average(reg_guess, reg_x/reg_guess);
  reg_pc++;
}

/**
 * goto sqrt-start;
 */
void do3()
{
  reg_pc = LABEL_SQRT_START;
}

void sqrt_main()
{
  for (;;) {
    func f = controller[reg_pc];
    if (! f) break;
    (*f)();
  }
}

/**
 * sqrt(1) -- compute square root of double-precision value
 * usage: ./sqrt
 * caution: d-value is written in main();
 */
int main(int argc, char* argv[])
{
  // prepare
  double d = 2.0;
  reg_x = d;
  reg_guess = 1.0;
  reg_pc = LABEL_SQRT_START;

  // main
  sqrt_main();

  std::printf("%lf %lf\n", d, reg_guess);

  return 0;
}

