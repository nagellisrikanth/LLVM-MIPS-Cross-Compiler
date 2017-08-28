define void @f() {
L0:
  %t0 = alloca i32
  %t1 = alloca i32
  %t2 = alloca i32
  %t3 = load i32* %t0
  %t4 = load i32* %t1
  %t5 = mul i32 %t3, %t4
  store i32 %t5, i32* %t2
  ret void
}

