# Gnuplot file for plotting 
set   autoscale                        # scale axes automatically
unset log                              # remove any log-scaling
unset label                            # remove any previous labels
set xtic auto                          # set xtics automatically
set ytic auto                          # set ytics automatically
set key at 128,71
set title "OpenMP strong scalability with 2 MPI process"
set xlabel "Number of total Threads"
set ylabel "Speed Up"
set xr [0:128]
set yr [0:128]
plot "data_omp_5k.txt" using (2*$1):(2*$1)  title "Ideal (linear)" with lines , \
 "data_omp_5k.txt" using (2*$1):(59.386769/$3) title "Size: 5.000" with lines , \
 "data_omp_10k.txt" using (2*$1):(236.720754/$3) title "Size: 10.000" with lines , \
 "data_omp_15k.txt" using (2*$1):(534.498939/$3) title "Size: 15.000" with lines , \
 
 
