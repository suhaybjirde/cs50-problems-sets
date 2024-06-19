from csv import DictReader, reader
import sys


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        print("USAGE: dna.py databases/large.csv sequences/12.txt ")
        sys.exit()
    
    # TODO: Read database file into a variable & DNA sequence file into a variable

    dna_database = []
    dna_sequence = ""

    try:
        with open(sys.argv[1]) as peoples_dna, open(sys.argv[2]) as dna_sequences:
            reader = DictReader(peoples_dna)
            for row in reader:
                dna_database.append(row)
            dna_sequence = dna_sequences.read()
    except FileNotFoundError as e:
        print(f"couldn't open {e.filename} No such file or directory found")
        sys.exit()

    # TODO: Find longest match of each STR in DNA sequence
    strs = [x for x in dna_database[0] if x != "name"]
    strs_count = {}

    for str in strs:
        strs_count[str] = longest_match(dna_sequence, str)

    # TODO: Check database for matching profiles
    for person in dna_database:
        check = {key: int(value) for key, value in person.items() if key != "name"}
        if check == strs_count:
            print(person['name'])
            break
    else:
        print("No Matched")
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
