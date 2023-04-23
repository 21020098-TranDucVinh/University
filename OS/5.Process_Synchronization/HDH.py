import os

n = int(input("Nhap so luong tien trinh con muon tao (1-10): "))

print("Tien trinh cha co PID:", os.getpid())

for i in range(n):
    pid = os.fork()
    if pid == 0:
        print("Tien trinh con co PID:", os.getpid(),
              "PID cua tien trinh cha:", os.getppid())
        exit()

pid, status = os.waitpid(-1, 0)
print("Tong so luong tien trinh:", n+1)
