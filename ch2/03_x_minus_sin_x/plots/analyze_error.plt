set title "Error in Direct Eval vs. Taylor Series of f(x) for x<=1.0"

line(x) = m*x+b

fit [-8:-1] line(x) "../data/2_6_3_error_tol_1e-32.dat" using 1:4 via m,b

set xlabel "log10(x)"
set ylabel "log10(error)"

set xrange [-11:0.5]
set yrange [-15:0.5]

set grid
set term png
set output "2_6_3_error_tol_1e-32.png"

plot "../data/2_6_3_error_tol_1e-32.dat" using 1:4 title "error" w p pt 7 ps 1.5, \
     [-8:2] line(x) title sprintf("m=%f",m)