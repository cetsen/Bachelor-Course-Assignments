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
out_name = "3b_gc123prot2.txt"
out = open(out_name,"w")
# write the column labels as a first line in this file
out.write("# name_of_organism		                    GC%   _1_   _2_   _3_\n")

# get current working directory
cwd = os.getcwd()
print(cwd)

# directory with genomes (CHANGE ACCORDING TO YOUR DIRECTORY ORGANISATION)
dir_genomes = cwd + "\\"

# loop over all files in the directory containing the genomes
for file in os.listdir(dir_genomes):
    # process file only if it is one of these organisms:
	if (file.startswith("Acidianus_hospitalis") or file.startswith("Bradyrhizobium_japonicum")):
        
        # extract organism name from file name
		organism = file.split('.')[0]
		print (">>> " + organism)

		# create full name to GenBank file (CHANGE IF NECESSARY)
		file_name = dir_genomes + file
		# read entire dna sequence from GenBank file
		dna = genbank2dna(file_name)
		# obtain sequences of protein coding genes from GenBank file
		gene_seq = genbank2gene_seqs(dna,file_name)

		for gene in gene_seq:
			gene_len = len(gene)
			if(gene_len > 600):
				# calculate GC content (in percent) and print
				GC_perc = 100.0*(gene.count('c') + gene.count('g'))/gene_len
				print ("GC content: %4.1f %%" %(GC_perc))

				starts = ['g','c','a','t']
				n_start1 = [0,0]
				n_start2 = [0,0]
				n_start3 = [0,0] 

				#CHECKS ALL THREE CODON POSITIONS FOR G AND C
				for i in range(0, gene_len, 3):
					if (gene[i:i+1] == starts[0] or gene[i:i+1] == starts[1]):
						n_start1[0] += 1
					else:
						n_start1[1] += 1
				for j in range(1, gene_len, 3):
					if (gene[j:j+1] == starts[0] or gene[j:j+1] == starts[1]):
						n_start2[0] += 1
					else:
						n_start2[1] += 1	
				for k in range(2, gene_len, 3):
					if (gene[k:k+1] == starts[0] or gene[k:k+1] == starts[1]):
						n_start3[0] += 1
					else:
						n_start3[1] += 1

				p_gc_start1 = 100.0*n_start1[0]/sum(n_start1)
				p_gc_start2 = 100.0*n_start2[0]/sum(n_start2)
				p_gc_start3 = 100.0*n_start3[0]/sum(n_start3)

				print ("1: %4.1f %%" %(p_gc_start1))
				print ("2: %4.1f %%" %(p_gc_start2))
				print ("3: %4.1f %%" %(p_gc_start3))

		        # write results to output file 
				out.write("%-50s %4.1f  %4.1f  %4.1f  %4.1f\n" % (organism,GC_perc,p_gc_start1,p_gc_start2,p_gc_start3))

out.close()