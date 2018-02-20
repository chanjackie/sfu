
void foo2(void);

int *new_42(void) {
    int x;
    int *ret;

    x = 42;
    ret = &x;

    return ret;
} // new_42

void foo(int *a) {
	foo2();
} // foo

