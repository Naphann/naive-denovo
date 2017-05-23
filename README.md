# Outline for PC to assembly read (naive approach)

## limitations & constraints

- parse reads without concerning about read qualities

- have to be computable using normal PC (testing machine MBPr mid-2014)

- computation needs to be finished within appropriate time

## Outline for this Algorithm

1. hash the read the fastq file ignoring (id, quality) into format ```<read> <left:ull> <right:ull>``` (ull is ```unsigned long long```) and write it to a new file and let's called it ```hash-read```.

2. sort and unique the ```hash-read``` with only ```<left> and <right>``` and called it ```hash-read.uniq```.

3. construct de brujin graph using the ```hash-read.uniq``` file and do Hierholzer's algorithm (find Euler tour) and write it to file ```sequence-out```.

4. revert the hash ```<left> <right>``` back to its read

## To Build and use the script

- you need to have ```gcc``` in your ```PATH```.

- in the root directory of this project run
```
    > ./naive-denovo.sh -d <dimension> -f <fastq_file>
```
and the output file will be generated with the name ```results```

- or specify the output file by flag ```-o <filename>``` example
```
    > ./naive-denovo.sh -d 64 -f read.fastq -o output.txt
```

- or to view the help message
```
    > ./naive-denovo.sh --help
```

## usage

- input file must be fastq file

- output format will be multiple lines, 
each line represensts each connected components