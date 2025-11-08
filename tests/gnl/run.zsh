#!/usr/bin/env zsh

TESTS_DIR="${HOME}/.42_ultimate_tester/tests/gnl"

TARGET="${TESTS_DIR}/test_gnl"
FILES=("get_next_line.c" "get_next_line_utils.c" "get_next_line.h")
BUFFER_SIZE_VALUES=(1 2 3 4 5 10 42 1000 9999 10000000)

INPUTS_DIR="${TESTS_DIR}/inputs"
EXPECTED_DIR="${TESTS_DIR}/expected"
OUTPUT_DIR="${TESTS_DIR}/outputs"

PASSED=0
FAILED=0
TOTAL=0

RED="\033[31m"
GREEN="\033[32m"
YELLOW="\033[33m"
BLUE="\033[34m"
NONE="\033[0m"

main()
{
	init
	check_files
	# Test each buffer_size
	for buffer_size in "${BUFFER_SIZE_VALUES[@]}"; do
		echo " ${BLUE}⏱${NONE} Testing with ${BLUE}BUFFER_SIZE=$buffer_size${NONE}..."
		compile $buffer_size

		# Test each input_file
		for f in "${INPUTS_DIR}"/*; do
			filename="$(basename "$f")"
			input_file="${INPUTS_DIR}/${filename}"
			expected_file="${EXPECTED_DIR}/${filename}"
			output_file="${OUTPUT_DIR}/${filename}"

			# Test with file as argument
			"${TARGET}" "${input_file}" | cat -e > "${output_file}"
			check_output "BUFFER_SIZE=$buffer_size\n${TESTS_DIR}/${TARGET} ${input_file} | cat -e" "${expected_file}" "${output_file}"

			# Test with file as stdin
			output_file="${OUTPUT_DIR}/stdin_${filename}"
			cat "${input_file}" | "${TARGET}" | cat -e > "${output_file}"
			check_output "cat ${input_file} | ${TARGET} | cat -e" "${expected_file}" "${output_file}"
		done
	done
	print_results
}

init()
{
	rm -f "${TARGET}" || true
	rm -rf "${OUTPUT_DIR}" || true
	mkdir -p "${OUTPUT_DIR}"
}

check_files()
{
	echo " ${BLUE}⏱${NONE} Checking ${BLUE}files${NONE}..."
	for f in "${FILES[@]}"; do
		if [[ ! -f "${f}" ]]; then
			echo " ❌ ${RED}${f} not found${NONE}"
			exit 1
		fi
	done
}

compile()
{
	local buffer_size=$1

	cc -Wall -Wextra -Werror \
		-D BUFFER_SIZE=$buffer_size \
		-I. ${TESTS_DIR}/main.c get_next_line.c get_next_line_utils.c \
		-o "${TARGET}"
	if [[ $? -ne 0 ]]; then
		local error_code= $?
		echo " ❌ ${RED}Compilation FAILED for BUFFER_SIZE=$buffer_size${NONE}"
		exit $error_code
	elif [[ ! -f "${TARGET}" ]]; then
		echo " ❌ ${RED}${TARGET} not found${NONE}"
		exit 1
	elif [[ ! -x "${TARGET}" ]]; then
		echo " ❌ ${RED}${TARGET} is not executable${NONE}"
		exit 1
	fi
}

check_output()
{
	local test_name="$1"
	local expected_file="$2"
	local output_file="$3"

	if [[ ! -f "$expected_file" ]]; then
		echo " ⚠️ ${YELLOW}Missing expected file: $expected_file${NONE}"
		((FAILED++))
	elif diff -q "${expected_file}" "${output_file}" > /dev/null; then
		((PASSED++))
	else
		((FAILED++))
		echo "------------------------------"
		echo
		echo " ❌ ${RED}${test_name}${NONE}"
		echo
		echo " ⮕ diff ${expected_file} ${output_file}"
		echo
		diff "${expected_file}" "${output_file}"
		echo
		echo "------------------------------"
	fi
	((TOTAL++))
}

print_results()
{
	echo
	if (( FAILED == 0 )); then
		echo "===> ✅ ${GREEN}${PASSED} / ${TOTAL} tests PASSED${NONE}"
		exit 0
	else
		echo "===> ❌ ${RED}${FAILED} / ${TOTAL} tests FAILED${NONE}"
		exit 1
	fi
}

main
