g = read.table("Temps1.txt")
jpeg("tempsMoy.jpg")
lambda=g$V1
moy1=g$V2

h=read.table("Temps2.txt")
moy2=h$V2

f = read.table("Temps3.txt")
moy3=f$V2

plot(lambda,moy2,type="l",,xlab="lambda",ylab="temps moyen d'attente",col="red")
lines(lambda,moy1,type="l",col="blue")
lines(lambda,moy3,type="l",col="green")
legend("topleft",legend=c("MM10","nMM1","MM10 min"),col=c("blue","red","green"),lty=1:1,cex=0.8)

dev.off()
