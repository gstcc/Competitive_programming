def compare_files(file1, file2, tolerance=0.001):
    # Open both files
    with open(file1, 'r') as f1, open(file2, 'r') as f2:
        # Read both files line by line
        lines1 = f1.readlines()
        lines2 = f2.readlines()

        # Check if number of lines is the same
        if len(lines1) != len(lines2):
            print("Files have different number of lines.")
            return False

        # Compare each line
        for i in range(len(lines1)):
            # Split the lines into numbers
            nums1 = [x if x=="inconsistent" or x=="?" else float(x) for x in lines1[i].split()]
            nums2 = [x if x=="inconsistent" or x=="?" else float(x) for x in lines1[i].split()]

            # Check if the number of numbers per row is the same
            if len(nums1) != len(nums2):
                print(f"Line {i+1} has different number of numbers.")
                return False

            # Compare corresponding numbers with the given tolerance
            for j in range(len(nums1)):
                if not isinstance(nums1[j], str) and not isinstance(nums2[j], str) and abs(nums1[j] - nums2[j]) > tolerance:
                    print(f"Difference at line {i+1}, position {j+1}: {nums1[j]} vs {nums2[j]}")
                    return False
                elif isinstance(nums1[j], str) and not isinstance(nums2[j], str):
                    print(f"Difference at line {i+1}, position {j+1}: {nums1[j]} vs {nums2[j]}")
                    return False
                elif not isinstance(nums1[j], str) and isinstance(nums2[j], str):
                    print(f"Difference at line {i+1}, position {j+1}: {nums1[j]} vs {nums2[j]}")
                    return False
                elif isinstance(nums1[j], str) and isinstance(nums2[j], str) and nums1[j] != nums2[j]:
                    print(f"Difference at line {i+1}, position {j+1}: {nums1[j]} vs {nums2[j]}")
                    return False

        print("Files are identical within the given tolerance.")
        return True


if __name__ == "__main__":
    # Define the file names
    file1 = "answer.out"
    file2 = "output.out"

    # Call the compare function
    compare_files(file1, file2)
