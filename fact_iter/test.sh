#!/usr/bin/bash

# usage: bash factorial_test.sh

# assert()
# usage: assert input expected
assert() {
  input="$1"
  expected="$2"

  actual=$(./fact_iter "$input" | awk '{print $2}')

  if [ "$actual" = "$expected" ]; then
    echo "$input => $actual"
  else
    echo "$input => $expected expected, but got $actual"
    exit 1
  fi
}

assert 1 1
assert 2 2
assert 3 6
assert 4 24
assert 5 120
assert 6 720
assert 7 5040
assert 8 40320
assert 9 362880
assert 10 3628800
assert 11 39916800

echo OK

