// test7.mc: Nested While
int main() {
    int i; 
    int j;
    i = 0;
    while (i < 3) {
        j = 0;
        while (j < 2) {
            print(i * 10 + j); // Expect 0, 1, 10, 11, 20, 21
            j = j + 1;
        }
        i = i + 1;
    }
    return 0;
}
