import re
import os

cwd = os.getcwd()
#print(cwd)
files = os.listdir(cwd)
#print(files[0].split('.')[0])
out_name = "prokaryotes40.txt"
out = open(out_name,"w")

organisms = ['Fusobacterium_nucleatum',
'Ehrlichia_ruminantium',
'Candidatus_Pelagibacter_ubique',
'Candidatus_Nitrosomarinus_catalina',
'Lactobacillus_salivarius',
'Methanococcus_maripaludis',
'Trichodesmium_erythraeum',
'Bacillus_cereus',
'Sulfolobus_solfataricus',
'Prochlorococcus_marinus',
'Treponema_denticola',
'Methanosarcina_barkeri',
'Thermoplasma_volcanium',
'Chlamydophila_pneumoniae',
'C_Methanomassiliicoccus_intestinalis',
'Methanosarcina_acetivorans',
'Bacteroides_thetaiotaomicron',
'Aquifex_aeolicus',
'Pyrococcus_abyssi',
'Thermotoga_maritima',
'Haloquadratum_walsbyi',
'Archaeoglobus_fulgidus',
'Candidatus_Korarchaeum_cryptofilum',
'Methanothermobacter_thermautotrophicus',
'Escherichia_coli',
'Pyrococcus_yayanosii',
'Thermococcus_gammatolerans',
'Hyperthermus_butylicus',
'Rhodopirellula_baltica',
'Ignicoccus_hospitalis',
'Thermofilum_pendens',
'Pseudomonas_fluorescens',
'Methanopyrus_kandleri',
'Gloeobacter_violaceus',
'Halorhabdus_utahensis',
'Bradyrhizobium_japonicum',
'Deinococcus_geothermalis',
'Halobacterium_salinarum',
'Sorangium_cellulosum',
'Anaeromyxobacter_dehalogenans']

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
 
out.write("# name_of_organism                      Mb    GC%   Prot  avg   ATG%  oth%  TAA%  TGA%  TAG%\n")

for i in range(0, 40):  
    organism = organisms[i]
    file_name = "C://Users//Sena Cetin//Desktop//ENS210//genbank//" + organism + ".gb"
    dna = genbank2dna(file_name)
    file = open(file_name)
    in_cd = False
    
    # a list that stores sequences of all protein genes
    gene_seq = []
    # a list to store the length (nt) of each protein gene
    gene_length = []
    
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

            length = len(gene)

            # take reverse complement of gene sequence if necessary
            if re.search('complement',line):
                gene = revcomp(gene)

        # if protein, collect gene, sense and length in a list
        if (in_cd and line[21:29] == '/protein'):
            gene_seq.append(gene)
            gene_length.append(length)
            in_cd = False

    out.write(organism)
    l = len(organism)
    while l!=40:
        out.write(" ")
        l+=1

    # obtain number of nucleotides in genome and print to screen
    genome_size = len(dna) 
    out.write("%4.2f "%(0.000001*genome_size))
    if (0.000001*genome_size < 10):
        out.write(" ")

    # calculate GC content (in percent) and print
    GC_perc = 100.0*(dna.count('c')+dna.count('g'))/genome_size
    out.write("%4.1f  "%(GC_perc))

    # obtain number of proteins in genome and print
    n_genes = len(gene_seq) 
    out.write ("%4i  "% (n_genes))

    # calculate average length (in nucleotides) of a protein gene
    avg_length = sum(gene_length)/n_genes 
    out.write("%3i  "%(round(avg_length,0)))
    if(avg_length < 1000):
        out.write(" ")
    
    # YOUR TURN (PART 1 OF 2)
    # count START codons
    n_start=[0,0] # numbers of ATG and other start codons
    for i in range(len(gene_seq)):
        gene = gene_seq[i]
        if (gene[0:3] == 'atg'):
            n_start[0] += 1
        else:
            n_start[1] += 1
    start_tot = n_start[0] + n_start[1]
   
    out.write("%4.1f  "%(100.0*n_start[0]/start_tot))
    out.write("%4.1f  "%(100.0*n_start[1]/start_tot))

    # YOUR TURN (PART 2 OF 2)
    # count STOP codons
    stops = ['taa','tga','tag','other']
    n_stop = [0,0,0,0]
    for i in range(len(gene_seq)):
        gene = gene_seq[i]
        if (gene[-3:] == stops[0]):
            n_stop[0] += 1
        elif (gene[-3:] == stops[1]):
            n_stop[1] += 1
        elif (gene[-3:] == stops[2]):
            n_stop[2] += 1
        else:
            n_stop[3] += 1
    stop_tot = n_stop[0] + n_stop[1] + n_stop[2]
    out.write("%4.1f  "%(100.0*n_stop[0]/stop_tot))
    out.write("%4.1f  "%(100.0*n_stop[1]/stop_tot))
    out.write("%4.1f  "%(100.0*n_stop[2]/stop_tot))
    out.write("\n")
    file.close()
    i+=1
     
out.close()

