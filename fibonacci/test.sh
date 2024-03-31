#!/usr/bin/bash

# usage: bash test.sh

# assert()
# usage: assert input expected
assert() {
  input="$1"
  expected="$2"

  actual=$(./fib "$input" | awk '{print $2}')

  if [ "$actual" = "$expected" ]; then
    echo "$input => $actual"
  else
    echo "$input => $expected expected, but got $actual"
    exit 1
  fi
}

assert 1 1
assert 2 1
assert 3 2
assert 4 3
assert 5 5
assert 6 8
assert 7 13
assert 8 21
assert 9 34
assert 10 55
assert 11 89
assert 12 144
assert 13 233
assert 14 377
assert 15 610
assert 16 987
assert 17 1597
assert 18 2584
assert 19 4181

echo OK

