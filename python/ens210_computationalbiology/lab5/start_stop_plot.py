import matplotlib.pyplot as plt

genome_size = []
GC_cont = []
num_prot = []
prot_len = []

startATG = []
start2 = []
stopTAA = []
stopTGA = []
stopTAG = []

file_name = 'prokaryotes19.txt'
file = open(file_name)
for line in file:
	if (line[0:1] != '#'):
		data = line.split()
		#print (data)
		if (len(data) > 1):
			genome_size.append(float(data[1]))
			GC_cont.append(float(data[2]))
			num_prot.append(0.001*int(data[3]))
			prot_len.append(int(data[4]))

			startATG.append(float(data[5]))
			start2.append(float(data[6]))
			stopTAA.append(float(data[7]))
			stopTGA.append(float(data[8]))
			stopTAG.append(float(data[9]))

file.close()


#plot 
x_min = 20
x_max = 80
fig = plt.figure(figsize=(8, 8))
plt.rc('grid',ls="--")

sub = fig.add_subplot(2,1,1)
y_min = 0
y_max = 100

sub.plot(GC_cont,startATG,'or',label='ATG')
sub.plot(GC_cont,start2,'sb',label='other')
sub.set_xlabel('GC content [%]')
sub.set_xlim(x_min,x_max)
sub.xaxis.set_ticks(range(x_min,x_max+1,5))
sub.set_ylabel('START codon [%]')
sub.set_ylim(y_min,y_max)
sub.grid()
sub.legend(loc=2)

sub = fig.add_subplot(2,1,2)
y_min = 0
y_max = 100
sub.plot(GC_cont,stopTAA, 'or', label='TAA')
sub.plot(GC_cont,stopTGA, 'sb', label='TGA')
sub.plot(GC_cont,stopTAG, '^g', label='TAG')
sub.set_xlabel('GC content [%]')
sub.set_xlim(x_min,x_max)
sub.xaxis.set_ticks(range(x_min,x_max+1,5))
sub.set_ylabel('STOP codon [%]')
sub.set_ylim(y_min,y_max)
sub.grid()
sub.legend(loc=2)



plt.show()
# save plot to file
fig.savefig("gc_start_stop.pdf", bbox_inches='tight')


