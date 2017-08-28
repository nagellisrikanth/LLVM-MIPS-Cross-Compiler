define void @f() {
L0:
  %t0 = alloca i32
  store i32 2, i32* %t0
  %t1 = alloca i32
  store i32 4, i32* %t1
  %t2 = load i32* %t0
  %t3 = icmp eq i32 %t2, 2
  br i1 %t3, label %L1, label %L2

L1:                                               ; preds = %L0
  store i32 4, i32* %t0
  br label %L2

L2:                                               ; preds = %L1, %L0
  %t4 = load i32* %t0
  %t5 = icmp eq i32 %t4, 2
  br i1 %t5, label %L3, label %L4

L3:                                               ; preds = %L2
  store i32 2, i32* %t1
  br label %L5

L4:                                               ; preds = %L2
  store i32 2, i32* %t0
  br label %L5

L5:                                               ; preds = %L4, %L3
  ret void
}
