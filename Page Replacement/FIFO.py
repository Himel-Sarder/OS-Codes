def FIFO(page_refs, frame_size):
    frames = []  # current pages in memory
    page_faults = 0

    for page in page_refs:
        if page not in frames:
            # page fault occurs
            page_faults += 1
            if len(frames) < frame_size:
                frames.append(page)  # empty slot available
            else:
                frames.pop(0)  # remove first (oldest) page
                frames.append(page)  # add new page
        print(f"Page: {page} -> Frames: {frames}")

    print(f"Total Page Faults: {page_faults}")


# Example
pages = [7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 0, 3, 2, 1, 2, 0, 1, 7, 0, 1]
frame_size = 3

FIFO(pages, frame_size)
