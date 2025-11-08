#!/usr/bin/env zsh

NAME="42_ultimate_tester"
INSTALL_DIR="${HOME}/.42_ultimate_tester"
ZSHRC="${HOME}/.zshrc"
ZSHRC_CONTENT_START="#-----------------------42_ultimate_tester----------------------#"
ZSHRC_CONTENT_END="#---------------------------------------------------------------#"

rm -rf "${INSTALL_DIR}" > /dev/null 2>&1
echo -e "\n🧹 All downloaded files have been deleted"

if [[ ! -f "${ZSHRC}" ]]; then
	ZSHRC=$(find "${HOME}" -maxdepth 3 -type f -name ".zshrc" 2>/dev/null | head -n 1)
	[[ -f "${ZSHRC}" ]] || {
		echo "⚠️  Unable to find .zshrc inside ${HOME}/"
		echo "👉 Remove ${NAME} aliases manually in your .zshrc"
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
echo -e "🧹 ${ZSHRC} has been restored\n"
echo -e "${GREEN}✔ ${NAME}${NONE} has been uninstalled"
