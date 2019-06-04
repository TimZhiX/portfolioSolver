library(tidyverse)
require(gridExtra)
data = 0
plot = 0
 #0to19
{
  i=19
filename = paste0("out_", i/200, ".csv")
data = read.csv(filename, header = FALSE)

plot20 = ggplot(data = data ) + 
  geom_point(aes(x = V2, y = V1)) +
  geom_hline(yintercept =  i/200) +
  labs(x = "variance", y = "mean", title = paste("Target Return = ",i/200) )+
  theme(plot.title = element_text(hjust = 0.5)) 
}
grid.arrange(plot1,plot2,plot3,plot4,plot5,plot6,plot7,plot8,plot9,plot10,
             plot11,plot12,plot13,plot14,plot15,plot16,plot17,plot18,plot19,plot20,ncol=5)
grid.arrange(plot1,plot2,plot3,plot4,plot5)
