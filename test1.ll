
define void @f() {
L0:
  %t0 = alloca i32
  %t1 = alloca i32
  %t2 = alloca i32
  br label %L1

L1:                                               ; preds = %L5, %L0
  %t3 = load i32* %t0
  %t4 = load i32* %t1
  %t5 = icmp sle i32 %t3, %t4
  br i1 %t5, label %L2, label %L3

L2:                                               ; preds = %L1
  %t6 = load i32* %t0
  %t7 = load i32* %t1
  %t8 = icmp sgt i32 %t6, %t7
  br i1 %t8, label %L4, label %L5

L3:                                               ; preds = %L1
  br label %L6

L4:                                               ; preds = %L2
  %t9 = load i32* %t0
  %t10 = add i32 %t9, 2
  store i32 %t10, i32* %t0
  br label %L5

L5:                                               ; preds = %L4, %L2
  br label %L1

L6:                                               ; preds = %L10, %L3
  %t11 = load i32* %t2
  %t12 = load i32* %t0
  %t13 = icmp ne i32 %t11, %t12
  br i1 %t13, label %L7, label %L8

L7:                                               ; preds = %L6
  %t14 = load i32* %t0
  %t15 = load i32* %t1
  %t16 = icmp eq i32 %t14, %t15
  br i1 %t16, label %L9, label %L10

L8:                                               ; preds = %L6
  ret void

L9:                                               ; preds = %L7
  store i32 2, i32* %t1
  br label %L10

L10:                                              ; preds = %L9, %L7
  br label %L6
}

