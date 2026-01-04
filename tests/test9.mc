// test9.mc: Recursion (Factorial)
int factorial(int n) {
    if (n <= 1) {
        return 1;
    }
    return n * factorial(n - 1);
}

int main() {
    print(factorial(5)); // 120
    return 0;
}
