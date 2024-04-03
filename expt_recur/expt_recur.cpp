
/**
expt -- compute expt_recur(b,n) with "the register machine."

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

#include <stack>
#include <cstdio>

// registers
int reg_b;
int reg_n;
int reg_val;
int reg_continue;
int reg_flag;
int reg_pc;

// stack
std::stack<int> the_stack;

void do0();
void do1();
void do2();
void do4();
void do5();
void do6();
void do8();
void do9();
void do10();
void do11();

typedef void (*func)();
func controller[] = {
/*  0: expt-loop:  */ do0 // test n == 0
/*  1:             */,do1 // if true, goto base_case
/*  2:             */,do2 // save continue
/*  3:             */,do4 // n = n -1
/*  4:             */,do5 // continue = after-expt
/*  5:             */,do6 // goto expt-loop
/*  6:             */,do8 // restore continue
/*  7:             */,do9 // val = val * b
/*  8:             */,do10 // goto continue
/*  9: base-case:  */,do11 // val = 1
/* 10:             */,do10 // goto continue
/* 11: expt-done   */,0
};

#define LABEL_EXPT_LOOP  0
#define LABEL_AFTER_EXPT 6
#define LABEL_BASE_CASE  9
#define LABEL_EXPT_DONE 11

/**
 * test n == 0
 */
void do0()
{
  reg_flag = ((reg_n == 0) ? 1 : 0);
  reg_pc++;
}

/**
 * if true, goto base_case
 */
void do1()
{
  if (reg_flag) {
    reg_pc = LABEL_BASE_CASE;
  } else {
    reg_pc++;
  }
}

/**
 * save continue
 */
void do2()
{
  the_stack.push(reg_continue);
  reg_pc++;
}

/**
 * n = n -1
 */
void do4()
{
  reg_n--;
  reg_pc++;
}

/**
 * continue = after-expt
 */
void do5()
{
  reg_continue = LABEL_AFTER_EXPT;
  reg_pc++;
}

/**
 * goto expt-loop
 */
void do6()
{
  reg_pc = LABEL_EXPT_LOOP;
}

/**
 * restore continue
 */
void do8()
{
  reg_continue = the_stack.top();
  the_stack.pop();
  reg_pc++;
}

/**
 * val = val * b
 */
void do9()
{
  reg_val *= reg_b;
  reg_pc++;
}

/**
 * goto continue
 */
void do10()
{
  reg_pc = reg_continue;
}

/**
 * val = 1
 */
void do11()
{
  reg_val = 1;
  reg_pc++;
}

void expt_recur_main()
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
 * expt_recur(1) -- compute b^n
 * usage: ./expt_recur b n
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
  reg_n = n;
  reg_continue = LABEL_EXPT_DONE;
  reg_pc = LABEL_EXPT_LOOP;

  // main
  expt_recur_main();

  std::printf("%d %d %d\n", b, n, reg_val);

  return 0;
}

