def SSTF(requests, head):
    total = 0
    current = head
    reqs = requests.copy()

    print("Path:", current, end="")

    while reqs:
        next_req = min(reqs, key=lambda x: abs(x - current))
        total += abs(next_req - current)
        current = next_req
        print(f" -> {current}", end="")
        reqs.remove(next_req)

    print(f"\nTotal movement = {total}")


requests = [82, 170, 43, 140, 24, 16, 190]
head = 50

SSTF(requests, head)
