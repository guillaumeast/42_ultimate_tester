#!/usr/bin/env zsh

test_dir="tests"
project=""

echo

check_project()
{
	echo "👉 Identifying current project..."
	if [[ -f "get_next_line.c "]]
		project="gnl"
	else
		# TODO: let user self_select project (numeroted list)
		echo "❌ Unable to identify current project"
	fi
}

download_tests()
{
	echo "👉 Downloading ${project} test Suite..."
	mkdir -p "$test_dir"
	if [[ $project == "gnl" ]]
		curl -fsSL "https://github.com/guillaumeast/42_ultimate_tester/tree/master/gnl" | xz
	fi
}
