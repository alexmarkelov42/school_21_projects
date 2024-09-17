#!/bin/sh

file1=../samples/generic_text_1.txt
file2=../samples/generic_text_2.txt
file3=../samples/generic_text_3.txt
file4=../samples/generic_text_4.txt
file5=../samples/generic_text_5.txt
echo "**no flags test**"
echo "----------------------------------------------------------------------------------"

cat $file1 $file2 $file3 $file4 > test1_cat.txt
./s21_cat $file1 $file2 $file3 $file4 > test1_s21_cat.txt
diff test1_cat.txt test1_s21_cat.txt

echo "**-b test**"
echo "----------------------------------------------------------------------------------"

cat -b $file1 $file2 $file3 $file4 > test2_cat.txt
./s21_cat -b $file1 $file2 $file3 $file4 > test2_s21_cat.txt
diff test2_cat.txt test2_s21_cat.txt

echo "\n**-e flags test**\n"
echo "----------------------------------------------------------------------------------"

cat -e $file1 $file2 $file3 $file4 > test3_cat.txt
./s21_cat -e $file1 $file2 $file3 $file4 > test3_s21_cat.txt
diff test3_cat.txt test3_s21_cat.txt

echo "\n**-n flags test**\n"
echo "----------------------------------------------------------------------------------"

cat -n $file1 $file2 $file3 $file4 > test4_cat.txt
./s21_cat -n $file1 $file2 $file3 $file4 > test4_s21_cat.txt
diff test4_cat.txt test4_s21_cat.txt

echo "\n**-s flags test**\n"
echo "----------------------------------------------------------------------------------"

cat -s $file1 $file2 $file3 $file4 > test5_cat.txt
./s21_cat -s $file1 $file2 $file3 $file4 > test5_s21_cat.txt
diff test5_cat.txt test5_s21_cat.txt

echo "\n**-t flags test**\n"
echo "----------------------------------------------------------------------------------"

cat -t $file1 $file2 $file3 $file4 > test6_cat.txt
./s21_cat -t $file1 $file2 $file3 $file4 > test6_s21_cat.txt
diff test6_cat.txt test6_s21_cat.txt

echo "\n** all flags test**\n"
echo "----------------------------------------------------------------------------------"

cat -benst $file1 $file2 $file3 $file4 > test7_cat.txt
./s21_cat -bnest $file1 $file2 $file3 $file4 > test7_s21_cat.txt
diff test7_cat.txt test7_s21_cat.txt

echo "\n incorrect input test**\n"
echo "----------------------------------------------------------------------------------"

cat -benst  xmc.,xzmc,xzmc.,xzmc.z, > test8_cat.txt
./s21_cat -bnest xmc.,xzmc,xzmc.,xzmc.z, > test8_s21_cat.txt
diff test8_cat.txt test8_s21_cat.txt

echo "\n flags not in order test**\n"
echo "----------------------------------------------------------------------------------"

cat $file1 $file2 $file3 $file4 -b ../samples/generic_text_1.txt -n  > test9_cat.txt
./s21_cat $file1 $file2 $file3 $file4 -b ../samples/generic_text_1.txt -n  > test9_s21_cat.txt
diff test9_cat.txt test9_s21_cat.txt

echo "\n all flags not in order test**\n"
echo "----------------------------------------------------------------------------------"

cat -s $file1 $file2 $file3 $file4 -be ../samples/generic_text_1.txt -nt  > test10_cat.txt
./s21_cat -s $file1 $file2 $file3 $file4 -be ../samples/generic_text_1.txt -nt  > test10_s21_cat.txt
diff test10_cat.txt test10_s21_cat.txt

echo "\n long options test**\n"
echo "----------------------------------------------------------------------------------"

cat -E $file1 $file2 $file3 $file4 --number-nonblank -T > test11_cat.txt --squeeze-blank
./s21_cat -E $file1 $file2 $file3 $file4 --number-nonblank -T > test11_s21_cat.txt --squeeze-blank
diff test11_cat.txt test11_s21_cat.txt

echo "\n** -setb test**\n"
echo "----------------------------------------------------------------------------------"

cat -b $file1 $file2 -te $file3 $file4 -s $file5 > test12_cat.txt
./s21_cat -b $file1 $file2 -te $file3 $file4 -s $file5 > test12_s21_cat.txt
diff test12_cat.txt test12_s21_cat.txt

echo "\n incorrect flags test**\n"
echo "----------------------------------------------------------------------------------"

cat -z --kappa --god $file1 -s $file2  > test13_cat.txt
./s21_cat -z --kappa --god $file1 -s $file2  > test13_s21_cat.txt
diff test13_cat.txt test13_s21_cat.txt

echo "\n --number test**\n"
echo "----------------------------------------------------------------------------------"

cat -E $file1 $file2 $file3 $file4 --number -T > test14_cat.txt
./s21_cat -E $file1 $file2 $file3 $file4 --number -T > test14_s21_cat.txt
diff test14_cat.txt test14_s21_cat.txt

echo "\n incorrect file test**\n"
echo "----------------------------------------------------------------------------------"

cat -benst  fffffile > test15_cat.txt
./s21_cat -bnest fffffile > test15_s21_cat.txt
diff test15_cat.txt test15_s21_cat.txt
