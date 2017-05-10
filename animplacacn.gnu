# Cal definir:
# k : valor inicial de l'index a l'animacio
# kmax : valor final de l'index a l'animacio
# p (s) : temps de pausa entre frames
#
# A continuacio feu
# load 'animplacacn.gnu'

print "k=", k
splot 'placacn.txt' index k w l
pause p
k=k+1
if (k<=kmax) reread
