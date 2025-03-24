import numpy as np

# Function to generate a random 3x3 matrix and corresponding vector
def generate_random_data(n):
    A = np.random.randint(0, 2, size=(n, n))  # Random nxn matrix with integers between 1 and 9
    b = np.random.randint(0, 3.0, size=n)       # Random nx1 vector with integers between 1 and 9
    return A, b

def generate_singular_matrix(n):
    # Start with a random row
    row = np.random.randint(1, 6, size=4)
    row2 = np.random.randint(1, 6, size=4)
    
    # Create linearly dependent rows by multiplying the first row
    A = np.array([row * (i+1) for i in range(3)])
    A = np.concatenate((A, [row2]), axis=0)  # row2 must be wrapped in []

    
    # Generate a dependent right-hand side vector b
    b = np.array([row.sum() * (i+1) for i in range(4)])
    
    # Augment the matrix
    # augmented_matrix = np.column_stack((A, b))
    
    return A, b


Aas = []
bbs = []
# for i in range(1, 1000):
#     A, b = generate_random_data(3)
#     Aas.append(A)
#     bbs.append(b)

for i in range(1, 100000):
    A, b = generate_singular_matrix(i)
    Aas.append(A)
    bbs.append(b)



# Open data.in to write matrix and vector data
with open('data.in', 'w') as f:
    # Write 5 matrices and vectors
    for idx, A in enumerate(Aas):
        
        # Write the dimensions of the matrix (3x3) and the vector (3x1)
        f.write(f"{A.shape[0]}\n")
        
        # Write matrix A
        for row in A:
            f.write(' '.join(map(str, row)) + '\n')
        
        # Write vector b
        f.write(' '.join(map(str, bbs[idx])) + '\n')
    f.write("0")

# Open answer.out to write the solutions
with open('answer.out', 'w') as f:
    for idx, A in enumerate(Aas):
        b = bbs[idx]
        # Solve the system of equations A * x = b
        try:
            x = np.linalg.solve(A, b)
            # Write the solution vector to answer.out
            f.write(' '.join(map(str, x)) + '\n')
        except np.linalg.LinAlgError:
            # In case the matrix A is singular (non-invertible)
            f.write("No solution\n")

print("5 random matrices, vectors, and their solutions have been written to files.")
