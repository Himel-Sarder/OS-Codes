def FCFS(requests, head):
    total_movement = 0
    current = head

    print("Path:", current, end="")

    for req in requests:
        total_movement += abs(req - current)
        print(f" -> {req}", end="")
        current = req

    print(f"\nTotal head movement: {total_movement}")


requests = [82, 170, 43, 140, 24, 16, 190]
head = 50

FCFS(requests, head)
