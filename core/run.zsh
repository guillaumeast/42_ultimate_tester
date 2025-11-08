#!/usr/bin/env zsh

REPO_URL="https://github.com/guillaumeast/42_ultimate_tester"
INSTALLER_URL="https://raw.githubusercontent.com/guillaumeast/42_ultimate_tester/master/install.zsh"

INSTALL_DIR="${HOME}/.42_ultimate_tester"
DISPATCHER="${INSTALL_DIR}/core/dispatch.zsh"

GREY="\033[38;5;240m"
ORANGE="\033[38;5;214m"
RED="\033[31m"
YELLOW="\033[33m"
NONE="\033[0m"

main()
{
	print_ascii_art
	update
	"${DISPATCHER}"
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
	printf "\n${GREY}${REPO_URL}${NONE}\n\n"
}

update()
{
	echo -e "${GREY} ⏱ Updating test cases...${NONE}"
	(
		cd "${INSTALL_DIR}"
		if ! git pull > /dev/null 2>&1; then
			if ! curl -fsSL "${INSTALLER_URL}" | zsh > /dev/null 2>&1; then
				echo " ${YELLOW}⚠ Update failed. Skipping.${NONE}" >&2
				echo " ${GREY}ℹ Manual update: 'curl -fsSL ${INSTALLER_URL}'${NONE}"
			else
				echo " ${GREY}✔ Updated${NONE}"
			fi
		else
			echo " ${GREY}✔ Updated${NONE}"
		fi
		echo
	)
}

main
