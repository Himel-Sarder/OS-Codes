def Optimal(page_refs, frame_size):
    frames = []
    page_faults = 0

    for i, page in enumerate(page_refs):
        if page not in frames:
            page_faults += 1
            if len(frames) < frame_size:
                frames.append(page)
            else:
                # Find page to replace
                future_uses = []
                for f in frames:
                    if f in page_refs[i+1:]:
                        future_uses.append(page_refs[i+1:].index(f))
                    else:
                        future_uses.append(float('inf'))  # not used again
                # Replace page with farthest future use
                idx = future_uses.index(max(future_uses))
                frames[idx] = page
        print(f"Page: {page} -> Frames: {frames}")

    print(f"Total Page Faults: {page_faults}")


# Example
pages = [7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2]
frame_size = 3

Optimal(pages, frame_size)
