; ModuleID = 'MiniC'
source_filename = "MiniC"

@0 = private unnamed_addr constant [4 x i8] c"%d\0A\00", align 1

declare i32 @printf(ptr, ...)

define i32 @main() {
entry:
  %z = alloca i32, align 4
  %y = alloca i32, align 4
  %x = alloca i32, align 4
  store i32 0, ptr %x, align 4
  store i32 0, ptr %y, align 4
  store i32 0, ptr %z, align 4
  store i32 10, ptr %x, align 4
  store i32 20, ptr %y, align 4
  %x1 = load i32, ptr %x, align 4
  %y2 = load i32, ptr %y, align 4
  %multmp = mul i32 %y2, 2
  %addtmp = add i32 %x1, %multmp
  store i32 %addtmp, ptr %z, align 4
  %z3 = load i32, ptr %z, align 4
  %printfcall = call i32 (ptr, ...) @printf(ptr @0, i32 %z3)
  ret i32 0
}
