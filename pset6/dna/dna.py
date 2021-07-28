import sys
import csv


# reading CSV files into memory.
def read_csv(file):
    with open(file, "r") as f:
        reader = csv.DictReader(f)
        return list(reader)


# reading TXT files into memory.
def read_txt(file):
    f = open(file, "r")
    DNA = f.read().strip()
    f.close()
    return DNA


# Find STR max repeat counts
def max_repeats(DNA, STR):
    indexes = []
    segments = []

    # Find all STR index in DNA sequence
    for i in range(0, len(DNA)-len(STR)):
        if DNA[i:i+len(STR)] == STR:
            indexes.append(i)

    if len(indexes) == 0:
        segments.append(0)
    else:
        counts = 1
        for i in range(len(indexes)-1):
            if indexes[i] + len(STR) == indexes[i+1]:
                counts += 1
            else:
                segments.append(counts)
                counts = 1
        segments.append(counts)

    return str(max(segments))


def main():
    # Check command-line argument
    if len(sys.argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        sys.exit(1)

    # reading CSV/TXT files into memory.
    database = read_csv(sys.argv[1])
    sequence = read_txt(sys.argv[2])

    # initial STR counts
    STR = {}
    for i in list(database[0].keys())[1:]:
        STR[i] = 0

    # Counts of each STR max repeat
    for i in list(STR.keys()):
        STR[i] = max_repeats(sequence, i)

    # Compare to each people's STR of database
    for people in database:
        STR['name'] = people["name"]

        if (people == STR):
            print(people["name"])
            break
    else:
        print("No match")

    del(STR['name'])

    sys.exit(0)


if __name__ == "__main__":
    main()