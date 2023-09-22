# Gnuplot file for plotting 
set   autoscale                        # scale axes automatically
unset log                              # remove any log-scaling
unset label                            # remove any previous labels
set xtic auto                          # set xtics automatically
set ytic auto                          # set ytics automatically
set key at 30,60
set title "MPI strong scalability with 2 nodes"
set xlabel "Number of MPI processes"
set ylabel "Time (in seconds)"
set xr [0:90]
set yr [0:90]
 plot 'data_MPI2nodes_10k.txt' using ($2):($2)  title "Ideal (linear)" with lines , \
"data_MPI_strong_10k.txt" using ($2):(23.692193/$3) title "Size: 10.000" w l , \
"data_MPI_strong_5k.txt" using ($2):(6.041365/$3) title "Size: 5.000" w l , \
"data_MPI_strong_15k.txt" using ($2):(53.336813/$3) title "Size: 15.000" w l 
