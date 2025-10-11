def FCFS(requests, head):
    total_movement = 0
    current = head

    print("Order of service:")

    for req in requests:
        print(f"{current} -> {req}")
        total_movement += abs(req - current) 
        current = req

    print(f"\nTotal head movement: {total_movement}")

requests = [82, 170, 43, 140, 24, 16, 190]
head = 50

FCFS(requests, head)
