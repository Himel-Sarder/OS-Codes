# Fixed Partition Memory Allocation (First Fit) - No Fragmentation Part

blocks = [100, 500, 200, 300, 600]   # হোটেলের রুম সাইজ (স্থায়ী, কমবে না)
processes = [212, 417, 112, 426]     # অতিথিদের লাগবে যতটুকু জায়গা

allocation = [-1] * len(processes)   # শুরুতে ধরে নিচ্ছি কেউ রুম পায়নি (Not allocated)
block_used = [False] * len(blocks)   # কোন রুম বুকড হয়েছে তা ট্র্যাক রাখার জন্য

# Booking শুরু (First Fit logic)
for i in range(len(processes)):           # একে একে প্রতিটা অতিথি আসবে
    for j in range(len(blocks)):          # প্রতিটা রুম চেক করবে, ফিট হবে কি না
        if not block_used[j] and blocks[j] >= processes[i]:  # রুম খালি এবং সাইজ যথেষ্ট?
            allocation[i] = j             # ওই গেস্টকে রুম নাম্বার লিখে রাখি
            block_used[j] = True          # রুমটাকে এখন বুকড হিসাবে মার্ক করি
            break                         # রুম পেয়ে গেছে, আর চেক করার দরকার নেই

# Booking Report Print করা হবে
print("Process\tSize\tBlock")
for i in range(len(processes)):
    if allocation[i] != -1:
        print(f"P{i+1}\t{processes[i]}\tB{allocation[i]+1}")
    else:
        print(f"P{i+1}\t{processes[i]}\tNot Allocated")
