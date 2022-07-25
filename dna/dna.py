import csv
import sys


def main():
    database = []
    count = []

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
    # TODO: Read database file into a variable
    with open(sys.argv[1], "r") as file:
        reader = csv.DictReader(file)
        for row in reader:
            database.append(row)
    # TODO: Read DNA sequence file into a variable
    with open(sys.argv[2], "r") as file:
        sequence = file.read()
    # TODO: Find longest match of each STR in DNA sequence
    j = 1
    for i in database:
        match = longest_match(sequence, list(i)[j])
        name = list(i)[j]
        STR = {name: match}
        count.append(STR)
        j += 1
        # is used to make sure that an index error does not occur
        if j >= len(database[0]):
            break

    # TODO: Check database for matching profiles
    sequences = 0
    counter = 0
    with open(sys.argv[1], "r") as file:
        reader = csv.DictReader(file)
        for row in reader:
            for n in range(1, len(database[0])):
                match = longest_match(sequence, list(i)[n])
                name = list(row)[n]
                STR_length = int(row[name])
                if(STR_length == match):
                    sequences += 1
                # if every number STR_length is the same as match, it is the same DNA strand and a person's name is printed
                if(sequences == len(database[0])-1):
                    print(database[counter]["name"])
                    return
            counter += 1
            sequences = 0
        print("No match")
        return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
