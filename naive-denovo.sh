#!/bin/sh

package="naive-denovo"
version="0.0.1"
inputfile=""
outputfile="output.txt"

print_help () {
    echo "$package - de novo assembly for short-reads on PC version $version May 23 2017"
    echo " "
    # echo "usage: $package [-d dimension] [-w windowsize] <fastq-filename> [-o outputfilename]" 
    echo "usage: $package [-d dimension] <fastq-filename> [-o outputfilename]" 
    echo " "
    echo "Arguments:"
    echo "   -d             configure dimension of de Brujin graph (minimum overlap size of each k-mer to connect)"
    echo "                  default to read length - 1"
    # echo "-w             configure window size for splitting reads into "
    echo "   -o             configure name for the output file default to output.txt"
    echo "   -h or --help   Print Help (this message) and exit"
}

while test $# -gt 0; do
    case "$1" in
        -h|--help)
            print_help
            exit 0
            ;;
        -d)
            dimension="$2"
            re='^[1-9][0-9]*$'
            if ! [[ $dimension =~ $re ]]; then
                echo "error: dimesion size is not a valid number"
                exit 1
            fi
            shift
            shift
            ;;
        -o)
            outputfile="$2"
            shift
            shift
            ;;
        -*|--*)
            echo "invalid argument $1"
            print_help
            exit 1
            ;;
        *)
            if [ -f "$1" ]; then
                inputfile="$1"
            else
                echo "cannot find file $1."
                exit 1
            fi
            shift
            ;;
    esac
done

if [ -z $inputfile ]; then
    echo "error no input file found: please specify input file"
    echo " "
    print_help
    exit 1
fi

command -v g++ >/dev/null 2>&1 || { 
    echo >&2 "g++ is required but it is not installed. Aborting ..."
    exit 1; 
}

# requirements check passed
# start working

mkdir -p builds

# compiling 
for cpppath in ./scripts/*.cpp; do
    cppfile=${cpppath##*/}
    filename=${cppfile%%.cpp}
    echo "$"
    g++ -std=c++11 -O2 "./scripts/$cppfile" -o "./builds/$filename.out"
done
echo "done compiling file ..."

# run program
./builds/hash.out -d "$dimension" < "$inputfile" | 
sort | 
uniq |
tee hash_mapping.temp | 
./builds/euler_hash.out > components.temp

./builds/sequence_construct.out hash_mapping.temp components.temp > "$outputfile"

# remove first line from outputfile
tail -n +2 "$outputfile" > "$outputfile.temp"
mv "$outputfile.temp" "$outputfile"

# remove temp file; clean up files
rm hash_mapping.temp
rm components.temp

