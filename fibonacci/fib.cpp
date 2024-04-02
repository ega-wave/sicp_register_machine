
/**
fibonacci(1) -- compute fib(n) with "the register machine."

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
void do3();
void do4();
void do5();
void do6();
void do7();
void do8();
void do9();
void do10();
void do11();
void do12();
void do13();
void do14();
void do15();
void do16();

typedef void (*func)();
func controller[] = {
/*  0: fib-loop:         */ do0  // test n < 2;
/*  1:                   */,do1  // if true goto immediate-answer
/*  2:                   */,do2  // save reg_continue;
/*  3:                   */,do3  // reg_continue = afterfib-n-1
/*  4:                   */,do4  // save reg_n
/*  5:                   */,do5  // reg_n -= 1
/*  6:                   */,do6  // goto fib-loop
/*  7: afterfib-n-1:     */,do7  // restore reg_n
/*  8:                   */,do8  // restore reg_continue
/*  9:                   */,do9  // reg_n -= 2
/* 10:                   */,do2  // save reg_continue;
/* 11:                   */,do10 // reg_continue = afterfib-n-2
/* 12:                   */,do16 // save reg_val;
/* 13:                   */,do6  // goto fib-loop
/* 14: afterfib-n-2:     */,do11 // reg_n = reg_val
/* 15:                   */,do12 // restore val
/* 16:                   */,do8  // restore reg_continue
/* 17:                   */,do13 // reg_val += reg_n
/* 18:                   */,do14 // goto reg_continue;
/* 19: immediate-answer: */,do15 // reg_val = reg_n;
/* 20:                   */,do14 // goto reg_continue;
/* 21: fib-done:         */,0
};

#define LABEL_FIB_LOOP          0
#define LABEL_AFTERFIB_N_1      7
#define LABEL_AFTERFIB_N_2     14
#define LABEL_IMMEDIATE_ANSWER 19
#define LABEL_FIB_DONE         21

/*
static
void
print_stack()
{
  std::stack<int> tmp_stack;
  std::printf("[");

  // the_stack -> tmp_stack
  for (; !the_stack.empty();) {
    int tmp = the_stack.top();
    std::printf("%d ", tmp);
    tmp_stack.push(tmp);
    the_stack.pop();
  }
  std::printf("]\n");

  // tmp_stack -> the_stack
  for (; !tmp_stack.empty();) {
    int tmp = tmp_stack.top();
    the_stack.push(tmp);
    tmp_stack.pop();
  }
}
*/

/**
 * test n < 2;
 */
void do0()
{
//printf(" %2d: %2d %2d %2d ", reg_pc, reg_n, reg_val, reg_continue); print_stack();
  reg_flag = ((reg_n < 2) ? 1 : 0);
  reg_pc++;
}

/**
 * if true goto immediate-answer
 */
void do1()
{
  if (reg_flag) {
    reg_pc = LABEL_IMMEDIATE_ANSWER;
  } else {
    reg_pc++;
  }
}

/**
 * save reg_continue;
 */
void do2()
{
  the_stack.push(reg_continue);
  reg_pc++;
}

/**
 * reg_continue = afterfib-n-1
 */
void do3()
{
  reg_continue = LABEL_AFTERFIB_N_1;
  reg_pc++;
}

/**
 * save reg_n
 */
void do4()
{
  the_stack.push(reg_n);
  reg_pc++;
}

/**
 * reg_n -= 1
 */
void do5()
{
  reg_n -= 1;
  reg_pc++;
}

/**
 * goto fib-loop
 */
void do6()
{
  reg_pc = LABEL_FIB_LOOP;
}

/**
 * restore reg_n
 */
void do7()
{
//printf(" %2d: %2d %2d %2d ", reg_pc, reg_n, reg_val, reg_continue); print_stack();
  reg_n = the_stack.top();
  the_stack.pop();
  reg_pc++;
}

/**
 * restore reg_continue
 */
void do8()
{
  reg_continue = the_stack.top();
  the_stack.pop();
  reg_pc++;
}

/**
 * reg_n -= 2
 */
void do9()
{
  reg_n -= 2;
  reg_pc++;
}

/**
 * reg_continue = afterfib-n-2
 */
void do10()
{
  reg_continue = LABEL_AFTERFIB_N_2;
  reg_pc++;
}

/**
 * reg_n = reg_val
 */
void do11()
{
//printf(" %2d: %2d %2d %2d ", reg_pc, reg_n, reg_val, reg_continue); print_stack();
  reg_n = reg_val;
  reg_pc++;
}

/**
 * restore val
 */
void do12()
{
  reg_val = the_stack.top();
  the_stack.pop();
  reg_pc++;
}

/**
 * reg_val += reg_n
 */
void do13()
{
  reg_val += reg_n;
  reg_pc++;
}

/**
 * goto reg_continue;
 */
void do14()
{
  reg_pc = reg_continue;
}

/**
 * reg_val = reg_n;
 */
void do15()
{
//printf(" %2d: %2d %2d %2d ", reg_pc, reg_n, reg_val, reg_continue); print_stack();
  reg_val = reg_n;
  reg_pc++;
}

/**
 * save reg_val;
 */
void do16()
{
  the_stack.push(reg_val);
  reg_pc++;
}

void fib_main()
{
  for (;;) {
    func f = controller[reg_pc];
    if (! f) break;
    (*f)();
  }
//printf(" %2d: %2d %2d %2d ", reg_pc, reg_n, reg_val, reg_continue); print_stack();
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
 * fibonacci(1) -- compute fib(n)
 * usage: fib
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
  reg_continue = LABEL_FIB_DONE;
  reg_pc = LABEL_FIB_LOOP;

  // main
  fib_main();

  std::printf("%d %d\n", n, reg_val);

  return 0;
}

