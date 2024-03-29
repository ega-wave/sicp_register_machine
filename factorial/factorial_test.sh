#!/usr/bin/bash

# usage: bash factorial_test.sh

# assert()
# usage: assert expected input
assert() {
  expected="$1"
  input="$2"

  actual=$(./factorial "$input" | awk '{print $2}')

  if [ "$actual" = "$expected" ]; then
    echo "$input => $actual"
  else
    echo "$input => $expected expected, but got $actual"
    exit 1
  fi
}

assert 1 1
assert 2 2
assert 6 3
assert 24 4
assert 120 5
assert 720 6
assert 5040 7
assert 40320 8
assert 362880 9
assert 3628800 10
assert 39916800 11

echo OK

