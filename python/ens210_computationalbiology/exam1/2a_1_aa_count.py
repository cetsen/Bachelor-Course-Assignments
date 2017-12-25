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

codon2aa = {
	# Phenylalanine # Serine  # Tyrosine   # Cysteine
	'TTT' : 'F', 'TCT' : 'S', 'TAT' : 'Y', 'TGT' : 'C', 
	'TTC' : 'F', 'TCC' : 'S', 'TAC' : 'Y', 'TGC' : 'C', 
	# Leucine                 # Stop       # Stop
	'TTA' : 'L', 'TCA' : 'S', 'TAA' : '_', 'TGA' : '_', 
	'TTG' : 'L', 'TCG' : 'S', 'TAG' : '_', 'TGG' : 'W', # Tryptophan
	# Leucine	  # Proline   # Histidine  # Arginine
	'CTT' : 'L', 'CCT' : 'P', 'CAT' : 'H', 'CGT' : 'R', 
	'CTC' : 'L', 'CCC' : 'P', 'CAC' : 'H', 'CGC' : 'R', 
	#						  # Glutamine
	'CTA' : 'L', 'CCA' : 'P', 'CAA' : 'Q', 'CGA' : 'R', 
	'CTG' : 'L', 'CCG' : 'P', 'CAG' : 'Q', 'CGG' : 'R', 
	# Isoleucine # Threonine  # Asparagine  # Serine
	'ATT' : 'I', 'ACT' : 'T', 'AAT' : 'N', 'AGT' : 'S', 
	'ATC' : 'I', 'ACC' : 'T', 'AAC' : 'N', 'AGC' : 'S',
	#						  # Lysine     # Arginine
	'ATA' : 'I', 'ACA' : 'T', 'AAA' : 'K', 'AGA' : 'R', 
	# Methionine
	'ATG' : 'M', 'ACG' : 'T', 'AAG' : 'K', 'AGG' : 'R', 
	# Valine     # Alanine    # Aspartic Acid # Glycine
	'GTT' : 'V', 'GCT' : 'A', 'GAT' : 'D', 'GGT' : 'G', 
	'GTC' : 'V', 'GCC' : 'A', 'GAC' : 'D', 'GGC' : 'G',
	#                         # Glutamic Acid
	'GTA' : 'V', 'GCA' : 'A', 'GAA' : 'E', 'GGA' : 'G',
	'GTG' : 'V', 'GCG' : 'A', 'GAG' : 'E', 'GGG' : 'G'	
}

def gene2prot(gene):
	prot = ''
	for i in range(0,len(gene),3):
		codon = gene[i:i+3]
		prot = prot + codon2aa[codon]
	return (prot)
	

def genbank2prot_seqs(dna,file_name):
	prot_seq = []
	# go over info in GenBank file and fill prot_seq list
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
			prot_seq.append(gene2prot(gene.upper()))
			in_cd = False

	file.close()
	return(prot_seq)

# list of amino acid names (one letter abbreviations)
aas = ['A','C','D','E','F','G','H','I','K','L','M','N','P','Q','R','S','T','V','W','Y']

# open file for writing
out_name = "2a_aa_counts.txt"
out = open(out_name,"w")
# write the column labels as a first line in this file
out.write("%-50s%4s" % ("# name_of_organism","GC%"))
for aa in aas:
	out.write("%5s" % (aa))
out.write("\n")

# get current working directory
cwd = os.getcwd()
# directory where the genomes are
dir_genomes = cwd + "\\"

# loop over all files in the directory containing the genomes
for file in os.listdir(dir_genomes):
    # process file only if ending is .txt
	if file.endswith(".gb"):
        
        # extract organism name from file name
		organism = file.split('.')[0]
		print (">>> " + organism)
        
        # create full name to GenBank file (CHANGE IF NECESSARY)
		file_name = dir_genomes + file
        # read entire dna sequence from GenBank file
		dna = genbank2dna(file_name)
		# obtain sequences of coded proteins from GenBank file
		prot_seq = genbank2prot_seqs(dna,file_name)

		# calculate GC content (in percent) and print
		genome_size = len(dna) 
		GC_perc = 100.0*(dna.count('c')+dna.count('g'))/genome_size 
		print ("GC content: %4.1f %%" %(GC_perc))
		# write organism name and GC% to file
		out.write("%-50s%4.1f" % (organism,GC_perc))

		# Count amino acids for all sequences in the list prot_seq
		# accumulate counts in dictionary aa_counts
		# initialize entries of dictionary to zero
		aa_counts = {}
		for aa in aas:
			aa_counts[aa] = 0
		# loop over all protein sequences and count
		for prot in prot_seq:
			for aa in aas:
				aa_counts[aa] += prot.count(aa)
		# Calculate percentage of amino acids and write to output file
		tot_aa = sum(aa_counts.values())
		for aa in aas:
			percent = 100.0*aa_counts[aa]/tot_aa;
			# write number to file 
			out.write("%5.1f" % (percent))

		out.write("\n")

out.close()
print ("results written to file " + out_name)

