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

# Main Round Robin loop
while True:
    # Add all newly arrived processes to the queue
    for i in range(n_process):
        if ArrivalT[i] <= current_time and remaining[i] > 0 and i not in Queue:
            Queue.append(i)

    if not Queue:
        # If all processes are done, break
        if all(r == 0 for r in remaining):
            break
        # Otherwise, CPU idle until next arrival
        gantt.append("Idle")
        current_time += 1
        continue

    # Dequeue and execute
    p = Queue.popleft()
    exec_time = min(TimeQuantum, remaining[p])
    gantt.append(f"P{p}")
    current_time += exec_time
    remaining[p] -= exec_time

    # Add processes that arrived during this execution
    for i in range(n_process):
        if ArrivalT[i] <= current_time and remaining[i] > 0 and i not in Queue and i != p:
            Queue.append(i)

    # If process still needs time, re-queue
    if remaining[p] > 0:
        Queue.append(p)
    else:
        TAT[p] = current_time - ArrivalT[p]
        WT[p] = TAT[p] - BurstT[p]

# Output
print("\nGantt Chart Sequence:")
print(" -> ".join(gantt))

print("\nProcess\tArrival\tBurst\tWaiting\tTurnaround")
for i in range(n_process):
    print(f"P{i}\t{ArrivalT[i]}\t{BurstT[i]}\t{WT[i]}\t{TAT[i]}")

AWT = sum(WT) / n_process
ATT = sum(TAT) / n_process
print(f"\nAverage Waiting Time (AWT): {AWT:.2f}")
print(f"Average Turnaround Time (ATT): {ATT:.2f}")
