n = int(input("Enter number of processes: "))
m = int(input("Enter number of resources: "))

print("\nEnter Allocation Matrix:")
alloc = [list(map(int, input(f"P{i}: ").split())) for i in range(n)]

print("\nEnter Max Matrix:")
max_need = [list(map(int, input(f"P{i}: ").split())) for i in range(n)]

avail = list(map(int, input("\nEnter Available Resources: ").split()))

# ✅ Need = Max - Alloc (No Loop Visible)
need = [[max_need[i][j] - alloc[i][j] for j in range(m)] for i in range(n)]

print("\nNeed Matrix:")
for i in range(n):
    print(f"P{i}: {need[i]}")

finish = [False]*n
safe = []
work = avail.copy()

# ✅ Banker's Logic
for _ in range(n):
    for i in range(n):
        if not finish[i] and all(need[i][j] <= work[j] for j in range(m)):
            for j in range(m):
                work[j] += alloc[i][j]
            safe.append(i)
            finish[i] = True

# ✅ Output Result
if len(safe) == n:
    print("\n✅ System is in SAFE STATE")
    print("Safe Sequence:", " -> ".join(f"P{i}" for i in safe))
else:
    print("\n❌ System is NOT in a safe state")
