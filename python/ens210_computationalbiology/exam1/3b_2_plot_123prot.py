import matplotlib.pyplot as plt

GC_cont = []
GC1 = []
GC2 = []
GC3 = []

file_name = '3b_gc123prot2.txt'
file = open(file_name)
for line in file:
	if (line[0] != '#'):
		data = line.split()
		#print (data)
		if (len(data) > 1):
			GC_cont.append(float(data[1]))
			GC1.append(float(data[2]))
			GC2.append(float(data[3]))
			GC3.append(float(data[4]))

file.close()


#plot 
x_min = 10
x_max = 90
fig = plt.figure(figsize=(8,8))
plt.rc('grid',ls="--")

sub = fig.add_subplot(1,1,1)
y_min = 0
y_max = 100

sub.plot([0, 100], [0, 100], ls='--', c='0.5')
sub.plot(GC_cont,GC1,'.b',ms=1,label='1')
sub.plot(GC_cont,GC2,'.g',ms=1,label='2')
sub.plot(GC_cont,GC3,'.r',ms=1,label='3')
sub.set_xlabel('GC of gene [%]')
sub.set_xlim(x_min,x_max)
sub.xaxis.set_ticks(range(x_min,x_max+1,10))
sub.set_ylabel('GC of codon position [%]')
sub.set_ylim(y_min,y_max)
sub.yaxis.set_ticks(range(y_min,y_max+1,10))
sub.grid()
sub.legend(loc="upper left")


plt.show()
# save plot to file
fig.savefig("3b_gc123prot2.pdf", bbox_inches='tight')


