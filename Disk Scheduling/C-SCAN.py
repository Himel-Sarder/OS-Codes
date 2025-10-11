def C_SCAN(requests, head, disk_size):
    total = 0
    path = [head]

    left = [r for r in requests if r < head]
    right = [r for r in requests if r >= head]

    left.sort()
    right.sort()

    # Move right side first
    for r in right:
        total += abs(head - r)
        head = r
        path.append(r)

    # Go to top boundary (disk_size-1)
    total += abs(head - (disk_size - 1))
    head = disk_size - 1
    path.append(head)

    # Jump to start (0) without counting movement again if you want exact C-SCAN
    total += abs(head - 0)
    head = 0
    path.append(head)

    # Serve left side
    for r in left:
        total += abs(head - r)
        head = r
        path.append(r)

    print("Path:", " -> ".join(map(str, path)))
    print("Total Movement:", total)


requests = [82, 170, 43, 140, 24, 16, 190]
C_SCAN(requests, head=50, disk_size=200)
