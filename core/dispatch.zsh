#!/usr/bin/env zsh

TESTS_DIR="${HOME}/.42_ultimate_tester/tests"
RUNNER="run.zsh"

RED="\033[31m"
YELLOW="\033[33m"
NONE="\033[0m"

main()
{
	if [[ -f "get_next_line.c" ]]; then
		echo -e " 🧪 Testing ${YELLOW}GET NEXT LINE${NONE} project...\n"
		"${TESTS_DIR}/gnl/${RUNNER}"
		exit $?
	fi

	if grep -q "libftprintf\.a" Makefile 2>/dev/null; then
		echo -e " 🧪 Testing ${YELLOW}PRINTF${NONE} project...\n"
		"${TESTS_DIR}/printf/${RUNNER}"
		exit $?
	fi

	echo " ❌ Error: ${RED}Unable to identify current project${NONE}" >&2
	exit 1
}

main
