n = int(input("Enter no of process : "))

AT = []
BT = []

WT = [0] * n
TAT = [0] * n

gantt = []
current = 0

for i in range(n):
    at = int(input(f"Enter arrival time for P{i} : "))
    AT.append(at)
    bt = int(input(f"Enter Burst time for P{i} : "))
    BT.append(bt)

remaining = list(range(n))

while remaining:
    # Available process selection
    available = [p for p in remaining if AT[p] <= current]
    
    if available:
        # Pick the one with shortest burst
        p = min(available, key=lambda x: BT[x])
        gantt.append(f"P{p}")
        current += BT[p]
        TAT[p] = current - AT[p]
        WT[p] = TAT[p] - BT[p]
        remaining.remove(p)
    else:
        gantt.append("Idle")
        current += 1

# Output Gantt chart
print("Gantt chart:")
print(" -> ".join(gantt))

# Compute average times
AWT = sum(WT) / n
ATT = sum(TAT) / n

# Process table
print("\nProcess\tArrival\tBurst\tWaiting\tTurnaround")
for i in range(n):
    print(f"P{i}\t{AT[i]}\t{BT[i]}\t{WT[i]}\t{TAT[i]}")

print(f"\nAverage Waiting Time (AWT): {AWT:.2f}")
print(f"Average Turnaround Time (ATT): {ATT:.2f}")
