
/**
gcd -- compute gcd(n,m) with "the register machine."

"The register machine" is introduced in the Chapter 5 of the
book "Structure and Interpretation of Computer Programs" by
Harold Abelson and Gerald Jay Sussman with Julie Sussman.
 */

/**
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
int reg_a;
int reg_b;
int reg_t;
int reg_flag;
int reg_pc;

void do0();
void do1();
void do2();
void do3();
void do4();
void do5();

typedef void (*func)();
func controller[] = {
/*  0: test-b:   */ do0 // test reg_b == 0;
/*  1:           */,do1 // if true, goto gcd-done;
/*  2:           */,do2 // reg_t = reg_a % reg_b;
/*  3:           */,do3 // reg_a = reg_b;
/*  4:           */,do4 // reg_b = reg_t;
/*  5:           */,do5 // goto test-b;
/*  6: gcd-done: */,0
};

#define LABEL_TEST_B    0
#define LABEL_GCD_DONE  6

/**
 * test reg_b == 0;
 */
void do0()
{
  reg_flag = ((reg_b == 0) ? 1 : 0);
  reg_pc++;
}

/**
 * if true, goto gcd-done;
 */
void do1()
{
  if (reg_flag) {
    reg_pc = LABEL_GCD_DONE;
  } else {
    reg_pc++;
  }
}

/**
 * reg_t = reg_a % reg_b;
 */
void do2()
{
  reg_t = reg_a % reg_b;
  reg_pc++;
}

/**
 * reg_a = reg_b;
 */
void do3()
{
  reg_a = reg_b;
  reg_pc++;
}

/**
 * reg_b = reg_t;
 */
void do4()
{
  reg_b = reg_t;
  reg_pc++;
}

/**
 * goto test-b;
 */
void do5()
{
  reg_pc = LABEL_TEST_B;
}

void gcd_main()
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
 * gcd(1) -- compute Greatest Common Divisor (GCD)
 * usage: gcd n m
 * args : n .. integer (n >= m)
 *        m .. integer
 */
int main(int argc, char* argv[])
{
  // prepare
  if (argc != 3) {
    return 1;
  }
  int n = atoi(argv[1]);
  int m = atoi(argv[2]);
  reg_a = n;
  reg_b = m;
  reg_pc = LABEL_TEST_B;

  // main
  gcd_main();

  std::printf("%d %d %d\n", n, m, reg_a);

  return 0;
}

