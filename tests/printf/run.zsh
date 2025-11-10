#!/usr/bin/env zsh

TEST_DIR="${HOME}/.42_ultimate_tester/tests/printf"
MAKEFILE="${TEST_DIR}/Makefile"

RED="\033[0;31m"
NONE="\033[0m"

main()
{
	compile_printf

	cp "${MAKEFILE}" "${MAKEFILE}.backup"
	update_makefile

	compile_tester

	mv "${MAKEFILE}.backup" "${MAKEFILE}"

	"${TEST_DIR}"/ft_printf_tester
	exit $?
}

compile_printf()
{
	make fclean > /dev/null 2>&1
	make > /dev/null || fail "Compilation failed" $?
}

compile_tester()
{
	make fclean -C ${TEST_DIR} > /dev/null 2>&1
	make -C ${TEST_DIR} > /dev/null 2>&1 || fail "Compilation failed" $?
}

update_makefile()
{
	local include_dirs include_flags

	include_dirs=($(find "${PWD}" -type f -name "*.h" -exec dirname {} \; | sort -u))

	include_flags=""
	for dir in "${include_dirs[@]}"; do
		include_flags+=" -I${dir}"
	done

	if sed --version >/dev/null 2>&1; then
		# GNU sed (Linux)
		sed -E -i "s|^INCLUDES$|INCLUDES :=${include_flags}|" "$MAKEFILE" 2>/dev/null
		sed -E -i "s|^LIBFT$|LIBFT :=${PWD}/libftprintf.a|" "$MAKEFILE" 2>/dev/null
	else
		# BSD sed (macOS)
		sed -E -i '' "s|^INCLUDES$|INCLUDES :=${include_flags}|" "$MAKEFILE" 2>/dev/null
		sed -E -i '' "s|^LIBFT$|LIBFT :=${PWD}/libftprintf.a|" "$MAKEFILE" 2>/dev/null
	fi
}

fail()
{
	local message="$1"
	local error_code="${2:-1}"

	echo -e "\n${RED}===> ❌ ${message}${NONE}" >&2
	exit error_code
}

main
