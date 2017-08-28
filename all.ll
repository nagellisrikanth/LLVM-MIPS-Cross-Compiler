define void @f() {
L0:
  %t0 = alloca i32
  %t1 = alloca i32
  %t2 = alloca i32
  br label %L1

L1:                                               ; preds = %L6, %L0
  %t3 = load i32* %t0
  %t4 = load i32* %t1
  %t5 = icmp slt i32 %t3, %t4
  br i1 %t5, label %L2, label %L3

L2:                                               ; preds = %L1
  %t6 = load i32* %t2
  %t7 = load i32* %t1
  %t8 = icmp ne i32 %t6, %t7
  br i1 %t8, label %L4, label %L5

L3:                                               ; preds = %L1
  ret void

L4:                                               ; preds = %L2
  %t9 = load i32* %t1
  %t10 = add i32 %t9, 2
  store i32 %t10, i32* %t1
  br label %L6

L5:                                               ; preds = %L2
  store i32 2, i32* %t0
  br label %L6

L6:                                               ; preds = %L5, %L4
  br label %L1
}

