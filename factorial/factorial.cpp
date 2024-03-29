
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

typedef void (*func)();
func controller[] = {
/*  0: fact-loop:  */ do0
/*  1:             */,do1
/*  2:             */,do2
/*  3:             */,do3
/*  4:             */,do4
/*  5:             */,do5
/*  6:             */,do6
/*  7: after-fact: */,do7
/*  8:             */,do8
/*  9:             */,do9
/* 10:             */,do10
/* 11: base-case:  */,do11
/* 12:             */,do10
/* 13: fact-done   */,0
};

#define LABEL_FACT_LOOP  0
#define LABEL_AFTER_FACT 7
#define LABEL_BASE_CASE 11
#define LABEL_FACT_DONE 13

/**
 * (test (op =) (reg n) (const 1))
 */
void do0()
{
  reg_flag = ((reg_n == 1) ? 1 : 0);
  reg_pc++;
}

/**
 * (branch (label base-case))
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
 * (save continue)
 */
void do2()
{
  the_stack.push(reg_continue);
  reg_pc++;
}

/**
 * (save n)
 */
void do3()
{
  the_stack.push(reg_n);
  reg_pc++;
}

/**
 * (assign n (op -) (reg n) (const 1))
 */
void do4()
{
  reg_n--;
  reg_pc++;
}

/**
 * (assign continue (label after-fact))
 */
void do5()
{
  reg_continue = LABEL_AFTER_FACT;
  reg_pc++;
}

/**
 * (goto (label fact-loop))
 */
void do6()
{
  reg_pc = LABEL_FACT_LOOP;
}

/**
 * (restore n)
 */
void do7()
{
  reg_n = the_stack.top();
  the_stack.pop();
  reg_pc++;
}

/**
 * (restore continue)
 */
void do8()
{
  reg_continue = the_stack.top();
  the_stack.pop();
  reg_pc++;
}

/**
 * (assign val (op *) (reg n) (reg val))
 */
void do9()
{
  reg_val *= reg_n;
  reg_pc++;
}

/**
 * (goto (reg continue))
 */
void do10()
{
  reg_pc = reg_continue;
}

/**
 * (assign val (const 1))
 */
void do11()
{
  reg_val = 1;
  reg_pc++;
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
  reg_continue = LABEL_FACT_DONE; // (assign continue (label fact-done))
  reg_pc = LABEL_FACT_LOOP;

  // main
  factorial_main();

  std::printf("%d %d\n", n, reg_val);

  return 0;
}

