# Assertions

Assertions are the core of your tests.  
They check if an expression evaluates to true, or if two values and/or outputs are equal / not equal.  

🛡️ **All assertions are safe**: they run in a forked process, catch crashes, handle timeouts and protect the test suite.

## Assertion Modes

With the `mode` argument, you can check the **return value**, `stdout` **output**, `stderr` **output**, or a combination of these:

| Mode      | Return | Stdout | Stderr | Behavior |
|-----------|:------:|:------:|:------:|----------|
| RET       | ✔️     | ❌      | ❌     | Compare **only** `return` values
| OUT       | ❌     | ✔️      | ❌     | Compare **only** `stdout` outputs
| ERR       | ❌     | ❌      | ✔️     | Compare **only** `stderr` outputs
| BOTH      | ❌     | ✔️      | ✔️     | Compare **both** `stdout` and `stderr` outputs
| RET_OUT   | ✔️     | ✔️      | ❌     | Compare **both** `return` values and `stdout` outputs
| RET_ERR   | ✔️     | ❌      | ✔️     | Compare **both** `return` values and `stderr` outputs
| RET_BOTH  | ✔️     | ✔️      | ✔️     | Compare **both** `return` values, `stdout` **and** `stderr` outputs

> You can test any kind of **primitive type** value (`int`, `long`, `char`, `char *`, `void *`, etc.)

## Boolean Assertion: `assert()`

The simplest form. Checks if the expression is true.

**Syntax**  
`assert(timeout_sec, expression)`

**Parameters**
- `timeout_sec`: Max execution time in seconds (`0` for no timeout).
- `expression`: Expression which should be true.

**Example**
```c
assert(1, strlen("42") == 2);
```

## Equality Assertion: `assert_eq()`

**Syntax**  
`assert_eq(mode, timeout_sec, got_expression, expected_expression)`

**Parameters**  
- `mode`: See [Assertion Modes](#assertion-modes)
- `timeout_sec`: Max execution time in seconds (`0` for no timeout).
- `got_expression`: Expression whose return/output values wille be tested.
- `expected_expr`: Control expression. `got_expression` must return/output the same values as this one to pass the test.

**Example**
```c
assert_eq(RET, 1, strlen("42"), 2);
```

## Inequality Assertion: `assert_neq()`

**Syntax**  
`assert_neq(mode, timeout_sec, got_expression, expected_expression)`  

Works the same as [Equality Assertion](#equality-assertion-assert_eq) except `got_expression` must return **different** return/output values as the `expected_expression` to pass the test.

**Example**
```c
assert_neq(RET, 1, ptr, NULL);
```

## Function Comparison: `compare()`

Checks if two distinct functions return/output the same values with the same parameters.

**Syntax**  
`compare(mode, timeout_sec, fn1_name, fn2_name, fn_args)`

**Parameters**  
- `mode`: See [Assertion Modes](#assertion-modes)
- `timeout_sec`: Max execution time in seconds (`0` for no timeout).
- `fn1_name`: Name of the function to be tested.
- `fn2_name`: Name of the control function. `fn1_name` must return/output the same values as this one to pass the test.
- `fn_args`: Arguments that will be passed to both functions to compare their return/output values.

**Example**
```c
compare(RET_OUT, 1, ft_printf, printf, ("Hello %s", "world"));
```

> 🛡️ Each function is executed inside its own isolated forked process, ensuring crash safety, timeout handling and perfectly separated outputs.

## Custom Labels

By default, the framework uses the expression code as the label:
```c
assert_eq(RET, 1, strlen("False"), 4);

// Logs
⤷ strlen("False") returned 5 instead of 4
````

You can override this using the `_label` variants.

```c
assert_eq_label(RET, 1, "Strlen check", strlen("False"), 4);

// Logs
⤷ Strlen check returned 5 instead of 4
```

**Syntax**  
- `assert_label(timeout_sec, label, expression)`  
- `assert_eq_label(mode, timeout_sec, label, got_expression, expected_expression)`  
- `assert_neq_label(mode, timeout_sec, label, got_expression, expected_expression)`  
- `compare_label(mode, timeout_sec, label, fn1_name, fn2_name, fn_args)`
