
/**
 * (define (factorial n)
 *   (if (= n 1)
 *       1
 *       (* (factorial (- n 1)) n))) 
 */

/**

(controller
   (assign continue (label fact-done))
 fact-loop   
   (test (op =) (reg n) (const 1))
   (branch (label base-case))
   (save continue)
   (save n)
   (assign n (op -) (reg n) (const 1))
   (assign continue (label after-fact))
   (goto (label fact-loop))
 after-fact
   (restore n)
   (restore continue)
   (assign val (op *) (reg n) (reg val)) ; val = n * (n-1)!;
   (goto (reg continue))
 base-case
   (assign val (const 1))
   (goto (reg continue))
 fact-done)

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

func library [] = {
 do0 // (test (op =) (reg n) (const 1))
,do1 // (branch (label base-case))
,do2 // (save continue)
,do3 // (save n)
,do4 // (assign n (op -) (reg n) (const 1))
,do5 // (assign continue (label after-fact))
,do6 // (goto (label fact-loop))
,do7 // (restore n)
,do8 // (restore continue)
,do9 // (assign val (op *) (reg n) (reg val))
,do10 // (goto (reg continue))
,do11 // (assign val (const 1))
};

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

