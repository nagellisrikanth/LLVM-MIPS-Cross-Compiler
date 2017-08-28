define void @f() {
L0:
  %t0 = alloca i32
  %t1 = alloca i32
  %t2 = alloca i32
  %t3 = load i32* %t0
  %t4 = add i32 %t3, 1
  store i32 %t4, i32* %t2
  ret void
}

