/*
** EPITECH PROJECT, 2023
**
** File description:
** 
*/

#include <criterion/criterion.h>
#include "main.h"

Test(errors, exit_code)
{
    error();
    cr_assert_stderr_eq_str("error", "");
}