#!/usr/bin/env sh

INSTALL_DIR="${HOME}/.42_ultimate_tester"

HEADER_NAME="fut.h"
HEADER_SYSTEM_SYMLINK="/usr/local/include/${HEADER_NAME}"
HEADER_LOCAL_SYMLINK="${HOME}/.local/include/${HEADER_NAME}"

LIB_NAME="libfut.a"
LIB_SYSTEM_SYMLINK="/usr/local/lib/${LIB_NAME}"
LIB_LOCAL_SYMLINK="${HOME}/.local/lib/${LIB_NAME}"

BOLD=""
GREY=""
RED=""
GREEN=""
YELLOW=""
BLUE=""
CYAN=""
NONE=""

EMJ_INFO="[INFO]"
EMJ_OK="[DONE]"
EMJ_WARN="[WARN]"
EMJ_ERR="[!ERR]"

IS_UTF8=0

main()
{
	init_colors
	init_emojis
	print_header

	uninstall

	print_uninstalled
}

########## UTILITIES ##########

init_colors()
{
	if [ -t 1 ] && command -v tput >/dev/null 2>&1 && [ "$(tput colors 2>/dev/null)" -ge 8 ]; then
		BOLD="\033[1m"
		GREY="\033[90m"
		RED="\033[31m"
		GREEN="\033[32m"
		YELLOW="\033[33m"
		BLUE="\033[34m"
		CYAN="\033[36m"
		NONE="\033[0m"
	fi
}

init_emojis()
{
	case "$LC_ALL$LC_CTYPE$LANG" in
		*.[Uu][Tt][Ff]-8*|*.[Uu][Tt][Ff]8*)
			IS_UTF8=1
			;;
		*)
			;;
	esac

	if [ $IS_UTF8 -eq 1 ]; then
		if printf "ℹ" | grep "ℹ" >/dev/null 2>&1; then
			EMJ_INFO="ℹ"
		fi
		if printf "✔" | grep "✔" >/dev/null 2>&1; then
			EMJ_OK="✔"
		fi
		if printf "⚠" | grep "⚠" >/dev/null 2>&1; then
			EMJ_WARN="⚠"
		fi
		if printf "✖" | grep "✖" >/dev/null 2>&1; then
			EMJ_ERR="✖"
		fi
	fi

	EMJ_INFO="${GREY}${EMJ_INFO}${NONE}"
	EMJ_OK="${GREEN}${EMJ_OK}${NONE}"
	EMJ_WARN="${YELLOW}${EMJ_WARN}${NONE}"
	EMJ_ERR="${RED}${EMJ_ERR}${NONE}"
}

print_header()
{
	if [ $IS_UTF8 -eq 1 ] && printf "╭" | grep "╭" >/dev/null 2>&1; then
		printf "\n   ${CYAN}╭────────────────────────────────────────╮${NONE}\n"
		printf "   ${CYAN}│           ${BOLD}${BLUE}42 ULTIMATE TESTER${CYAN}           │\n"
		printf "   ${CYAN}╰────────────────────────────────────────╯${NONE}\n\n"
	else
		printf "\n   ${CYAN}------------------------------------------${NONE}\n"
		printf "   ${CYAN}|           ${BOLD}${BLUE}42 ULTIMATE TESTER${CYAN}           |\n"
		printf "   ${CYAN}------------------------------------------${NONE}\n\n"
	fi
}

print_uninstalled()
{
	if [ $IS_UTF8 -eq 1 ] && printf "╭" | grep "╭" >/dev/null 2>&1; then
		printf "\n   ${CYAN}╭────────────────────────────────────────╮${NONE}\n"
		printf "   ${CYAN}│              ${BOLD}${GREEN}UNINSTALLED!${CYAN}              │\n"
		printf "   ${CYAN}╰────────────────────────────────────────╯${NONE}\n\n"
	else
		printf "\n   ${CYAN}------------------------------------------${NONE}\n"
		printf "   ${CYAN}|              ${BOLD}${GREEN}UNINSTALLED!${CYAN}              |\n"
		printf "   ${CYAN}------------------------------------------${NONE}\n\n"
	fi
}

print_info()
{
	printf " ${EMJ_INFO} ${GREY}${1}${NONE}\n"
}

print_ok()
{
	printf " ${EMJ_OK} ${GREEN}${1}${NONE}\n"
}

print_warn()
{
	printf " ${EMJ_WARN} ${YELLOW}${1}${NONE}\n"
}

print_err()
{
	printf " ${EMJ_ERR} ${RED}${1}${NONE}\n" >&2
}

########## LOGIC ##########

uninstall()
{
	if [ -L "${HEADER_SYSTEM_SYMLINK}" ] || [ -f "${HEADER_SYSTEM_SYMLINK}" ]; then
		sudo rm -f "${HEADER_SYSTEM_SYMLINK}" > /dev/null 2>&1
		print_ok "${HEADER_SYSTEM_SYMLINK} deleted."
	fi

	if [ -L "${HEADER_LOCAL_SYMLINK}" ] || [ -f "${HEADER_LOCAL_SYMLINK}" ]; then
		rm -f "${HEADER_LOCAL_SYMLINK}" > /dev/null 2>&1
		print_ok "${HEADER_LOCAL_SYMLINK} deleted."
	fi

	if [ -L "${LIB_SYSTEM_SYMLINK}" ] || [ -f "${LIB_SYSTEM_SYMLINK}" ]; then
		sudo rm -f "${LIB_SYSTEM_SYMLINK}" > /dev/null 2>&1
		print_ok "${LIB_SYSTEM_SYMLINK} deleted."
	fi

	if [ -L "${LIB_LOCAL_SYMLINK}" ] || [ -f "${LIB_LOCAL_SYMLINK}" ]; then
		rm -f "${LIB_LOCAL_SYMLINK}" > /dev/null 2>&1
		print_ok "${LIB_LOCAL_SYMLINK} deleted."
	fi

	if [ -d "${INSTALL_DIR}" ]; then
		rm -rf "${INSTALL_DIR}" > /dev/null 2>&1
		print_ok "${INSTALL_DIR} deleted."
	else
		print_warn "${INSTALL_DIR} not found. Skipping."
	fi
}

main
