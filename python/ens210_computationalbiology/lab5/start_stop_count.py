import re

def genbank2dna(file_name):
	file = open(file_name)
	dna = ''
	start_dna = False
	for line in file:
		if start_dna:
			nt_groups = re.findall('[acgt]+',line)
			for group in nt_groups:
				dna = dna + group
		else:
			if (line[0:6] == 'ORIGIN'):
				start_dna = True		
	file.close()
	return(dna)

def revcomp(sequence):
	rc = sequence[::-1]
	rc = rc.upper()
	rc = rc.replace("A","t")
	rc = rc.replace("T","a")
	rc = rc.replace("G","c")
	rc = rc.replace("C","g")
	return rc

organisms = ['Ehrlichia_ruminantium',
'Candidatus_Pelagibacter_ubique',
'Lactobacillus_salivarius',
'Trichodesmium_erythraeum',
'Prochlorococcus_marinus',
'Methanosarcina_barkeri',
'Aquifex_aeolicus',
'Pyrococcus_abyssi',
'Thermotoga_maritima',
'Haloquadratum_walsbyi',
'Methanothermobacter_thermautotrophicus',
'Escherichia_coli',
'Thermococcus_gammatolerans',
'Pseudomonas_fluorescens',
'Halorhabdus_utahensis',
'Deinococcus_geothermalis',
'Halobacterium_salinarum',
'Sorangium_cellulosum',
'Anaeromyxobacter_dehalogenans']

organism = organisms[18]
file_name = "C://Users//Sena Cetin//Desktop//ENS210//genbank//" + organism + ".gb"


print ("organism: " + organism)

# read entire dna sequence from GenBank file
dna = genbank2dna(file_name)


# a list that stores sequences of all protein genes
gene_seq = []
# a list to store the length (nt) of each protein gene
gene_length = []

# go over info in GenBank file and fill above lists
file = open(file_name)
in_cd = False
for line in file:
	if (line[5:8] == 'CDS'):
		in_cd = True
		position = re.findall('\d+', line)
		start = int(position[0])
		end = int(position[1])
		gene = dna[start-1:end]

		if (re.search('join',line)):
			#print ("single join")
			start = int(position[2])
			end = int(position[3])
			gene = gene + dna[start-1:end]

			if (len(position) == 6):
				#print ("double join")
				start = int(position[4])
				end = int(position[5])
				gene = gene + dna[start-1:end]

		length = len(gene)

		# take reverse complement of gene sequence if necessary
		if re.search('complement',line):
			gene = revcomp(gene)

	# if protein, collect gene, sense and length in a list
	if (in_cd and line[21:29] == '/protein'):			
		gene_seq.append(gene)
		gene_length.append(length)
		in_cd = False

file.close()


# obtain number of nucleotides in genome and print to screen
genome_size = len(dna) 
print ("genome size: % 4.2f Mb" % (0.000001*genome_size))

# calculate GC content (in percent) and print
GC_perc = 100.0*(dna.count('c')+dna.count('g'))/genome_size 
print ("GC content: %4.1f %%" %(GC_perc))

# obtain number of proteins in genome and print
n_genes = len(gene_seq) 
print ("# of protein genes: %4i" % (n_genes))

# calculate average length (in nucleotides) of a protein gene
avg_length = sum(gene_length)/n_genes 
print("avg gene len: %3i nt = %3i codons" %(round(avg_length,0),round(avg_length/3,0)))


# YOUR TURN (PART 1 OF 2)
# count START codons
starts = ['ATG','other']
n_start = [0,0] # numbers of ATG and other start codons
for i in range(len(gene_seq)):
	gene = gene_seq[i]
	if(gene[0:3] == 'atg'):
		n_start[0] += 1
	else:
		n_start[1] += 1


start_tot = n_start[0] + n_start[1]
print("start atg: %5i  %4.1f %%" %(n_start[0],100.0*n_start[0]/start_tot))
print("start oth: %5i  %4.1f %%" %(n_start[1],100.0*n_start[1]/start_tot))


# YOUR TURN (PART 2 OF 2)
# count STOP codons
stops = ['taa','tga','tag','other']
n_stop = [0,0,0,0]
for i in range(len(gene_seq)):
	gene = gene_seq[i]
	if(gene[-3:] == 'taa'):
		n_stop[0] += 1
	elif(gene[-3:] == 'tga'):
		n_stop[1] += 1
	elif(gene[-3:] == 'tag'):
		n_stop[2] += 1
	else:
		n_stop[3] += 1


stop_tot = n_stop[0] + n_stop[1] + n_stop[2]
print(" stop oth: %5i" %(n_stop[3]))
print(" stop taa: %5i  %4.1f %%" %(n_stop[0],100.0*n_stop[0]/stop_tot))
print(" stop tga: %5i  %4.1f %%" %(n_stop[1],100.0*n_stop[1]/stop_tot))
print(" stop tag: %5i  %4.1f %%" %(n_stop[2],100.0*n_stop[2]/stop_tot))
