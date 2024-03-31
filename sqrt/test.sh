#!/usr/bin/bash

# usage: bash test.sh

# assert()
# usage: assert input expected
assert() {
  input="$1"
  expected="$2"

  actual=$(./sqrt "$input" | awk '{print $2}')

  if [ "$actual" = "$expected" ]; then
    echo "$input => $actual"
  else
    echo "$input => $expected expected, but got $actual"
    exit 1
  fi
}

assert 2 1.414216

echo OK

