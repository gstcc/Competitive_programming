def generate_worst_case(n, d, m):
    moles = []
    mole_count = 0
    
    # Generate moles for the worst-case scenario
    # Place moles at every possible (x, y) for each time from 1 to 11
    for t in range(1, 11):  # Time steps from 1 to 11
        for x in range(n):
            for y in range(n):
                if mole_count < m:
                    moles.append((x, y, t))
                    mole_count += 1
                if mole_count >= m:
                    break
            if mole_count >= m:
                break
        if mole_count >= m:
            break

    return moles

# Function to write the worst-case scenario to tmp.in
def write_worst_case_to_file(n, d, m):
    moles = generate_worst_case(n, d, m)

    # Open the file tmp.in in write mode
    with open('tmp.in', 'w') as file:
        # Write the test case parameters
        file.write(f"{n} {d} {m}\n")
        
        # Write each mole's position and time
        for mole in moles:
            file.write(f"{mole[0]} {mole[1]} {mole[2]}\n")
        file.write(f"0 0 0")

# Read input and generate the worst-case scenario
def main():
    # Read n, d, m
    n = 20
    d = 5
    m = 1000

    # Write the worst-case scenario to tmp.in
    write_worst_case_to_file(n, d, m)


if __name__ == "__main__":
    main()
