
/**
factorial -- compute factorial(n) with "the register machine."

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
int reg_n;
int reg_product;
int reg_counter;
int reg_flag;
int reg_pc;

void do0();
void do1();
void do2();
void do3();
void do4();

typedef void (*func)();
func controller[] = {
/*  0: fact-start: */ do0 // reg_counter > reg_n;
/*  1:             */,do1 // if true goto fact-done;
/*  2:             */,do2 // reg_product *= reg_counter;
/*  3:             */,do3 // reg_counter += 1;
/*  4:             */,do4 // goto fact-start;
/*  5: fact-done:  */,0
};

#define LABEL_FACT_START 0
#define LABEL_FACT_DONE  5

/**
 * reg_counter > reg_n;
 */
void do0()
{
  reg_flag = ((reg_counter > reg_n) ? 1 : 0);
  reg_pc++;
}

/**
 * if true goto fact-done;
 */
void do1()
{
  if (reg_flag) {
    reg_pc = LABEL_FACT_DONE;
  } else {
    reg_pc++;
  }
}

/**
 * reg_product *= reg_counter;
 */
void do2()
{
  reg_product *= reg_counter;
  reg_pc++;
}

/**
 * reg_counter += 1;
 */
void do3()
{
  ++reg_counter;
  reg_pc++;
}

/**
 * goto fact-start;
 */
void do4()
{
  reg_pc = LABEL_FACT_START;
}

void factorial_main()
{
  for (;;) {
    func f = controller[reg_pc];
    if (! f) break;
    (*f)();
  }
}

static
int
atoi(const char* s)
{
  int ret = 0;

  for (; *s && ('0' <= *s) && (*s <= '9'); ++s) {
    ret *= 10;
    ret += *s - '0';
  }
  return ret;
}

/**
 * factorial(1) -- compute n!
 * usage: ./factorial n
 * args : n .. integer
 */
int main(int argc, char* argv[])
{
  // prepare
  if (argc != 2) {
    return 1;
  }
  int n = atoi(argv[1]);
  reg_n = n;
  reg_product = 1;
  reg_counter = 1;
  reg_pc = LABEL_FACT_START;

  // main
  factorial_main();

  std::printf("%d %d\n", n, reg_product);

  return 0;
}

