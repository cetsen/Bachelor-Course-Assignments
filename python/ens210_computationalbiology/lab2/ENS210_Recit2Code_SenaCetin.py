def file2dna(file_name):
	file_object = open(file_name)
	# read the dna
	dna = ''
	for line in file_object:
		dna = dna + line.strip("\n")
	file_object.close()
	return(dna)

# read dna from file
dna = file2dna("Thermococcus_gammatolerans.txt")

bases = ['A','C','G','T']

counts = {}
odds = {}

total_nucleo = dna.count('A') + dna.count('C') + dna.count('G') + dna.count('T')

def count_dinuc1(b1, b2):
	count = 0
	for i in range(len(dna)-1):
		duplet = b1 + b2
		if (dna[i:i+2] == duplet):
			count += 1
	return(count)

def base_probability(base):
	base_prob = (dna.count(base))/total_nucleo
	return(base_prob)

def duplet_probability(b1,b2):
	duplet_prob = ((count_duplets(b1,b2)) / (total_nucleo-1))
	return(duplet_prob)

def odds_ratio(b1,b2):
	odds = (duplet_probability(b1,b2)/(base_probability(b1)*base_probability(b2)))
	return(odds)

#fill in the counts dictionary by getting the duplet counts for each pair
for b1 in bases:
	for b2 in bases:
		duplet = b1 + b2
		counts[duplet] = count_duplets(b1,b2)

#print counts as a matrix
print("\ncounts:\n          A".rjust(10) + "C".rjust(10) + "G".rjust(10) + "T".rjust(10))
for b1 in bases:
	line = b1
	for b2 in bases:
		duplet = b1 + b2
		line = line + str(counts[duplet]).rjust(10)
	print(line)

#fill in the odds dictionary by getting duplet probabilities for each pair
for b1 in bases:
	for b2 in bases:
		duplet = b1 + b2
		odds[duplet] = round(odds_ratio(b1,b2),2)

#print odds ratios as a matrix
print("\nodds:\n      A".rjust(6) + "C".rjust(6) + "G".rjust(6) + "T".rjust(6))
for b1 in bases:
	line = b1
	for b2 in bases:
		duplet = b1 + b2
		line = line + str(odds[duplet]).rjust(6)
	print (line)