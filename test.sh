#!/bin/bash

mkdir -p build/tests

failed=0

build_test() {
  local name=$1
  local source=$2
  local output="build/tests/${name}"
  local log="build/tests/${name}.build.log"

  printf "Building %-22s " "${name}"
  if g++ "${source}" --std=c++26 -Ofast -march=native -fno-rtti -o "${output}" >"${log}" 2>&1; then
    printf "PASS\n"
  else
    printf "FAIL\n"
    cat "${log}"
    failed=1
  fi
}

run_test() {
  local name=$1
  local binary="build/tests/${name}"
  local log="build/tests/${name}.run.log"

  if [ ! -x "${binary}" ]; then
    printf "Running  %-22s SKIP - build failed\n" "${name}"
    return
  fi

  printf "Running  %-22s " "${name}"
  if "${binary}" >"${log}" 2>&1; then
    printf "PASS\n"
  else
    printf "FAIL\n"
    cat "${log}"
    failed=1
  fi
}

build_test "test_bisection" "tests/test_bisection.cpp"
build_test "test_bissection_error" "tests/test_bissection_error.cpp"
build_test "test_newton_raphsor" "tests/test_newton_raphsor.cpp"
build_test "test_false_position" "tests/test_false_position.cpp"

echo

run_test "test_bisection"
run_test "test_bissection_error"
run_test "test_newton_raphsor"
run_test "test_false_position"

echo

if [ "${failed}" -eq 0 ]; then
  echo "Test summary: all tests passed."
else
  echo "Test summary: one or more tests failed."
  exit 1
fi
