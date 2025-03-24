# Gustav Carlsson (gusca083)
# Solve the equation Ax=b, if a single solution exists, otherwise output multiple or inconsistent
#  Time complexity O(n^3) (np.linalg.solve(A, b))

import numpy as np

def main():
    n = int(input())

    while n != 0:
        A = []  
        b = []

        for _ in range(n):
            row = list(map(float, input().split()))
            A.append(row)

        b = list(map(float, input().split()))

        A = np.array(A)
        b = np.array(b)

        augmented_matrix = np.column_stack((A, b))

        # If we have a singular matrix it either has 0 or infinite solutions
        # If the rank of A is not the same as the rank of A | b there are none
        # If the rank of A is less than n we have multiple solutions
        # Otherwise we can invert the matrix and solve it normally, ie:
        # Ax=b => x = A^-1 * b
        
        rank_A = np.linalg.matrix_rank(A) 
        rank_augmented = np.linalg.matrix_rank(augmented_matrix)
        
        if rank_A != rank_augmented: 
            print("inconsistent")
        elif rank_A < n:
            print("multiple")
        else:
            x = np.linalg.solve(A, b)
            print(" ".join(f"{xi:.3f}" for xi in x))

        n = int(input())

if __name__ == "__main__":
    main()
