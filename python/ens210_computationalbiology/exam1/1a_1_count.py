import re
import os

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

def genbank2gene_seqs(dna,file_name):
	gene_seq = []
	# go over info in GenBank file and fill gene_seq list
	# with the sequences of the protein-coding genes
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

			# take reverse complement of gene sequence if necessary
			if re.search('complement',line):
				gene = revcomp(gene)

		# if protein, collect gene, sense and length in a list
		if (in_cd and line[21:29] == '/protein'):
			gene_seq.append(gene)
			in_cd = False

	file.close()
	return(gene_seq)


# open file for writing
out_name = "1a_prokaryotes.txt"
out = open(out_name,"w")
# write the column labels as a first line in this file
out.write("# name_of_organism		                    Mb   GC%  Prot   avg  ATG% oth%  TAA% TGA% TAG%\n")

# get current working directory
cwd = os.getcwd()
print(cwd)


# directory with genomes (CHANGE ACCORDING TO YOUR DIRECTORY ORGANISATION)
dir_genomes = cwd + "/../genbank/"

# loop over all files in the directory containing the genomes
for file in os.listdir(dir_genomes):
    # process file only if ending is .txt
	if file.endswith(".gb"): # (CHANGE ENDING IF NECESSARY)
        
        # extract organism name from file name
		organism = file.split('.')[0]
		print (">>> " + organism)

		# create full name to GenBank file (CHANGE IF NECESSARY)
		file_name = dir_genomes + file
		# read entire dna sequence from GenBank file
		dna = genbank2dna(file_name)
		# obtain sequences of protein coding genes from GenBank file
		gene_seq = genbank2gene_seqs(dna,file_name)


		# find number of nucleotides in genome and print to screen
		genome_size = len(dna) 
		print ("genome size: % 4.2f Mb" % (0.000001*genome_size))

		# calculate GC content (in percent) and print
		GC_perc = 100.0*(dna.count('c')+dna.count('g'))/genome_size 
		print ("GC content: %4.1f %%" %(GC_perc))

		# obtain number of proteins in genome and print
		n_genes = len(gene_seq) 
		print ("# of protein genes: %4i" % (n_genes))

		# calculate average length (in nucleotides) of a protein gene
		tot_length = 0
		for gene in gene_seq:
			tot_length += len(gene)
		avg_length = 1.0*tot_length/n_genes 
		print("avg gene len: %4i nt = %3i aa" %(round(avg_length,0),round(avg_length/3,0)))

		# count START codons by checking first three letters in gene
		starts = ['atg','oth']
		n_start = [0,0] # numbers of ATG and other start codons
		for gene in gene_seq:
			if (gene[0:3] == starts[0]):
				n_start[0] += 1
			else:
				n_start[1] += 1
		tot_start = sum(n_start)
		# convert numbers to percentages 
		p_start = [0,0]
		for i in range(len(p_start)):
			p_start[i] = 100.0*n_start[i]/tot_start
		for i in range(len(p_start)):
			print("start %3s: %5i  %4.1f %%" %(starts[i],n_start[i],p_start[i]))

		# count STOP codons by checking last three letters in gene
		stops = ['taa','tga','tag','oth']
		n_stop = [0,0,0,0]
		for gene in gene_seq:
			if (gene[-3:] == stops[0]):
				n_stop[0] += 1
			elif (gene[-3:] == stops[1]):
				n_stop[1] += 1
			elif (gene[-3:] == stops[2]):
				n_stop[2] += 1
			else:
				n_stop[3] += 1
		tot_stop = sum(n_stop)
		# convert numbers to percentages 
		p_stop = [0,0,0]
		for i in range(len(p_stop)):
			p_stop[i] = 100.0*n_stop[i]/tot_stop
		print(" stop oth: %5i" %(n_stop[3]))
		for i in range(len(p_stop)):
			print(" stop %3s: %5i  %4.1f %%" %(stops[i],n_stop[i],p_stop[i]))

        # write results to output file 
		out.write("%-50s %5.2f %4.1f %4i  %4i  %4.1f %4.1f  %4.1f %4.1f %4.1f\n" 
			% (organism,0.000001*genome_size,GC_perc,n_genes,round(avg_length,0),
				p_start[0],p_start[1],p_stop[0],p_stop[1],p_stop[2]))

out.close()


