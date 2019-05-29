g = read.table("MM1theo.txt")
jpeg("90theosimu2.jpg")
lambda=g$V1
moy1=g$V3


h=read.table("Temps2.txt")
moy2=h$V3

plot(lambda,moy1,type="l",,xlab="lambda",ylab="90 percentile",col="red")
lines(lambda,moy2,type="l",col="blue")
legend("topleft",legend=c("Théorique","simul"),col=c("red","blue"),lty=1:1,cex=0.8)

dev.off()
