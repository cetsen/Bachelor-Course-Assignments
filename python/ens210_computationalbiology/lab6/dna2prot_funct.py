# This is essentially the exercise at the end of Ch.8: Dictionaries
# of the Python textbook (p4b: Python for Biologists)
# Read the solution of this exercise (p.184 - p.194 in p4b) 
import re

def codon2aa(codon):
    if re.match(r"TT[TC]",codon): return ("F")  
    elif re.match(r"TT[AG]",codon): return ("L") 
    elif re.match(r"AT[TCA]",codon) : return ("I")
    elif re.match(r"ATG",codon): return("M")
    elif re.match(r"GT[ATCG]",codon) : return("V")
    elif re.match(r"TC[ATGC]",codon): return ("S")
    elif re.match(r"CC[ATGC]",codon): return ("P")
    elif re.match(r"AC[ATGC]",codon): return ("T")
    elif re.match(r"GC[ACGT]", codon): return ("A") 
    elif re.match(r"TA[TC]",codon) : return ("Y")
    elif re.match(r"TA[AG]",codon) : return ("_")
    elif re.match(r"AA[AG]",codon): return ("K")
    elif re.match(r"GA[TC]",codon) : return ("D")
    elif re.match(r"GA[AG]",codon): return ("E")
    elif re.match(r"TG[CT]", codon): return ("C") 
    elif re.match(r"TGA",codon): return ("_")
    elif re.match(r"CT[ATGC]",codon): return ("L")
    elif re.match(r"TGG",codon): return ("W")
    elif re.match (r"CG[ATCG]",codon): return ("R")
    elif re.match(r"AG[TC]",codon): return ("S")
    elif re.match(r"AG[AG]",codon): return ("R")
    elif re.match(r"GG[ATGC]",codon): return ("G")
    elif re.match(r"CA[TC]",codon) : return ("H")
    elif re.match(r"CA[AG]",codon) : return ("Q")
    elif re.match(r"AA[TC]",codon) : return ("N")
    

dna = 'atgagcgagttcgatgcgccagacggcaacgacgcgttccagcgccagggcgacacgaccgaccgtgtctatgatgtcctcggcgtcaccacaccgacgacgtaccgtgcgattgcggaccgagcggactgttcggcgaatgccgcgaaaaaacaccttgaccggctcacggagatgggtgtcgtccggaaagacgaacagagccggccggcgcgctatgaacgggatgacggctatcttgagtggcaggaagcgagtcgcatcgcccgcgaactctcggttgaagagatgtag'
dna = dna.upper()

prot = ''
for i in range(0,len(dna),3):
	codon = dna[i:i+3]
	aa = codon2aa(codon)
	prot += aa 
print(prot)

