B = [100, 627, 50, 453, 211] 
P = [143, 101, 60, 43, 290]

# Step 1: Enumerate and sort ascending (smallest block first) → BEST FIT
inxB = list(enumerate(B))
sorted_blocks = sorted(inxB, key=lambda x: x[1])

# Step 2: Allocate using First Fit on sorted ascending blocks → BEST FIT
allocation = [-1] * len(P)
used = [False] * len(sorted_blocks)

for i in range(len(P)):
    for j in range(len(sorted_blocks)):
        if not used[j] and sorted_blocks[j][1] >= P[i]:
            allocation[i] = sorted_blocks[j][0]
            used[j] = True
            break

# Step 3: Output
for i in range(len(P)):
    if allocation[i] != -1:
        print(f"P{i}      Block {allocation[i] + 1}")
    else:
        print(f"P{i}     Not allocated")
