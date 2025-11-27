#!/usr/bin/env zsh

# Variables for update()
typeset -g INSTALL_DIR="${HOME}/.42_ultimate_tester"
typeset -g REPO_URL="github.com/guillaumeast/42_ultimate_tester"
typeset -g INSTALLER_URL="https://raw.githubusercontent.com/guillaumeast/42_ultimate_tester/master/1_launcher/install.zsh"

# Variables for Makefile
typeset -g PROJ_NAME=""
typeset -g PROJ_DIR=""
typeset -ga PROJ_SRCS=()
typeset -ga PROJ_INCLUDES=()
typeset -ga PROJ_LIBS=()

# Colors
typeset -g BGREY="\033[1;90m"
typeset -g GREY="\033[0;90m"
typeset -g BORANGE="\033[1;38;5;214m"
typeset -g ORANGE="\033[38;5;214m"
typeset -g BRED="\033[1;31m"
typeset -g RED="\033[0;31m"
typeset -g BGREEN="\033[1;32m"
typeset -g GREEN="\033[0;32m"
typeset -g BYELLOW="\033[1;33m"
typeset -g YELLOW="\033[0;33m"
typeset -g BBLUE="\033[1;34m"
typeset -g BLUE="\033[0;34m"
typeset -g BMAG="\033[1;35m"
typeset -g MAG="\033[0;35m"
typeset -g CYAN="\033[0;36m"
typeset -g BCYAN="\033[1;36m"
typeset -g BWHITE="\033[1;37m"
typeset -g NC="\033[0m"


main()
{
	print_ascii_art
	update
	dispatch
}

print_ascii_art()
{
	printf "\n   ${CYAN}╭─────────────────────────────────────────╮${NC}\n"
	printf "   ${CYAN}│           ${BBLUE}42 ULTIMATE TESTER${CYAN}            │\n"
	printf "   ${CYAN}╰─────────────────────────────────────────╯${NC}\n\n"
}

#-------------------------- Printer -------------------------#

print_project_name()
{
	printf "   ${CYAN}╭─────────────────────────────────────────╮${NC}\n"
	if [[ "$PROJ_NAME" == "libft" ]]; then
		printf "   ${CYAN}│                  ${BBLUE}LIBFT${CYAN}                  │\n"
	elif [[ "$PROJ_NAME" == "printf" ]]; then
		printf "   ${CYAN}│                 ${BBLUE}PRINTF${CYAN}                  │\n"
	elif [[ "$PROJ_NAME" == "gnl" ]]; then
		printf "   ${CYAN}│                   ${BBLUE}GNL${CYAN}                   │\n"
	else
		printf "   ${CYAN}│                  ${BBLUE}TESTS${CYAN}                  │\n"
	fi
	printf "   ${CYAN}╰─────────────────────────────────────────╯${NC}\n\n"
}

print_h1()
{
	printf " ${GREY}➜${BORANGE} ${1} ${NC}"
}

print_indicator_pass()
{
	printf "${GREEN}✔${NC} "
}

print_indicator_fail()
{
	printf "${RED}✖${NC} "
}

print_error()
{
	printf "    ${GREY}⤷ ${RED}${1}${NC}\n" >&2
}

#-------------------------- Updater -------------------------#

update()
{
	local fetch_cmd

	printf "${GREY} ➜ ${REPO_URL}${NC}\n\n"
	printf "${GREY} ⏱ Updating...${NC}\n"
	(
		cd "${INSTALL_DIR}"
		if ! git pull > /dev/null 2>&1; then
			if command -v curl >/dev/null 2>&1; then
				if ! curl -fsSL "${INSTALLER_URL}" | zsh > /dev/null 2>&1; then
					printf " ${YELLOW}⚠ Update failed. Skipping.${NC}\n" >&2
					printf " ${GREY}ℹ Manual update: 'curl -fsSL ${INSTALLER_URL}'${NC}\n" >&2
				else
					printf " ${GREY}✔ Updated${NC}\n"
				fi
			elif command -v wget >/dev/null 2>&1; then
				if ! wget -qO- "${INSTALLER_URL}" | zsh > /dev/null 2>&1; then
					printf " ${YELLOW}⚠ Update failed. Skipping.${NC}\n" >&2
					printf " ${GREY}ℹ Manual update: 'wget -qO- ${INSTALLER_URL}'${NC}\n" >&2
				else
					printf " ${GREY}✔ Updated${NC}\n"
				fi
			else
				printf " ${YELLOW}⚠ Update failed: curl or wget is required. Skipping.${NC}\n" >&2
			fi
		else
			printf " ${GREY}✔ Updated${NC}\n"
		fi
		printf "\n"
	)
}

#------------------------ Dispatcher ------------------------#

dispatch()
{
	if grep -q "ultimate_tester" Makefile 2>/dev/null; then
		test_framework
	elif [[ -f "libft.h" ]]; then
		test_libft
	elif grep -q "libftprintf\.a" Makefile 2>/dev/null; then
		test_printf
	elif [[ -f "get_next_line.c" ]]; then
		test_gnl
	else
		printf " ${RED}✖ Unable to identify current project${NC}\n" >&2
		exit 1
	fi
}

#---------------------- Project testers ---------------------#

test_framework()
{
	PROJ_NAME="framework"
	PROJ_DIR="${PWD}"

	PROJ_SRCS=()
	PROJ_INCLUDES=()
	PROJ_LIBS=()

	print_project_name

	print_h1 "Makefile   "
	test_makefile

	make -C "${INSTALL_DIR}" \
		PROJ_NAME="$PROJ_NAME" \
		PROJ_DIR="$PROJ_DIR" \
		PROJ_SRCS="${PROJ_SRCS[*]}" \
		PROJ_INCLUDES="${PROJ_INCLUDES[*]}" \
		PROJ_LIBS="${PROJ_LIBS[*]}" \
		run
	exit $?
}

test_libft()
{
	PROJ_NAME="libft"
	PROJ_DIR="${PWD}"

	init_proj_srcs
	init_proj_includes
	init_proj_libs

	print_project_name

	print_h1 "Makefile   "
	test_makefile

	make -C "${INSTALL_DIR}" \
		PROJ_NAME="$PROJ_NAME" \
		PROJ_DIR="$PROJ_DIR" \
		PROJ_SRCS="${PROJ_SRCS[*]}" \
		PROJ_INCLUDES="${PROJ_INCLUDES[*]}" \
		PROJ_LIBS="${PROJ_LIBS[*]}" \
		run
	exit $?
}

test_printf()
{
	PROJ_NAME="printf"
	PROJ_DIR="${PWD}"

	init_proj_srcs
	init_proj_includes
	init_proj_libs

	print_project_name

	print_h1 "Makefile           "
	test_makefile

	make -C "${INSTALL_DIR}" \
		PROJ_NAME="$PROJ_NAME" \
		PROJ_DIR="$PROJ_DIR" \
		PROJ_SRCS="${PROJ_SRCS[*]}" \
		PROJ_INCLUDES="${PROJ_INCLUDES[*]}" \
		PROJ_LIBS="${PROJ_LIBS[*]}" \
		run
	exit $?
}

# TODO
test_gnl()
{
	# TODO
}

#----------------------- Files finders ----------------------#

init_proj_srcs()
{
	local file

	while IFS= read -r -d '' file; do
		PROJ_SRCS+=("${(q)file}")
	done < <(find "$PWD" -type f -name '*.c' -print0)
}

init_proj_includes()
{
	local dir

	while IFS= read -r dir; do
		PROJ_INCLUDES+=("-I${(q)dir}")
	done < <(
		find "$PWD" -type f -name '*.h' -print0 \
			| xargs -0 -I{} dirname "{}" \
			| sort -u
	)
}

init_proj_libs()
{
	local file

	while IFS= read -r -d '' file; do
		PROJ_LIBS+=("${(q)file}")
	done < <(find "$PWD" -type f -name '*.a' -print0)
}

#---------------------- Makefile tester ---------------------#

test_makefile()
{
	test_makefile_rule fclean
	test_makefile_rule ""
	test_makefile_rule clean
	test_makefile_rule fclean
	test_makefile_relink

	printf "\n"
}

test_makefile_rule()
{
	local rule="$1"

	if [[ -z "$rule" ]]; then
		make -C "${PROJ_DIR}" > /dev/null 2>&1
	else
		make -C "${PROJ_DIR}" "${rule}" > /dev/null 2>&1
	fi

	if [[ $? -ne 0 ]]; then
		print_indicator_fail
		printf "\n"
		print_error "Your Makefile is incorrect: 'make ${rule}' doesn't work"
		exit 1
	fi

	print_indicator_pass
}

test_makefile_relink()
{
	local build_before build_after

	make -C "${PROJ_DIR}" fclean > /dev/null 2>&1
	make -C "${PROJ_DIR}" > /dev/null 2>&1
	build_before=$(find "${PROJ_DIR}" -type f -name "libftprintf.a" -exec md5sum {} + 2>/dev/null)

	make -C "${PROJ_DIR}" > /dev/null 2>&1

	build_after=$(find "${PROJ_DIR}" -type f -name "libftprintf.a" -exec md5sum {} + 2>/dev/null)
	if [[ "$build_before" != "$build_after" ]]; then
		print_indicator_fail
		printf "\n"
		print_error "Your Makefile is incorrect: 'make' does relink"
		exit 1
	fi

	print_indicator_pass
}

main
