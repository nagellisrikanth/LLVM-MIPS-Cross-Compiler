define void @f() {
L0:
  %t0 = alloca i32
  %t1 = alloca i32
  br label %L1

L1:                                               ; preds = %L5, %L0
  %t2 = load i32* %t0
  %t3 = load i32* %t1
  %t4 = icmp sle i32 %t2, %t3
  br i1 %t4, label %L2, label %L3

L2:                                               ; preds = %L1
  %t5 = load i32* %t0
  %t6 = load i32* %t1
  %t7 = icmp eq i32 %t5, %t6
  br i1 %t7, label %L4, label %L5

L3:                                               ; preds = %L1
  ret void

L4:                                               ; preds = %L2
  %t8 = load i32* %t1
  %t9 = add i32 %t8, 2
  store i32 %t9, i32* %t1
  br label %L5

L5:                                               ; preds = %L4, %L2
  br label %L1
}

