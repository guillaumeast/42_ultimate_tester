#!/usr/bin/env zsh

typeset -g NAME="42_ultimate_tester"
typeset -g REPO_URL="https://github.com/guillaumeast/42_ultimate_tester"

typeset -g TMP_DIR="/tmp/${NAME}"
typeset -g INSTALL_DIR="${HOME}/.${NAME}"
typeset -g LAUNCHER_DIR="${INSTALL_DIR}/1_launcher"
typeset -g RUNNER="${LAUNCHER_DIR}/run.zsh"
typeset -g UNINSTALLER="${LAUNCHER_DIR}/uninstall.zsh"

typeset -g ZSHRC="${HOME}/.zshrc"
typeset -g ZSHRC_CONTENT_START="#-----------------------42_ultimate_tester----------------------#"
typeset -g ZSHRC_CONTENT_END="#---------------------------------------------------------------#"
typeset -g ZSHRC_CONTENT="alias test=\"${RUNNER}\"\nalias rmtest=\"${UNINSTALLER}\""

typeset -g TEST_CMD="${RUNNER}"
typeset -g UNINSTALL_CMD="${UNINSTALLER}"

typeset -g GREY="\033[90m"
typeset -g RED="\033[0;31m"
typeset -g ORANGE="\033[38;5;214m"
typeset -g GREEN="\033[0;32m"
typeset -g YELLOW="\033[0;33m"
typeset -g BLUE="\033[34m"
typeset -g NONE="\033[0m"

main()
{
	print_ascii_art
	download
	update_zshrc
	print_help
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
	printf "${NONE}\n"
}

download()
{
	printf " ${BLUE}⏱ Downloading...${NONE}\n"

	rm -rf "${TMP_DIR}" > /dev/null 2>&1
	if ! git clone --depth=1 "${REPO_URL}" "${TMP_DIR}" > /dev/null 2>&1; then
		local error_code=$?

		printf "\n 🚨 ${RED}Installation canceled: Unable to clone ${REPO_URL}${NONE}\n" >&2

		rm -rf "${TMP_DIR}" > /dev/null 2>&1
		printf " 🧹 All downloaded files have been deleted\n"

		clean_zshrc
		printf " 🧹 ${ZSHRC} has been restored\n"

		exit $error_code
	fi
	rm -rf "${INSTALL_DIR}"
	mv "${TMP_DIR}" "${INSTALL_DIR}"
}

update_zshrc()
{
	if [[ ! -f "${ZSHRC}" ]]; then
		ZSHRC=$(find "${HOME}" -maxdepth 3 -type f -name ".zshrc" 2>/dev/null | head -n 1)
		if [[ ! -f "${ZSHRC}" ]]; then
			printf "\n ${YELLOW}⚠ Unable to find .zshrc inside ${HOME}/${NONE}\n" >&2
			printf " ℹ You should manually add an alias to run tests : ${RUNNER}\n" >&2
			printf " ℹ You should manually add an alias to uninstall tests : ${UNINSTALLER}\n\n" >&2
			return 1
		fi
	fi

	clean_zshrc

	for alias_name in test rmtest; do
		if grep -qE "^[[:space:]]*alias[[:space:]]+${alias_name}=" "${ZSHRC}"; then
			printf "\n ${YELLOW}⚠ Alias '${alias_name}' already exists in ${ZSHRC}.${NONE}\n" >&2
			printf " ℹ You should manually add an alias to run tests : ${RUNNER}\n" >&2
			printf " ℹ You should manually add an alias to uninstall tests : ${UNINSTALLER}\n\n" >&2
			return 1
		fi
	done

	echo -e "${ZSHRC_CONTENT_START}\n${ZSHRC_CONTENT}\n${ZSHRC_CONTENT_END}" >> "${ZSHRC}"
	TEST_CMD="test"
	UNINSTALL_CMD="rmtest"
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
	printf " ${GREEN}✔ Downloaded${NONE}\n"

	printf " 👉 ${YELLOW}Reload your terminal${NONE} or run ${YELLOW}source \"${ZSHRC}\"${NONE}, then:\n"
	printf " 💡 Run ${YELLOW}${TEST_CMD}${NONE} inside a 42 project to test it\n"
	printf " 💡 Run ${YELLOW}${UNINSTALL_CMD}${NONE} anywhere to uninstall ${NAME}\n\n"
}

main
