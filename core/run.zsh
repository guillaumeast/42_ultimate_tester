#!/usr/bin/env zsh

REPO_URL="https://github.com/guillaumeast/42_ultimate_tester"

INSTALL_DIR="${HOME}/.42_ultimate_tester"
SCRIPTS_DIR="${INSTALL_DIR}/core"
TESTS_DIR="${INSTALL_DIR}/tests"

RUNNER="run.zsh"

GREY="\033[38;5;240m"
RED="\033[31m"
ORANGE="\033[38;5;214m"
YELLOW="\033[33m"
NONE="\033[0m"

main()
{
	print_ascii_art
	dispatch
}

print_ascii_art()
{
	printf "${YELLOW}                    (          (      *                                 (              (     \n"
	printf "     )    )         )\\ )  *   ))\\ ) (  \`    (      *   )       *   )    )\\ )  *   )    )\\ )  \n"
	printf "  ( /( ( /(      ( (()/(\` )  /(()/( )\\))(   )\\   \` )  /((    \` )  /((  (()/(\` )  /((  (()/(  \n"
	printf "${ORANGE}  )\\()))(_))     )\\ /(_))( )(_))(_)|(_)()((((_)(  ( )(_))\\    ( )(_))\\  /(_))( )(_))\\  /(_)) \n"
	printf " ((_)\((_)    _ ((_|_)) (_(_()|_)) (_()((_)\ _ )\\(_(_()|(_)  (_(_()|(_)(_)) (_(_()|(_)(_))   \n"
	printf "${RED}| | ${ORANGE}(_)${RED}_  )  | | | | |  |_   _|_ _||  \\/  ${ORANGE}(_)${RED}_\\"
	printf "${ORANGE}(_)${RED}_   _| __| |_   _| __/ __||_   _| __| _ \\  \n"
	printf "|_  _| / /   | |_| | |__  | |  | | | |\\/| |/ _ \\   | | | _|    | | | _|\\__ \\  | | | _||   /  \n"
	printf "  |_| /___|   \\___/|____| |_| |___||_|  |_/_/ \\_\\  |_| |___|   |_| |___|___/  |_| |___|_|_\\  \n"
	printf "\n${GREY}${REPO_URL}${NONE}\n\n"
}

dispatch()
{
	if [[ -f "get_next_line.c" ]]; then
		echo -e "🧪 Testing ${YELLOW}GET NEXT LINE${NONE} project..."
		"${TESTS_DIR}/gnl/${RUNNER}"
		exit $?
	fi

	if grep -q "libftprintf\.a" Makefile 2>/dev/null; then
		echo -e "🧪 Testing ${YELLOW}PRINTF${NONE} project..."
		"${TESTS_DIR}/printf/${RUNNER}"
		exit $?
	fi

	echo "❌ Error: ${RED}Unable to identify current project${NONE}" >&2
	exit 1
}

main
