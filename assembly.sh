./overlap $1 output_overlaps.txt 7
python script.py -f output_overlaps.txt -o $2 -pm 0.1 -size 500
