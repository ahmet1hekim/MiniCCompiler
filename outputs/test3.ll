; ModuleID = 'MiniC'
source_filename = "MiniC"

@0 = private unnamed_addr constant [4 x i8] c"%d\0A\00", align 1
@1 = private unnamed_addr constant [4 x i8] c"%d\0A\00", align 1

declare i32 @printf(ptr, ...)

define i32 @main() {
entry:
  %n = alloca i32, align 4
  store i32 0, ptr %n, align 4
  store i32 7, ptr %n, align 4
  %n1 = load i32, ptr %n, align 4
  %cmptmp = icmp sgt i32 %n1, 5
  %booltmp = zext i1 %cmptmp to i32
  %ifcond = icmp ne i32 %booltmp, 0
  br i1 %ifcond, label %then, label %else

then:                                             ; preds = %entry
  %n2 = load i32, ptr %n, align 4
  %printfcall = call i32 (ptr, ...) @printf(ptr @0, i32 %n2)
  br label %ifcont

else:                                             ; preds = %entry
  %printfcall3 = call i32 (ptr, ...) @printf(ptr @1, i32 0)
  br label %ifcont

ifcont:                                           ; preds = %else, %then
  ret i32 0
}
