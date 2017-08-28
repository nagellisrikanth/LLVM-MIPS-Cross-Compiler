define void @f() {
L0:
  %t0 = alloca i32
  %t1 = alloca i32
  %t2 = load i32* %t0
  %t3 = load i32* %t1
  %t4 = icmp sgt i32 %t2, %t3
  br i1 %t4, label %L1, label %L2

L1:                                               ; preds = %L0
  store i32 10, i32* %t0
  br label %L3

L2:                                               ; preds = %L0
  store i32 20, i32* %t1
  br label %L3

L3:                                               ; preds = %L2, %L1
  ret void
}

