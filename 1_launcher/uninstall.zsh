#!/usr/bin/env zsh

typeset -g NAME="42_ultimate_tester"
typeset -g INSTALL_DIR="${HOME}/.42_ultimate_tester"

typeset -g ZSHRC="${HOME}/.zshrc"
typeset -g ZSHRC_CONTENT_START="#-----------------------42_ultimate_tester----------------------#"
typeset -g ZSHRC_CONTENT_END="#---------------------------------------------------------------#"

typeset -g GREEN="\033[0;32m"
typeset -g NONE="\033[0m"

rm -rf "${INSTALL_DIR}" > /dev/null 2>&1
printf "\n 🧹 All downloaded files have been deleted\n"

if [[ ! -f "${ZSHRC}" ]]; then
	ZSHRC=$(find "${HOME}" -maxdepth 3 -type f -name ".zshrc" 2>/dev/null | head -n 1)
	[[ -f "${ZSHRC}" ]] || {
		printf " ${YELLOW}⚠ Unable to find .zshrc inside ${HOME}/${NONE}\n" >&2
		printf " ℹ Remove ${NAME} aliases manually in your .zshrc\n" >&2
		exit 0
	}
fi

if sed --version >/dev/null 2>&1; then
	# GNU sed (Linux)
	sed -i "/${ZSHRC_CONTENT_START}/,/${ZSHRC_CONTENT_END}/d" "${ZSHRC}" 2>/dev/null
else
	# BSD sed (macOS)
	sed -i '' "/${ZSHRC_CONTENT_START}/,/${ZSHRC_CONTENT_END}/d" "${ZSHRC}" 2>/dev/null
fi

printf " 🧹 ${ZSHRC} has been restored\n"
printf "\n ${GREEN}✔ ${NAME} has been uninstalled${NONE}\n\n"
