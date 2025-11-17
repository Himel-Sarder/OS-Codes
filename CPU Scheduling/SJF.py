n_p = int(input("Enter no of P : "))

AT = []
BT = []

for i in range(n_p):
    at = int(input(f"Enter AT for P{i} : "))
    AT.append(at)
    bt = int(input(f"Enter BT for P{i} : "))
    BT.append(bt)

process = list(range(n_p))
gantt = []
TAT = [0] * n_p
WT = [0] * n_p
current = 0

while process:
    available = [p for p in process if current >= AT[p]]
    if available:
        p = min(available, key=lambda x: (BT[x], AT[x]))
        current += BT[p]
        TAT[p] = current - AT[p]
        WT[p] = TAT[p] - BT[p]
        gantt.append(f"P{p}")
        process.remove(p)
    else:
        gantt.append("ideal")
        current += 1


print("Gantt chart ")
print(" -> " .join(gantt))

# Compute and print ATT and AWT
AWT = sum(WT) / n_p
ATT = sum(TAT) / n_p

print("\nProcess\tArrival\t\t\tBurst\t\tWaiting\t\tTurnaround")
for i in range(n_p):
    print(f"P{i}\t\t\t{AT[i]}\t\t\t{BT[i]}\t\t\t{WT[i]}\t\t\t{TAT[i]}")

print(f"\nAverage Waiting Time (AWT): {AWT:.2f}")
print(f"Average Turnaround Time (ATT): {ATT:.2f}")