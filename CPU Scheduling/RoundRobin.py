from collections import deque


# Input
n_process = int(input("Enter number of processes: "))
ArrivalT, BurstT = [], []

for i in range(n_process):
    ArrivalT.append(int(input(f"Enter Arrival Time of P{i}: ")))
    BurstT.append(int(input(f"Enter Burst Time of P{i}: ")))

TimeQuantum = int(input("Enter Time Quantum: "))

# Initialization
remaining = BurstT.copy()
WT = [0] * n_process
TAT = [0] * n_process
current_time = 0
gantt = []
Queue = deque()

while True:
        for i in range(n_process):
            if current_time >= ArrivalT[i] and remaining[i] > 0 and i not in Queue:
                Queue.append(i)

        if not Queue:
            if all(r == 0 for r in remaining):
                break
            else:
                gantt.append("idle")
                current_time += 1
                continue

        p = Queue.popleft()
        accessT = min(TimeQuantum, remaining[p])
        gantt.append(f"P{p}")
        current_time += accessT
        remaining[p] -= accessT

        for i in range(n_process):
            if current_time >= ArrivalT[i] and remaining[i] > 0 and i not in Queue and i != p:
                Queue.append(i)
        if remaining[p] > 0:
            Queue.append(p)

        else:
            TAT[p] = current_time - ArrivalT[p]
            WT[p] = TAT[p] - BurstT[p]

print("Gantt Chart:")
print(" -> ".join(gantt))