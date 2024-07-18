set title "Error in s_{up} vs. s_{down} as a Function of N"

fit_1(x) = a_1*x+b_1
fit_2(x) = a_2*x+b_2
fit_3(x) = a_3*x+b_3

fit [x=2:4] fit_1(x) "../data/2_6_2_2_single.dat" using 1:4 via a_1, b_1
fit [x=4:8] fit_2(x) "../data/2_6_2_2_single.dat" using 1:4 via a_2, b_2
fit [x=2:10] fit_3(x) "../data/2_6_2_2_double.dat" using 1:4 via a_3, b_3

set xlabel "log10(N)"
set ylabel "log(error)"
set key left top
set xrange [1.5:10.5]

set grid
set term png  
set output "2_6_2_error_plot.png"

plot "../data/2_6_2_2_single.dat" using 1:4 title "float" w p pt 7 ps 1.5, \
     "../data/2_6_2_2_double.dat" using 1:4 title "double" w p pt 7 ps 1.5, \
     [2:4] fit_1(x) title sprintf("m_1=%f",a_1) lt rgb "red", \
     [4:8] fit_2(x) title sprintf("m_2=%f",a_2) lt rgb "blue", \
     [2:10] fit_3(x) title sprintf("m_3=%f",a_3)  lt rgb "orange"