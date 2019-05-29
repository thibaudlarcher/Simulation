g = read.table("MM1theo.txt")
jpeg("tempsMoytheosimu2.jpg")
lambda=g$V1
moy1=g$V2


h=read.table("Temps2.txt")
moy2=h$V2

plot(lambda,moy1,type="l",,xlab="lambda",ylab="temps moyen d'attente",col="red")
lines(lambda,moy2,type="l",col="blue")
legend("topleft",legend=c("Théorique","simul"),col=c("red","blue"),lty=1:1,cex=0.8)

dev.off()
