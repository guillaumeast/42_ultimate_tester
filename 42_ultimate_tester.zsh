#!/usr/bin/env zsh

tests_dir="42_ultimate_tests"
tests_script="${tests_dir}/test.zsh"
gnl_zip_url="https://github.com/guillaumeast/42_ultimate_tester/raw/zip/gnl.zip"
tmp_zip="/tmp/42_ultimate_tests.zip"

project=""
zip_url=""

main()
{
	echo
	check_project
	download_tests
	run_tests
	print_help
}

check_project()
{
	echo "👉 Identifying current project..."
	if [[ -f "get_next_line.c" ]]; then
		project="gnl"
		zip_url="$gnl_zip_url"
	else
		# TODO: let user self_select project (numeroted list)
		echo "❌ Unable to identify current project"
		exit 1
	fi
}

download_tests()
{
	echo "👉 Downloading ${project} test Suite..."
	rm -rf "$tests_dir" > /dev/null 2>&1
	mkdir -p "$tests_dir"
	if ! curl -fsSL "$zip_url" -o "$tmp_zip"; then
		echo "❌ Unable to download $zip_url" >&2
		exit 2
	fi
	unzip -q "$tmp_zip" -d "$tests_dir"
	rm -f "$tmp_zip"
	echo "✅ Tests installed in './$tests_dir/"
}

run_tests()
{
	if [[ ! -f "${tests_script}" ]]
		echo "❌ Unable to find ${tests_script}"
		exit 3
	fi
	if ! chmod +x "${tests_script}"; then
		echo "❌ Unable to make ${tests_script} executable"
		exit 3
	fi
	echo "🚀 Running tests..."
	./"${tests_script}"
}

print_help()
{
	echo
	echo "💡 Re-run tests with './${tests_dir}/test.zsh'"
	echo "💡 Uninstall tests with 'rm -rf ./${tests_dir}'"
}

main
