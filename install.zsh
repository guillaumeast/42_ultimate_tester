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

TEST_CMD="${RUNNER}"
UNINSTALL_CMD="${UNINSTALLER}"

GREY="\033[90m"
RED="\033[0;31m"
ORANGE="\033[38;5;214m"
GREEN="\033[0;32m"
YELLOW="\033[0;33m"
BLUE="\033[34m"
NONE="\033[0m"

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
	echo " ${BLUE}⏱ Downloading...${NONE}"

	rm -rf "${TMP_DIR}" > /dev/null 2>&1
	if ! git clone --depth=1 "${REPO_URL}" "${TMP_DIR}" > /dev/null 2>&1; then
		local error_code=$?
		echo -e "\n 🚨 ${RED}Installation canceled: Unable to clone ${REPO_URL}${NONE}" >&2

		rm -rf "${TMP_DIR}" > /dev/null 2>&1
		echo " 🧹 All downloaded files have been deleted"

		clean_zshrc
		echo " 🧹 ${ZSHRC} has been restored"

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
			echo
			echo " ${YELLOW}⚠ Unable to find .zshrc inside ${HOME}/${NONE}" >&2
			echo " ℹ You should manually add an alias to run tests : /Users/gui/.42_ultimate_tester/core/run.zsh" >&2
			echo " ℹ You should manually add an alias to uninstall tests : /Users/gui/.42_ultimate_tester/core/uninstall.zsh" >&2
			echo
			return 1
		fi
	fi

	clean_zshrc

	for alias_name in test rmtest; do
		if grep -qE "^[[:space:]]*alias[[:space:]]+${alias_name}=" "${ZSHRC}"; then
			echo
			echo " ${YELLOW}⚠ Alias '${alias_name}' already exists in ${ZSHRC}.${NONE}" >&2
			echo " ℹ You should manually add an alias to run tests : /Users/gui/.42_ultimate_tester/core/run.zsh" >&2
			echo " ℹ You should manually add an alias to uninstall tests : /Users/gui/.42_ultimate_tester/core/uninstall.zsh" >&2
			echo
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
	echo -e " ${GREEN}✔ Downloaded${NONE}\n"

	echo " 👉 ${YELLOW}Reload your terminal${NONE} or run ${YELLOW}source \"${ZSHRC}\"${NONE}, then:"
	echo " 💡 Run ${YELLOW}${TEST_CMD}${NONE} inside a 42 project to test it"
	echo " 💡 Run ${YELLOW}${UNINSTALL_CMD}${NONE} anywhere to uninstall ${NAME}\n"
}

main
