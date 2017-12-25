import matplotlib.pyplot as plt
from math import sqrt

aas = ['A','C','D','E','F','G','H','I','K','L','M','N','P','Q','R','S','T','V','W','Y']
# find number of amino acids
naa = len(aas)

# read info from file aa_counts.txt
info = {}
file_name = '2a_aa_counts.txt'
file = open(file_name)
for line in file:
	if (line[0:1] != '#'):
		data = line.split()
		#print (data)
		if (len(data) > 1):
			organism = data[0]
			info[organism] = []
			GC_cont = float(data[1])
			info[organism].append(GC_cont)
			for i in range(naa):
				info[organism].append(float(data[2+i]))
file.close()

# find number of organisms
n_org = len(info)

# calculate percentages
percentages = naa*[0]
for i in range(naa):
	for organism in info:
		percentages[i] += float(info[organism][i+1])
	percentages[i] /= n_org
# calculate standard deviation
std_dev = naa*[0]
for i in range(naa):
	for organism in info:
		std_dev[i] += (float(info[organism][i+1]) - percentages[i])**2
	std_dev[i] = sqrt(std_dev[i]/n_org)

#plot 
ind = range(1,naa+1)		
fig = plt.figure(figsize=(8, 6))
plt.rc('grid',ls="--")
sub = fig.add_subplot(1,1,1)
sub.bar(ind,percentages,yerr=std_dev,error_kw={'capsize':3, 'capthick':1})
sub.set_xlabel('amino acid')
sub.set_xticks(ind)
sub.set_xticklabels(aas)
sub.set_ylabel('occurrence [%]')
sub.set_ylim(0,12)

plt.show()
# save plot to file
fig.savefig("2a_aa_freq.pdf", bbox_inches='tight')

plt.close(fig)

