# Cal definir:
# k : valor inicial de l'index a l'animacio
# dk : increment de k
# kmax : valor final de l'index a l'animacio
# p (s) : temps de pausa entre frames

print "k=", k
splot 'placaexp.txt' index k w l
pause p
k=k+dk
if (k<=kmax) reread
