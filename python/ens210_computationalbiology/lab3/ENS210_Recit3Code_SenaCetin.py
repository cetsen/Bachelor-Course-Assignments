import random

tot = 1765118 # Pyrococcus_abyssi

nt_count = { # Pyrococcus_abyssi
	'A' : 486862,
	'C' : 395973,
	'G' : 393280,
	'T' : 489003
}

di_count = { # Pyrococcus_abyssi
	'AA' : 150350,
	'AC' : 83821,
	'AG' : 131441,
	'AT' : 121250,
	'CA' : 92392,
	'CC' : 107937,
	'CG' : 62364,
	'CT' : 133279,
	'GA' : 124091,
	'GC' : 78210,
	'GG' : 107262,
	'GT' : 83717,
	'TA' : 120029,
	'TC' : 126005,
	'TG' : 92212,
	'TT' : 150757
}

di_count['CG'] += 1

bases = ['A','C','G','T']

nt_prob = {}
for b in bases:
	nt_prob[b] = 1.0*nt_count[b]/tot
print(nt_prob)

file_name = "dna1.txt"
file = open(file_name,"w")

#print the first nucleotide
dna = ''
rnd = random.random()
nxt = ''

for nt in range(1):
	rnd = random.random()
	nxt = ''
	
	for b in bases:
		if (nxt == ''):
			if (rnd < nt_prob[b]):
				nxt = b
			else:
				rnd -= nt_prob[b]

	dna += nxt
	currentbase = b

cond_prob = {}
for b1 in bases:
	for b2 in bases:
		dup = b1 + b2
		cond_prob[dup] = (1.0*di_count[dup]/tot)/(nt_prob[b1])


#choosing the rest of the dna sequence according to their conditional probabilities

for nt in range(tot-1):
	rnd = random.random()
	nxt = ''
	
	for b3 in bases:
		if (nxt == ''):
			if (rnd < cond_prob[currentbase+b3]):
				nxt = b3
				currentbase = b3
			else:
				rnd -= cond_prob[currentbase+b3]
		
	dna += nxt

	if (len(dna) == 70):
		file.write(dna + "\n")
		dna = ''

file.write(dna)
file.close()	



