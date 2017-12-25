#Sena Necla Cetin 21120


def file2dna(file_name):
	file_object = open(file_name)
	# read the dna
	dna = ''
	for line in file_object:
		dna = dna + line.strip("\n")
	file_object.close()
	return(dna)


def revcomp(dna):

	rc = dna[::-1]
	rc = rc.upper()
	rc = rc.replace("A","t")
	rc = rc.replace("T","a")
	rc = rc.replace("G","c")
	rc = rc.replace("C","g")
	rc = rc.upper()
	return rc


def find_orf_lengths(dna,frame,cutoff):
	orfs_lengths = []
	i=abs(frame)-1
	dnalength = len(dna)

	while(i < dnalength):
		if(dna[i:i+3] == "ATG"):
			nt=3
			i+=3
			while(i < dnalength):
				if((dna[i:i+3]=="TAA") or (dna[i:i+3]=="TAG") or (dna[i:i+3]=="TGA")):
					if (nt >= cutoff):
						orfs_lengths.append(nt)
					i+=3
					break
				else:
					nt+=3
					i+=3
		else:
			i+=3

	return(orfs_lengths)
			

organism = 'Escherichia_coli'

file_name = "C://Users//Sena Cetin//Desktop//ENS210//" + organism + ".txt"
dna = file2dna(file_name)
# show beginning of dna
print("dna: " + dna[0:50])
tot = len(dna)
print ("organism: " + organism)
print ("genome length: " + str(tot))

cutoff = 700

frames = [1,2,3,-1,-2,-3]

orfs_tot = 0

for frame in frames:

	if (frame == -1):
		dna = revcomp(dna)
		print("reversed")

	lengths = find_orf_lengths(dna,frame,cutoff)
	n_orfs = len(lengths)
	orfs_tot += n_orfs
	print ("frame %2i: genes %5i, longest %5i" 
		%(frame,n_orfs,max(lengths)))

print("total genes: " + str(orfs_tot))

