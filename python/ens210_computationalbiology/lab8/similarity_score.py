import numpy as np

seq1 = 'tgcctggcggccgtagcgcggtggtcccacctgaccccatgccgaactcagaagtgaaacgccgtagcgccgatggtagtgtggggtctccccatgcgagagtagggaactgccaggcat'
seq2 = 'gccgacggtcataggacgggggaaacacccggactcattccgaacccggaagttaagccccgttccgtcccgcacagtactgtgttccgagagggcacgggaactgcgggaaccgtcggct'

seq1.upper()
seq2.upper()

print("seq1:" + seq1)
print("seq2:" + seq2)

len1 = len(seq1)
len2 = len(seq2)

# Reward (match) and penalties (mismatch, gap) for SIMILARITY score
match = 2
mismatch = -1
gap = -2

# similarity matrix
D = np.zeros((len1+1,len2+1),dtype=int)

# YOUR TURN 1 OF 2: CHANGE VALUES AT BOUNDARIES
# the rows correspond to seq1
for i in range(len1+1):
	D[i][0] = i*gap

# the columns correspond to seq2
for j in range(len2+1):
	D[0][j] = j*gap

# compute the edit distance
for i in range(1,len1+1):
	for j in range(1,len2+1):

		# YOUR TURN 2 OF 2: CHANGE VALUES OF REWARDS/PENALTIES
		# progress along diagonal
		if (seq1[i-1] == seq2[j-1]):
			# match
			a = D[i-1][j-1] + match
		else:
			# mismatch (substitution)
			a = D[i-1][j-1] + mismatch
		# seq1 is missing a character
		b = D[i-1][j] + gap
		# seq2 is missing a character
		c = D[i][j-1] + gap

		D[i][j] = max([a,b,c])

print(D)
print("similarity score: " + str(D[len1][len2]))

