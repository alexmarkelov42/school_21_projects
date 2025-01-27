output_precision(9)
mult_num = 2;
pkg load symbolic;

matrix1 = randn(3,3,"double");
matrix2 = randn(3,3,"double");
matrix3 = randn(3,1,"double");
matrix4 = [1,2,3;6,5,4;7,9,8];

output_precision(7)

file = fopen('123_test.txt', 'w');
fdisp(file, adjoint(matrix4));
fdisp(file, det(matrix4));
fdisp(file, inv(matrix4));
fclose(file);

file = fopen('matrix1.txt', 'w');
fdisp(file, matrix1);
fclose(file);

file = fopen('matrix2.txt', 'w');
fdisp(file, matrix2);
fclose(file);

file = fopen('matrix3.txt', 'w');
fdisp(file, matrix3);
fclose(file);

file = fopen('test_1.txt', 'w');
fdisp(file, matrix1 * mult_num);
fclose(file);

file = fopen('test_matrix1.txt', 'w');
fdisp(file, matrix1);
fclose(file);

file = fopen('test_2.txt', 'w');
fdisp(file, matrix1 + matrix2);
fclose(file);

file = fopen('test_3.txt', 'w');
fdisp(file, matrix1 - matrix2);
fclose(file);

file = fopen('test_4.txt', 'w');
fdisp(file, matrix1 * matrix2);
fclose(file);

file = fopen('test_5.txt', 'w');
fdisp(file, matrix1 * matrix3);
fclose(file);

file = fopen('test_6.txt', 'w');
fdisp(file, inv(matrix1));
fclose(file);

file = fopen('test_7.txt', 'w');
fdisp(file, det(matrix1));
fclose(file);

file = fopen('test_8.txt', 'w');
fdisp(file, adjoint(matrix1));
fclose(file);

file = fopen('test_9.txt', 'w');
fdisp(file, resize(matrix1,4,4));
fclose(file);

file = fopen('test_10.txt', 'w');
fdisp(file, resize(matrix1,2,2));
fclose(file);

file = fopen('test_11.txt', 'w');
fdisp(file, transpose(matrix1));
fclose(file);

file = fopen('test_12.txt', 'w');
fdisp(file, transpose(matrix3));
fclose(file);

