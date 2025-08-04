// Intentionally broken/test code
void unusedFunction() {}

void uninitializedVar()
{
    int x;
    if (x > 0) // use of uninitialized variable
        return;
}
