gcc -o UserDflibeary/libaccountcreation.so -fpic -shared src/account_creation.c -lmysqlclient 
gcc -c src/account_management.c -o output/accountManagement.o -Iinclude
gcc -o UserDflibeary/test2test output/accountManagement.o -laccountcreation -LUserDflibeary
LD_LIBRARY_PATH=UserDflibeary ./UserDflibeary/test2test
