n_process = int(input("Enter number of processes: "))

ArrivalT = []
BurstT = []
Priority = []

for i in range(n_process):
    Pri = int(input(f"Enter Priority of P{i}: "))
    Priority.append(Pri)
    AT = int(input(f"Enter Arrival Time of P{i}: "))
    ArrivalT.append(AT)
    BT = int(input(f"Enter Burst Time of P{i}: "))
    BurstT.append(BT)

process = list(range(n_process))
cut = 0
gantt = []
TAT = [0] * n_process
WT = [0] * n_process
BTC = BurstT.copy()

while process:
    av = [p for p in process if cut >= ArrivalT[p]]
    if av:
        p = max(av, key=lambda x: (Priority[x], ArrivalT[x]))
        cut += 1
        BTC[p] -= 1
        gantt.append(f"P{p}")
        if BTC[p] == 0:
            TAT[p] = cut - ArrivalT[p]
            WT[p] = TAT[p] - BurstT[p]
            process.remove(p)
    else:
        gantt.append("ideal")
        cut += 1

# Output Gantt chart
print("\nGantt Chart Sequence:")
print(" -> ".join(gantt))

# Output process table
print("\nProcess\tAT\tBT\tPri\tWT\tTAT")
for i in range(n_process):
    print(f"P{i}\t{ArrivalT[i]}\t{BurstT[i]}\t{Priority[i]}\t{WT[i]}\t{TAT[i]}")

# Average times
AWT = sum(WT) / n_process
ATT = sum(TAT) / n_process
print(f"\nAverage Waiting Time (AWT): {AWT:.2f}")
print(f"Average Turnaround Time (ATT): {ATT:.2f}")
