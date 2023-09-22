# Gnuplot file for plotting 
set   autoscale                        # scale axes automatically
unset log                              # remove any log-scaling
unset label                            # remove any previous labels
set xtic auto                          # set xtics automatically
set ytic auto                          # set ytics automatically
set key at 250,400
set title "Weak MPI scalability with work load 5000 x 5000"
set xlabel "Number of processes "
set ylabel "Time (in seconds)"
set xr [0:10]
set yr [58:62]
plot "data_weakMPI.txt" using ($2):($3)  title "Weak scalability" with lines , \
