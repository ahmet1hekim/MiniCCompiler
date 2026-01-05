# Mini C Derleyicisi Proje Sunumu

Bu belge, Mini C derleyicisinin tasarımını, bileşenlerini, çalışma mantığını ve LLVM entegrasyonunu detaylandırmaktadır.

## 1. Sözdizimi ve Lexer (Sözcük Analizi)

Derleyicinin ilk aşaması olan **Lexer**, kaynak kodu ham karakter dizisi olarak okur ve bu karakterleri dilin anlamlı en küçük yapı taşları olan **Token**'lara ayırır.

### Tanımlanan Dilin Özdizimi
Mini C dili, C dilinin temel özelliklerini barındıran basitleştirilmiş bir dildir:
*   **Veri Tipleri**: `int` (tam sayı), `float` (kayan noktalı sayı).
*   **Anahtar Kelimeler**: `if`, `else`, `while`, `return`, `print`.
*   **Operatörler**: Aritmetik (`+`, `-`, `*`, `/`) ve Karşılaştırma (`==`, `!=`, `<`, `>`, `<=`, `>=`).
*   **Yapı**: Program, fonksiyon tanımlarından oluşur. Her fonksiyonun bir gövdesi (`block`) vardır.

### Lexer Çalışma Mantığı
Bu projede Lexer, **Flex** aracı kullanılarak (`src/lexer.l`) oluşturulmuştur. Düzenli ifadeler (Regular Expressions) kullanılarak kaynak koddaki desenler eşleştirilir.

**Örnek Token Eşleşmeleri:**
*   `int` $\rightarrow$ `KW_INT`
*   `if` $\rightarrow$ `KW_IF`
*   `[0-9]+` $\rightarrow$ `NUM` (Örn: `123`)
*   `[a-zA-Z][a-zA-Z0-9]*` $\rightarrow$ `ID` (Örn: `count`, `main`)
*   `+` $\rightarrow$ `PLUS`

**Doğru Girdi Örneği:**
Kod: `int x = 10;`
Lexer Çıktısı: `[KW_INT] [ID:x] [ASSIGN] [NUM:10] [SEMICOLON]`

**Hatalı Girdi Örneği:**
Kod: `int #y = 5;`
Sonuç: Lexer, `#` karakteri için bir kural tanımadığından (veya "unexpected character" kuralına düşeceğinden) hata verir.

---

## 2. Dilbilgisi ve Parser (Sözdizim Analizi) ve AST

Lexer'dan gelen token akışı, **Parser** tarafından alınır ve dilin dilbilgisi kurallarına (Grammar) uygunluğu denetlenir. Bu süreçte kodun hiyerarşik yapısını temsil eden **Abstract Syntax Tree (AST)** oluşturulur.

### Parser ve Gramer Yapısı
Parser, **Bison** aracı kullanılarak (`src/parser.y`) oluşturulmuştur. Context-Free Grammar (CFG) kuralları tanımlanmıştır.

**Gramer Özeti (Basitleştirilmiş):**
```
program      : function_decl*
function_decl: type ID ( param_list ) block
block        : { statement* }
statement    : var_decl | assign_stmt | if_stmt | while_stmt | print_stmt | return_stmt
expression   : term (+/-) term | ...
```

### AST Üretimi
Parser, gramer kurallarını işlerken C++ nesneleri (`src/ast.h`) oluşturarak bunları birbirine bağlar.

**Örnek:** `x = y + 5;`
Oluşan AST Yapısı:
*   `AssignStmt`
    *   Target: `Variable("x")`
    *   Value: `BinaryExpr("+")`
        *   Left: `Variable("y")`
        *   Right: `Number(5)`

**Doğru Girdi:**
```c
int main() { return 0; }
```
Parser bu girdiyi kabul eder ve `Program` $\rightarrow$ `FunctionDecl` $\rightarrow$ `Block` $\rightarrow$ `ReturnStmt` zincirini kurar.

**Hatalı Girdi (Syntax Error):**
```c
if (x > 0) { x = 1;  // Parantez kapatılmamış '}' eksik
```
Parser, dosya sonuna (EOF) geldiğinde beklediği `RBRACE` (`}`) token'ını bulamazsa `syntax error` hatası üretir.

---

## 3. Kod Üretimi (Code Generation) ve Hedef Kod

Bu projede hedef kod olarak **LLVM Intermediate Representation (LLVM IR)** kullanılmaktadır.

### Neden LLVM IR?
LLVM IR, donanımdan bağımsız, assembly benzeri ancak tip bilgisi içeren (strongly typed) güçlü bir ara dildir. Bu sayede üretilen kod, LLVM altyapısı kullanılarak x86, ARM, WebAssembly gibi pek çok mimariye optimize edilerek derlenebilir.

### CodeGen Çalışma Mantığı (`src/codegen.cpp`)
AST üzerinde `Visitor Pattern` benzeri bir yapıyla (`codegen()` metotları) dolaşılır. LLVM C++ API'sı kullanılarak IR komutları üretilir.

*   **Değişkenler**: Her değişken için fonksiyon başında `alloca` ile yığın bellekte (stack) yer ayrılır. Bu, LLVM'in SSA (Static Single Assignment) kısıtlamalarını aşarak, değişkenlerin değerinin güncellenebilmesini (mutable) sağlar.
*   **Kontrol Akışı**: `if` ve `while` yapıları için `BasicBlock`'lar oluşturulur ve `br` (branch/zıplama) komutları ile akış yönlendirilir.
*   **Tipler**: `int` $\rightarrow$ `i32`, `float` $\rightarrow$ `float`.

### Çalışan Kod Örneği

**Kaynak Kod (`ornek.mc`):**
```c
int main() {
    int res;
    res = 5 * 4;
    print(res);
    return 0;
}
```

**Derleme ve Çalıştırma:**
Bu dil doğrudan bir binary üretmek yerine LLVM IR üretir. Bu IR daha sonra LLVM araçları ile çalıştırılır.

1.  **IR Üretimi:**
    ```bash
    ./minic < ornek.mc > ornek.ll
    ```

2.  **IR'ı Çalıştırma (Interpreter - lli):**
    ```bash
    lli ornek.ll
    # Çıktı: 20
    ```

3.  **Executable'a Çevirme (Clang):**
    ```bash
    clang ornek.ll -o program
    ./program
    # Çıktı: 20
    ```

**Üretilen Hedef Kod (LLVM IR - Özet):**
```llvm
define i32 @main() {
entry:
  %res = alloca i32               ; Değişken için yer ayır
  store i32 0, i32* %res          ; Sıfırla başlat
  %multmp = mul i32 5, 4          ; Çarpma işlemi
  store i32 %multmp, i32* %res    ; Sonucu kaydet
  %val = load i32, i32* %res      ; Değeri yükle
  %call = call i32 (i8*, ...) @printf(..., i32 %val) ; Yazdır
  ret i32 0
}
```

### Hatalı Girdi (Semantik Hata)

**Girdi:**
```c
int main() {
    x = 10; // 'x' tanımlanmamış
}
```
*   **Lexer**: `x`, `ID` olarak tanınır (Başarılı).
*   **Parser**: Gramer yapısı doğrudur (`ID = Expression;`). Sözdizimi hatası yok (Başarılı).
*   **CodeGen**: AST dolaşılırken `Variable("x")` için sembol tablosuna bakılır. `x` bulunamaz.
*   **Sonuç**: `Error: Unknown variable: x` hatası verilir ve kod üretimi başarısız olur.
