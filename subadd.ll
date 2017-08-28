define void @f() {
L0:
  %t0 = alloca i32
  %t1 = alloca i32
  %t2 = alloca i32
  %t3 = load i32* %t0
  %t4 = load i32* %t1
  %t5 = sub i32 %t3, %t4
  store i32 %t5, i32* %t2
  %t6 = load i32* %t0
  %t7 = load i32* %t1
  %t8 = add i32 %t6, %t7
  store i32 %t8, i32* %t0
  ret void
}

