modelname = "/Users/jean-charles/Desktop/Simulation/Simulation/Simulation.txt"
data = read.table(modelname)
attach(data);

temps = V1
moyenne = V2

plot(temps,moyenne,type = "l",xlab = "temps",ylab = "E[N],col" ,col = "red")
