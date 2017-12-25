import numpy as np
import re

def align(seq1,seq2,match,mismatch,gap):
	score = 0
	len1 = len(seq1)
	len2 = len(seq2)
	# similarity matrix
	D = np.zeros((len1+1,len2+1),dtype=int)

	for i in range(len1+1):
		D[i][0] = i*gap

	for j in range(len2+1):
		D[0][j] = j*gap
		
	# YOUR TURN (1 OF 2)
	# calculate similarity score between the two sequences
	for i in range(1,len1+1):
		for j in range(1,len2+1):
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

	score = D[len1][len2]
	return score


# Reward (match) and penalties (mismatch, gap) for SIMILARITY score
match = 2
mismatch = -1
gap = -2


file_name = '5S_rrna_sequences.txt'
file = open(file_name)

# empty list for organism names
names = []
# empty list for 5S rrna sequences
rrnas = []

i = 0
for line in file:
	if (line[0:2] == '>>'):
		# read organism name
		data = line.split()
		organism = data[1] + "_" + data[2]
		names.append(organism)
	else:
		# read 5S rRNA sequence
		rrna = re.findall('[acgt]+',line)
		rrnas.append(rrna)

file.close()

#print(rrnas)

# number of organisms (sequences)
N = len(rrnas)
print("number of 5S rRNA sequences: " + str(N))

# construct similarity matrix M from alignment scores
M = np.zeros((N,N))

for i in range(N):
	seq1 = str(rrnas[i])
	print("processing sequence: " + names[i])
	for j in range(i,N):
		seq2 = str(rrnas[j])
		# YOUR TURN (1 OF 2)
		# FILL BODY OF FUNCTION align GIVEN ABOVE
		dist = align(seq1,seq2,match,mismatch,gap)
		M[i][j] = dist
		M[j][i] = dist

diag = -1000
# set diagonal entries equal to diag
np.fill_diagonal(M,diag)
print("calculated similarity matrix:")
print(M)
# holds the number of elements in each entry
# initailly all equal to 1
nums = np.ones(N).astype(int)

# pair things together
while (N>1):
	# find position of MAXIMUM
	imx,jmx = np.transpose(np.where(M == np.max(M)))[0]
	
	print("%2i:%-15s %2i:%-15s" % (imx,names[imx],jmx,names[jmx]))

	# calculate new distances as weighted average of rows imx and jmx of M
	scores = (nums[imx]*M[imx] + nums[jmx]*M[jmx])/(nums[imx]+nums[jmx])
	# make a column vector
	scores = scores.reshape(N,1)

	# calculate number of elements in new entry	
	new_num = nums[imx] + nums[jmx]
	# form the name of the new entry
	new_name = '(' + names[imx] + ',' + names[jmx] + ')'
	# append number of elements and name of new entry to the end
	nums = np.append(nums,new_num)
	names = np.append(names,new_name)
	# remove imx and jmx elements of names and nums
	nums = np.delete(nums, (imx,jmx))
	names = np.delete(names, (imx,jmx))
	print(names)
	print(nums)

	# form new distance matrix:
	# stack scores as column to M
	M = np.hstack((M,scores))
	# append one zero to scores and convert to row vector
	scores = np.append(scores,0).reshape(1,N+1)
	# now stack as row to M
	M = np.vstack((M,scores))

	# delete rows imx and jmx of M
	M = np.delete(M, (imx,jmx), axis=0)
	# delete columxs imx and jmx of M
	M = np.delete(M, (imx,jmx), axis=1)
	print(M)
	
	# reduce N
	N -= 1


# write tree to file
file_name = 'tree.tre'
file = open(file_name,"w")
file.write(str(names))
file.close()
print("tree written to: " + file_name)

