def SCAN(requests, head, disk_size):
    total = 0
    path = [head]

    left = [r for r in requests if r < head]
    right = [r for r in requests if r >= head]

    left.sort(reverse=True)   # later
    right.sort()              # go first

    # Move right first
    for r in right:
        total += abs(head - r)
        head = r
        path.append(r)

    # Go to boundary (like elevator reaches top floor)
    total += abs(head - (disk_size - 1))
    head = disk_size - 1
    path.append(head)

    # Now go left side (reverse serve)
    for r in left:
        total += abs(head - r)
        head = r
        path.append(r)

    print("Path:", " -> ".join(map(str, path)))
    print("Total Movement:", total)


requests = [82, 170, 43, 140, 24, 16, 190]
SCAN(requests, head=50, disk_size=200)
