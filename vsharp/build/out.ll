declare i32 @printf(i8*, ...)
declare double @npv(double,double*,i32)
declare double @irr(double*,i32)
declare double @wacc(double,double,double,double)
declare i8* @malloc(i64)

@.str0 = private constant [4 x i8] c"ok\0A\00"
@.str1 = private constant [6 x i8] c"fail\0A\00"

define i32 @main(){
  %t0 = mul i32 2, 3
  %t1 = add i32 1, %t0
  %a = alloca i32
  %t2 = mul i32 2, 3
  %t3 = add i32 1, %t2
  store i32 %t3, i32* %a
  %b = alloca i32
  store i32 10, i32* %b
  %t4 = load i32, i32* %a
  %t5 = load i32, i32* %b
  %t7 = icmp slt i32 %t4, %t5
  %t6 = zext i1 %t7 to i32
  %t8 = load i32, i32* %b
  %t10 = icmp ne i32 %t8, 0
  %t9 = zext i1 %t10 to i32
  %t11 = icmp ne i32 %t6, 0
  %t12 = icmp ne i32 %t9, 0
  %t13 = and i1 %t11, %t12
  %t14 = zext i1 %t13 to i32
  %t15 = icmp ne i32 %t14, 0
  br i1 %t15, label %then0, label %else1
then0:
  %t16 = getelementptr inbounds [4 x i8], [4 x i8]* @.str0, i32 0, i32 0
  call i32 (i8*, ...) @printf(i8* %t16)
  br label %endif2
else1:
  %t17 = getelementptr inbounds [6 x i8], [6 x i8]* @.str1, i32 0, i32 0
  call i32 (i8*, ...) @printf(i8* %t17)
  br label %endif2
endif2:
  ret i32 0
}
