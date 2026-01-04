// test10.mc: Shadowing
int main() {
    int x;
    x = 10;
    print(x); // 10
    if (x > 5) {
        int x;
        x = 20;
        print(x); // 20
        x = x + 1;
        print(x); // 21
    }
    print(x); // 10 (Original)
    return 0;
}
