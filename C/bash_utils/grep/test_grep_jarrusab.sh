#!/bin/sh

file1=../samples/generic_text_1.txt
file2=../samples/generic_text_2.txt
file3=../samples/generic_text_3.txt
echo "test 1"
echo "**no flags test**"

grep "Lo" $file3 > test1_grep.txt
./s21_grep "Lo" $file3 > test1_s21_grep.txt
diff test1_grep.txt test1_s21_grep.txt

echo "----------------------------------------------------------------------------------"
echo "test 2"
echo "**-e test**"

grep -e "Lo" -e "kappa" $file3 ../samples/generic_text_2.txt > test2_grep.txt
./s21_grep -e "Lo" -e "kappa" $file3 ../samples/generic_text_2.txt > test2_s21_grep.txt
diff test2_grep.txt test2_s21_grep.txt

echo "----------------------------------------------------------------------------------"
echo "test 3"
echo "**-f flags test**"

grep -f ../samples/pattern1.txt -f ../samples/pattern2.txt $file3 > test3_grep.txt
./s21_grep -f ../samples/pattern1.txt -f ../samples/pattern2.txt $file3 > test3_s21_grep.txt
diff test3_grep.txt test3_s21_grep.txt

echo "----------------------------------------------------------------------------------"
echo "test 4"
echo "**-n flags test**"

grep -n "Lo" $file3 > test4_grep.txt
./s21_grep -n "Lo" $file3 > test4_s21_grep.txt
diff test4_grep.txt test4_s21_grep.txt

echo "----------------------------------------------------------------------------------"
echo "test 5"
echo "**-s flags test**"

grep -s "Lo" ka[ppa $file3 ../samples/generic_text_2.txt > test5_grep.txt
./s21_grep -s "Lo" ka[ppa $file3 ../samples/generic_text_2.txt > test5_s21_grep.txt
diff test5_grep.txt test5_s21_grep.txt

echo "----------------------------------------------------------------------------------"
echo "test 6"
echo "**-i test**"

grep -i "Lo" "kappa" $file3 > test6_grep.txt
./s21_grep -i "Lo" "kappa" $file3 > test6_s21_grep.txt
diff test6_grep.txt test6_s21_grep.txt

echo "----------------------------------------------------------------------------------"
echo "test 7"
echo "**-v test**"

grep -v "Lo" "kappa" $file3 > test7_grep.txt
./s21_grep -v "Lo" "kappa" $file3 > test7_s21_grep.txt
diff test7_grep.txt test7_s21_grep.txt

echo "----------------------------------------------------------------------------------"
echo "test 8"
echo "**-h test**"

grep -h "Lo" $file3 $file2 > test8_grep.txt
./s21_grep -h "Lo" $file3 $file2 > test8_s21_grep.txt
diff test8_grep.txt test8_s21_grep.txt

echo "----------------------------------------------------------------------------------"
echo "test 9"
echo "**-c test**"

grep -c "Lo" $file3 $file2 > test9_grep.txt
./s21_grep -c "Lo" $file3 $file2 > test9_s21_grep.txt
diff test9_grep.txt test9_s21_grep.txt

echo "----------------------------------------------------------------------------------"
echo "test 10"
echo "**-l test**"

grep -l "Lo" $file3 $file2 > test10_grep.txt
./s21_grep -l "Lo" $file3 $file2 > test10_s21_grep.txt
diff test10_grep.txt test10_s21_grep.txt

echo "----------------------------------------------------------------------------------"
echo "test 11"
echo "**-o test**"

grep -o "Lo" $file3 $file2 > test11_grep.txt
./s21_grep -o "Lo" $file3 $file2 > test11_s21_grep.txt
diff test11_grep.txt test11_s21_grep.txt

echo "----------------------------------------------------------------------------------"
echo "test 12"
echo "**-oi test**"

grep -oi -e "loRem" $file3 $file2 > test12_grep.txt
./s21_grep -oi -e "loRem" $file3 $file2 > test12_s21_grep.txt
diff test12_grep.txt test12_s21_grep.txt

echo "----------------------------------------------------------------------------------"
echo "test 13"
echo "**-oi test**"

grep -oi $file3 $file2 > test13_grep.txt -f ../samples/pattern2.txt
./s21_grep -oi $file3 $file2 > test13_s21_grep.txt -f ../samples/pattern2.txt
diff test13_grep.txt test13_s21_grep.txt

echo "----------------------------------------------------------------------------------"
echo "test 14"
echo "**-oc test**"

grep -oc $file3 $file2 > test14_grep.txt -f ../samples/pattern1.txt
./s21_grep -oc $file3 $file2 > test14_s21_grep.txt -f ../samples/pattern1.txt
diff test14_grep.txt test14_s21_grep.txt

echo "----------------------------------------------------------------------------------"
echo "test 15"
echo "**-on test**"

grep -on $file3 $file2 > test15_grep.txt -f ../samples/pattern1.txt
./s21_grep -on $file3 $file2 > test15_s21_grep.txt -f ../samples/pattern1.txt
diff test15_grep.txt test15_s21_grep.txt

echo "----------------------------------------------------------------------------------"
echo "test 16"
echo "**-oh test**"

grep -oh $file3 $file2 > test16_grep.txt -f ../samples/pattern1.txt
./s21_grep -oh $file3 $file2 > test16_s21_grep.txt -f ../samples/pattern1.txt
diff test16_grep.txt test16_s21_grep.txt

echo "----------------------------------------------------------------------------------"
echo "test 17"
echo "**-iv test**"

grep -iv $file3 $file2 > test17_grep.txt -f ../samples/pattern1.txt -e "loReM"
./s21_grep -iv $file3 $file2 > test17_s21_grep.txt -f ../samples/pattern1.txt -e "loReM"
diff test17_grep.txt test17_s21_grep.txt

echo "----------------------------------------------------------------------------------"
echo "test 18"
echo "**-is test**"

grep -is "Lo" "kappa" $file3 > test18_grep.txt
./s21_grep -is "Lo" "kappa" $file3 > test18_s21_grep.txt
diff test18_grep.txt test18_s21_grep.txt

echo "----------------------------------------------------------------------------------"
echo "test 19"
echo "**-shn test**"

grep -shn "Lo" "kappa" $file3 $file2 $file1 > test19_grep.txt
./s21_grep -shn "Lo" "kappa" $file3 $file2 $file1 > test19_s21_grep.txt
diff test19_grep.txt test19_s21_grep.txt

echo "----------------------------------------------------------------------------------"
echo "test 20"
echo "**-sh -e -e -n -h test**"

grep -sh -e "Lo" $file3 $file2 $file1 > test20_grep.txt -e "kappa" -h
./s21_grep -sh -e "Lo" $file3 $file2 $file1 > test20_s21_grep.txt -e "kappa" -h
diff test20_grep.txt test20_s21_grep.txt

echo "----------------------------------------------------------------------------------"
echo "test 21"
echo "**-sh -e -e -n test**"

grep -sh -e "Lo" $file3 $file2 $file1 > test21_grep.txt -e "kappa" -n -e "Nm" -i
./s21_grep -sh -e "Lo" $file3 $file2 $file1 > test21_s21_grep.txt -e "kappa" -n -e "Nm" -i
diff test21_grep.txt test21_s21_grep.txt

echo "----------------------------------------------------------------------------------"
echo "test 22"
echo "incorrect input test"

grep -jdflksjflkdsjflkdsjflk jdskljflkdsjfkdsj jfkdlsjflkdsjflkdsjlkf -e jfdlksjflkdsjfklds -f jfdklsjflkdsjf > test22_grep.txt
./s21_grep -jdflksjflkdsjflkdsjflk jdskljflkdsjfkdsj jfkdlsjflkdsjflkdsjlkf -e jfdlksjflkdsjfklds -f jfdklsjflkdsjf > test22_s21_grep.txt
diff test22_grep.txt test22_s21_grep.txt

echo "----------------------------------------------------------------------------------"
echo "test 23"
echo "incorrect input test"

grep -f jdsklfjlkdsfjlkds > test23_grep.txt
./s21_grep -f jdsklfjlkdsfjlkds > test23_s21_grep.txt
diff test23_grep.txt test23_s21_grep.txt

echo "----------------------------------------------------------------------------------"
echo "test 24"
echo "all flags test №1 "

grep -i -e "Lo" -f ../samples/pattern1.txt -h $file1 -o > test24_grep.txt
./s21_grep -i -e "Lo" -f ../samples/pattern1.txt -h $file1 -o > test24_s21_grep.txt
diff test24_grep.txt test24_s21_grep.txt

echo "----------------------------------------------------------------------------------"
echo "test 25"
echo "all flags test №2 "

grep -i -e "Lo" -f ../samples/pattern1.txt -h $file1 -c > test25_grep.txt
./s21_grep -i -e "Lo" -f ../samples/pattern1.txt -h $file1 -c > test25_s21_grep.txt
diff test25_grep.txt test25_s21_grep.txt

echo "----------------------------------------------------------------------------------"
echo "test 26"
echo "all flags test №2 "

grep -i -e "Lo" $file2 -f ../samples/pattern1.txt $file3 -h $file1 -l > test26_grep.txt
./s21_grep -i -e "Lo" $file2 -f ../samples/pattern1.txt $file3 -h $file1 -l > test26_s21_grep.txt
diff test26_grep.txt test26_s21_grep.txt

echo "----------------------------------------------------------------------------------"
echo "test 27"
echo "all flags test №3 "

grep -i -e "Lo" -f ../samples/pattern1.txt -h $file1 $file2 -c > test27_grep.txt
./s21_grep -i -e "Lo" -f ../samples/pattern1.txt -h $file1 $file2 -c > test27_s21_grep.txt
diff test27_grep.txt test27_s21_grep.txt

echo "----------------------------------------------------------------------------------"
echo "test 28"
echo "all flags test №4 "

grep -i -e "Lo" -f ../samples/pattern1.txt $file1 $file2 -c > test28_grep.txt
./s21_grep -i -e "Lo" -f ../samples/pattern1.txt $file1 $file2 -c > test28_s21_grep.txt
diff test28_grep.txt test28_s21_grep.txt

echo "----------------------------------------------------------------------------------"
echo "test 29"
echo "all flags test №5 "

grep -i -e "Lo" $file2 kappa -f ../samples/pattern1.txt $file3 -h $file1 -l > test29_grep.txt -s
./s21_grep -i -e "Lo" $file2 kappa -f ../samples/pattern1.txt $file3 -h $file1 -l > test29_s21_grep.txt -s
diff test29_grep.txt test29_s21_grep.txt

echo "----------------------------------------------------------------------------------"
echo "test 30"
echo "all flags test №6 "

grep -i -e "Lo" $file2 kappa -f ../samples/pattern1.txt $file3 -h $file1 -l > test30_grep.txt
./s21_grep -i -e "Lo" $file2 kappa -f ../samples/pattern1.txt $file3 -h $file1 -l > test30_s21_grep.txt
diff test30_grep.txt test30_s21_grep.txt
