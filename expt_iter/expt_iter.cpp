
/**
expt -- compute expt_iter(b,n) with "the register machine."

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
int reg_b;
int reg_counter;
int reg_product;
int reg_flag;
int reg_pc;

void do0();
void do1();
void do2();
void do3();
void do4();

typedef void (*func)();
func controller[] = {
/* 0: expt-loop: */ do0 // test counter == 0
/* 1:            */,do1 // if true, goto expt-done
/* 2:            */,do2 // counter -= 1
/* 3:            */,do3 // product *= b
/* 4:            */,do4 // goto expt-loop
/* 5: expt-done: */,0
};

#define LABEL_EXPT_LOOP 0
#define LABEL_EXPT_DONE 5

/**
 * test counter == 0
 */
void do0()
{
  reg_flag = ((reg_counter == 0) ? 1 : 0);
  reg_pc++;
}

/**
 * if true, goto expt-done
 */
void do1()
{
  if (reg_flag) {
    reg_pc = LABEL_EXPT_DONE;
  } else {
    reg_pc++;
  }
}

/**
 * counter -= 1
 */
void do2()
{
  reg_counter -= 1;
  reg_pc++;
}

/**
 * product *= b
 */
void do3()
{
  reg_product *= reg_b;
  reg_pc++;
}

/**
 * goto expt-loop
 */
void do4()
{
  reg_pc = LABEL_EXPT_LOOP;
}

void expt_iter_main()
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
 * expt_iter(1) -- compute b^n
 * usage: ./expt_iter b n
 * args : b .. integer
 * args : n .. integer
 */
int main(int argc, char* argv[])
{
  // prepare
  if (argc != 3) {
    return 1;
  }
  int b = atoi(argv[1]);
  int n = atoi(argv[2]);
  reg_b = b;
  reg_counter = n;
  reg_product = 1;
  reg_pc = LABEL_EXPT_LOOP;

  // main
  expt_iter_main();

  std::printf("%d %d %d\n", b, n, reg_product);

  return 0;
}

