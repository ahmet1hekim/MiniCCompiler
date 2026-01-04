// test6.mc: Nested If/Else
int main() {
    int x;
    x = 10;
    if (x > 5) {
        if (x < 20) {
            print(1); // Expect 1
        } else {
            print(0);
        }
    } else {
        print(0);
    }
    return 0;
}
