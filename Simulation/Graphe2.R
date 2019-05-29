g = read.table("Temps1.txt")
jpeg("90percentil.jpg")
lambda=g$V1
t901=g$V3

h=read.table("Temps2.txt")
t902=h$V3

f = read.table("Temps3.txt")
t903=f$V3

plot(lambda,t902,type="l",,xlab="lambda",ylab="90 percentil",col="red")
lines(lambda,t901,type="l",col="blue")
lines(lambda,t903,type="l",col="green")
legend("topleft",legend=c("MM10","nMM1","MM10 min"),col=c("blue","red","green"),lty=1:1,cex=0.8)

dev.off()
