#!/usr/bin/bash

# usage: bash test.sh

# assert()
# usage: assert input1 input2 expected
assert() {
  input1="$1"
  input2="$2"
  expected="$3"

  actual=$(./gcd "$input1" "$input2" | awk '{print $3}')

  if [ "$actual" = "$expected" ]; then
    echo "$input1 $input2 => $actual"
  else
    echo "$input1 $input2  => $expected expected, but got $actual"
    exit 1
  fi
}

assert 1 1 1
assert 2 2 2
assert 70 15 5

echo OK

