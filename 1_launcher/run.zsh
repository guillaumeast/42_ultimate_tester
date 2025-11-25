#!/usr/bin/env zsh

# Variables for update()
typeset -g INSTALL_DIR="${HOME}/.42_ultimate_tester"
typeset -g REPO_URL="https://github.com/guillaumeast/42_ultimate_tester"
typeset -g INSTALLER_URL="https://raw.githubusercontent.com/guillaumeast/42_ultimate_tester/master/install.zsh"

# Variables for Makefile
typeset -g PROJ_NAME=""
typeset -g PROJ_DIR=""
typeset -ga PROJ_SRCS=()
typeset -ga PROJ_INCLUDES=()
typeset -ga PROJ_LIBS=()

# Colors
typeset -g GREY="\033[90m"
typeset -g ORANGE="\033[38;5;214m"
typeset -g RED="\033[31m"
typeset -g GREEN="\033[32m"
typeset -g YELLOW="\033[33m"
typeset -g NONE="\033[0m"

main()
{
	print_ascii_art
	update
	dispatch
}
#-------------------------- Printer -------------------------#

print_ascii_art()
{
	printf "\n${YELLOW}                               )\\      \`           *                         * )    \` )\\     \n"
	printf "  \` *           (  \`.         /((                \`      /((    \`   )          /(\`   /((.\\    \n"
	printf "${ORANGE}    (           )\\ /(        / (*   .     *    (        )\\        ()   \`     /)(_))\\ /( (    \n"
	printf " ${RED}_  ${ORANGE})\\ ${RED}___    _ ${ORANGE}((_|_${ORANGE})   ${RED}___${ORANGE}(_|_))${RED}_${ORANGE}()${RED}_  __${ORANGE})\\ _ )\\ ${RED}_____ ${ORANGE}(_)   ${RED}___${ORANGE}(_)${RED}_______ ${ORANGE}(_(_()|(${RED}_${ORANGE})(${RED}__${ORANGE})${RED}   \n"
	printf "| |_${ORANGE}(_)${RED}_  )  | | | | |  |_   _|_ _||  \\/  ${ORANGE}(_)${RED}_\\"
	printf "${ORANGE}(_)${RED}_   _| __| |_   _| __/ __||_   _| __| _ \\  \n"
	printf "|_  _| / /   | |_| | |__  | |  | | | |\\/| |/ _ \\   | | | _|    | | | _|\\__ \\  | | | _||   /  \n"
	printf "  |_| /___|   \\___/|____| |_| |___||_|  |_/_/ \\_\\  |_| |___|   |_| |___|___/  |_| |___|_|_\\  \n"
	printf "\n${GREY}${REPO_URL}${NONE}\n\n"
}

# TODO: update with framework graphic style
print_project_name()
{
	printf " 🧪 Testing ${YELLOW}${PROJ_NAME}${NONE} project...\n"
}

print_h1()
{
	printf " ${GREY}➜${NONE} ${1} "
}

print_indicator_pass()
{
	printf "${GREEN}✔${NONE} "
}

print_indicator_fail()
{
	printf "${RED}✖${NONE} "
}

print_error()
{
	printf "    ${GREY}⤷ ${RED}${1}${NONE}\n" >&2
}

#-------------------------- Updater -------------------------#

update()
{
	printf "${GREY} ⏱ Updating...${NONE}\n"
	(
		cd "${INSTALL_DIR}"
		if ! git pull > /dev/null 2>&1; then
			if ! curl -fsSL "${INSTALLER_URL}" | zsh > /dev/null 2>&1; then
				printf " ${YELLOW}⚠ Update failed. Skipping.${NONE}\n" >&2
				printf " ${GREY}ℹ Manual update: 'curl -fsSL ${INSTALLER_URL}'${NONE}\n" >&2
			else
				printf " ${GREY}✔ Updated${NONE}"
			fi
		else
			printf " ${GREY}✔ Updated${NONE}"
		fi
		printf "\n"
	)
}

#------------------------ Dispatcher ------------------------#

dispatch()
{
	if [[ -f "get_next_line.c" ]]; then
		test_gnl
	elif grep -q "libftprintf\.a" Makefile 2>/dev/null; then
		test_printf
	else
		printf " ${RED}✖ Unable to identify current project${NONE}\n" >&2
		exit 1
	fi
}

#---------------------- Project testers ---------------------#

test_printf()
{
	PROJ_NAME="printf"
	PROJ_DIR="${PWD}"

	init_proj_srcs
	init_proj_includes
	PROJ_LIBS=("libftprintf.a")

	print_project_name

	test_makefile
	printf "\n"

	make -C .. \
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

#---------------------- Makefile tester ---------------------#

test_makefile()
{
	print_h1 "Makefile"

	test_makefile_rule fclean
	test_makefile_rule ""
	test_makefile_rule clean
	test_makefile_rule fclean
	test_makefile_relink
}

test_makefile_rule()
{
	local rule="$1"

	if [[ -z "$rule" ]]; then
		make -C "${PROJ_DIR}"
	else
		make -C "${PROJ_DIR}" "${rule}"
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
	make -C "${PROJ_DIR}"
	build_before=$(find "${PROJ_DIR}" -type f -name "libftprintf.a" -exec md5sum {} + 2>/dev/null)

	make -C "${PROJ_DIR}"

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
