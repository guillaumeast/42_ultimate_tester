#!/usr/bin/env sh

INSTALL_DIR="${HOME}/.42_ultimate_tester"

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

	update
	rebuild

	print_updated
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

print_updated()
{
	if [ $IS_UTF8 -eq 1 ] && printf "╭" | grep "╭" >/dev/null 2>&1; then
		printf "\n   ${CYAN}╭────────────────────────────────────────╮${NONE}\n"
		printf "   ${CYAN}│                ${BOLD}${GREEN}UPDATED!${CYAN}                │\n"
		printf "   ${CYAN}╰────────────────────────────────────────╯${NONE}\n\n"
	else
		printf "\n   ${CYAN}------------------------------------------${NONE}\n"
		printf "   ${CYAN}|                ${BOLD}${GREEN}UPDATED!${CYAN}                |\n"
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

update()
{
	if [ ! -d "${INSTALL_DIR}" ]; then
		print_err "${INSTALL_DIR} not found"
		exit 1
	fi

	print_info "Pulling repo update..."

	(
		cd "${INSTALL_DIR}" || exit 1
		git pull > /dev/null 2>&1
		exit $?
	)

	if [ $? -ne 0 ]; then
		print_err "Unable to pull repo update. Keeping previous library version."
		exit 1
	fi

	print_ok "Done"
}

rebuild()
{
	print_info "Rebuilding libfut.so..."

	if ! make -C "${INSTALL_DIR}" >/dev/null 2>&1; then
		print_err "Compilation failed. Keeping previous library version."
		exit 1
	fi

	print_ok "Done"
}

main
