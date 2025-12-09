#!/usr/bin/env sh

NAME="42_ultimate_tester"
REPO_URL="https://github.com/guillaumeast/42_ultimate_tester"

TMP_DIR="/tmp/${NAME}"
INSTALL_DIR="${HOME}/.${NAME}"

HEADER_NAME="fut.h"
HEADER_PATH="${INSTALL_DIR}/3_include/${HEADER_NAME}"

LIB_NAME="libfut.a"
LIB_PATH="${INSTALL_DIR}/${LIB_NAME}"

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

	check_dependencies
	printf "\n"
	download
	printf "\n"
	build
	printf "\n"
	link

	print_installed
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

print_installed()
{
	if [ $IS_UTF8 -eq 1 ] && printf "╭" | grep "╭" >/dev/null 2>&1; then
		printf "\n   ${CYAN}╭────────────────────────────────────────╮${NONE}\n"
		printf "   ${CYAN}│               ${BOLD}${GREEN}INSTALLED!${CYAN}               │\n"
		printf "   ${CYAN}╰────────────────────────────────────────╯${NONE}\n\n"
	else
		printf "\n   ${CYAN}------------------------------------------${NONE}\n"
		printf "   ${CYAN}|               ${BOLD}${GREEN}INSTALLED!${CYAN}               |\n"
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

check_dependencies()
{
	failed=0
	missing=""

	print_info "Checking dependencies..."

	if ! git --version > /dev/null 2>&1; then
		print_warn "git not found"
		failed=1
		missing="${missing}git, "
	fi

	if ! make --version > /dev/null 2>&1; then
		print_warn "make not found"
		failed=1
		missing="${missing}make, "
	fi

	if ! cc --version > /dev/null 2>&1; then
		print_warn "cc not found"
		failed=1
		missing="${missing}cc, "
	fi

	missing=$(printf "%s" "$missing" | sed 's/, $//' 2> /dev/null)

	if [ $failed -eq 1 ]; then
		print_err "Please install the following dependencies and retry: ${missing}"
		exit 1
	fi

	print_ok "Done"
}

download()
{
	print_info "Downloading..."

	rm -rf "${TMP_DIR}" > /dev/null 2>&1
	if ! git clone --depth=1 "${REPO_URL}" "${TMP_DIR}" > /dev/null 2>&1; then
		error_code=$?
		print_err "Unable to clone ${REPO_URL}"
		rm -rf "${TMP_DIR}" > /dev/null 2>&1
		exit $error_code
	fi
	rm -rf "${INSTALL_DIR}"
	mv "${TMP_DIR}" "${INSTALL_DIR}"

	print_ok "Done"
}

build()
{
	print_info "Building libfut.a..."
	
	if ! make -C "${INSTALL_DIR}" >/dev/null 2>&1; then
		rm -rf "${INSTALL_DIR}"
		print_err "Compilation failed. All downloaded files have been removed."
		exit 1
	fi

	print_ok "Done"
}

link()
{
	print_warn "Install into /usr/local (requires sudo) ? [y/N]"
	print_info "If YES, you'll be able to compile with: 'cc my_test.c -g -lfut'"
	print_info "If NO, you'll need to compile with:     'cc my_test.c -g -I \$HOME/.local/include -L \$HOME/.local/lib -lfut'"

	if [ -e /dev/tty ]; then
		printf " > "
		read answer </dev/tty
	else
		answer="n"
		print_warn "Non-interactive environment detected. Defaulting to local install."
	fi

	case "$answer" in
		y|Y|yes|YES)
			link_with_sudo ;;
		*)
			link_without_sudo ;;
	esac
}

link_with_sudo()
{
	if ! command -v sudo >/dev/null 2>&1; then
		print_warn "sudo not found. Fallback to local install."
		link_without_sudo
		return
	fi

	header_target="/usr/local/include/${HEADER_NAME}"
	lib_target="/usr/local/lib/${LIB_NAME}"

	sudo mkdir -p /usr/local/include /usr/local/lib
	sudo rm -f "${header_target}"
	sudo rm -f "${lib_target}"

	if ! sudo ln -s "${HEADER_PATH}" "${header_target}"; then
		rm -rf "${INSTALL_DIR}"
		print_err "Failed to create header symlink. All downloaded files have been removed."
		exit 1
	fi

	if ! sudo ln -s "${LIB_PATH}" "${lib_target}"; then
		rm -rf "${INSTALL_DIR}"
		rm -f "${header_target}"
		print_err "Failed to create library symlink. All downloaded files have been removed."
		exit 1
	fi
}

link_without_sudo()
{
	include_dir="${HOME}/.local/include"
	lib_dir="${HOME}/.local/lib"

	mkdir -p "${include_dir}" "${lib_dir}"

	rm -f "${include_dir}/${HEADER_NAME}"
	rm -f "${lib_dir}/${LIB_NAME}"

	if ! ln -s "${HEADER_PATH}" "${include_dir}/${HEADER_NAME}"; then
		rm -rf "${INSTALL_DIR}"
		print_err "Failed to create header symlink. All downloaded files have been removed."
		exit 1
	fi

	if ! ln -s "${LIB_PATH}" "${lib_dir}/${LIB_NAME}"; then
		rm -rf "${INSTALL_DIR}"
		rm -f "${include_dir}/${HEADER_NAME}"
		print_err "Failed to create library symlink. All downloaded files have been removed."
		exit 1
	fi
}

main
