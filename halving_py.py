from itertools import permutations

MOD = 998244353

# Function to verify if the current assignment satisfies the min/max conditions
def is_valid_assignment(C, R, B, N):
    for i in range(N):
        a1 = C[2 * i]
        a2 = C[2 * i + 1]
        if R[i] == 0:  # We expect min(a1, a2) == B[i]
            if min(a1, a2) != B[i]:
                return False
        else:  # We expect max(a1, a2) == B[i]
            if max(a1, a2) != B[i]:
                return False
    return True

# Backtracking function to assign missing values and check valid assignments
def backtrack(C, R, B, available, idx, N):
    if idx == len(C):  # Base case: all values assigned
        if is_valid_assignment(C, R, B, N):
            return 1
        return 0
    
    if C[idx] != -1:  # Skip already assigned values
        return backtrack(C, R, B, available, idx + 1, N)
    
    count = 0
    for num in available:
        new_C = C[:]  # Copy the current state
        new_C[idx] = num  # Assign the number
        new_available = available - {num}  # Remove this number from the available set
        count = (count + backtrack(new_C, R, B, new_available, idx + 1, N)) % MOD
    
    return count

# Main function to start the backtracking process
def solve(N, C, R, B):
    # Collect available numbers (those not used in C and B)
    used = set(x for x in C if x != -1) | set(B)
    available = set(range(1, 2 * N + 1)) - used
    
    # Start the backtracking process from the first index
    return backtrack(C, R, B, available, 0, N)

# Test with the given case:
N = 3
C = [-1, 2, 3, -1, -1, -1]
R = [0, 0, 1]
B = [2, 3, 6]

# Solve and see the output
output_backtrack = solve(N, C, R, B)
print(output_backtrack)
