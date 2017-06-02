# Cal definir:
# k : valor inicial de l'index a l'animacio
# kmax : valor final de l'index a l'animacio
# p (s) : temps de pausa entre frames
#
# A continuacio feu
# load 'animplacacn.gnu'

set view map
set size ratio -1
set pm3d
unset surface
set cbrange [0:25]
kmax=100
p=0
set output 'peli.gif'
set terminal gif animate delay 0.1

do for [k=0:kmax]{
  print "k=", k
  splot 'placacn.txt' index k w l
  pause p
}

set output



