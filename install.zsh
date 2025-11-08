#!/usr/bin/env zsh

NAME="42_ultimate_tester"
REPO_URL="https://github.com/guillaumeast/42_ultimate_tester"

TMP_DIR="/tmp/${NAME}"
INSTALL_DIR="${HOME}/.${NAME}"
RUNNER="${INSTALL_DIR}/core/run.zsh"
UNINSTALLER="${INSTALL_DIR}/core/uninstall.zsh"

ZSHRC="${HOME}/.zshrc"
ZSHRC_CONTENT_START="#-----------------------42_ultimate_tester----------------------#"
ZSHRC_CONTENT_END="#---------------------------------------------------------------#"
ZSHRC_CONTENT="alias test=\"${RUNNER}\"\nalias rmtest=\"${UNINSTALLER}\""

GREY="\033[38;5;240m"
RED="\033[0;31m"
ORANGE="\033[38;5;214m"
GREEN="\033[0;32m"
YELLOW="\033[0;33m"
NONE="\033[0m"

main()
{
	print_ascii_art
	download
	update_zshrc
	print_help
	exec zsh
}

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
	printf "\n"
}

download()
{
	echo " ${GREY}⏱${NONE} Downloading ${NAME} into ${INSTALL_DIR}..."

	rm -rf "${TMP_DIR}" > /dev/null 2>&1
	git clone --depth=1 "${REPO_URL}" "${TMP_DIR}" > /dev/null 2>&1 || fail "Unable to clone ${REPO_URL}"
	rm -rf "${INSTALL_DIR}"
	mv "${TMP_DIR}" "${INSTALL_DIR}"
}

update_zshrc()
{
	if [[ ! -f "${ZSHRC}" ]]; then
		ZSHRC=$(find "${HOME}" -maxdepth 3 -type f -name ".zshrc" 2>/dev/null | head -n 1)
		[[ -f "${ZSHRC}" ]] || fail "Unable to find .zshrc inside ${HOME}/"
	fi

	clean_zshrc

	for alias_name in test rmtest; do
		if grep -qE "^[[:space:]]*alias[[:space:]]+${alias_name}=" "${ZSHRC}"; then
			fail "Alias '${alias_name}' already exists in ${ZSHRC}"
		fi
	done

	echo -e "${ZSHRC_CONTENT_START}\n${ZSHRC_CONTENT}\n${ZSHRC_CONTENT_END}" >> "${ZSHRC}"
}

clean_zshrc()
{
	if sed --version >/dev/null 2>&1; then
		# GNU sed (Linux)
		sed -i "/${ZSHRC_CONTENT_START}/,/${ZSHRC_CONTENT_END}/d" "${ZSHRC}" 2>/dev/null
	else
		# BSD sed (macOS)
		sed -i '' "/${ZSHRC_CONTENT_START}/,/${ZSHRC_CONTENT_END}/d" "${ZSHRC}" 2>/dev/null
	fi
}

print_help()
{
	echo -e " ${GREEN}✔${NONE} Downloaded\n"

	echo " 💡 Run ${YELLOW}'test'${NONE} inside a 42 project to test it"
	echo " 💡 Run ${YELLOW}'rmtest'${NONE} anywhere to uninstall ${NAME}\n"
}

fail()
{
	local message="$1"
	local error_code="${2:-1}"

	echo -e "\n ❌ Installation canceled: ${RED}${message}${NONE}" >&2

	rm -f "${TMP_DIR}" > /dev/null 2>&1
	rm -rf "${INSTALL_DIR}" > /dev/null 2>&1

	echo " 🧹 All downloaded files have been deleted"

	clean_zshrc
	echo " 🧹 ${ZSHRC} has been restored"

	exit $error_code
}

main
