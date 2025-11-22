#include <stdio.h>

#include "account_creation.h"


int main() {
    mysql_query_excuter("create database testdb",NULL);
    return 0;
}