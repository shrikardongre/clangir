// RUN: %clang_cc1 -triple x86_64-unknown-linux-gnu -fclangir -emit-llvm %s -o %t.ll
// RUN: FileCheck --input-file=%t.ll %s -check-prefix=LLVM

unsigned char table[10][5] =
{
    {1,0},
    {7,6,5},
};

// LLVM: @table = {{.*}}[10 x [5 x i8]] {{.*}}[5 x i8] c"\01\00\00\00\00", [5 x i8] c"\07\06\05\00\00", [5 x i8] zeroinitializer

unsigned char table2[15][16] =
{
    {1,0},
    {1,1,0},
    {3,2,1,0},
    {3,2,1,1,0},
    {3,2,3,2,1,0},
    {3,0,1,3,2,5,4},
    {7,6,5,4,3,2,1,1,1,1,1,1,1,1,1},
};

// LLVM: @table2 = {{.*}}[15 x [16 x i8]] {{.*}}[16 x i8] c"\01\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00", [16 x i8] c"\01\01\00\00\00\00\00\00\00\00\00\00\00\00\00\00", [16 x i8] c"\03\02\01\00\00\00\00\00\00\00\00\00\00\00\00\00", [16 x i8] c"\03\02\01\01\00\00\00\00\00\00\00\00\00\00\00\00", [16 x i8] c"\03\02\03\02\01\00\00\00\00\00\00\00\00\00\00\00", [16 x i8] c"\03\00\01\03\02\05\04\00\00\00\00\00\00\00\00\00", [16 x i8] c"\07\06\05\04\03\02\01\01\01\01\01\01\01\01\01\00", [16 x i8] zeroinitializer

unsigned char table3[15][16] =
{
    {1,1},
    {1,2,2},
    {2,2,2,2},
    {2,2,2,3,3},
    {2,2,3,3,3,3},
    {2,3,3,3,3,3,3},
    {3,3,3,3,3,3,3,4,5,6,7,8,9,10,11},
};

// LLVM: @table3 = {{.*}}[15 x [16 x i8]] {{.*}}[16 x i8] c"\01\01\00\00\00\00\00\00\00\00\00\00\00\00\00\00", [16 x i8] c"\01\02\02\00\00\00\00\00\00\00\00\00\00\00\00\00", [16 x i8] c"\02\02\02\02\00\00\00\00\00\00\00\00\00\00\00\00", [16 x i8] c"\02\02\02\03\03\00\00\00\00\00\00\00\00\00\00\00", [16 x i8] c"\02\02\03\03\03\03\00\00\00\00\00\00\00\00\00\00", [16 x i8] c"\02\03\03\03\03\03\03\00\00\00\00\00\00\00\00\00", [16 x i8] c"\03\03\03\03\03\03\03\04\05\06\07\08\09\0A\0B\00", [16 x i8] zeroinitializer


unsigned char table4[][20] =
{
  {  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  {  0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 2, 2, 2, 2, 0, 0, 0, 0 }
};
// LLVM: @table4 = {{.*}}[2 x [20 x i8]] {{.*}}[20 x i8] zeroinitializer, [20 x i8] c"\00\00\00\00\00\00\00\01\01\01\01\00\02\02\02\02\00\00\00\00"]

unsigned char table5[][20] =
{
  {  0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  {  0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 2, 2, 2, 2, 0, 0, 0, 0 }
};
// LLVM: @table5 = {{.*}}[2 x [20 x i8]] {{.*}}[20 x i8] c"\00\00\00\00\00\00\00\01\00\00\00\00\00\00\00\00\00\00\00\00", [20 x i8] c"\00\00\00\00\00\00\00\01\01\01\01\00\02\02\02\02\00\00\00\00"]

unsigned char table6[][20] =
{
  {  1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  {  0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 2, 2, 2, 2, 0, 0, 0, 0 }
};
// LLVM: @table6 = {{.*}}[2 x [20 x i8]] {{.*}}[20 x i8] c"\01\00\00\00\00\00\00\01\00\00\00\00\00\00\00\00\00\00\00\00", [20 x i8] c"\00\00\00\00\00\00\00\01\01\01\01\00\02\02\02\02\00\00\00\00"]
