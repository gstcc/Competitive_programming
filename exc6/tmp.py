import sys

def generate_worst_case(test_cases=1, n=100, max_clubs=10):
    """
    Generates the worst-case scenario for the input format.
    - `test_cases`: Number of test cases.
    - `n`: Number of residents per test case.
    - `max_clubs`: Maximum clubs each resident belongs to.
    """
    
    clubs = [f"Club{i}" for i in range(n)]  # Create n unique clubs
    parties = [f"Party{i%5}" for i in range(n)]  # Create at most 5 parties
    
    # Print the number of test cases
    print(test_cases)
    
    for _ in range(test_cases):
        print(n)  # Print number of residents
        
        for i in range(n):
            resident = f"Resident{i}"
            party = parties[i % len(parties)]  # Assign to a repeating party
            
            # Each resident joins up to `max_clubs` different clubs
            club_list = clubs[i:i+max_clubs] if i + max_clubs <= n else clubs[i:] + clubs[:(i+max_clubs)%n]
            
            # Print resident information
            print(resident, party, len(club_list), " ".join(club_list))

if __name__ == "__main__":
    # Example: Generate 1 worst-case scenario with 100 residents
    # print(12)
    # for i in range(1, 12):
    generate_worst_case(12, 1000, 110)
