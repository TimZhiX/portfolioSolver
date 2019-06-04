library(tidyverse)
require(gridExtra)
data = 0
plot = 0
m = 0
v = 0
p <- c(paste0('plot',1:20))
 #0to19
for (i in 0:19){
filename = paste0("out_", i/200, ".csv")
data = read.csv(filename, header = FALSE)
v[i+1] = mean(data[[2]])
plot = ggplot(data = data ) + 
  geom_point(aes(x = V2, y = V1, color = factor(V3))) +
  geom_hline(yintercept =  i/200, color='blue') +
  labs(x = "variance", y = "mean",colour = "Win", title = paste("Target Return = ",i/200) )+
  theme(plot.title = element_text(hjust = 0.5)) 
assign(p[i+1],plot)
}
grid.arrange(plot1,plot2,plot3,plot4,plot5,plot6,plot7,plot8,plot9,plot10,
             plot11,plot12,plot13,plot14,plot15,plot16,plot17,plot18,plot19,plot20,ncol=5)

err = c(5.35232e-005,
        0.490032,
        3.12257e-005,
        0.0001067,
        1.55921e-006,
        7.3851e-007,
        2.00592e-007,
        0.000979939,
        0.000170047,
        1.06356e-007,
        5.243e-008,
        2.22139e-008,
        1.49515e-008,
        0.00127769,
        1.40866e-006,
        1.1676e-008,
        1.18346e-008,
        7.3796e-009,
        2.27242e-008,
        2.38814e-006,
        1.0756e-008,
        4.21707e-009,
        2.5381e-009,
        2.18603e-009,
        4.45858e-006,
        8.15629e-006,
        1.56895e-009,
        2.54363e-008,
        1.22073e-009,
        3.63012e-009,
        3.24403e-007,
        2.27302e-006,
        2.0713e-009,
        1.24974e-009,
        9.2373e-010,
        2.73549e-009,
        3.84387e-006,
        3.0974e-006,
        6.86013e-010,
        1.92951e-009,
        6.34116e-010,
        6.22663e-010,
        1.19737e-006,
        2.4699e-007,
        3.48319e-010,
        3.39616e-010,
        2.25874e-010,
        2.39112e-007,
        4.11824e-007,
        8.58532e-009,
        2.74109e-010,
        2.22966e-010,
        4.79518e-010,
        1.32021e-007,
        3.07982e-008,
        2.8018e-010,
        3.10351e-010,
        2.83639e-010,
        8.7708e-011)
num = c(1:59)
ggplot(data = data.frame(num,err) ) + 
  geom_smooth(aes(x=num,y=err)) +
  labs(x = "Time", y = "Error") +
  coord_cartesian(xlim=c(0,50))+ 
  scale_x_continuous(expand = c(0, 0))


                  