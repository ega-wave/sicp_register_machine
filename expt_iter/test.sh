#!/usr/bin/bash

# usage: bash test.sh

# assert()
# usage: assert input1 input2 expected
assert() {
  input1="$1"
  input2="$2"
  expected="$3"

  actual=$(./expt_iter "$input1" "$input2" | awk '{print $3}')

  if [ "$actual" = "$expected" ]; then
    echo "$input1 $input2 => $actual"
  else
    echo "$input1 $input2 => $expected expected, but got $actual"
    exit 1
  fi
}

assert 1 0 1
assert 1 1 1
assert 1 2 1
assert 2 0 1
assert 2 1 2
assert 2 2 4
assert 2 3 8
assert 3 0 1
assert 3 1 3
assert 3 2 9
assert 3 3 27 
assert 3 4 81 
assert 3 5 243

echo OK

