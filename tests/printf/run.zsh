#!/usr/bin/env zsh

tests_dir="${HOME}/.42_ultimate_tester/tests/printf"
make -C ${tests_dir}
"${tests_dir}"/ft_printf_tester
