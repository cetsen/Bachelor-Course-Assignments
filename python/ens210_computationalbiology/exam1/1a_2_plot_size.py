import matplotlib.pyplot as plt

genome_size = []
GC_cont = []
num_prot = []
prot_avg = []

file_name = '1a_prokaryotes.txt'
file = open(file_name)
for line in file:
	if (line[0:1] != '#'):
		# assumes white space between entries to split each line 
		data = line.split()
		if (len(data) > 1):
			# assumes the numbers are in the correct columns
			genome_size.append(float(data[1]))
			GC_cont.append(float(data[2]))
			num_prot.append(0.001*int(data[3])) # convert number to Kilo
			prot_avg.append(int(data[4])/3.0) # convert avg length from nt to aa
file.close()

#plot 
x_min = int(min(genome_size)-1)
x_max = int(max(genome_size)+1)
fig = plt.figure(figsize=(12, 8))
plt.rc('grid',ls="--")

sub = fig.add_subplot(2,2,1)
y_min = 20
y_max = 80
sub.plot(genome_size,GC_cont,'or')
sub.set_xlabel('genome size [Mb]')
sub.set_xlim(x_min,x_max)
sub.xaxis.set_ticks(range(x_min,x_max+1))
sub.set_ylabel('GC of genome [%]')
sub.set_ylim(y_min,y_max)
sub.yaxis.set_ticks(range(y_min,y_max+1,10))
sub.grid()

sub = fig.add_subplot(2,2,2)
y_min = 250
y_max = 400
sub.plot([0, 12], [0, 12], ls='--', c='0.5')
sub.plot(genome_size,prot_avg,'og')
sub.set_xlabel('genome size [Mb]')
sub.set_xlim(x_min,x_max)
sub.xaxis.set_ticks(range(x_min,x_max+1))
sub.set_ylabel('avg. protein length [aa]')
sub.set_ylim(y_min,y_max)
sub.yaxis.set_ticks(range(y_min,y_max+1,25))
sub.grid()

sub = fig.add_subplot(2,2,4)
y_min = 0
y_max = 12
sub.plot([0, 12], [0, 12], ls='--', c='0.5')
sub.plot(genome_size,num_prot,'ob')
sub.set_xlabel('genome size [Mb]')
sub.set_xlim(x_min,x_max)
sub.xaxis.set_ticks(range(x_min,x_max+1))
sub.set_ylabel('number of proteins in genome [K]')
sub.set_ylim(y_min,y_max)
sub.grid()

plt.show()
# save plot to file
fig.savefig("1a_size_gc_prot.pdf", bbox_inches='tight')


