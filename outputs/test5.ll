; ModuleID = 'MiniC'
source_filename = "MiniC"

@0 = private unnamed_addr constant [4 x i8] c"%d\0A\00", align 1

declare i32 @printf(ptr, ...)

define i32 @add(i32 %a1, i32 %b2) {
entry:
  %r = alloca i32, align 4
  %b = alloca i32, align 4
  %a = alloca i32, align 4
  store i32 %a1, ptr %a, align 4
  store i32 %b2, ptr %b, align 4
  store i32 0, ptr %r, align 4
  %a3 = load i32, ptr %a, align 4
  %b4 = load i32, ptr %b, align 4
  %addtmp = add i32 %a3, %b4
  store i32 %addtmp, ptr %r, align 4
  %r5 = load i32, ptr %r, align 4
  ret i32 %r5
}

define i32 @main() {
entry:
  %x = alloca i32, align 4
  store i32 0, ptr %x, align 4
  %calltmp = call i32 @add(i32 3, i32 4)
  store i32 %calltmp, ptr %x, align 4
  %x1 = load i32, ptr %x, align 4
  %printfcall = call i32 (ptr, ...) @printf(ptr @0, i32 %x1)
  ret i32 0
}
