define void @f() {
L0:
  %t0 = alloca i32
  %t1 = alloca i32
  %t2 = load i32* %t0
  %t3 = icmp ne i32 %t2, 0
  br i1 %t3, label %L1, label %L2

L1:                                               ; preds = %L0
  %t4 = load i32* %t1
  %t5 = add i32 %t4, 2
  store i32 %t5, i32* %t1
  br label %L2

L2:                                               ; preds = %L1, %L0
  ret void
}

