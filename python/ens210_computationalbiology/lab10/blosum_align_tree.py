import numpy as np


def align(seq1,seq2,blosum,gap):
	len1 = len(seq1)
	len2 = len(seq2)
	# similarity matrix
	D = np.zeros((len1+1,len2+1),dtype=int)
	# the rows correspond to seq1
	for i in range(len1+1):
		D[i][0] = i*gap
	# the columns correspond to seq2
	for j in range(len2+1):
		D[0][j] = j*gap

	# compute the similarity score
	for i in range(1,len1+1):
		for j in range(1,len2+1):
			# progress along diagonal
			key = seq1[i-1] + seq2[j-1]
			a = D[i-1][j-1] + blosum[key]
			# seq1 is missing a character
			b = D[i-1][j] + gap
			# seq2 is missing a character
			c = D[i][j-1] + gap
			# find max
			D[i][j] = max([a,b,c])
	return D[len1][len2]


# Reward (match) and penalties (mismatch, gap) for SIMILARITY score
match = 2
mismatch = -1
gap = -2

# Read substitution matrix

#blos = 'blosum62'
blos = 'blosum80'
blosum = {}
file = open(blos+'.txt')
for line in file:
	if (line[0:1] == '#'):
		continue
	elif (line[3:4] == 'A'):
		aas = line.split()
	else:
		data = line.split()
		aa1 = data[0].lower()
		for i in range(len(aas)):
			aa2 = aas[i].lower()
			key = aa1 + aa2
			blosum[key] = int(data[i+1])

print(blosum)
file.close()

if (blos == 'blosum62'):
	gap = -4
elif (blos == 'blosum80'):
	gap = -6 # blosum80


file_name = 'euk_cox1_seqs.txt'
file = open(file_name)

# empty list for organism names
names = []
# empty list for cox1 protein sequences
cox1s = []

i = 0
for line in file:
	if (line[0:2] == '>>'):
		data = line.split()
		organism = data[1] + "_" + data[2]
		names.append(organism)
	else:
		cox1 = line.strip("\n")
		cox1s.append(cox1)

file.close()

print(cox1s)

# number of organisms (sequences)
N = len(cox1s)
print(N)

# construct similarity matrix M from alignment score
M = np.zeros((N,N))

for i in range(N):
	seq1 = str(cox1s[i])
	print(names[i])
	for j in range(i,N):
		seq2 = str(cox1s[j])
		dist = align(seq1,seq2,blosum,gap)
		M[i][j] = dist
		M[j][i] = dist

diag = -1000
# set diagonal entries equal to diag
np.fill_diagonal(M,diag)
print(M)
# holds the number of elements in each entry
# initailly all equal to 1
nums = np.ones(N).astype(int)

# pair things together
while (N>1):

	print(">>>combine " + str(N) + " organisms")

	# find position of a MAXIMUM
	imn,jmn = np.transpose(np.where(M == np.max(M)))[0]
	# calculate new distances as weighted average of rows imn and jmn of M
	scores = (nums[imn]*M[imn] + nums[jmn]*M[jmn])/(nums[imn]+nums[jmn])
	# make a column vector
	scores = scores.reshape(N,1)
	# calculate number of elements in new entry	
	new_num = nums[imn] + nums[jmn]
	# form the name of the new entry
	new_name = '(' + names[imn] + ',' + names[jmn] + ')'
	# append number of elements and name of new entry to the end
	nums = np.append(nums,new_num)
	names = np.append(names,new_name)
	# remove imn and jmn elements of names and nums
	nums = np.delete(nums, (imn,jmn))
	names = np.delete(names, (imn,jmn))
	# form new distance matrix:
	# stack scores as column to M
	M = np.hstack((M,scores))
	# append one zero to scores and convert to row vector
	scores = np.append(scores,diag).reshape(1,N+1)
	# now stack as row to M
	M = np.vstack((M,scores))
	# delete rows imn and jmn of M
	M = np.delete(M, (imn,jmn), axis=0)
	# delete columns imn and jmn of M
	M = np.delete(M, (imn,jmn), axis=1)
	
	# reduce N
	N -= 1


file_name = 'tree.tre'
file = open(file_name,"w")
print(names)
file.write(str(names))
file.close()
print("tree written to: " + file_name)

