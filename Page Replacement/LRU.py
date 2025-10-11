def LRU(page_refs, frame_size):
    frames = []
    page_faults = 0

    for page in page_refs:
        if page in frames:
            # Hit: move page to the end (most recently used)
            frames.remove(page)
            frames.append(page)
        else:
            # Page fault
            page_faults += 1
            if len(frames) < frame_size:
                frames.append(page)  # empty slot available
            else:
                frames.pop(0)  # remove least recently used
                frames.append(page)
        print(f"Page: {page} -> Frames: {frames}")

    print(f"Total Page Faults: {page_faults}")


# Example
pages = [7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2]
frame_size = 3

LRU(pages, frame_size)
