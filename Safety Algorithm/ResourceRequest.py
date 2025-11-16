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


work = avail.copy()

def banker(work, need):
    finish = [False] * n
    safe = []
    for _ in range(n):
        for i in range(n):
            if not finish[i] and all(need[i][j] <= work[j] for j in range(m)):
                for j in range(m):
                    work[j] += alloc[i][j]
                safe.append(i)
                finish[i] = True
    return safe

safe = banker(work, need)

# ✅ Output Result
if len(safe) == n:
    print("\n✅ System is in SAFE STATE")
    print("Safe Sequence:", " -> ".join(f"P{i}" for i in safe))
else:
    print("\n❌ System is NOT in a safe state")

response = input('Do you want to request resource? (y/n): ')
if response.lower() == 'y':
    p_req = int(input("Enter process number making request: "))
    req = list(map(int, input(f"Enter request for P{p_req}: ").split()))

    if all(req[i] <= need[p_req][i] for i in range(m)):
        if all(req[i] <= work[i] for i in range(m)):
            for j in range(m):
                work[j] -= req[j]
                alloc[p_req][j] += req[j]
                need[p_req][j] -= req[j]

            safe = banker(work, need)
            if len(safe) == n:
                print("\n✅ System is in SAFE STATE")
                print("Safe Sequence:", " -> ".join(f"P{i}" for i in safe))
            else:
                print("\n❌ System is NOT in a safe state")
        else:
            print("Process must wait, not enough available resources.")
    else:
        print("Error! Request exceeds its maximum claim.")
