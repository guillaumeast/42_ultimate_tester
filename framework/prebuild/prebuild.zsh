#!/usr/bin/env zsh

ULT_DIR="/Users/gui/repos/42_ultimate_tester/"	# TODO: "~/.42_ultimate_tester" for prod
TESTS_DIR="${ULT_DIR}/printf"
TEMP_DIR="${ULT_DIR}/framework/prebuild/templates"
OUT_DIR="${ULT_DIR}/framework/prebuild/outputs"

TEMPLATE="${TEMP_DIR}/try.c"

main()
{
	rm -rf "${OUTDIR}"
	mkdir -p "${OUTDIR}"
	find_tries
}

find_tries()
{
	local filename
	local outfile
	local args
	local code

	for file in "${TESTS_DIR}"/*.c; do
		echo "file = ${file}"
		filename="$(basename "${file}")"
		outfile="${OUTDIR}/${filename}"
		rm -f "${outfile}" > /dev/null 2>&1
		cp "${file}" "${outfile}"
		grep -E '^[[:space:]]*Try\(' "$outfile" | while IFS= read -r line; do
			args="$(echo "$line" | sed -E 's/^[[:space:]]*Try\((.*)\)[[:space:]]*;.*$/\1/')"
			echo "-------------------"
			echo "→ Args --->$args<--"
			code="$(sed "s/__VA_ARGS__/${args//\//\\/}/g" "$TEMPLATE")"
			echo "-------------------"
			echo "code:"
			echo -e "${code}"
			echo "-------------------"
			echo
			# TODO: replace $line by $code in $outfile
		done
	done
}

main
