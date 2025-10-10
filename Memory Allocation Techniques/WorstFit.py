B = [100, 627, 50, 453, 211]
P = [143, 101, 60, 43, 290]

# Step 1: Enumerate and sort descending (largest block first)
inxB = list(enumerate(B))          # [(0,100), (1,627), (2,50), (3,453), (4,211)]
sorted_blocks = sorted(inxB, key=lambda x: x[1], reverse=True)

# Step 2: First Fit allocation on descending blocks → automatically Worst Fit
allocation = [-1] * len(P)
used = [False] * len(sorted_blocks)

for i in range(len(P)):
    for j in range(len(sorted_blocks)):
        if not used[j] and sorted_blocks[j][1] >= P[i]:
            # Store the ORIGINAL block index, not the sorted index
            allocation[i] = sorted_blocks[j][0]
            used[j] = True
            break

# Step 3: Print results with original block indices
for i in range(len(P)):
    if allocation[i] != -1:
        print(f"P{i}      Block {allocation[i] + 1}")
    else:
        print(f"P{i}     Not allocated")
