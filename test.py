class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

head = ListNode


start = head.val
direction = True if start < start.next else False

# True L -> S, False S -> L

while True:
    if head.val < head.next:
        head.val == head.next
    else:
        head.val == head.next